
#include <CppUTest/TestHarness.h>

extern "C"
{
#include "bmp_file.h"
#include "unistd.h"
}


/* The definition of a TEST_GROUP, the name is sample */
TEST_GROUP(bmp_file){};


TEST(bmp_file, create_file){
    bmp_file_t f = NULL;
    f = bmp_file_create(10,10);
    CHECK(f != NULL);
    bmp_file_delete(f);
}

TEST(bmp_file, write_points){
    bmp_file_t f = bmp_file_create(2,2);
    bmp_file_write(f, 0,0, 0xFFFFFF);
    CHECK(bmp_file_read(f, 0, 0) == 0xFFFFFF);
    bmp_file_write(f, 1,1, 0xFFFFFF);
    CHECK(bmp_file_read(f, 1, 1) == 0xFFFFFF);
    bmp_file_delete(f);
}

TEST(bmp_file, write_file){
    bmp_file_t f = bmp_file_create(10,10);

    bmp_file_save(f, "bloc.bmp");
    if( access("bloc.bmp", F_OK ) != -1 ) {
        unlink("bloc.bmp");
    } else {
        CHECK(0);
    }
    bmp_file_delete(f);
}
