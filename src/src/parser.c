//
// Created by DERTY on 4/20/2023.
//

#include <include/project.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 100000


facet *parser_obj(char filename[], int *indices_count, int *vertex_count) {
  Vectori2 v = count_obj(filename);
  Vector3 *vertices = 0;
  facet *indices = 0;
  FILE *file = fopen(filename, "r");
  if(file == NULL) {
    fprintf(stderr, "Could not read file: %s\n", filename);
  } else {
  vertices = (Vector3 *)calloc(1, v.x * sizeof(Vector3));
  indices = (facet *)calloc(1, v.y * sizeof(facet));

  int facet_count = 0;
  char line[100] = {0};
  while (fgets(line, 100, file)) {
    if (strncmp(line, "v ", 2) == 0) {
      int match =
          sscanf(line, "v %f %f %f", &vertices[*vertex_count].x,
                 &vertices[*vertex_count].y, &vertices[*vertex_count].z);
      if (match == 3) (*vertex_count)++;
    } else if ((strncmp(line, "vt ", 3) == 0) ||
               (strncmp(line, "vn ", 3) == 0) || (strncmp(line, "#", 1) == 0)) {
    } else if (strncmp(line, "f", 1) == 0 && *vertex_count > 0) {
      unsigned int v1, v2, v3, vt1, vt2, vt3, vn1, vn2, vn3;
      int matches = sscanf(line, "f %u/%u/%u %u/%u/%u %u/%u/%u\n", &v1, &vt1,
                           &vn1, &v2, &vt2, &vn2, &v3, &vt3, &vn3);
      if (matches != 9) {
        matches = sscanf(line, "f %u//%u %u//%u %u//%u\n", &v1, &vn1, &v2, &vn2,
                         &v3, &vn3);

        if (matches != 6) {
          matches = sscanf(line, "f %u %u %u\n", &v1, &v2, &v3);
          if (matches != 3) {
            fprintf(stderr,
                "Не удалось прочитать f строку. Вместо этого получено "
                "значение %d.\n",
                matches);
            char *p = line;
            while (*p != 0) {
              *p = 0;
              p++;
            }
            continue;
          }
        }
      }
      /* Индексы в OBJ начинаются с 1, в Си - с 0 */
      if (v1 < MAX_VERTEX && v2 < MAX_VERTEX && v3 < MAX_VERTEX) {
        indices[facet_count].v1 = vertices[v1 - 1];
        indices[facet_count].v2 = vertices[v2 - 1];
        indices[facet_count].v3 = vertices[v3 - 1];
        facet_count++;
      }
    } else {
      // fprintf(stderr, "FAIL STRING: %s\n", line);
    }
    char *p = line;
    while (*p != 0) {
      *p = 0;
      p++;
    }
  }
  if (v.x) free(vertices);
  fclose(file);
  *indices_count = facet_count;
  }
  return indices;
}