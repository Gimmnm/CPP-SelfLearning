#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <memory>
#include <iostream>

// 模板类声明
template <typename T>
class LinkedList {
private:
    // Node 节点内部类
    struct Node {
        T data;  // 数据
        std::shared_ptr<Node> next;  // 指向下一个节点的智能指针
        Node(T val) : data(val), next(nullptr) {}  // Node 构造函数 
    };

    std::shared_ptr<Node> head;  // 链表头节点

public:
    // 构造函数与析构函数
    LinkedList();  // 默认构造函数
    ~LinkedList();  // 析构函数

    // 拷贝构造函数
    LinkedList(const LinkedList<T>& other);

    // 移动构造函数
    LinkedList(LinkedList<T>&& other) noexcept;

    // 拷贝赋值运算符
    LinkedList<T>& operator=(const LinkedList<T>& other);

    // 移动赋值运算符
    LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;

    // 添加节点到链表尾部
    void append(T val);

    // 在指定位置插入值
    void insert(T val, size_t position);

    // 删除指定位置的节点
    void removeAt(size_t position);

    // 打印链表
    void print() const;

    // 获取链表长度
    size_t size() const;
};

#endif  // LINKEDLIST_HPP