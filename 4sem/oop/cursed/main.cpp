#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <memory>
#include <map>
#include <algorithm>
#include <stdexcept>

// 1. Класс комментария
class Comment {
private:
    std::string author;
    std::time_t date;
    std::string text;
public:
    Comment(const std::string& author, const std::string& text)
        : author(author), text(text), date(std::time(nullptr)) {}

    void print() const {
        std::cout << author << " (" << std::ctime(&date) << "): " << text << "\n";
    }

    std::string getAuthor() const { return author; }
};

// 2. Класс поста
class Post {
private:
    std::string author;
    std::string title;
    std::string content;
    std::time_t date;
    std::vector<Comment> comments;
    bool commentsAllowed;
public:
    Post(const std::string& author, const std::string& title, const std::string& content)
        : author(author), title(title), content(content), date(std::time(nullptr)), commentsAllowed(true) {}

    void addComment(const Comment& comment) {
        if (commentsAllowed) {
            comments.push_back(comment);
        }
    }

    void print() const {
        std::cout << "\n=== " << title << " ===\n";
        std::cout << "Author: " << author << "\n";
        std::cout << "Date: " << std::ctime(&date);
        std::cout << content << "\n\nComments:\n";
        for (const auto& comment : comments) {
            comment.print();
        }
    }

    std::string getAuthor() const { return author; }
    std::string getTitle() const { return title; }
    std::time_t getDate() const { return date; }
    bool canComment() const { return commentsAllowed; }
    void toggleComments() { commentsAllowed = !commentsAllowed; }
};

// 3. Класс профиля
class Profile {
private:
    std::string bio;
    std::vector<std::string> interests;
public:
    Profile(const std::string& bio = "", const std::vector<std::string>& interests = {})
        : bio(bio), interests(interests) {}

    void print() const {
        std::cout << "\nBio: " << bio << "\n";
        std::cout << "Interests: ";
        for (const auto& interest : interests) {
            std::cout << interest << ", ";
        }
        std::cout << "\n";
    }
};

// 4. Класс блога
class Blog {
private:
    std::string owner;
    std::vector<Post> posts;
public:
    Blog(const std::string& owner) : owner(owner) {}

    void addPost(const Post& post) {
        posts.push_back(post);
        std::sort(posts.begin(), posts.end(),
            [](const Post& a, const Post& b) {
                return a.getDate() > b.getDate();
            });
    }

    void printPosts() const {
        for (const auto& post : posts) {
            post.print();
        }
    }

    std::vector<Post>& getPosts() { return posts; }
    const std::vector<Post>& getPosts() const { return posts; }
    std::string getOwner() const { return owner; }
};

// 5. Класс пользователя
class User {
private:
    std::string username;
    std::string password;
    Profile profile;
    Blog blog;
public:
    User(const std::string& username, const std::string& password, const Profile& profile)
        : username(username), password(password), profile(profile), blog(username) {}

    bool checkPassword(const std::string& pwd) const { return password == pwd; }

    Blog& getBlog() { return blog; }
    const Blog& getBlog() const { return blog; }
    Profile& getProfile() { return profile; }
    std::string getUsername() const { return username; }

    void printInfo() const {
        std::cout << "\n=== " << username << " ===\n";
        profile.print();
    }
};

// 6. Интерфейс репозитория
class IUserRepository {
public:
    virtual void addUser(std::shared_ptr<User> user) = 0;
    virtual std::shared_ptr<User> findUser(const std::string& username) = 0;
    virtual std::vector<std::shared_ptr<User>> getAllUsers() = 0;
    virtual ~IUserRepository() = default;
};

// 7. Репозиторий пользователей
class UserRepository : public IUserRepository {
private:
    std::map<std::string, std::shared_ptr<User>> users;
public:
    void addUser(std::shared_ptr<User> user) override {
        users[user->getUsername()] = user;
    }

    std::shared_ptr<User> findUser(const std::string& username) override {
        auto it = users.find(username);
        return it != users.end() ? it->second : nullptr;
    }

    std::vector<std::shared_ptr<User>> getAllUsers() override {
        std::vector<std::shared_ptr<User>> allUsers;
        for (const auto& pair : users) {
            allUsers.push_back(pair.second);
        }
        return allUsers;
    }
};

