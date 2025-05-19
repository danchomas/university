#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <fstream>

// Comment.h
class Comment {
    std::string author;
    std::time_t date;
    std::string text;

public:
    Comment(const std::string& author, const std::string& text);
    void print() const;
};

// Comment.cpp
Comment::Comment(const std::string& author, const std::string& text)
    : author(author), date(std::time(nullptr)), text(text) {}

void Comment::print() const {
    char time_str[100];
    std::strftime(time_str, sizeof(time_str), "%H:%M %d/%m/%Y", std::localtime(&date));
    std::cout << author << " [" << time_str << "]: " << text << "\n";
}

// Post.h
class Post {
    std::string author;
    std::string title;
    std::string content;
    std::time_t date;
    std::vector<Comment> comments;

public:
    Post(const std::string& author, const std::string& title, const std::string& content);
    void add_comment(const Comment& comment);
    void print() const;
    std::string get_author() const;
    std::string get_title() const;
    std::time_t get_date() const;
};

// Post.cpp
Post::Post(const std::string& author, const std::string& title, const std::string& content)
    : author(author), title(title), content(content), date(std::time(nullptr)) {}

void Post::add_comment(const Comment& comment) {
    comments.push_back(comment);
}

void Post::print() const {
    char time_str[100];
    std::strftime(time_str, sizeof(time_str), "%H:%M %d/%m/%Y", std::localtime(&date));

    std::cout << "\n════════ " << title << " ════════\n"
              << "Автор: " << author << "\n"
              << "Дата: " << time_str << "\n\n"
              << content << "\n\n"
              << "Комментарии (" << comments.size() << "):\n";

    for (const auto& c : comments) c.print();
}

std::string Post::get_author() const { return author; }
std::string Post::get_title() const { return title; }
std::time_t Post::get_date() const { return date; }

// Profile.h
class Profile {
    std::string bio;
    std::vector<std::string> interests;

public:
    Profile(const std::string& bio, const std::vector<std::string>& interests);
    void print() const;
};

// Profile.cpp
Profile::Profile(const std::string& bio, const std::vector<std::string>& interests)
    : bio(bio), interests(interests) {}

void Profile::print() const {
    std::cout << "\nО пользователе: " << bio << "\nИнтересы: ";

    if (interests.empty()) std::cout << "не указаны";
    else for (size_t i = 0; i < interests.size(); ++i)
        std::cout << interests[i] << (i != interests.size()-1 ? ", " : "");
    std::cout << "\n";
}

// Blog.h
class Blog {
    std::string owner;
    std::vector<Post> posts;

public:
    Blog(const std::string& owner);
    void add_post(const Post& post);
    void print_posts() const;
    std::vector<Post>& get_posts();
    std::string get_owner() const;
};

// Blog.cpp
Blog::Blog(const std::string& owner) : owner(owner) {}

void Blog::add_post(const Post& post) {
    posts.push_back(post);
    std::sort(posts.begin(), posts.end(),
        [](const Post& a, const Post& b) { return a.get_date() > b.get_date(); });
}

void Blog::print_posts() const {
    std::cout << "\n═════════ Посты пользователя " << owner << " ═════════\n";
    for (const auto& p : posts) p.print();
}

std::vector<Post>& Blog::get_posts() { return posts; }
std::string Blog::get_owner() const { return owner; }

// IUserRepository.h
class IUserRepository {
public:
    virtual ~IUserRepository() = default;
    virtual void add_user(std::shared_ptr<class User> user) = 0;
    virtual std::shared_ptr<class User> find_user(const std::string& username) = 0;
    virtual std::vector<std::shared_ptr<class User>> get_all_users() = 0;
};

// User.h
class User {
    std::string username;
    std::string password;
    Profile profile;
    std::unique_ptr<Blog> blog;

public:
    User(const std::string& username, const std::string& password, const Profile& profile);
    bool check_password(const std::string& pwd) const;
    Blog& get_blog();
    Profile& get_profile();
    std::string get_username() const;
    void print_info() const;
};

// User.cpp
User::User(const std::string& username, const std::string& password, const Profile& profile)
    : username(username), password(password), profile(profile),
      blog(std::make_unique<Blog>(username)) {}

bool User::check_password(const std::string& pwd) const { return password == pwd; }

Blog& User::get_blog() { return *blog; }
Profile& User::get_profile() { return profile; }
std::string User::get_username() const { return username; }

void User::print_info() const {
    std::cout << "\n═════════ Профиль " << username << " ═════════\n";
    profile.print();
}

// UserRepository.h
class UserRepository : public IUserRepository {
    std::unordered_map<std::string, std::shared_ptr<User>> users;
    std::string filename = "users.txt";

public:
    UserRepository();
    void add_user(std::shared_ptr<User> user) override;
    std::shared_ptr<User> find_user(const std::string& username) override;
    std::vector<std::shared_ptr<User>> get_all_users() override;
    void save_users_to_file();
};

