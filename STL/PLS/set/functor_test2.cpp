// 仿函数的一个核心优势是它可以保存状态。通过构造函数，仿函数可以保存算法的上下文数据，这在一些复杂的数值分析算法中非常有用。例如，某些迭代算法可能需要维护某种内部状态，如初始条件、迭代步数等。
#include <cmath>
#include <iostream>

struct NewtonSolver {
    double tol;    // 容差
    int max_iters; // 最大迭代次数

    // 构造函数保存状态
    NewtonSolver(double tolerance, int max_iterations) : tol(tolerance), max_iters(max_iterations) {}

    // 仿函数实现牛顿法
    double operator()(double (*f)(double), double (*f_prime)(double), double initial_guess) const {
        double x = initial_guess;
        for (int i = 0; i < max_iters; ++i) {
            double fx = f(x);
            double fpx = f_prime(x);
            if (std::abs(fx) < tol) {
                break;
            }
            x = x - fx / fpx; // 更新 x
        }
        return x;
    }
};

// 示例函数 f(x) = x^2 - 2 和它的导数
double func(double x) { return x * x - 2; }
double func_prime(double x) { return 2 * x; }

int main() {
    // 实例化牛顿法仿函数，设置容差为 1e-6，最大迭代次数为 100
    NewtonSolver solver(1e-6, 100);

    // 计算 f(x) = x^2 - 2 在 x=1.0 附近的根
    double root = solver(func, func_prime, 1.0);
    std::cout << "Root: " << root << std::endl; // 输出接近于 sqrt(2) 的结果

    return 0;
}