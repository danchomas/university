#define FUSE_USE_VERSION 31
#define _GNU_SOURCE

#include <fuse3/fuse.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>

typedef struct {
    char *content;
    size_t size;
    time_t ctime;
    time_t mtime;
    int write_count;
    pid_t creator_pid;
} file_data;

typedef struct node {
    char *name;
    file_data data;
    struct node *next;
} node;

static node *files = NULL;

static node* find_file(const char *path) {
    if (path[0] != '/' || path[1] == '\0') return NULL;
    const char *name = path + 1;
    for (node *n = files; n; n = n->next)
        if (strcmp(n->name, name) == 0)
            return n;
    return NULL;
}

static node* create_file(const char *path) {
    node *n = calloc(1, sizeof(node));
    if (!n) return NULL;
    n->name = strdup(path + 1);
    if (!n->name) { free(n); return NULL; }
    n->data.content = strdup("");
    n->data.ctime = n->data.mtime = time(NULL);
    n->data.creator_pid = getpid();
    n->data.write_count = 0;
    n->data.size = 0;
    n->next = files;
    files = n;
    return n;
}

static int fs_getattr(const char *path, struct stat *st, struct fuse_file_info *fi) {
    (void)fi;
    memset(st, 0, sizeof(*st));

    if (strcmp(path, "/") == 0) {
        st->st_mode = S_IFDIR | 0755;
        st->st_nlink = 2;
        return 0;
    }

    const char *name = path + 1;
    size_t len = strlen(name);

    if (len > 5 && strcmp(name + len - 5, ".meta") == 0) {
        char realname[256];
        snprintf(realname, sizeof(realname), "/%.*s", (int)(len - 5), name);
        if (find_file(realname)) {
            st->st_mode = S_IFREG | 0444;
            st->st_nlink = 1;
            st->st_size = 1024;
            return 0;
        }
        return -ENOENT;
    }

    node *n = find_file(path);
    if (!n) return -ENOENT;

    st->st_mode = S_IFREG | 0644;
    st->st_nlink = 1;
    st->st_size = n->data.size;
    st->st_ctime = n->data.ctime;
    st->st_mtime = n->data.mtime;
    return 0;
}

static int fs_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                      off_t offset, struct fuse_file_info *fi, enum fuse_readdir_flags flags) {
    (void)offset; (void)fi; (void)flags;
    if (strcmp(path, "/") != 0) return -ENOENT;

    filler(buf, ".", NULL, 0, 0);
    filler(buf, "..", NULL, 0, 0);

    for (node *n = files; n; n = n->next) {
        filler(buf, n->name, NULL, 0, 0);
        char meta[512];
        snprintf(meta, sizeof(meta), "%s.meta", n->name);
        filler(buf, meta, NULL, 0, 0);
    }
    return 0;
}

static int fs_open(const char *path, struct fuse_file_info *fi) {
    (void)fi;
    if (strstr(path, ".meta")) {
        char realpath[256];
        snprintf(realpath, sizeof(realpath), "%.*s", (int)strlen(path)-5, path);
        return find_file(realpath) ? 0 : -ENOENT;
    }
    return find_file(path) ? 0 : -ENOENT;
}

static int fs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    (void)fi;

    if (strstr(path, ".meta")) {
        char realpath[256];
        snprintf(realpath, sizeof(realpath), "%.*s", (int)strlen(path)-5, path);
        node *n = find_file(realpath);
        if (!n) return -ENOENT;

        char meta[1024];
        snprintf(meta, sizeof(meta),
            "Файл: %s\n"
            "Создан: %s"
            "Изменён: %s"
            "Записей: %d\n"
            "Размер: %zu байт\n"
            "PID создателя: %d\n",
            n->name,
            ctime(&n->data.ctime),
            ctime(&n->data.mtime),
            n->data.write_count,
            n->data.size,
            (int)n->data.creator_pid);

        size_t len = strlen(meta);
        if (offset >= (off_t)len) return 0;
        if (offset + size > len) size = len - offset;
        memcpy(buf, meta + offset, size);
        return size;
    }

    node *n = find_file(path);
    if (!n || offset >= (off_t)n->data.size) return 0;
    if (offset + size > n->data.size) size = n->data.size - offset;
    memcpy(buf, n->data.content + offset, size);
    return size;
}

static int fs_write(const char *path, const char *buf, size_t size,
                    off_t offset, struct fuse_file_info *fi) {
    (void)fi;
    if (strstr(path, ".meta")) return -EACCES;

    node *n = find_file(path);
    if (!n) n = create_file(path);

    if (offset + size > n->data.size) {
        char *new = realloc(n->data.content, offset + size + 1);
        if (!new) return -ENOMEM;
        n->data.content = new;
        if (offset > (off_t)n->data.size)
            memset(n->data.content + n->data.size, 0, offset - n->data.size);
        n->data.size = offset + size;
    }
    memcpy(n->data.content + offset, buf, size);
    n->data.content[n->data.size] = '\0';
    n->data.mtime = time(NULL);
    n->data.write_count++;
    return size;
}

static int fs_create(const char *path, mode_t mode, struct fuse_file_info *fi) {
    (void)mode; (void)fi;
    if (find_file(path)) return -EEXIST;
    return create_file(path) ? 0 : -ENOMEM;
}

static int fs_unlink(const char *path) {
    if (strstr(path, ".meta")) return -EACCES;
    node **p = &files;
    while (*p) {
        if (strcmp((*p)->name, path + 1) == 0) {
            node *tmp = *p;
            *p = tmp->next;
            free(tmp->name);
            free(tmp->data.content);
            free(tmp);
            return 0;
        }
        p = &(*p)->next;
    }
    return -ENOENT;
}

static const struct fuse_operations ops = {
    .getattr   = fs_getattr,
    .readdir   = fs_readdir,
    .open      = fs_open,
    .read      = fs_read,
    .write     = fs_write,
    .create    = fs_create,
    .unlink    = fs_unlink,
};

int main(int argc, char *argv[]) {
    return fuse_main(argc, argv, &ops, NULL);
}
