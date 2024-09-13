#include "list.hpp"

// 默认构造函数，初始化为空链表
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr) {}

// 析构函数（默认行为，因为使用智能指针）
template <typename T>
LinkedList<T>::~LinkedList() {
    // 智能指针会自动释放节点的内存，无需手动清理
}

// 拷贝构造函数，实现深拷贝
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) : head(nullptr) {
    if (other.head) {
        // 深拷贝头节点
        head = std::make_shared<Node>(other.head->data);

        // 逐节点复制
        auto current = head;
        auto otherCurrent = other.head->next;
        while (otherCurrent) {
            current->next = std::make_shared<Node>(otherCurrent->data);
            current = current->next;
            otherCurrent = otherCurrent->next;
        }
    }
}

// 移动构造函数，将资源所有权从 other 转移到当前对象
template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& other) noexcept : head(std::move(other.head)) {
    other.head = nullptr;  // 确保 other 不再拥有原资源
}

// 拷贝赋值运算符，实现深拷贝
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
    if (this == &other) {
        return *this;  // 防止自我赋值
    }

    head.reset();  // 释放原有的链表

    if (other.head) {
        // 深拷贝
        head = std::make_shared<Node>(other.head->data);
        auto current = head;
        auto otherCurrent = other.head->next;
        while (otherCurrent) {
            current->next = std::make_shared<Node>(otherCurrent->data);
            current = current->next;
            otherCurrent = otherCurrent->next;
        }
    }

    return *this;
}

// 移动赋值运算符，转移资源所有权
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) noexcept {
    if (this == &other) {
        return *this;  // 防止自我赋值
    }

    // 释放当前对象的资源
    head.reset();

    // 转移所有权
    head = std::move(other.head);
    other.head = nullptr;

    return *this;
}

// 添加节点到链表尾部
template <typename T>
void LinkedList<T>::append(T val) {
    auto newNode = std::make_shared<Node>(val);  // 创建新节点

    if (!head) {
        // 链表为空，设置为头节点
        head = newNode;
    } else {
        // 遍历链表找到尾部
        auto current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;  // 插入到尾部
    }
}

// 在指定位置插入值
template <typename T>
void LinkedList<T>::insert(T val, size_t position) {
    auto newNode = std::make_shared<Node>(val);

    if (position == 0) {
        // 如果在头部插入
        newNode->next = head;
        head = newNode;
        return;
    }

    auto current = head;
    for (size_t i = 0; current && i < position - 1; ++i) {
        current = current->next;
    }

    if (current) {
        newNode->next = current->next;
        current->next = newNode;
    } else {
        // 如果位置超出了链表长度，则在尾部插入
        append(val);
    }
}

// 删除指定位置的节点
template <typename T>
void LinkedList<T>::removeAt(size_t position) {
    if (!head) return;  // 如果链表为空，直接返回

    if (position == 0) {
        // 删除头节点
        head = head->next;
        return;
    }

    auto current = head;
    for (size_t i = 0; current && i < position - 1; ++i) {
        current = current->next;
    }

    if (current && current->next) {
        current->next = current->next->next;
    }
}

// 打印链表中的所有元素
template <typename T>
void LinkedList<T>::print() const {
    auto current = head;
    while (current) {
        std::cout << current->data << " -> ";
        current = current->next;
    }
    std::cout << "nullptr" << std::endl;
}

// 获取链表长度
template <typename T>
size_t LinkedList<T>::size() const {
    size_t count = 0;
    auto current = head;
    while (current) {
        ++count;
        current = current->next;
    }
    return count;
}

// 需要在.cpp文件中实例化模板
template class LinkedList<int>;
template class LinkedList<double>;