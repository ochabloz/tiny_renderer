
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

void vec2i_swap(vec2i_t a, vec2i_t b){ // a améliorer en utilisant les pointeurs
    struct vec2i_struct c = {a->x, a->y};
    a->x = b->x;
    a->y = b->y;
    b->x = c.x;
    b->y = c.y;
}

void draw_triangle(void* data, vec2i_t * t, int color){
    // 1) sort vertices from lower (t0) to upper (t2)
    if(t[0]->y > t[1]->y) vec2i_swap(t[0], t[1]);
    if(t[0]->y > t[2]->y) vec2i_swap(t[0], t[2]);
    if(t[1]->y > t[2]->y) vec2i_swap(t[1], t[2]);

    int total_height = t[2]->y - t[0]->y;
    int seg_height = t[1]->y - t[0]->y + 1;
    for(int y = t[0]->y; y < t[1]->y; y++){
        float alpha = (float)(y-t[0]->y)/total_height;
        float beta  = (float)(y-t[0]->y)/seg_height;
        int x_alpha = t[0]->x + (t[2]->x - t[0]->x) * alpha;
        int x_beta  = t[0]->x + (t[1]->x - t[0]->x) * beta;
        if(x_alpha > x_beta) swap(&x_alpha, &x_beta);
        for(int x = x_alpha; x <= x_beta; x++){
            DRAW(x, y, color);
        }
    }

    seg_height = t[2]->y - t[1]->y + 1;
    for(int y = t[1]->y; y < t[2]->y; y++){
        float alpha = (float)(y-t[0]->y)/total_height;
        float beta  = (float)(y-t[1]->y)/seg_height;
        int x_alpha = t[0]->x + (t[2]->x - t[0]->x) * alpha;
        int x_beta  = t[1]->x + (t[2]->x - t[1]->x) * beta;
        if(x_alpha > x_beta) swap(&x_alpha, &x_beta);
        for(int x = x_alpha; x <= x_beta; x++){
            DRAW(x, y, color);
        }
    }
}

void render_obj(void* data, const char * filename, int height, int width){
    obj_parser_t obj = obj_parser_open(filename);
    if(obj == (void*)0){
        return;
    }
    vec2i_t vector[] = {vec2i_create(0, 0), vec2i_create(0, 0), vec2i_create(0, 0)};

    int num_faces = obj_parser_faces_size(obj);
    for (int i = 0; i < num_faces; i++) {
        int * face = obj_parser_get_face(obj, i);
        float * v1 = obj_parser_get_vertice(obj, face[0] -1);
        float * v2 = obj_parser_get_vertice(obj, face[1] -1);
        float * v3 = obj_parser_get_vertice(obj, face[2] -1);
        vec2i_modify(vector[0], (v1[0]+1.)*width/2., (v1[1]+1.)*height/2.);
        vec2i_modify(vector[1], (v2[0]+1.)*width/2., (v2[1]+1.)*height/2.);
        vec2i_modify(vector[2], (v3[0]+1.)*width/2., (v3[1]+1.)*height/2.);
        draw_triangle(data, vector, 0x010101 + (i << 8) + (i << 16) + i);
    }
    vec2i_destroy(vector[0]);
    vec2i_destroy(vector[1]);
    vec2i_destroy(vector[2]);
    obj_parser_destroy(obj);
}
