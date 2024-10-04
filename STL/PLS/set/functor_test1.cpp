// 仿函数不仅可以执行简单的算术操作，还可以处理更复杂的逻辑。例如，我们可以创建一个自定义的仿函数来计算向量的内积（点积），这也是一种算子行为：
#include <iostream>
#include <vector>

// 自定义向量内积算子仿函数
struct DotProduct {
    double operator()(const std::vector<double> &v1, const std::vector<double> &v2) const {
        if (v1.size() != v2.size()) {
            throw std::invalid_argument("Vectors must have the same length.");
        }
        double result = 0;
        for (size_t i = 0; i < v1.size(); ++i) {
            result += v1[i] * v2[i];
        }
        return result;
    }
};

int main() {
    std::vector<double> vec1 = {1.0, 2.0, 3.0};
    std::vector<double> vec2 = {4.0, 5.0, 6.0};

    DotProduct dotProduct;
    double result = dotProduct(vec1, vec2); // 计算向量内积

    std::cout << "Dot product: " << result << std::endl; // 输出：Dot product: 32

    return 0;
}