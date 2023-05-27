//
// Created by DERTY on 4/20/2023.
//
#include <include/project.h>
MeshObj initMesh() {
  MeshObj mesh = {0};
  mesh.transform = loads_tr();
  return mesh;
}

int fgetsn(char buff[], int max, FILE* f) {
  char c = getc(f);
  for (int i = 0; i < max && c != '\n' && c != '\0' && c != EOF;
       ++i, c = getc(f))
    buff[i] = c;
  if (c == EOF) c = 0;
  return c;
}

Vectori2 count_obj(char filename[]) {
  /**
   * @brief Возвращяет структуру со значениями
   * x = vertext
   * y = facet
   */
  Vectori2 v = {0};
  char line[100];
  FILE* file = fopen(filename, "r");
  if (file == NULL)
    fprintf(stderr, "Could not read file: %s\n", filename);
  else
    while (fgetsn(line, 100, file))
      v.x += !strncmp(line, "v ", 2), v.y += !strncmp(line, "f ", 2);
  return v;
}

int chrbrk(char simb, char* str) {
  char* p;
  int err = 1;
  for (p = str; *p != '\0' && err; ++p) {
    if (simb == *p) err = 0;
  }
  return err;
}

double validVal(char* input) {
  char numbs[] = {'1', '2', '3', '4', '5', '6', '7',
                  '8', '9', '0', '.', '-', '\0'};

  int start = 1;
  char* p = input;
  int dot = 0;
  double res = 0;
  int err = 0;
  while (*(p) && !err) {
    if (chrbrk(*p, numbs)) err++;
    if (*p == '.' && dot == 0)
      dot++;
    else if (*p == '.' && dot > 0)
      err++;
    else if (*p == '-' && !start) {
      err++;
    }
    start = 0;
    p++;
  }
  if (!err)
    sscanf(input, "%lf", &res);
  else
    res = 0;

  return res;
}

char* findFilename(char* filePaths) {
  char* p = filePaths;
  char* slash = NULL;
  while (*p != 0) {
    if (*p == '/') slash = p;
    p++;
  }
  return ++slash;
}

Vector3 scaleV(Vector3 v, float scale) {
  v.x = v.x * scale;
  v.y = v.y * scale;
  v.z = v.z * scale;
  return v;
}

Vector3 moveV(Vector3 v, Vector3 move) {
  v.x = v.x + move.x;
  v.y = v.y + move.y;
  v.z = v.z + move.z;
  return v;
}
Vector3 centerV(Vector3 v1, Vector3 v2) {
  Vector3 v = {
      (v1.x + v2.x) / 2,
      (v1.y + v2.y) / 2,
      (v1.z + v2.z) / 2,
  };
  return v;
}

void draw_model(MeshObj* mesh, flagsScene flag) {
  for (int i = 0; i < mesh->count_index; i++) {
    Vector3 v1 = moveV(scaleV(oper(mesh->indices[i].v1, mesh->transform.rotate),
                              mesh->transform.scale),
                       mesh->transform.move);
    Vector3 v2 = moveV(scaleV(oper(mesh->indices[i].v2, mesh->transform.rotate),
                              mesh->transform.scale),
                       mesh->transform.move);
    Vector3 v3 = moveV(scaleV(oper(mesh->indices[i].v3, mesh->transform.rotate),
                              mesh->transform.scale),
                       mesh->transform.move);

    Vector3 vc12 = centerV(v1, v2);
    Vector3 vcvc122 = centerV(vc12, v2);
    Vector3 vcvc221 = centerV(vc12, v1);
    Vector3 vc23 = centerV(v2, v3);
    Vector3 vcvc232 = centerV(vc23, v2);
    Vector3 vcvc233 = centerV(vc23, v3);

    if (!flag.is_dropped) {
      DrawLine3D(v1, v2, GREEN);
      DrawLine3D(v2, v3, GREEN);
    } else {
      DrawLine3D(v1, vcvc122, GREEN);
      DrawLine3D(vcvc221, v2, GREEN);
      DrawLine3D(v2, vcvc232, GREEN);
      DrawLine3D(vcvc233, v3, GREEN);
    }
  }
}
