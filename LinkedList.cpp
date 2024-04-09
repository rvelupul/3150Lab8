#include "LinkedList.h"

LinkedList::LinkedList() : root(nullptr), nodeCount(0), copyNodesArray(nullptr) {}

LinkedList::~LinkedList() {
    delete_node_shared_ptr_list();
    delete[] copyNodesArray;
}

void LinkedList::build_node_list(int k) {
    std::shared_ptr<Node> last = nullptr;
    for (int i = 0; i < k; ++i) {
        auto newNode = std::make_shared<Node>(i, nullptr);
        if (!root) {
            root = newNode;
            last = newNode;
        } else {
            last->next = newNode;
            last = newNode;
        }
    }
    nodeCount = k;
}

LinkedList::CopyNode* LinkedList::build_copyNodes_weak_ptrs() {
    copyNodesArray = new CopyNode[nodeCount];
    auto temp = root;
    for (int i = 0; i < nodeCount; ++i) {
        copyNodesArray[i].weak_node_ptr = temp;
        temp = temp->next;
    }
    return copyNodesArray;
}

void LinkedList::delete_node_shared_ptr_list() {
    while (root) {
        auto temp = root; 
        root = root->next; 
        temp->next = nullptr; 
    }
}

void LinkedList::print_node_list_shared_ptrs() {
    auto temp = root;
    while (temp) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

void LinkedList::print_node_array_weak_ptrs() {
    for (int i = 0; i < nodeCount; ++i) {
        if (auto sp = copyNodesArray[i].weak_node_ptr.lock()) {
            std::cout << sp->data << " ";
        } else {
            std::cout << "nullptr ";
        }
    }
    std::cout << std::endl;
}
