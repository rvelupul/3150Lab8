#include "LinkedList.h"
#include <iostream>

int main() {
    LinkedList list;

    std::cout << "Building a list with 5 nodes:" << std::endl;
    list.build_node_list(5);
    list.print_node_list_shared_ptrs(); 

    list.build_copyNodes_weak_ptrs();
    list.print_node_array_weak_ptrs();  

    list.delete_node_shared_ptr_list();
    list.print_node_array_weak_ptrs();  

    std::cout << "\nBuilding a list with 3 nodes:" << std::endl;
    list.build_node_list(3);
    list.print_node_list_shared_ptrs();  

    list.build_copyNodes_weak_ptrs();
    list.print_node_array_weak_ptrs(); 

    list.delete_node_shared_ptr_list();
    list.print_node_array_weak_ptrs(); 

    return 0;
}
