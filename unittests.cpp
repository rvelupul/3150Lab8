#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "LinkedList.h"

TEST_CASE("Testing build_node_list_shared_ptrs") {
    LinkedList list;

    SUBCASE("List is initially empty") {
        CHECK(list.root == nullptr);  
        CHECK(list.nodeCount == 0);  
    }

    SUBCASE("Building list with 5 elements") {
        list.build_node_list_shared_ptrs(5);
        CHECK(list.nodeCount == 5);  

        std::shared_ptr<LinkedList::Node> node = list.root;
        int count = 0;
        while (node != nullptr) {
            CHECK(node->data == count);  
            node = node->next;
            count++;
        }
        CHECK(count == 5); 
    }

    SUBCASE("Building list with 0 elements") {
        list.build_node_list_shared_ptrs(0);
        CHECK(list.root == nullptr);  
        CHECK(list.nodeCount == 0);   
    }
}

TEST_CASE("Testing delete_node_shared_ptr_list") {
    LinkedList list;

    SUBCASE("Deleting an empty list") {
        list.delete_node_shared_ptr_list();
        CHECK(list.root == nullptr);  
    }

    SUBCASE("Deleting a list with multiple elements") {
        
        list.build_node_list_shared_ptrs(5);
        CHECK(list.nodeCount == 5);  

        list.delete_node_shared_ptr_list();
        CHECK(list.root == nullptr);  

    }

    SUBCASE("Deleting a list with one element") {
        
        list.build_node_list_shared_ptrs(1);
        CHECK(list.nodeCount == 1); 

        list.delete_node_shared_ptr_list();
        CHECK(list.root == nullptr);  
    }
}

TEST_CASE("Testing build_copyNodes_weak_ptrs") {
    LinkedList list;

    SUBCASE("Building copy nodes from an empty list") {
        list.build_node_list_shared_ptrs(0); 
        auto copyNodes = list.build_copyNodes_weak_ptrs();
        CHECK(copyNodes != nullptr);  
        CHECK(list.nodeCount == 0);   
        delete[] copyNodes;
    }

    SUBCASE("Building copy nodes from a list with multiple elements") {
        list.build_node_list_shared_ptrs(5);  
        auto copyNodes = list.build_copyNodes_weak_ptrs();

        std::shared_ptr<LinkedList::Node> node = list.root;
        for (int i = 0; i < 5; ++i) {
            CHECK(copyNodes[i].weak_node_ptr.lock() == node);  
            node = node->next;
        }
}

}