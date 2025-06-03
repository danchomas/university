#include <vector>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <array>

class EquationSolver {
public:
    virtual std::vector<double> solve() = 0;
    virtual void printEquation() = 0;
    virtual ~EquationSolver() {}
};

class QuadraticEquationSolver : public EquationSolver {
private:
    double a;
    double b;
    double c;

public:
    QuadraticEquationSolver(double a, double b, double c) : a(a), b(b), c(c) {
        if (a == 0) {
            throw std::invalid_argument("Коэффициент a не должен быть равен нулю.");
        }
    }

    void printEquation() override {
        std::cout << a << "x^2 ";
        if (b >= 0) {
            std::cout << "+ " << b << "x ";
        } else {
            std::cout << "- " << -b << "x ";
        }
        
        if (c >= 0) {
            std::cout << "+ " << c;
        } else {
            std::cout << "- " << -c;
        }
        std::cout << " = 0" << std::endl;
    }

    std::vector<double> solve() override {
        const double discriminant = b * b - 4 * a * c;
        std::vector<double> roots;

        if (discriminant < 0) {
            throw std::runtime_error("Уравнение не имеет действительных корней.");
        }
        else if (discriminant == 0) {
            roots.push_back(-b / (2 * a));
        }
        else {
            const double sqrt_discriminant = std::sqrt(discriminant);
            const double denominator = 2 * a;
            roots.push_back((-b + sqrt_discriminant) / denominator);
            roots.push_back((-b - sqrt_discriminant) / denominator);
        }
        return roots;
    }
};

int main() {
    std::vector<std::array<int, 3>> testCases = {
        {2, -5, 3},
        {1, -4, 4},
        {1, 0, 1},
        {4, 0, -16}
    };

    for (auto& testCase : testCases) {
        try {
            QuadraticEquationSolver solver(testCase[0], testCase[1], testCase[2]);
            solver.printEquation();

            auto roots = solver.solve();
            if (!roots.empty()) {
                std::cout << "Корни уравнения:" << std::endl;
                for (double root : roots) {
                    std::cout << " " << root << std::endl;
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
        }
        std::cout << "---------------------------------" << std::endl;
    }

    return 0;
}