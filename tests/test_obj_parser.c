
#include <CppUTest/TestHarness.h>

extern "C"{
    #include "obj_parser.h"
}


TEST_GROUP(test_obj_parser){};



obj_parser_t cube_obj;

TEST(test_obj_parser, open_file){
    cube_obj = obj_parser_open("objects/cube.obj");

    obj_parser_t obj = obj_parser_open("not_existing_file.obj");
    CHECK(obj == NULL);
    CHECK(cube_obj != NULL);

    obj_parser_destroy(cube_obj);
}

TEST(test_obj_parser, get_number_of_vertices){
    cube_obj = obj_parser_open("objects/diablo_pose.obj");

    int n = obj_parser_vertices_size(cube_obj);
    CHECK_EQUAL(2519, n);

    obj_parser_destroy(cube_obj);
}

TEST(test_obj_parser, get_number_of_faces){
    cube_obj = obj_parser_open("objects/diablo_pose.obj");

    int n = obj_parser_faces_size(cube_obj);
    CHECK_EQUAL(5022,  n);

    obj_parser_destroy(cube_obj);
}
