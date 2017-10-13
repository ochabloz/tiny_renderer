#ifndef OBJ_PARSER_H
#define OBJ_PARSER_H

#include <stdint.h>

typedef struct obj_parser * obj_parser_t;

obj_parser_t obj_parser_open(const char * filename);
int obj_parser_faces_size(obj_parser_t obj);
int obj_parser_vertices_size(obj_parser_t obj);
float * obj_parser_get_vertice(obj_parser_t obj, uint32_t num);
int * obj_parser_get_face(obj_parser_t obj, uint32_t num);
void obj_parser_destroy(obj_parser_t obj);
#endif
