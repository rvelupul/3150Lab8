#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "LinkedList.h"

TEST_CASE("Testing build_node_list function") {
    LinkedList list;

    SUBCASE("Test with 0 elements") {
        list.build_node_list(0);
        CHECK(list.nodeCount == 0);
        CHECK(list.root == nullptr);
    }

    SUBCASE("Test with 1 element") {
        list.build_node_list(1);
        CHECK(list.nodeCount == 1);
        CHECK(list.root != nullptr);
        CHECK_EQ(list.root->data, 0);
    }

    SUBCASE("Test with multiple elements") {
        int numElements = 5;
        list.build_node_list(numElements);
        CHECK(list.nodeCount == numElements);
        
        std::shared_ptr<LinkedList::Node> node = list.root;
        for (int i = 0; i < numElements; i++) {
            CHECK(node != nullptr);
            CHECK_EQ(node->data, i);
            node = node->next;
        }
        CHECK(node == nullptr); 
    }
}

TEST_CASE("Testing build_copyNodes_weak_ptrs function") {
    LinkedList list;

    SUBCASE("Build copy nodes from non-empty list") {
        int numElements = 5;
        list.build_node_list(numElements);
        auto copyNodes = list.build_copyNodes_weak_ptrs();
        CHECK(copyNodes != nullptr);
    }

    SUBCASE("Check weak_ptrs are invalidated after deleting main list") {
        list.build_node_list(3);
        auto copyNodes = list.build_copyNodes_weak_ptrs();
        
        list.delete_node_shared_ptr_list(); 

        for (int i = 0; i < 3; i++) {
            auto weakPtr = copyNodes[i].weak_node_ptr;
            CHECK(weakPtr.expired()); 
        }
    }
}

TEST_CASE("Testing delete_node_shared_ptr_list function") {
    LinkedList list;

    SUBCASE("Deleting an empty list should not cause errors") {
        list.build_node_list(0); 
        list.delete_node_shared_ptr_list();
    }

    SUBCASE("Deleting a non-empty list should clear all nodes") {
        list.build_node_list(5);
        auto copyNodes = list.build_copyNodes_weak_ptrs();
        list.delete_node_shared_ptr_list();

        for (int i = 0; i < 5; i++) {
            CHECK(copyNodes[i].weak_node_ptr.expired());
        }
    }

    SUBCASE("Ensure deletion is idempotent") {
        list.build_node_list(3);
        list.delete_node_shared_ptr_list();

        list.delete_node_shared_ptr_list();
    }
}