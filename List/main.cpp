#include "list.hpp"

int main() {
    LinkedList<int> list;

    // 添加元素
    list.append(10);
    list.append(20);
    list.append(30);
    list.print();  // 输出: 10 -> 20 -> 30 -> nullptr

    // 在指定位置插入元素
    list.insert(15, 1);  // 在位置 1 插入 15
    list.print();  // 输出: 10 -> 15 -> 20 -> 30 -> nullptr

    list.insert(5, 0);   // 在头部插入 5
    list.print();  // 输出: 5 -> 10 -> 15 -> 20 -> 30 -> nullptr

    list.insert(35, 100);  // 在超出范围的位置插入，默认插入到尾部
    list.print();  // 输出: 5 -> 10 -> 15 -> 20 -> 30 -> 35 -> nullptr

    // 删除指定位置的元素
    list.removeAt(3);  // 删除位置 3 的元素（即 20）
    list.print();  // 输出: 5 -> 10 -> 15 -> 30 -> 35 -> nullptr

    list.removeAt(0);  // 删除头部元素
    list.print();  // 输出: 10 -> 15 -> 30 -> 35 -> nullptr

    list.removeAt(100);  // 删除超出范围的位置，不做任何操作
    list.print();  // 输出: 10 -> 15 -> 30 -> 35 -> nullptr

    return 0;
}