// UserRepository.cpp
UserRepository::UserRepository() {
    std::ifstream infile(filename);
    if (infile) {
        std::string username, password, bio, line;
        std::vector<std::string> interests;
        while (std::getline(infile, line)) {
            if (line.find("Username: ") == 0) {
                username = line.substr(10);
            } else if (line.find("Password: ") == 0) {
                password = line.substr(10);
            } else if (line.find("Bio: ") == 0) {
                bio = line.substr(5);
            } else if (line.find("Interests: ") == 0) {
                interests.clear();
                std::string interests_str = line.substr(11);
                std::istringstream iss(interests_str);
                std::string interest;
                while (std::getline(iss, interest, ',')) {
                    interests.push_back(interest);
                }
                Profile profile(bio, interests);
                auto user = std::make_shared<User>(username, password, profile);
                users[username] = user;
            }
        }
    }
}

void UserRepository::add_user(std::shared_ptr<User> user) {
    users[user->get_username()] = user;
    save_users_to_file();
}

std::shared_ptr<User> UserRepository::find_user(const std::string& username) {
    auto it = users.find(username);
    return it != users.end() ? it->second : nullptr;
}

std::vector<std::shared_ptr<User>> UserRepository::get_all_users() {
    std::vector<std::shared_ptr<User>> result;
    for (const auto& pair : users) result.push_back(pair.second);
    return result;
}

void UserRepository::save_users_to_file() {
    std::ofstream outfile(filename);
    for (const auto& pair : users) {
        auto user = pair.second;
        outfile << "Username: " << user->get_username() << "\n";
        outfile << "Password: " << "password" << "\n"; // Avoid saving actual password for security
        outfile << "Bio: " << user->get_profile().bio << "\n";
        outfile << "Interests: ";
        auto interests = user->get_profile().interests;
        for (size_t i = 0; i < interests.size(); ++i) {
            outfile << interests[i] << (i != interests.size()-1 ? "," : "");
        }
        outfile << "\n";
    }
}

// UserFactory.h
class UserFactory {
    std::shared_ptr<IUserRepository> repo;

public:
    UserFactory(std::shared_ptr<IUserRepository> repo);
    std::shared_ptr<User> create_user(
        const std::string& username,
        const std::string& password,
        const std::string& bio,
        const std::vector<std::string>& interests);
};

// UserFactory.cpp
UserFactory::UserFactory(std::shared_ptr<IUserRepository> repo) : repo(repo) {}

std::shared_ptr<User> UserFactory::create_user(
    const std::string& username,
    const std::string& password,
    const std::string& bio,
    const std::vector<std::string>& interests
) {
    auto user = std::make_shared<User>(username, password, Profile(bio, interests));
    repo->add_user(user);
    return user;
}

// AuthService.h
class AuthService {
    std::shared_ptr<IUserRepository> user_repo;

public:
    AuthService(std::shared_ptr<IUserRepository> repo);
    std::shared_ptr<User> authenticate(const std::string& username, const std::string& password);
};

// AuthService.cpp
AuthService::AuthService(std::shared_ptr<IUserRepository> repo) : user_repo(repo) {}

std::shared_ptr<User> AuthService::authenticate(const std::string& username, const std::string& password) {
    auto user = user_repo->find_user(username);
    return (user && user->check_password(password)) ? user : nullptr;
}

// BlogService.h
class BlogService {
    std::shared_ptr<IUserRepository> user_repo;

public:
    BlogService(std::shared_ptr<IUserRepository> repo);
    bool create_post(const std::string& username, const std::string& title, const std::string& content);
    void print_all_posts();
    bool add_comment(const std::string& commenter, int post_index, const std::string& text);
    void print_post_numbers();
    std::pair<std::string, int> find_post(int global_index);
};

// BlogService.cpp
std::pair<std::string, int> BlogService::find_post(int global_index) {
    int counter = 1;
    for (auto& user : user_repo->get_all_users()) {
        auto& posts = user->get_blog().get_posts();
        for (size_t i = 0; i < posts.size(); ++i) {
            if (counter++ == global_index) return {user->get_username(), static_cast<int>(i)};
        }
    }
    return {"", -1};
}

BlogService::BlogService(std::shared_ptr<IUserRepository> repo) : user_repo(repo) {}

bool BlogService::create_post(const std::string& username, const std::string& title, const std::string& content) {
    if (auto user = user_repo->find_user(username)) {
        user->get_blog().add_post(Post(username, title, content));
        return true;
    }
    return false;
}

