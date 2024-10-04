// 仿函数可以通过状态和构造函数传递参数，方便地组合不同的算法。仿函数不仅可以执行特定的运算，还可以被作为另一个算法的参数进行组合。

#include <cmath>
#include <functional>
#include <iostream>

// 数值积分仿函数（梯形法）
struct TrapezoidalRule {
    double operator()(std::function<double(double)> f, double a, double b, int n) const {
        double h = (b - a) / n;
        double sum = 0.5 * (f(a) + f(b));
        for (int i = 1; i < n; ++i) {
            sum += f(a + i * h);
        }
        return sum * h;
    }
};

// 数值积分仿函数（辛普森法）
struct SimpsonRule {
    double operator()(std::function<double(double)> f, double a, double b, int n) const {
        if (n % 2 != 0) n++; // 辛普森法要求 n 是偶数
        double h = (b - a) / n;
        double sum = f(a) + f(b);
        for (int i = 1; i < n; ++i) {
            sum += (i % 2 == 0 ? 2 : 4) * f(a + i * h);
        }
        return sum * h / 3.0;
    }
};

int main() {
    auto func = [](double x) { return std::sin(x); };

    TrapezoidalRule trapezoid;
    SimpsonRule simpson;

    double result_trap = trapezoid(func, 0.0, M_PI, 1000); // 使用梯形法
    double result_simp = simpson(func, 0.0, M_PI, 1000);   // 使用辛普森法

    std::cout << "Trapezoidal Rule: " << result_trap << std::endl;
    std::cout << "Simpson Rule: " << result_simp << std::endl;

    return 0;
}