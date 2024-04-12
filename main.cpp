#include "LinkedList.h"
#include <iostream>

using namespace std;


int main() {
    int count = 5;
    LinkedList *cl1 = new LinkedList();
    cl1->build_node_list_shared_ptrs(count);
    cout << "-------" << endl;
   
    LinkedList::CopyNode *copy_node_array = cl1->build_copyNodes_weak_ptrs();
    cl1->print_node_array_weak_ptrs();
    cl1->print_node_list_shared_ptrs();
    cl1->delete_node_shared_ptr_list();
    cl1->print_node_array_weak_ptrs();

    cout << "-------" << endl;

    if (std::shared_ptr<LinkedList::Node> spt = copy_node_array[3].weak_node_ptr.lock()) {
        cout << "*** indirection is expired" << endl;
    } else {
        cout << "indirection is expired\n";
    }

    delete cl1; 
    
    return 0;
}