void BlogService::print_all_posts() {
    std::cout << "\n═════════ Все посты в системе ═════════\n";
    for (auto& user : user_repo->get_all_users()) {
        auto& posts = user->get_blog().get_posts();
        if (!posts.empty()) {
            std::cout << "\n═════════ Посты пользователя " << user->get_username() << " ═════════\n";
            for (const auto& post : posts) {
                post.print();
            }
        }
    }
}

bool BlogService::add_comment(const std::string& commenter, int post_index, const std::string& text) {
    auto [author, index] = find_post(post_index);
    if (author.empty()) return false;

    if (auto user = user_repo->find_user(author)) {
        auto& posts = user->get_blog().get_posts();
        if (index >= 0 && static_cast<size_t>(index) < posts.size()) {
            posts[index].add_comment(Comment(commenter, text));
            return true;
        }
    }
    return false;
}

void BlogService::print_post_numbers() {
    int counter = 1;
    for (auto& user : user_repo->get_all_users()) {
        for (const auto& post : user->get_blog().get_posts()) {
            std::cout << counter++ << ". " << post.get_title()
                      << " (" << user->get_username() << ")\n";
        }
    }
}

// BlogConsole.h
class BlogConsole {
    std::shared_ptr<UserRepository> user_repo;
    std::shared_ptr<AuthService> auth_service;
    std::shared_ptr<BlogService> blog_service;
    std::shared_ptr<User> current_user;

public:
    BlogConsole();
    void run();

private:
    void print_main_menu();
    void handle_registration();
    void handle_login();
    void user_session();
};

// BlogConsole.cpp
BlogConsole::BlogConsole() {
    user_repo = std::make_shared<UserRepository>();
    auth_service = std::make_shared<AuthService>(user_repo);
    blog_service = std::make_shared<BlogService>(user_repo);

    UserFactory factory(user_repo);
    factory.create_user("admin", "admin", "Администратор", {"программирование"});
    factory.create_user("user", "123", "Обычный пользователь", {"книги", "музыка"});
}

void BlogConsole::print_main_menu() {
    std::cout << "\n═════════ Блог-платформа ═════════\n"
                 "1. Регистрация\n"
                 "2. Вход\n"
                 "3. Просмотр всех постов\n"
                 "4. Выход\n"
                 "Выбор: ";
}

void BlogConsole::handle_registration() {
    std::string username, password, bio, input;
    std::vector<std::string> interests;

    std::cout << "\n═════════ Регистрация ═════════\nЛогин: ";
    std::cin >> username;
    std::cout << "Пароль: ";
    std::cin >> password;

    std::cin.ignore();
    std::cout << "О себе: ";
    std::getline(std::cin, bio);

    std::cout << "Интересы (через запятую): ";
    std::getline(std::cin, input);

    std::istringstream iss(input);
    while (std::getline(iss, input, ','))
        interests.push_back(input.substr(0, input.find_first_not_of(" ")));

    UserFactory factory(user_repo);
    factory.create_user(username, password, bio, interests);
    std::cout << "Регистрация успешна!\n";
}

void BlogConsole::handle_login() {
    std::string username, password;
    std::cout << "\n═════════ Вход ═════════\nЛогин: ";
    std::cin >> username;
    std::cout << "Пароль: ";
    std::cin >> password;

    current_user = auth_service->authenticate(username, password);
    if (current_user) user_session();
    else std::cout << "Ошибка входа!\n";
}

void BlogConsole::user_session() {
    int choice;
    do {
        std::cout << "\n═════════ Личный кабинет ═════════\n"
                     "1. Мой профиль\n"
                     "2. Новый пост\n"
                     "3. Мои посты\n"
                     "4. Все посты\n"
                     "5. Оставить комментарий\n"
                     "6. Выход\n"
                     "Выбор: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: current_user->print_info(); break;
            case 2: {
                std::string title, content;
                std::cout << "Заголовок: ";
                std::getline(std::cin, title);
                std::cout << "Текст поста:\n";
                std::getline(std::cin, content);
                blog_service->create_post(current_user->get_username(), title, content);
                std::cout << "Пост опубликован!\n";
                break;
            }
            case 3: current_user->get_blog().print_posts(); break;
            case 4: blog_service->print_all_posts(); break;
            case 5: {
                blog_service->print_post_numbers();
                std::cout << "Номер поста: ";
                int n; std::cin >> n; std::cin.ignore();
                std::cout << "Текст комментария: ";
                std::string text; std::getline(std::cin, text);
                std::cout << (blog_service->add_comment(current_user->get_username(), n, text)
                          ? "Комментарий добавлен!\n" : "Ошибка!\n");
                break;
            }
        }
    } while (choice != 6);
}

void BlogConsole::run() {
    int choice;
    do {
        print_main_menu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: handle_registration(); break;
            case 2: handle_login(); break;
            case 3: blog_service->print_all_posts(); break;
        }
    } while (choice != 4);
}

// main.cpp
int main() {
    BlogConsole console;
    console.run();
    return 0;
}
