//
// Created by DERTY on 4/20/2023.
//

#ifndef EXAMPLE_PROJECT_H
#define EXAMPLE_PROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

enum {
  SCENE_START,
  SCENE_VIEW,
  SCENE_FORMAT,
  SCENE_SUCCESS
};

enum {
  NONE,
  IMG_SUCCSESS,
  IMG_ERR,
  GIF_SUCCSESS,
  GIF_ERR,
};

typedef struct elem {
  char drawText[20];
  float* dest;
  float min;
  float max;
  char floatText[30];
  int editMode;
}elem;

typedef struct Vectori2 {
    int x;                // Vector x component
    int y;                // Vector y component
} Vectori2;

typedef struct facet {
    Vector3 v1, v2, v3;
} facet;

typedef struct transform3d {
    Vector3 move;
    Vector3 rotate;
    float scale;
} transform3d;

typedef union {
    struct {
        unsigned int is_dropped: 1;
        unsigned int is_view_parale: 1;
        unsigned int is_view_central: 1;
        unsigned int is_gif:1;
        unsigned int is_screenshot_format:2;
        unsigned int is_color:3;
    };
    unsigned short int flags;
} flagsScene;

typedef struct {
  facet* indices;
  int count_vertex; 
  int count_index;
  transform3d transform;
  char path[1024];
  Color lineColor;
}MeshObj;

MeshObj initMesh();
facet *parser_obj(char filename[], int *indices_count, int* vertex_count);
void draw_model(MeshObj *mesh, flagsScene flag);
Vector3 oper(Vector3 vec, Vector3 rotate);
void draw_gui(Vector3 *opt,  elem* element, int* openExpl, char* filePaths, int count_index, int count_vertex, int* screenshot, int* gif);
elem* initGui(Vector3 *move, Vector3 *rotate, float* scale);
int explBotton(float startX, float startY, float X, float Y, int isStart);
int chooseFormat(int* scene, flagsScene *flags);
int saveImg(flagsScene *flags, int* scene);
double validVal(char* input);
char* findFilename(char* filePaths);
Vectori2 count_obj(char filename[]);
void scene_loads_file(int* process, MeshObj* mesh, flagsScene *flags);
void scene_draft(int *process, elem* element, MeshObj *mesh, flagsScene *flags);
int successDraw(int status, flagsScene flags);
int saveGif(int* gif_counter, flagsScene* flags, int* scene);
void initBack(flagsScene flags);
void save_tr(transform3d tr);
transform3d loads_tr();
#endif //EXAMPLE_PROJECT_H

