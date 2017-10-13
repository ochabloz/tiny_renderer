#ifndef BMP_FILE_H
#define BMP_FILE_H
#include <stdint.h>

typedef struct bmp_file_struct * bmp_file_t;

bmp_file_t bmp_file_create(int x, int y);
void bmp_file_delete(bmp_file_t f);
void bmp_file_write(bmp_file_t file, uint32_t x, uint32_t y, uint32_t color);
uint32_t bmp_file_read(bmp_file_t f, uint32_t x, uint32_t y);
int bmp_file_save(bmp_file_t bmp, const char * filename);

#endif
