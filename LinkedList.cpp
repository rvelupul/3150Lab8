#include "LinkedList.h"

using namespace std;

LinkedList::LinkedList() : nodeCount(0), root(nullptr), copyNodesArray(nullptr) {
    
}

LinkedList::~LinkedList() {
    
    delete_node_shared_ptr_list();  
    delete_copyNodes_weak_ptrs();   
}

void LinkedList::build_node_list_shared_ptrs(int totalNumber) {
    cout << "build_node_list_shared_ptrs START" << endl;
    shared_ptr<Node> traverse = this->root;
    for (int i = 0; i < totalNumber; i++) {
        if (!traverse) {
            traverse = make_shared<Node>(nodeCount++, nullptr);
            if (!this->root) this->root = traverse;
        } else {
            traverse->next = make_shared<Node>(nodeCount++, nullptr);
            traverse = traverse->next;
        }
        cout << traverse << endl;
    }
    cout << "build_node_list_shared_ptrs END" << endl;
}

void LinkedList::print_node_list_shared_ptrs() {
    cout << "print_node_list_shared_ptrs START" << endl;
    shared_ptr<Node> myNext = this->root;

    while (myNext) {
        cout << myNext << endl;
        myNext = myNext->next;
    }

    cout << "print_node_list_shared_ptrs END" << endl;
}

void LinkedList::delete_node_shared_ptr_list() {
    cout << "delete_node_shared_ptr_list START" << endl;
    auto current = root;
    while (current) {
        auto next = current->next; 
        current->next.reset(); 
        current = next; 
        cout << "@" << " shared_ptr count: [0]" << endl; 
    }
    root.reset(); 
    cout << "delete_node_shared_ptr_list END" << endl;
}


LinkedList::CopyNode* LinkedList::build_copyNodes_weak_ptrs() {
    cout << "build_copyNodes_ARRAY_weak_ptrs START" << endl;
    this->copyNodesArray = new CopyNode[this->nodeCount];
    auto current = this->root;
    for (int i = 0; i < this->nodeCount; ++i) {
        this->copyNodesArray[i].weak_node_ptr = current;
        cout << current << endl;
        if (current) current = current->next;
    }
    cout << "build_copyNodes_ARRAY_weak_ptrs END" << endl;
    return this->copyNodesArray;
}

void LinkedList::print_node_array_weak_ptrs() {
    cout << "print_node_ARRAY_weak_ptrs START" << endl;
    for (int i = 0; i < this->nodeCount; ++i) {
        auto sp = this->copyNodesArray[i].weak_node_ptr.lock();
        if (sp) {
            cout << "spt == " << sp << endl;
        } else {
            cout << "the list is expired" << endl;
        }
    }
    cout << "print_node_ARRAY_weak_ptrs END" << endl;
}

void LinkedList::delete_copyNodes_weak_ptrs() {
    cout << "delete_copyNodes_weak_ptrs START" << endl;
    delete[] this->copyNodesArray;
    this->copyNodesArray = nullptr;
    cout << "delete_copyNodes_weak_ptrs END" << endl;
}