// 8. Сервис аутентификации
class AuthService {
private:
    std::shared_ptr<IUserRepository> userRepo;
public:
    AuthService(std::shared_ptr<IUserRepository> repo) : userRepo(repo) {}

    std::shared_ptr<User> authenticate(const std::string& username, const std::string& password) {
        auto user = userRepo->findUser(username);
        return user && user->checkPassword(password) ? user : nullptr;
    }
};

// 9. Сервис блогов
class BlogService {
private:
    std::shared_ptr<IUserRepository> userRepo;
public:
    BlogService(std::shared_ptr<IUserRepository> repo) : userRepo(repo) {}

    bool createPost(const std::string& username, const std::string& title, const std::string& content) {
        auto user = userRepo->findUser(username);
        if (!user) return false;
        user->getBlog().addPost(Post(username, title, content));
        return true;
    }

    void printAllPosts() {
        std::cout << "\n=== All Posts ===\n";
        auto users = userRepo->getAllUsers();
        for (const auto& user : users) {
            std::cout << "\n=== Posts by " << user->getUsername() << " ===\n";
            user->getBlog().printPosts();
        }
    }

    bool addCommentToPost(const std::string& postAuthor, int postIndex,
                         const std::string& commentAuthor, const std::string& commentText) {
        auto author = userRepo->findUser(postAuthor);
        if (!author || postIndex < 0 || postIndex >= author->getBlog().getPosts().size()) {
            return false;
        }

        // Получаем неконстантную ссылку на пост
        author->getBlog().getPosts()[postIndex].addComment(Comment(commentAuthor, commentText));
        return true;
    }

    void printAllPostsWithNumbers() {
        std::cout << "\n=== All Posts ===\n";
        auto users = userRepo->getAllUsers();
        int globalIndex = 1;
        for (const auto& user : users) {
            const auto& posts = user->getBlog().getPosts();
            for (size_t i = 0; i < posts.size(); ++i) {
                std::cout << globalIndex++ << ". " << posts[i].getTitle()
                          << " (by " << user->getUsername() << ")\n";
            }
        }
    }

    std::pair<std::string, int> getPostAuthorAndIndex(int globalIndex) {
        auto users = userRepo->getAllUsers();
        int currentIndex = 1;
        for (const auto& user : users) {
            const auto& posts = user->getBlog().getPosts();
            for (size_t i = 0; i < posts.size(); ++i) {
                if (currentIndex == globalIndex) {
                    return {user->getUsername(), static_cast<int>(i)};
                }
                currentIndex++;
            }
        }
        return {"", -1};
    }
};

// 10. Фабрика пользователей
class UserFactory {
private:
    std::shared_ptr<IUserRepository> repository;

    // Приватный метод для создания профиля
    Profile createProfile(const std::string& bio, const std::vector<std::string>& interests) {
        return Profile(bio, interests);
    }

    // Приватный метод для создания пользователя
    std::shared_ptr<User> createUserInstance(
        const std::string& username,
        const std::string& password,
        const Profile& profile)
    {
        return std::make_shared<User>(username, password, profile);
    }

    // Приватный метод для регистрации пользователя
    void registerUser(const std::shared_ptr<User>& user) {
        repository->addUser(user);
    }

public:
    explicit UserFactory(std::shared_ptr<IUserRepository> repo)
        : repository(repo) {}

    // Основной публичный метод
    std::shared_ptr<User> createUser(
        const std::string& username,
        const std::string& password,
        const std::string& bio,
        const std::vector<std::string>& interests)
    {
        Profile profile = createProfile(bio, interests);
        auto user = createUserInstance(username, password, profile);
        registerUser(user);
        return user;
    }
};

// Консольный интерфейс
class BlogConsole {
private:
    std::shared_ptr<IUserRepository> userRepo;
    std::shared_ptr<AuthService> authService;
    std::shared_ptr<BlogService> blogService;
    std::shared_ptr<User> currentUser;

    void printMainMenu() {
        std::cout << "\n=== Blog System ===\n";
        std::cout << "1. Register\n";
        std::cout << "2. Login\n";
        std::cout << "3. View all posts\n";
        std::cout << "4. Exit\n";
        std::cout << "Choice: ";
    }

