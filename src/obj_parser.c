#include "obj_parser.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "linked_list.h"

struct obj_parser{
    linked_list_t list_vertices, list_faces;
} obj_parser;

int get_pos_of_next(const char * str, char c){
    int i = 0;
    while (str[i] != c && str[i] != '\n'){i++;}
    return i;
}

obj_parser_t obj_parser_open(const char * filename){
    FILE* fp = fopen(filename, "r");
    if(fp != NULL){
        obj_parser_t new_parser = malloc(sizeof(obj_parser));
        new_parser->list_vertices = linked_list_create();
        new_parser->list_faces = linked_list_create();

        char *line = NULL;
        size_t linecap = 0;
        ssize_t line_len;
        while ((line_len = getline(&line, &linecap, fp)) != EOF){
            if(line[0] == '#'){ // comment
                //printf("comment : %s\n",line);
            }
            else if (line_len > 1){
                if(line[0] == 'v' && line[1] == ' '){
                    float *vertice = malloc(3 * sizeof(float));
                    int offset = 2;
                    for(int i = 0; i < 3; i++){
                        vertice[i] = atof(line + offset);
                        offset += 1 + get_pos_of_next(line + offset, ' ');
                    }
                    linked_list_add(new_parser->list_vertices, vertice);
                }
                else if(line[0] == 'f' && line[1] == ' '){
                    int *face = malloc(3 * sizeof(int));;

                    int offset = 2;
                    for(int i = 0; i < 3; i++){
                        face[i] = atoi(line + offset);
                        offset += 1 + get_pos_of_next(line + offset, ' ');
                    }
                    linked_list_add(new_parser->list_faces, face);
                    //printf("new parsed face : %d, %d, %d\n",face[0], face[1], face[2]);
                }
            }
        }

        fclose(fp);
        return new_parser;
    }
    return NULL;
}

int obj_parser_vertices_size(obj_parser_t obj){
    return linked_list_size(obj->list_vertices);
}

int obj_parser_faces_size(obj_parser_t obj){
    return linked_list_size(obj->list_faces);
}

float * obj_parser_get_vertice(obj_parser_t obj, uint32_t num){
    return linked_list_get(obj->list_vertices, num);
}

int * obj_parser_get_face(obj_parser_t obj, uint32_t num){
    return linked_list_get(obj->list_faces, num);
}

void obj_parser_destroy(obj_parser_t obj){
    int nb = linked_list_size(obj->list_vertices);
    for(int i = 0; i < nb; i++){
        float* item = linked_list_get(obj->list_vertices, i);
        free(item);
    }
    linked_list_delete(obj->list_vertices);
    
    nb = linked_list_size(obj->list_faces);
    for(int i = 0; i < nb; i++){
        float* item = linked_list_get(obj->list_faces, i);
        free(item);
    }
    linked_list_delete(obj->list_faces);
    free(obj);
}
