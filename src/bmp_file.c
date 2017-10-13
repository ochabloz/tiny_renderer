#include "bmp_file.h"
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BITS_PER_PIXELS 24

struct bmp_file_struct{
    int height, width;
    int padding;
    uint32_t * pixels;
    uint32_t size;
}bmp_file_struct;

bmp_file_t bmp_file_create(int width, int height){
    bmp_file_t f = malloc(sizeof(bmp_file_struct));
    f->size =  width * height;
    f->pixels = malloc(sizeof(uint32_t) * f->size);
    memset(f->pixels, 0x00, f->size * sizeof(uint32_t));
    f->height = height;
    f->width = width;
    int pixels_row_size = (BITS_PER_PIXELS / 8) * width;
    f->padding = 0;
    while((pixels_row_size + f->padding) % 4){
        f->padding++;
    }
    return f;
}

void bmp_file_delete(bmp_file_t f){
    free(f->pixels);
    free(f);
}


void write_header(int width, int height, int fd){
    uint8_t header[14+40] = {0};
    int pixels_row_size = (BITS_PER_PIXELS / 8) * width;
    int padding = 0;
    //
    while((pixels_row_size + padding) % 4){
        padding++;
    }
    int bitmap_data_size = (pixels_row_size + padding) * height;
    int bmp_total_size = 14 + 40 + bitmap_data_size;
    // BMP Header
    header[0] = 'B';
    header[1] = 'M';
    memcpy(header + 2, &bmp_total_size, sizeof(int));
    int tmp = 14 + 40;  // offset
    memcpy(header + 0xA, &tmp, sizeof(int));
    // end of BMP Header

    // DIB Header
    tmp = 40;  // DIB header size
    memcpy(header + 0xE, &tmp, sizeof(int));
    memcpy(header + 0x12, &width, 4);
    memcpy(header + 0x16, &height, 4);
    tmp = 1;  // 1 plane
    memcpy(header + 0x1A, &tmp, 2);
    tmp = BITS_PER_PIXELS;
    memcpy(header + 0x1C, &tmp, 2);

    memcpy(header + 0x22, &bitmap_data_size, 4); //size of the raw bitmap data

    tmp = 2835;  // nb pixels / meters
    memcpy(header + 0x26, &tmp, sizeof(int));
    memcpy(header + 0x2A, &tmp, sizeof(int));
    write(fd, header, 40 + 14);
}


int bmp_file_save(bmp_file_t bmp, const char * filename){
    int fd = open(filename, O_CREAT | O_WRONLY);
    write_header(bmp->width, bmp->height, fd);
    // now write pixels data
    uint8_t * buffer = malloc(bmp->height * bmp->width * (BITS_PER_PIXELS /8));
    for(int i = 0; i < bmp->height; i++){
        for(int j = 0; j< bmp->width;j++){
            memcpy(buffer + (j + i* bmp->width) * 3, bmp->pixels + j + i* bmp->width, BITS_PER_PIXELS / 8);
        }
    }
    write(fd, buffer,bmp->height * bmp->width * (BITS_PER_PIXELS /8));
    close(fd);
    return 0;
}


void bmp_file_write(bmp_file_t file, uint32_t x, uint32_t y, uint32_t color){
    if(x >= file->width || y >= file->height){
        return;
    }
    file->pixels[file->width * y + x] = color;
}


uint32_t bmp_file_read(bmp_file_t file, uint32_t x, uint32_t y){
    if(x >= file->width || y >= file->height){
        return 0x00;
    }
    return file->pixels[file->width*y + x];
}
