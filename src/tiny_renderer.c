
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
    // 1st check if the line is steep
    //(the difference between y0 and y1 is greater than between x0 and x1)
    int transposed = 0;
    if(abs(v0->x - v1->x) < abs(v0->y - v1->y)){
        // then we transpose the line
        swap(&(v0->x), &(v0->y));
        swap(&(v1->x), &(v1->y));
        transposed = 1;
    }
    if(v1->x < v0->x){
        swap(&(v1->x), &(v0->x));
        swap(&(v1->y), &(v0->y));
    }
    int dx = v1->x - v0->x;
    int dy = v1->y - v0->y;
    int delta_error = abs(dy) * 2;
    int error = 0;
    int y = v0->y;
    for(int i = v0->x; i <= v1->x; i++){
        if(transposed){
            DRAW(y, i, color);
        }
        else{
            DRAW(i, y, color);
        }
        error += delta_error;
        if(error > dx){
            y += (v1->y > v0->y ? 1 : -1);
            error -= dx * 2;
        }
    }
}


void draw_triangle(void* data, int x0, int y0 ){
    x0;
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
