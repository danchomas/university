#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <map>
#include <algorithm>
#include <sstream>

using namespace std;

class Comment {
    string author;
    time_t date;
    string text;

public:
    Comment(const string& author, const string& text)
        : author(author), text(text), date(time(nullptr)) {}

    void print() const {
        char time_str[100];
        strftime(time_str, sizeof(time_str), "%H:%M %d/%m/%Y", localtime(&date));
        cout << author << " [" << time_str << "]: " << text << "\n";
    }
};

class Post {
    string author;
    string title;
    string content;
    time_t date;
    vector<Comment> comments;

public:
    Post(const string& author, const string& title, const string& content)
        : author(author), title(title), content(content), date(time(nullptr)) {}

    void add_comment(const Comment& comment) {
        comments.push_back(comment);
    }

    void print() const {
        char time_str[100];
        strftime(time_str, sizeof(time_str), "%H:%M %d/%m/%Y", localtime(&date));

        cout << "\n════════ " << title << " ════════\n"
             << "Автор: " << author << "\n"
             << "Дата: " << time_str << "\n\n"
             << content << "\n\n"
             << "Комментарии (" << comments.size() << "):\n";

        for (const auto& c : comments) c.print();
    }

    string get_author() const { return author; }
    string get_title() const { return title; }
    time_t get_date() const { return date; }
};

class Profile {
    string bio;
    vector<string> interests;

public:
    Profile(const string& bio = "", const vector<string>& interests = {})
        : bio(bio), interests(interests) {}

    void print() const {
        cout << "\nО пользователе: " << bio << "\nИнтересы: ";

        if (interests.empty()) cout << "не указаны";
        else for (size_t i = 0; i < interests.size(); ++i)
            cout << interests[i] << (i != interests.size()-1 ? ", " : "");
        cout << "\n";
    }
};

class Blog {
    string owner;
    vector<Post> posts;

public:
    Blog(const string& owner) : owner(owner) {}

    void add_post(const Post& post) {
        posts.push_back(post);
        sort(posts.begin(), posts.end(),
            [](const Post& a, const Post& b) { return a.get_date() > b.get_date(); });
    }

    void print_posts() const {
        cout << "\n═════════ Посты пользователя " << owner << " ═════════\n";
        for (const auto& p : posts) p.print();
    }

    vector<Post>& get_posts() { return posts; }
    string get_owner() const { return owner; }
};

class User {
    string username;
    string password;
    Profile profile;
    Blog blog;

public:
    User(const string& username, const string& password, const Profile& profile)
        : username(username), password(password), profile(profile), blog(username) {}

    bool check_password(const string& pwd) const { return password == pwd; }

    Blog& get_blog() { return blog; }
    Profile& get_profile() { return profile; }
    string get_username() const { return username; }

    void print_info() const {
        cout << "\n═════════ Профиль " << username << " ═════════\n";
        profile.print();
    }
};

class IUserRepository {
public:
    virtual void add_user(User* user) = 0;
    virtual User* find_user(const string& username) = 0;
    virtual vector<User*> get_all_users() = 0;
    virtual ~IUserRepository() = default;
};

class UserRepository : public IUserRepository {
    map<string, User*> users;

public:
    ~UserRepository() {
        for (auto& pair : users) delete pair.second;
    }

    void add_user(User* user) override {
        users[user->get_username()] = user;
    }

    User* find_user(const string& username) override {
        auto it = users.find(username);
        return it != users.end() ? it->second : nullptr;
    }

    vector<User*> get_all_users() override {
        vector<User*> result;
        for (const auto& pair : users) result.push_back(pair.second);
        return result;
    }
};

class AuthService {
    IUserRepository* user_repo;

public:
    AuthService(IUserRepository* repo) : user_repo(repo) {}

    User* authenticate(const string& username, const string& password) {
        User* user = user_repo->find_user(username);
        return user && user->check_password(password) ? user : nullptr;
    }
};

class BlogService {
    IUserRepository* user_repo;

    pair<string, int> find_post(int global_index) {
        int counter = 1;
        for (User* user : user_repo->get_all_users()) {
            auto& posts = user->get_blog().get_posts();
            for (size_t i = 0; i < posts.size(); ++i) {
                if (counter++ == global_index) return {user->get_username(), i};
            }
        }
        return {"", -1};
    }

public:
    BlogService(IUserRepository* repo) : user_repo(repo) {}

    bool create_post(const string& username, const string& title, const string& content) {
        if (User* user = user_repo->find_user(username)) {
            user->get_blog().add_post(Post(username, title, content));
            return true;
        }
        return false;
    }

