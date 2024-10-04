// 我们可以用仿函数保存多项式的系数，实现多项式求值。每次使用时，无需重新传递系数数组。
#include <iostream>
#include <vector>

struct Polynomial {
    std::vector<double> coefficients;

    Polynomial(const std::vector<double> &coeffs) : coefficients(coeffs) {}

    // 重载仿函数，实现多项式求值
    double operator()(double x) const {
        double result = 0;
        double power_of_x = 1;
        for (double coeff : coefficients) {
            result += coeff * power_of_x;
            power_of_x *= x;
        }
        return result;
    }
};

int main() {
    // 创建一个多项式：P(x) = 1 + 2x + 3x^2
    Polynomial poly({1, 2, 3});

    // 求多项式在 x = 2 处的值
    std::cout << "P(2) = " << poly(2) << std::endl; // 输出：P(2) = 17

    return 0;
}