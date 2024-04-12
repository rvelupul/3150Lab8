#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <memory>
#include <iostream>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::shared_ptr<T>& p) {
    return os << p.get() << " shared_ptr count: [" << p.use_count() << "]";
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::weak_ptr<T>& p) {
    T* raw = nullptr;
    auto sp = p.lock();
    raw = sp.get();
    return os << raw << " weak_ptr to shared_ptr count: [" << (sp ? sp.use_count() : 0) << "]";
}

struct LinkedList {
public:
    struct Node {
        int data;
        std::shared_ptr<Node> next;
        Node(int data, std::shared_ptr<Node> ptr) : data(data), next(ptr) {}
    };

    struct CopyNode {
        std::weak_ptr<Node> weak_node_ptr;
    };

    LinkedList();
    ~LinkedList();

    void build_node_list_shared_ptrs(int k);
    void print_node_list_shared_ptrs();
    void delete_node_shared_ptr_list();
    CopyNode* build_copyNodes_weak_ptrs();
    void print_node_array_weak_ptrs();
    void delete_copyNodes_weak_ptrs();

    
    std::shared_ptr<Node> root;
    int nodeCount;
    CopyNode* copyNodesArray;
};


#endif
