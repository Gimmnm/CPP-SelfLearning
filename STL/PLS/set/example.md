在现代 C++ 开发中，虽然许多库采用了面向对象的设计，但也有一些库广泛使用了 **仿函数（Functor）** 进行设计，尤其是在涉及到算法和函数对象的库中。仿函数在算法库中的优势在于它们的灵活性和状态保持能力，允许用户定义自定义操作并传递这些操作给算法。

以下是一些使用了大量仿函数的算法库：

### 1. **C++ 标准模板库（STL）**
STL 本身广泛使用了仿函数，特别是在算法模块中。STL 的许多算法（如 `std::sort`, `std::for_each` 等）都允许用户传入自定义的仿函数来实现灵活的操作。

- **`std::function`**：STL 中的 `std::function` 是一个通用的函数包装器，允许将仿函数、lambda 表达式、普通函数等以统一的形式传递给算法。
  
- **标准仿函数**：STL 提供了一些常见的仿函数类型，比如 `std::plus`, `std::minus`, `std::multiplies` 等，用于基本的算术操作。例如：

  ```cpp
  #include <iostream>
  #include <algorithm>
  #include <vector>
  #include <functional>

  int main() {
      std::vector<int> nums = {1, 2, 3, 4, 5};

      // 使用 std::plus 仿函数求和
      int sum = std::accumulate(nums.begin(), nums.end(), 0, std::plus<int>());
      std::cout << "Sum: " << sum << std::endl;

      return 0;
  }
  ```

  STL 的算法库如 `std::sort`, `std::transform`, `std::accumulate` 等允许传递仿函数，用户可以通过自定义仿函数修改算法的行为。

### 2. **Boost 库**
**Boost** 是 C++ 社区中非常流行的扩展库，它提供了大量的高级算法和数据结构，其中也广泛使用了仿函数。`Boost` 中的仿函数用法体现在以下几个方面：

- **Boost.Function**：类似 `std::function`，但提供了更多的功能和兼容性，特别是在 C++11 之前的版本中，它是函数对象和回调的标准实现。

  ```cpp
  #include <boost/function.hpp>
  #include <iostream>

  void print_sum(int a, int b) {
      std::cout << "Sum: " << a + b << std::endl;
  }

  int main() {
      boost::function<void(int, int)> func = print_sum;
      func(5, 3);  // 调用函数对象
      return 0;
  }
  ```

- **Boost.Bind**：用于绑定函数参数，生成仿函数对象，从而在不完全调用函数的情况下传递一部分参数。这使得函数的传递更加灵活。

  ```cpp
  #include <boost/bind.hpp>
  #include <iostream>

  void print_numbers(int a, int b) {
      std::cout << "A: " << a << ", B: " << b << std::endl;
  }

  int main() {
      // 绑定参数 a 为 10，生成一个新的仿函数
      auto bindFunc = boost::bind(print_numbers, 10, _1);
      bindFunc(20);  // 这将调用 print_numbers(10, 20)
      return 0;
  }
  ```

- **Boost.Phoenix**：`Boost.Phoenix` 是一个元编程库，它通过仿函数实现了表达式模板，用户可以像编写 lambda 表达式一样，编写复杂的嵌套计算和逻辑操作。

  ```cpp
  #include <boost/phoenix/phoenix.hpp>
  #include <iostream>

  int main() {
      using namespace boost::phoenix::placeholders;
      
      // 创建仿函数，计算 x + y
      auto f = arg1 + arg2;
      
      std::cout << f(10, 20) << std::endl;  // 输出 30
      return 0;
  }
  ```

- **Boost.Lambda**：提供了一种类似于 lambda 表达式的仿函数机制，允许用户编写内联的函数对象，非常适合简单的操作。

### 3. **Thrust 库**
**Thrust** 是 NVIDIA 的一个用于并行计算的 C++ 模板库，广泛用于 GPU 和 CPU 上的高性能计算。`Thrust` 利用仿函数来定义和传递操作，支持将复杂的运算封装成仿函数并传递给并行算法执行。

