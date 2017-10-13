
#include "tiny_renderer.h"
#include "bmp_file.h"
#include "obj_parser.h"
#include <stdio.h>

#define DRAW(x, y, color) bmp_file_write((bmp_file_t)data, x, y, color)

int abs(int x){
    if(x < 0){
        return -1 * x;
    }
    return x;
}

void swap(int *a, int *b){
    uint32_t c = *a;
    *a = *b;
    *b = c;
}

void draw_line(void* data, int x0, int y0, int x1, int y1, int color){
    // 1st check if the line is steep
    //(the difference between y0 and y1 is greater than between x0 and x1)
    int transposed = 0;
    if(abs(x0-x1) < abs(y0-y1)){
        // then we transpose the line
        swap(&x0, &y0);
        swap(&x1, &y1);
        transposed = 1;
    }
    if(x1 < x0){
        swap(&x1, &x0);
        swap(&y1, &y0);
    }
    int dx = x1-x0;
    int dy = y1-y0;
    int delta_error = abs(dy) * 2;
    int error = 0;
    int y = y0;
    for(int i = x0; i <= x1; i++){
        if(transposed){
            DRAW(y, i, color);
        }
        else{
            DRAW(i, y, color);
        }
        error += delta_error;
        if(error > dx){
            y += (y1>y0 ? 1 : -1);
            error -= dx * 2;
        }
    }
}

void render_obj(void* data, const char * filename, int height, int width){
    obj_parser_t obj = obj_parser_open(filename);
    if(obj == (void*)0){
        return;
    }
    int num_faces = obj_parser_faces_size(obj);
    for (int i = 0; i < num_faces; i++) {
        int * face = obj_parser_get_face(obj, i);
        for (int j = 0; j < 3; j++) {
            float * v1 = obj_parser_get_vertice(obj, face[j] -1);
            float * v2 = obj_parser_get_vertice(obj, face[(j+1) % 3] -1);
            //printf("%d = %p, %d = %p\n",face[j] -1, v1, face[(j+1) % 3] -1, v2);
            //printf("v1 : %f, %f\n", v1[0], v1[1]);
            //printf("v2 : %f, %f\n", v2[0], v2[1]);

            int x0 = (v1[0]+1.)*width/2.;
            int y0 = (v1[1]+1.)*height/2.;
            int x1 = (v2[0]+1.)*width/2.;
            int y1 = (v2[1]+1.)*height/2.;
            draw_line(data, x0, y0, x1, y1, 0xFFFFFF);
        }
    }
    obj_parser_destroy(obj);
}
