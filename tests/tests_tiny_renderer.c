
#include <CppUTest/TestHarness.h>

extern "C"{
  #include "bmp_file.h"
  #include "unistd.h"
  #include "tiny_renderer.h"
}



// new_bmp(x, y, colors)

TEST_GROUP(renderer){};

bmp_file_t f = NULL;


void test_draw_line(bmp_file_t f, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t c){
    draw_line(f, x0, y0, x1, y1, c);
    CHECK(c == bmp_file_read(f,  x0,  y0));
    CHECK(c == bmp_file_read(f, x1, y1));
}

TEST(renderer, draw_a_line){
    f = bmp_file_create(100,100);
    // diagonale
    test_draw_line(f,  0,  0, 99, 99, 0xFFFFFF); // WHITE
    test_draw_line(f, 99, 00, 00, 99, 0x00FF00); // GREEN

    // test steepness
    test_draw_line(f, 70, 99, 10,  0, 0xFF00FF); // FUSHIA
    test_draw_line(f, 71, 99, 89,  0, 0xFFFF00); // YELLOW
    // horizontal line
    test_draw_line(f, 10, 30, 90, 30, 0x0000FF); // BLUE

    // vertical line
    test_draw_line(f, 40, 19, 40, 99, 0xFF0000); // RED

    bmp_file_save(f, "test_renderer.bmp");
    bmp_file_delete(f);
}

TEST(renderer, test_render_obj){
    bmp_file_t ren = bmp_file_create(1200,1200);
    render_obj(ren, "objects/african_head.obj", 1200, 1200);
    bmp_file_save(ren, "diablo_renderer.bmp");
    bmp_file_delete(ren);
}
