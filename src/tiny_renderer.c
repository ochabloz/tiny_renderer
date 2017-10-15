
#include "tiny_renderer.h"
#include "bmp_file.h"
#include "obj_parser.h"
#include <stdio.h>
#include <stdlib.h>

#define DRAW(x, y, color) bmp_file_write((bmp_file_t)data, x, y, color)


struct vec2i_struct{
    int x;
    int y;
}vec2i_struct;


vec2i_t vec2i_create(int x, int y){
    vec2i_t new_v = malloc(sizeof(vec2i_struct));
    new_v->x = x;
    new_v->y = y;
    return new_v;
}

void vec2i_modify(vec2i_t obj, int x, int y){
    obj->x = x;
    obj->y = y;
}

void vec2i_destroy(vec2i_t obj){
    free(obj);
}

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

void draw_line(void* data, vec2i_t v0, vec2i_t v1, int color){
    int x0 = v0->x;
    int x1 = v1->x;
    int y0 = v0->y;
    int y1 = v1->y;
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


void draw_triangle(void* data, vec2i_t * t, int color){
    draw_line(data, t[0], t[1], color);
    draw_line(data, t[1], t[2], color);
    draw_line(data, t[2], t[0], color);
}

void render_obj(void* data, const char * filename, int height, int width){
    obj_parser_t obj = obj_parser_open(filename);
    if(obj == (void*)0){
        return;
    }
    vec2i_t vector0 = vec2i_create(0, 0);
    vec2i_t vector1 = vec2i_create(0, 0);

    int num_faces = obj_parser_faces_size(obj);
    for (int i = 0; i < num_faces; i++) {
        int * face = obj_parser_get_face(obj, i);
        for (int j = 0; j < 3; j++) {
            float * v1 = obj_parser_get_vertice(obj, face[j] -1);
            float * v2 = obj_parser_get_vertice(obj, face[(j+1) % 3] -1);
            vec2i_modify(vector0, (v1[0]+1.)*width/2., (v1[1]+1.)*height/2.);
            vec2i_modify(vector1, (v2[0]+1.)*width/2., (v2[1]+1.)*height/2.);
            draw_line(data, vector0, vector1, 0xFFFFFF);
        }
    }
    vec2i_destroy(vector0);
    vec2i_destroy(vector1);
    obj_parser_destroy(obj);
}
