/* 基于智能指针实现双向链表 */
#include <memory>
#include <iostream>
#include <initializer_list>

template <typename T>
struct Node {
    std::shared_ptr<Node<T>> next;
    std::weak_ptr<Node<T>> prev;

    T value_;

    Node(int val) : value_{val} {}

    void insert(T val) { // before this from 0
        auto node = std::make_shared<Node<T>>(val);
        node->next = prev.lock()->next;
        node->prev = prev;
        prev.lock()->next = node;
        prev = node;
    }

    void erase() {
        if (prev.lock())
            prev.lock()->next = next;
        if (next)
            next->prev = prev;
    }

    ~Node() {
    }
};
template<typename T>
class List {
private:
    std::shared_ptr<Node<T>> head;

public:
    
    List() = default;

    explicit List(std::initializer_list<T> list) {
        for (auto _ : list) {
            this->push_front(_);
        }
    }

     List(List const &other) : head {std::make_shared<Node<T>>(other.head->value_)}
    {
        auto cur = other.head;
        auto mcur = head;
        while (cur->next) {
            auto mnext = std::make_shared<Node<T>>(cur->next->value_);
            mcur->next = mnext;
            mnext->prev = mcur;
            mcur = mnext;
            cur = cur->next;
        }
    }

    List &operator=(List const &other) {
        this->~List();
        new (this) List(other);
        return *this;
    }

    List(List &&other): head{std::move(other.head)} {
        other.head = nullptr;
    }
    List &operator=(List &&other) {
        if (this == &other) {
            return *this;
        }
        head.reset();
        head = std::move(other.head);
        other.head = nullptr;

        return *this;
    }

    Node<T> *front() const {
        return head.get();
    }

    T pop_front() {
        T ret = head->value_;
        head = head->next;
        return ret;
    }

    void push_front(T value) {
        auto node = std::make_shared<Node<T>>(value);
        node->next = head;
        if (head)
            head->prev = node;
        head = node;
    }
    size_t find(T val) { // first val from 0
        size_t i = 0;
        for (auto curr = front(); curr; curr = curr->next.get()) {
            if (curr->value_ == val) return i;
            i++;
        }
        return -1;
    }

    Node<T> *at(size_t index) const {
        auto curr = front();
        for (size_t i = 0; i < index; i++) {
            curr = curr->next.get();
        }
        return curr;
    }

    void print() {
        std::cout << "[";
        for (auto curr = front(); curr; curr = curr->next.get()) {
            std::cout << " " << curr->value_;
        }
        std::cout << "]\n";
    }
};

int main() {
    List<int> a{7, 5, 8, 2, 9, 4, 1};

    a.print();   // [ 1 4 9 2 8 5 7 ]

    a.at(2)->erase();

    // a.print(); // [ 1 4 2 8 5 7 ]

    a.at(2)->insert(10);

    // a.print();   // [ 1 4 10 2 8 5 7 ]

    List b = a;

    a.at(3)->erase();

    a.print();   // [ 1 4 10 2 5 7 ]
    b.print();   // [ 1 4 10 2 8 5 7 ]

    b = a;

    std::cout << b.find(5) << std::endl; // 4

    int c = 3;
    std::unique_ptr<int> p = std::make_unique<int>(10);
    std::unique_ptr<int> p2 = std::make_unique<int>(c);
    std::unique_ptr<int> p3 = std::make_unique<int>(c);

    return 0;
}
