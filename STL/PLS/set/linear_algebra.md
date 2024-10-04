下面是一个使用仿函数（函数对象）实现的线性代数算法库。该库实现了多个常见的线性代数算法，如矩阵乘法、矩阵转置、矩阵求逆、高斯消去法、LU 分解、以及求解线性方程组等。这些算法均通过 C++ 仿函数进行封装，使其具有灵活性和状态保存的能力。

### 1. **矩阵类定义**
首先，我们定义一个基础的矩阵类 `Matrix`，用于存储矩阵数据以及常见的矩阵操作。该类将作为其他仿函数实现的基础。

```cpp
#include <iostream>
#include <vector>
#include <stdexcept>

class Matrix {
public:
    std::vector<std::vector<double>> data;
    size_t rows, cols;

    Matrix(size_t r, size_t c) : rows(r), cols(c), data(r, std::vector<double>(c, 0.0)) {}

    Matrix(const std::vector<std::vector<double>>& d) : rows(d.size()), cols(d[0].size()), data(d) {}

    std::vector<double>& operator[](size_t i) {
        return data[i];
    }

    const std::vector<double>& operator[](size_t i) const {
        return data[i];
    }

    void print() const {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};
```

### 2. **矩阵乘法**
仿函数用于实现矩阵乘法。该函数接受两个矩阵，并返回其乘积。

```cpp
struct MatrixMultiply {
    Matrix operator()(const Matrix& A, const Matrix& B) const {
        if (A.cols != B.rows) {
            throw std::invalid_argument("Matrix dimensions do not match for multiplication.");
        }

        Matrix result(A.rows, B.cols);
        for (size_t i = 0; i < A.rows; ++i) {
            for (size_t j = 0; j < B.cols; ++j) {
                for (size_t k = 0; k < A.cols; ++k) {
                    result[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        return result;
    }
};
```

### 3. **矩阵转置**
仿函数用于实现矩阵的转置操作。

```cpp
struct MatrixTranspose {
    Matrix operator()(const Matrix& A) const {
        Matrix result(A.cols, A.rows);
        for (size_t i = 0; i < A.rows; ++i) {
            for (size_t j = 0; j < A.cols; ++j) {
                result[j][i] = A[i][j];
            }
        }
        return result;
    }
};
```

### 4. **高斯消去法**
用于求解线性方程组的高斯消去法仿函数。该方法将线性方程组转换为上三角矩阵，并逐步求解。

```cpp
struct GaussianElimination {
    std::vector<double> operator()(Matrix A, std::vector<double> b) const {
        size_t n = A.rows;
        for (size_t i = 0; i < n; ++i) {
            // 寻找主元
            double maxElem = std::abs(A[i][i]);
            size_t maxRow = i;
            for (size_t k = i + 1; k < n; ++k) {
                if (std::abs(A[k][i]) > maxElem) {
                    maxElem = std::abs(A[k][i]);
                    maxRow = k;
                }
            }

            // 交换最大行和当前行
            std::swap(A[i], A[maxRow]);
            std::swap(b[i], b[maxRow]);

            // 归一化主元
            for (size_t k = i + 1; k < n; ++k) {
                double factor = A[k][i] / A[i][i];
                for (size_t j = i; j < n; ++j) {
                    A[k][j] -= factor * A[i][j];
                }
                b[k] -= factor * b[i];
            }
        }

        // 回代过程
        std::vector<double> x(n);
        for (int i = n - 1; i >= 0; --i) {
            x[i] = b[i] / A[i][i];
            for (int k = i - 1; k >= 0; --k) {
                b[k] -= A[k][i] * x[i];
            }
        }
        return x;
    }
};
```

### 5. **LU 分解**
用于矩阵的 LU 分解仿函数，将矩阵分解为一个下三角矩阵和一个上三角矩阵。

```cpp
struct LUDecomposition {
    std::pair<Matrix, Matrix> operator()(const Matrix& A) const {
        size_t n = A.rows;
        Matrix L(n, n), U(n, n);

        for (size_t i = 0; i < n; ++i) {
            for (size_t j = i; j < n; ++j) {
                // 计算 U 矩阵
                U[i][j] = A[i][j];
                for (size_t k = 0; k < i; ++k) {
                    U[i][j] -= L[i][k] * U[k][j];
                }
            }

            for (size_t j = i; j < n; ++j) {
                if (i == j) {
                    L[i][i] = 1;  // L 的对角线元素为 1
                } else {
                    // 计算 L 矩阵
                    L[j][i] = A[j][i];
                    for (size_t k = 0; k < i; ++k) {
                        L[j][i] -= L[j][k] * U[k][i];
                    }
                    L[j][i] /= U[i][i];
                }
            }
        }
        return std::make_pair(L, U);
    }
};
```