    void printUserMenu() {
        std::cout << "\n=== Welcome, " << currentUser->getUsername() << " ===\n";
        std::cout << "1. View profile\n";
        std::cout << "2. Create post\n";
        std::cout << "3. View my posts\n";
        std::cout << "4. View all posts\n";
        std::cout << "5. Comment on post\n";
        std::cout << "6. Logout\n";
        std::cout << "Choice: ";
    }

    void registerUser() {
        std::string username, password, bio;
        std::vector<std::string> interests;

        std::cout << "\nUsername: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password;

        std::cin.ignore();
        std::cout << "Bio: ";
        std::getline(std::cin, bio);

        std::cout << "Enter interests (comma separated): ";
        std::string interestsStr;
        std::getline(std::cin, interestsStr);

        size_t pos = 0;
        while ((pos = interestsStr.find(',')) != std::string::npos) {
            interests.push_back(interestsStr.substr(0, pos));
            interestsStr.erase(0, pos + 1);
        }
        interests.push_back(interestsStr);

        // Создаем фабрику и используем ее
        UserFactory factory(userRepo);
        factory.createUser(username, password, bio, interests);
        std::cout << "User registered successfully!\n";
    }

    void login() {
        std::string username, password;
        std::cout << "\nUsername: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password;

        currentUser = authService->authenticate(username, password);
        if (currentUser) {
            std::cout << "Login successful!\n";
            userSession();
        } else {
            std::cout << "Invalid credentials!\n";
        }
    }

    void commentOnPost() {
        blogService->printAllPostsWithNumbers();

        std::cout << "\nEnter post number to comment: ";
        int postNum;
        std::cin >> postNum;
        std::cin.ignore();

        auto [author, index] = blogService->getPostAuthorAndIndex(postNum);
        if (author.empty() || index == -1) {
            std::cout << "Invalid post number!\n";
            return;
        }

        std::cout << "Enter your comment: ";
        std::string commentText;
        std::getline(std::cin, commentText);

        if (blogService->addCommentToPost(author, index, currentUser->getUsername(), commentText)) {
            std::cout << "Comment added successfully!\n";
        } else {
            std::cout << "Failed to add comment!\n";
        }
    }

    void userSession() {
        int choice;
        do {
            printUserMenu();
            std::cin >> choice;
            std::cin.ignore();

            switch (choice) {
                case 1:
                    currentUser->printInfo();
                    break;
                case 2: {
                    std::string title, content;
                    std::cout << "Post title: ";
                    std::getline(std::cin, title);
                    std::cout << "Post content: ";
                    std::getline(std::cin, content);
                    blogService->createPost(currentUser->getUsername(), title, content);
                    std::cout << "Post created!\n";
                    break;
                }
                case 3:
                    std::cout << "\n=== My Posts ===\n";
                    currentUser->getBlog().printPosts();
                    break;
                case 4:
                    blogService->printAllPosts();
                    break;
                case 5:
                    commentOnPost();
                    break;
                case 6:
                    currentUser = nullptr;
                    std::cout << "Logged out.\n";
                    break;
                default:
                    std::cout << "Invalid choice.\n";
            }
        } while (currentUser && choice != 6);
    }

public:
    BlogConsole() {
        userRepo = std::make_shared<UserRepository>();
        authService = std::make_shared<AuthService>(userRepo);
        blogService = std::make_shared<BlogService>(userRepo);

        // Создаем фабрику
        UserFactory userFactory(userRepo);

        // Создаем тестовых пользователей через фабрику
        userFactory.createUser("admin", "admin123", "System Administrator", {"technology"});
        userFactory.createUser("user1", "password1", "Regular User", {"sports", "music"});
    }

    void run() {
        int choice;
        do {
            printMainMenu();
            std::cin >> choice;
            std::cin.ignore();

            switch (choice) {
                case 1: registerUser(); break;
                case 2: login(); break;
                case 3: blogService->printAllPosts(); break;
                case 4: std::cout << "Goodbye!\n"; break;
                default: std::cout << "Invalid choice.\n";
            }
        } while (choice != 4);
    }
};

int main() {
    BlogConsole console;
    console.run();
    return 0;
}
