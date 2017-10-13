#ifndef TINY_RENDERER_H
#define TINY_RENDERER_H

void draw_line(void* data, int x0, int y0, int x1, int y1, int color);
void render_obj(void* data, const char * filename, int height, int width);
#endif