### 6. **矩阵求逆**
通过高斯-约尔当法实现矩阵的逆。

```cpp
struct MatrixInverse {
    Matrix operator()(Matrix A) const {
        size_t n = A.rows;
        Matrix I(n, n);
        for (size_t i = 0; i < n; ++i) {
            I[i][i] = 1.0;
        }

        for (size_t i = 0; i < n; ++i) {
            double pivot = A[i][i];
            if (pivot == 0) {
                throw std::invalid_argument("Matrix is singular and cannot be inverted.");
            }

            for (size_t j = 0; j < n; ++j) {
                A[i][j] /= pivot;
                I[i][j] /= pivot;
            }

            for (size_t k = 0; k < n; ++k) {
                if (k != i) {
                    double factor = A[k][i];
                    for (size_t j = 0; j < n; ++j) {
                        A[k][j] -= factor * A[i][j];
                        I[k][j] -= factor * I[i][j];
                    }
                }
            }
        }
        return I;
    }
};
```

### 7. **求矩阵的行列式**
通过 LU 分解来计算矩阵的行列式。

```cpp
struct Determinant {
    double operator()(const Matrix& A) const {
        LUDecomposition lu;
        auto [L, U] = lu(A);
        double det = 1.0;
        for (size_t i = 0; i < A.rows; ++i) {
            det *= U[i][i];  // 行列式为 U 矩阵对角元素的乘积
        }
        return det;
    }
};
```

### 8. **线性方程组求解（LU 分解法）**
通过 LU 分解求解线性方程组 `Ax = b`。

```cpp
struct LUSolver {
    std::vector<double> operator()(const Matrix& A, const std::vector<double>& b) const {
        LUDecomposition lu;
        auto [L, U] = lu(A);

        size_t n = A.rows;
        std::vector<double> y(n), x(n);

        // 前向替换求解 Ly = b
        for (size_t i = 0; i < n; ++i) {
            y[i] = b[i];
            for (size_t j = 0; j < i; ++j) {
                y[i] -= L[i][j] * y[j];
            }
            y[i] /= L[i][i];
        }

        // 回代求解 Ux = y
        for (int i = n - 1; i >= 0; --i) {
            x[i] = y[i];
            for (size_t j = i + 1; j < n; ++j) {
                x[i] -= U[i][j] * x[j];
            }
            x[i] /= U[i][i];
        }

        return x;
    }
};
```

### 测试代码
以下是一个使用上述仿函数库进行矩阵运算的简单示例。

```cpp
int main() {
    Matrix A = {
        {2, -1, 0},
        {-1, 2, -1},
        {0, -1, 2}
    };

    Matrix B = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    // 矩阵乘法
    MatrixMultiply multiply;
    Matrix C = multiply(A, B);
    std::cout << "Matrix A * B:" << std::endl;
    C.print();

    // 矩阵转置
    MatrixTranspose transpose;
    Matrix AT = transpose(A);
    std::cout << "Transpose of A:" << std::endl;
    AT.print();

    // LU 分解
    LUDecomposition lu;
    auto [L, U] = lu(A);
    std::cout << "LU Decomposition - L:" << std::endl;
    L.print();
    std::cout << "LU Decomposition - U:" << std::endl;
    U.print();

    // 矩阵求逆
    MatrixInverse inverse;
    Matrix invA = inverse(A);
    std::cout << "Inverse of A:" << std::endl;
    invA.print();

    // 矩阵行列式
    Determinant det;
    double detA = det(A);
    std::cout << "Determinant of A: " << detA << std::endl;

    return 0;
}
```

### 总结

这个使用仿函数实现的线性代数库包含了多种常见的矩阵运算与线性代数算法，如矩阵乘法、矩阵转置、LU 分解、矩阵求逆、高斯消去法等。仿函数提供了灵活性，可以保存状态，并且便于扩展和组合。这种设计也能提高代码的模块化和可读性，适用于复杂的线性代数计算场景。