    void print_all_posts() {
        cout << "\n═════════ Все посты в системе ═════════\n";
        for (User* user : user_repo->get_all_users()) {
            auto& posts = user->get_blog().get_posts();
            if (!posts.empty()) { // Check if the user has any posts
                cout << "\n═════════ Посты пользователя " << user->get_username() << " ═════════\n";
                for (const auto& post : posts) {
                    post.print();
                }
            }
        }
    }

    bool add_comment(const string& commenter, int post_index, const string& text) {
        auto [author, index] = find_post(post_index);
        if (author.empty()) return false;

        if (User* user = user_repo->find_user(author)) {
            auto& posts = user->get_blog().get_posts();
            if (index < posts.size()) {
                posts[index].add_comment(Comment(commenter, text));
                return true;
            }
        }
        return false;
    }

    void print_post_numbers() {
        int counter = 1;
        for (User* user : user_repo->get_all_users()) {
            for (const auto& post : user->get_blog().get_posts()) {
                cout << counter++ << ". " << post.get_title()
                     << " (" << user->get_username() << ")\n";
            }
        }
    }
};

class UserFactory {
    IUserRepository* repo;

public:
    explicit UserFactory(IUserRepository* repo) : repo(repo) {}

    User* create_user(
        const string& username,
        const string& password,
        const string& bio,
        const vector<string>& interests
    ) {
        User* user = new User(username, password, Profile(bio, interests));
        repo->add_user(user);
        return user;
    }
};

class BlogConsole {
    UserRepository* user_repo = new UserRepository();
    AuthService* auth_service = new AuthService(user_repo);
    BlogService* blog_service = new BlogService(user_repo);
    User* current_user = nullptr;

public: // Make the destructor public
    ~BlogConsole() {
        delete blog_service;
        delete auth_service;
        delete user_repo;
    }

    void print_main_menu() {
        cout << "\n═════════ Блог-платформа ═════════\n"
                "1. Регистрация\n"
                "2. Вход\n"
                "3. Просмотр всех постов\n"
                "4. Выход\n"
                "Выбор: ";
    }

    void handle_registration() {
        string username, password, bio, input;
        vector<string> interests;

        cout << "\n═════════ Регистрация ═════════\nЛогин: ";
        cin >> username;
        cout << "Пароль: ";
        cin >> password;

        cin.ignore();
        cout << "О себе: ";
        getline(cin, bio);

        cout << "Интересы (через запятую): ";
        getline(cin, input);

        istringstream iss(input);
        while (getline(iss, input, ','))
            interests.push_back(input.substr(0, input.find_first_not_of(" ")));

        UserFactory factory(user_repo);
        factory.create_user(username, password, bio, interests);
        cout << "Регистрация успешна!\n";
    }

    void handle_login() {
        string username, password;
        cout << "\n═════════ Вход ═════════\nЛогин: ";
        cin >> username;
        cout << "Пароль: ";
        cin >> password;

        current_user = auth_service->authenticate(username, password);
        if (current_user) user_session();
        else cout << "Ошибка входа!\n";
    }

    void user_session() {
        int choice;
        do {
            cout << "\n═════════ Личный кабинет ═════════\n"
                    "1. Мой профиль\n"
                    "2. Новый пост\n"
                    "3. Мои посты\n"
                    "4. Все посты\n"
                    "5. Оставить комментарий\n"
                    "6. Выход\n"
                    "Выбор: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1: current_user->print_info(); break;
                case 2: {
                    string title, content;
                    cout << "Заголовок: ";
                    getline(cin, title);
                    cout << "Текст поста:\n";
                    getline(cin, content);
                    blog_service->create_post(current_user->get_username(), title, content);
                    cout << "Пост опубликован!\n";
                    break;
                }
                case 3: current_user->get_blog().print_posts(); break;
                case 4: blog_service->print_all_posts(); break;
                case 5: {
                    blog_service->print_post_numbers();
                    cout << "Номер поста: ";
                    int n; cin >> n; cin.ignore();
                    cout << "Текст комментария: ";
                    string text; getline(cin, text);
                    cout << (blog_service->add_comment(current_user->get_username(), n, text)
                              ? "Комментарий добавлен!\n" : "Ошибка!\n");
                    break;
                }
            }
        } while (choice != 6);
    }

public:
    BlogConsole() {
        UserFactory factory(user_repo);
        factory.create_user("admin", "admin", "Администратор", {"программирование"});
        factory.create_user("user", "123", "Обычный пользователь", {"книги", "музыка"});
    }

    void run() {
        int choice;
        do {
            print_main_menu();
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1: handle_registration(); break;
                case 2: handle_login(); break;
                case 3: blog_service->print_all_posts(); break;
            }
        } while (choice != 4);
    }
};

int main() {
    BlogConsole console;
    console.run();
    return 0;
}
