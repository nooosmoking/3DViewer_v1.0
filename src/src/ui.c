//
// Created by DERTY on 4/20/2023.
//
#include <include/project.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <include/terminal.h>
#include "gui_file_dialog.h"

#define STARTX 620
#define STARTY 0
#define STEP 20
#define YPOS(x) (STARTY + 10 + (STEP + 10) * (x - 1))
#define XPOS (STARTX + 20)
#define SLIDEXPOS (STARTX + 75)

extern int draw_dialog();

bool test_file(char filename[]){
  size_t len = strlen(filename);
  return len > 4 && !strcmp(filename+(len-4), ".obj");
}

elem* initGui(Vector3* move, Vector3* rotate, float* scale) {
  GuiLoadStyleTerminal();
  GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
  GuiSetStyle(CHECKBOX, TEXT_ALIGNMENT, 0);

  elem* element = calloc(1, 7 * sizeof(elem));
  element[0] = (elem){"Move x", &move->x, -10, 10, "0", 0};
  element[1] = (elem){"Move y", &move->y, -10, 10, "0", 0};
  element[2] = (elem){"Move z", &move->z, -10, 10, "0", 0};
  element[3] = (elem){"Rotate x", &rotate->x, -360, 360, "0", 0};
  element[4] = (elem){"Rotate z", &rotate->z, -360, 360, "0", 0};
  element[5] = (elem){"Rotate y", &rotate->y, -360, 360, "0", 0};
  element[6] = (elem){"Scale", scale, 0.1, 5, "0", 0};

  return element;
};

void textSlide(int pos, elem* element) {
  float tmpSlide = GuiSliderBar((Rectangle){SLIDEXPOS, YPOS(pos), 120, 20},
                                element->drawText, NULL, *(element->dest),
                                element->min, element->max);
  if (GuiTextBox((Rectangle){SLIDEXPOS + 130, YPOS(pos), 110, 20},
                 element->floatText, 29, element->editMode))
    element->editMode = !(element->editMode);
  float tmpText = validVal(element->floatText);
  if (tmpSlide != *(element->dest)) {
    *(element->dest) = tmpSlide;
    sprintf(element->floatText, "%.2f", *(element->dest));
  } else if (tmpText != *(element->dest)) {
    *(element->dest) = tmpText;
  }
}

int explBotton(float startX, float startY, float X, float Y, int isStart) {
  int openExpl = 0;
  if (isStart == 1)
    openExpl = GuiButton((Rectangle){startX, startY, X, Y}, "Open file");
  else
    openExpl = GuiButton((Rectangle){startX, startY, X, Y}, "Open new file");
  return openExpl;
}

void scene_loads_file(int* process, MeshObj* mesh, flagsScene *flags) {
  // Отвечает за начальный экран загрузку файла
  static int is_file = 0;
  BeginDrawing();
  if (IsFileDropped()) {
    FilePathList droppedFiles = LoadDroppedFiles();
    if (mesh->indices) free(mesh->indices);
    if (droppedFiles.count == 1) {
      TextCopy(mesh->path, droppedFiles.paths[0]);
      is_file = 1;
    }
    UnloadDroppedFiles(droppedFiles);  // Unload filepaths from memory
  } else if(GuiButton((Rectangle){400, 450 / 2 + 30, 150, 30}, "Open Explorer")) {
    is_file = draw_dialog(mesh->path);
  } else if (is_file && !test_file(mesh->path)){
    GuiGroupBox((Rectangle){400, 200 / 2 - 50, 12}, "Faile file");
    DrawText(mesh->path, 300, 250 / 2 - 50, 12, RED);
  }
    DrawText("Drop file", 380, 450 / 2 - 50, 45, RED);
    EndDrawing();
  if(is_file && test_file(mesh->path)) {
          mesh->indices =
          parser_obj(mesh->path, &(mesh->count_index), &(mesh->count_vertex));
          *process = SCENE_VIEW;
        is_file = false;
  }
}

void scene_draft(int* process, elem* element, MeshObj* mesh,
                 flagsScene* flags) {
  char vertexText[30] = {0};
  char facetText[30] = {0};
  DrawRectangle(STARTX, STARTY, 350, 470, BLACK);
  DrawLine(STARTX, STARTY, STARTX, 460, DARKGRAY);

  for (int i = 0; i < 7; i++) {
    textSlide(i + 1, &(element[i]));
  }

  flags->is_dropped = GuiCheckBox((Rectangle){XPOS + 170, YPOS(8), 20, STEP},
                                  "Dropped line", flags->is_dropped);

  if (GuiCheckBox((Rectangle){XPOS + 148, YPOS(9), 20, STEP}, "Projection:    Parallel",
                  flags->is_view_parale)) {
    flags->is_view_parale = 1;
    flags->is_view_central = 0;
  }

  if (GuiCheckBox((Rectangle){XPOS + 255, YPOS(9), 20, STEP}, "Central",
                  flags->is_view_central)) {
    flags->is_view_parale = 0;
    flags->is_view_central = 1;
  }
  if (GuiCheckBox((Rectangle){XPOS + 135, YPOS(10), 20, STEP}, "Background:  Black",
                  flags->is_color == 1)) {
    flags->is_color = 1;
  }
  if (GuiCheckBox((Rectangle){XPOS + 203, YPOS(10), 20, STEP}, "Gray",
                  flags->is_color == 2)) {
    flags->is_color = 2;
  }
  if (GuiCheckBox((Rectangle){XPOS + 275, YPOS(10), 20, STEP}, "Violet",
                  flags->is_color == 3)) {
    flags->is_color = 3;
  }
  if (GuiButton((Rectangle){XPOS + 30, YPOS(11), 100, 25}, "Screenshot")) {
    *process = SCENE_FORMAT;
  }
  if (GuiButton((Rectangle){XPOS + 150, YPOS(11), 100, 25}, "GIF")) {
    flags->is_gif = 1;
  }

  DrawText(findFilename(mesh->path), XPOS + 20, YPOS(12), 20, GREEN);

  sprintf(vertexText, "Count of vertex: %d", mesh->count_vertex);
  sprintf(facetText, "Count of facet: %d", mesh->count_index);

  DrawText(vertexText, XPOS + 20, YPOS(13), 20, GREEN);
  DrawText(facetText, XPOS + 20, YPOS(14), 20, GREEN);

  if (explBotton(XPOS + 10, YPOS(15), 260, 25, 0)) {
    *mesh = initMesh();
    *process = SCENE_START;
  }
}

void initBack(flagsScene flags){
  switch (flags.is_color)
    {
    case 1:
      ClearBackground(BLACK);
      break;
    case 2:
      ClearBackground(GRAY);
      break;
    case 3:
      ClearBackground(VIOLET);
      break;
    }

}

