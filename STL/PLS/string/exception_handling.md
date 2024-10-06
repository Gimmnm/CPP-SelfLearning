在 C++ 标准模板库（STL）中，异常处理是保证代码安全性和可恢复性的重要机制之一。STL 的设计哲学是通过异常报告运行时的错误，而不是依赖返回值或其他错误码。这意味着 STL 中许多操作可能会抛出异常，尤其是在处理动态内存分配、越界访问、非法迭代器等情况下。以下是 STL 中常见的异常处理策略和抛出异常的场景。

### 1. **标准异常类**
STL 中异常类基于 C++ 标准库中的 `std::exception` 继承体系。所有 STL 抛出的异常类型都继承自 `std::exception`，可以通过捕获基类 `std::exception` 来处理所有异常。

常用的异常类包括：
- `std::exception`：所有异常类的基类。
- `std::bad_alloc`：内存分配失败时抛出。
- `std::out_of_range`：容器访问越界时抛出。
- `std::invalid_argument`：传递非法参数时抛出。
- `std::length_error`：试图创建过大的容器时抛出。
- `std::logic_error`：逻辑错误基类，主要用于编译期或开发者错误。
- `std::runtime_error`：运行时错误基类，主要用于动态检查和运行时错误。

### 2. **常见 STL 异常场景**

#### 2.1. **动态内存分配失败（`std::bad_alloc`）**
当容器（如 `std::vector`、`std::map` 等）无法分配足够的内存时，抛出 `std::bad_alloc` 异常。

```cpp
#include <iostream>
#include <vector>
#include <new>  // std::bad_alloc

int main() {
    try {
        std::vector<int> vec;
        vec.reserve(SIZE_MAX);  // 试图分配过多的内存
    } catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << '\n';
    }

    return 0;
}
```

#### 2.2. **越界访问（`std::out_of_range`）**
STL 容器的 `at()` 成员函数在访问越界时抛出 `std::out_of_range` 异常，而 `operator[]` 则不会抛出异常，它不进行边界检查。

```cpp
#include <iostream>
#include <vector>
#include <stdexcept>  // std::out_of_range

int main() {
    std::vector<int> vec = {1, 2, 3};

    try {
        int value = vec.at(10);  // 越界访问
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range error: " << e.what() << '\n';
    }

    return 0;
}
```

#### 2.3. **非法迭代器操作（`std::logic_error` 或未定义行为）**
STL 算法和容器要求合法的迭代器操作，如排序、删除或访问等。当使用非法迭代器（如未初始化的迭代器或已被删除的迭代器）时，行为通常是**未定义的**，不会抛出异常。但是，某些库实现可能会抛出 `std::logic_error` 以帮助调试。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 3};
    auto it = vec.end();  // 非法迭代器（超出末尾）

    try {
        std::cout << *it << std::endl;  // 未定义行为，通常不会抛出异常
    } catch (const std::logic_error& e) {
        std::cerr << "Logic error: " << e.what() << '\n';
    }

    return 0;
}
```

在实践中，处理迭代器非法操作时，推荐使用调试工具（如 `sanitizer` 或库的调试模式）进行检查。

#### 2.4. **非法参数（`std::invalid_argument`）**
某些 STL 算法（如 `std::stoi`、`std::stod`）在接收到不合法的参数时会抛出 `std::invalid_argument`。

```cpp
#include <iostream>
#include <string>
#include <stdexcept>  // std::invalid_argument

int main() {
    try {
        int num = std::stoi("abc");  // 非法参数，无法转换为整数
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << '\n';
    }

    return 0;
}
```

#### 2.5. **容器长度超出限制（`std::length_error`）**
在 STL 容器中，若试图创建的容器超出其最大限制（如 `std::vector::max_size()`），则抛出 `std::length_error`。

```cpp
#include <iostream>
#include <vector>
#include <stdexcept>  // std::length_error

int main() {
    try {
        std::vector<int> vec;
        vec.resize(SIZE_MAX);  // 超出容器的最大大小
    } catch (const std::length_error& e) {
        std::cerr << "Length error: " << e.what() << '\n';
    }

    return 0;
}
```

### 3. **`noexcept` 和 STL 中的异常安全**

C++11 引入了 `noexcept` 关键字，用于指示函数不会抛出异常。C++ 标准库中的很多函数标记为 `noexcept`，以便编译器进行优化和异常安全检查。

#### 3.1. **使用 `noexcept` 的函数**
STL 中的一些函数（如析构函数、某些移动构造函数）被标记为 `noexcept`，以保证这些函数不会抛出异常。

```cpp
void safe_function() noexcept {
    // 该函数不会抛出异常
}
```

如果标记为 `noexcept` 的函数抛出了异常，将调用 `std::terminate()` 结束程序。

#### 3.2. **异常安全的三种保证**

STL 的大部分操作提供了以下三种异常安全保证：

1. **基本保证（Basic Guarantee）**：即使发生异常，程序状态依然是有效的，但可能处于不可预测的状态。大部分 STL 算法和容器提供此类保证。
   
2. **强烈保证（Strong Guarantee）**：如果发生异常，程序状态将完全恢复为调用前的状态。例如，在异常情况下， `std::vector::push_back` 会保证没有新元素被插入。
   
3. **无失败保证（No-Throw Guarantee）**：函数保证不会抛出任何异常。标记为 `noexcept` 的函数提供此保证。

### 4. **自定义异常处理**

用户可以在使用 STL 时编写自定义的异常处理代码，以便在需要时捕获并处理异常。

#### 示例：自定义异常处理

```cpp
#include <iostream>
#include <vector>
#include <stdexcept>

int main() {
    std::vector<int> vec;

    try {
        vec.at(10);  // 越界访问，抛出 std::out_of_range 异常
    } catch (const std::out_of_range& e) {
        std::cerr << "Caught out_of_range exception: " << e.what() << '\n';
    } catch (const std::exception& e) {
        std::cerr << "Caught generic exception: " << e.what() << '\n';
    }

    return 0;
}
```

此代码会先捕获 `std::out_of_range`，如果捕获失败，则捕获其他标准异常类型。

### 5. **防止异常传播**

在某些性能敏感的场景中，STL 算法或容器可能被要求不允许异常传播。在这种情况下，用户可以使用 `noexcept` 来防止意外的异常传播，并强制确保函数不会抛出异常。

```cpp
void safe_function() noexcept {
    // 任何异常都会终止程序，而不是传播
}
```

### 总结

STL 的异常处理设计以安全、稳健为目标，大部分异常都是通过标准的异常类型来传递的，主要包括内存分配失败、越界访问、非法迭代器和无效参数等情况。理解 STL 中的异常处理机制，尤其是在处理复杂的容器操作和算法时，可以帮助开发者编写更健壮和安全的代码。