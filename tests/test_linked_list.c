
#include <CppUTest/TestHarness.h>

extern "C"{
#include "linked_list.h"
}

TEST_GROUP(test_linked_list){};


linked_list_t test_list;

void setup(){
    //test_list = linked_list_create();
}


void teardown(){
    linked_list_delete(test_list);
}


TEST(test_linked_list, create_list){
    linked_list_t my_list = NULL;
    my_list = linked_list_create();
    CHECK(my_list != NULL);
    linked_list_delete(my_list);
}


TEST(test_linked_list, add_item){
    test_list = linked_list_create();

    int s = linked_list_size(test_list);
    CHECK(s == 0);
    float vec[] = {1.0, -1.3, 0.004};
    linked_list_add(test_list, vec);
    s = linked_list_size(test_list);
    CHECK(s == 1);
    linked_list_add(test_list, vec);
    s = linked_list_size(test_list);
    CHECK(s == 2);

    linked_list_delete(test_list);
}

TEST(test_linked_list, get_an_item_back){
    test_list = linked_list_create();

    char item_to_add [] = {'a', 'b', 'c', 'd'};
    for(int i = 0; i < 4; i++){
        linked_list_add(test_list, item_to_add + i);
    }
    char *back = (char*)linked_list_get(test_list, 2);
    CHECK(back != NULL);
    CHECK(*back == 'c');

    linked_list_delete(test_list);
}


TEST(test_linked_list, check_out_of_bound_when_getting_an_item){
    test_list = linked_list_create();

    char *back = (char*)linked_list_get(test_list, 0);
    CHECK(back == NULL);
    char item_to_add [] = {'a', 'b', 'c', 'd'};
    for(int i = 0; i < 4; i++){
         linked_list_add(test_list, item_to_add + i);
    }
    back = (char*)linked_list_get(test_list, 4);
    CHECK(back == NULL);

    linked_list_delete(test_list);
}
