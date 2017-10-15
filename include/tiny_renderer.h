#ifndef TINY_RENDERER_H
#define TINY_RENDERER_H


typedef struct vec2i_struct * vec2i_t;

vec2i_t vec2i_create(int x, int y);
void vec2i_modify(vec2i_t obj, int x, int y);
void vec2i_destroy(vec2i_t obj);

void draw_line(void* data, vec2i_t v0, vec2i_t v1, int color);
void render_obj(void* data, const char * filename, int height, int width);
#endif
