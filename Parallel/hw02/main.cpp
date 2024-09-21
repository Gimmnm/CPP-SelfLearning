/* 基于智能指针实现双向链表 */
#include <cstdio>
#include <memory>

struct Node {
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;
    // 如果能改成 unique_ptr 就更好了!

    int value;

    Node(int val) : value{val} {}

    void insert(int val) {
        auto node = std::make_shared<Node>(val);
        node->next = next;
        node->prev = prev;
        if (prev.lock())
            prev.lock()->next = node;
        if (next)
            next->prev = node;
    }

    void erase() {
        if (prev.lock())
            prev.lock()->next = next;
        if (next)
            next->prev = prev;
    }

    ~Node() {
        printf("~Node()\n");  
    }
};

struct List {
    std::shared_ptr<Node> head;

    List() = default;

    List(List const &other) : head {std::make_shared<Node>(other.head->value)}
    {
        printf("List 被拷贝！\n");
        // head = other.head;   这是浅拷贝！
        // 请实现拷贝构造函数为 **深拷贝**
        auto cur = other.head;
        auto mcur = head;
        while (cur->next) {
            auto mnext = std::make_shared<Node>(cur->next->value);
            mcur->next = mnext;
            mnext->prev = mcur;
            mcur = mnext;
            cur = cur->next;
        }
    }

    List &operator=(List const &) = delete;  // 为什么删除拷贝赋值函数也不出错？

    List(List &&) = default;
    List &operator=(List &&) = default;

    Node *front() const {
        return head.get();
    }

    int pop_front() {
        int ret = head->value;
        head = head->next;
        return ret;
    }

    void push_front(int value) {
        auto node = std::make_shared<Node>(value);
        node->next = head;
        if (head)
            head->prev = node;
        head = node;
    }

    Node *at(size_t index) const {
        auto curr = front();
        for (size_t i = 0; i < index; i++) {
            curr = curr->next.get();
        }
        return curr;
    }
};

void print(const List &lst) {  
    printf("[");
    for (auto curr = lst.front(); curr; curr = curr->next.get()) {
        printf(" %d", curr->value);
    }
    printf(" ]\n");
}

int main() {
    List a;

    a.push_front(7);
    a.push_front(5);
    a.push_front(8);
    a.push_front(2);
    a.push_front(9);
    a.push_front(4);
    a.push_front(1);

    print(a);   // [ 1 4 9 2 8 5 7 ]

    a.at(2)->erase();

    print(a);   // [ 1 4 2 8 5 7 ]

    List b = a;

    a.at(3)->erase();

    print(a);   // [ 1 4 2 5 7 ]
    print(b);   // [ 1 4 2 8 5 7 ]

    b = {};
    a = {};

    return 0;
}
