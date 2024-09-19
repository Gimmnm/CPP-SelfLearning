#include <iostream>

//https://www.bilibili.com/video/BV1Gg4y1p71w?p=6&spm_id_from=pageDriver&vd_source=d72149d61ee2ced13ed6a01a55bbadf6

template <typename T>
void f(T param) {
    std::cout << param << std::endl;
}

void func(int, int) {}
int func2(int) { return 10; }

using F = int(int);

// 函数重载的时候，什么时候构成重载？？？什么时候编译器认为不需要有区别？？？
// --------------------------------------------------------------
void ff(int a) {}

void ff(const int a) {} // 不构成重载 为什么不构成重载 这是一个拷贝 是不是const编译器不需要认定，底层const一样，只是指针的拷贝，指针改变也就改变了

void ff(int& a) {
    std::cout << "Non-const reference" << std::endl;
}

void ff(const int& a) {
    std::cout << "Const reference" << std::endl; // 但是如果是const引用或者是顶层const 那么就不能视作一样，因为确实可以改变设置为不可变的变量
                                                // 也就是说，编译器认为在这个时候，函数的操作应当不一样
}

void ff(int* ptr) {
    std::cout << "Non-const pointer to non-const int" << std::endl;
}

void ff(const int* ptr) {
    std::cout << "Pointer to const int" << std::endl;
}

void ff(int* const ptr) { // 不构成重载
    std::cout << "Const pointer to non-const int" << std::endl;
}

void ff(const int* const ptr) { //不构成重载
    std::cout << "Const pointer to const int" << std::endl;
}
// --------------------------------------------------------------


int main() {

    int a = 10;
    f(a);
    int *aptr = &a;
    f(aptr);
    int &aref = a;
    f(aref);// 引用放在右边与一般变量没有区别
    int &&arref = std::move(a);
    f(arref);

    const int ca = 20;
    f(ca); // 因为传的是拷贝，无所谓改不改变
    const int *captr = &ca;
    f(captr); // 顶层const 要保证不能改变指向的对象，所以有区别
    const int &caref = ca;
    f(caref);
    const int &&carref = std::move(ca);
    f(carref);


    int *const acptr = &a;
    f(acptr);
    const int *const cacptr = &a;
    f(cacptr);

    10;
    f(10);

    int arr[2] = {0, 1};
    f(arr); // 数组名当作参数的时候 会退化 为指针

    "hello world";
    f("hello world");

    int (*arrptr)[2] = &arr; // 数组指针 也就是一个指针指向一个数组
    f(arrptr);  // 不会退化

    int (&arrref)[2] = arr;
    f(arrref); // 同样会退化

    func;
    f(func); // 函数名当作参数的时候 会退化 为指针

    void (*funcptr)(int, int) = func;
    f(funcptr); // 和上面一样

    void (&funcref)(int, int) = func;
    f(funcref); // 传参数的时候，引用都没用！！！！
    //----------------------------------------------------



    return 0;
}