- **自定义仿函数在 Thrust 中的使用**：
  在 `Thrust` 中，用户可以定义自定义仿函数并将其传递给算法，如并行的 `thrust::transform`，`thrust::reduce` 等。Thrust 的设计与 STL 类似，但它能在 GPU 上高效执行。

  ```cpp
  #include <thrust/transform.h>
  #include <thrust/device_vector.h>
  #include <iostream>

  // 自定义仿函数，用于对每个元素加 10
  struct AddTen {
      __host__ __device__
      int operator()(int x) const {
          return x + 10;
      }
  };

  int main() {
      thrust::device_vector<int> d_vec(5, 1); // 初始化一个 GPU 向量

      // 使用 transform 函数执行自定义仿函数
      thrust::transform(d_vec.begin(), d_vec.end(), d_vec.begin(), AddTen());

      for(int i = 0; i < d_vec.size(); i++) {
          std::cout << d_vec[i] << std::endl;
      }

      return 0;
  }
  ```

`Thrust` 中的大量算法通过仿函数设计，用户可以非常灵活地定义自己的计算操作，并在 GPU 上高效并行执行。

### 4. **TBB（Intel Threading Building Blocks）**
**TBB** 是一个用于并行计算的库，提供了高层次的并行算法，它也使用了大量仿函数。特别是在 `parallel_for`, `parallel_reduce` 等并行算法中，TBB 允许用户传递自定义仿函数来定义并行操作。

- **TBB 的仿函数用法**：
  在 `parallel_for` 中，用户需要定义一个仿函数对象来表示循环体的操作。

  ```cpp
  #include <tbb/parallel_for.h>
  #include <iostream>

  // 自定义仿函数，定义并行操作
  struct ParallelOp {
      void operator()(int i) const {
          std::cout << "Processing index: " << i << std::endl;
      }
  };

  int main() {
      tbb::parallel_for(0, 10, ParallelOp());  // 并行执行
      return 0;
  }
  ```

TBB 中的并行算法广泛依赖仿函数，通过自定义操作来实现并行化的任务分发和执行。

### 5. **Eigen**
虽然 **Eigen** 是一个线性代数库，主要用于矩阵操作，但它内部也大量使用了仿函数，特别是通过表达式模板实现高效的矩阵操作。用户可以通过 `Eigen::UnaryExpr` 和 `Eigen::BinaryExpr` 来自定义对矩阵元素的操作。

- **仿函数操作矩阵**：

  ```cpp
  #include <Eigen/Dense>
  #include <iostream>

  // 自定义仿函数，用于矩阵元素的平方操作
  struct SquareOp {
      double operator()(double x) const {
          return x * x;
      }
  };

  int main() {
      Eigen::MatrixXd mat(3, 3);
      mat << 1, 2, 3, 4, 5, 6, 7, 8, 9;

      // 使用自定义仿函数操作矩阵元素
      Eigen::MatrixXd squaredMat = mat.unaryExpr(SquareOp());
      std::cout << "Squared Matrix:\n" << squaredMat << std::endl;

      return 0;
  }
  ```

`Eigen` 的这种设计允许用户轻松对矩阵的每个元素应用自定义操作，而无需显式编写循环。

### 总结

- **STL** 是使用仿函数的经典示例，它提供了大量的内置仿函数，并允许用户通过仿函数自定义算法的行为。
- **Boost** 在多个模块中使用仿函数，包括 `Boost.Function`、`Boost.Bind`、`Boost.Lambda` 和 `Boost.Phoenix` 等。它提供了更灵活的仿函数机制。
- **Thrust** 广泛使用仿函数，用于在 GPU 上执行并行计算，允许用户自定义高性能计算操作。
- **TBB** 使用仿函数在并行计算中分发任务，允许用户定义并行执行的操作。
- **Eigen** 使用仿函数扩展矩阵的操作，实现灵活的元素级操作。

这些库展示了仿函数在 C++ 编程中强大的表达能力和灵活性，使得算法库能够根据用户需求高度定制操作，同时保持高性能和可扩展性。