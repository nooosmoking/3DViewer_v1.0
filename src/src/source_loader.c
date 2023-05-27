#include <stdio.h>
#include <stdlib.h>
#include <include/project.h>

void init(transform3d tr){
    char *init = "move = %f %f %f\nrotate = %f %f %f\nscale = %f\n";
    FILE* f = fopen("./ini.txt", "w");
    fprintf(f, init, tr.move.x,tr.move.y,tr.move.z, tr.rotate.x,tr.rotate.y,tr.rotate.z, tr.scale);
    fclose(f);
}

transform3d loads_tr(){
  FILE* file = fopen("./ini.txt", "r");
  char line[512];
  transform3d tr = {0};
  if(file == NULL) {
    fprintf(stderr, "Could not settings file");
    init(tr);
  } else {
    while (fgets(line, 100, file)) {
    if (strncmp(line, "move ", 6) == 0) {
      int match =
          sscanf(line, "move = %f %f %f", &tr.move.x,
                 &tr.move.y, &tr.move.z);
      if (match != 3) tr.move = (Vector3) {0};
    } else if (strncmp(line, "rotate ", 8) == 0) {
      int match =
          sscanf(line, "rotate = %f %f %f", &tr.rotate.x,
                 &tr.rotate.y, &tr.rotate.z);
      if (match != 3) tr.rotate = (Vector3) {0};
    } else if (strncmp(line, "scale ", 7) == 0) {
      int match =
          sscanf(line, "scale = %f", &tr.scale);
      if (match != 3) tr.rotate = (Vector3) {0};
    } 
  }
}
  return tr;
}
void save_tr(transform3d tr){
    init(tr);
}