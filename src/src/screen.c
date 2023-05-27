#include <include/project.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include "raygui.h"

int chooseFormat(int* scene, flagsScene* flags) {
  int format = 0;
  int bmp = GuiButton((Rectangle){330, 225 + 30, 150, 30}, "BMP");
  int jpeg = GuiButton((Rectangle){510, 225 + 30, 150, 30}, "JPEG");
  if (bmp) {
    flags->is_screenshot_format = 1;
    *scene = SCENE_VIEW;
  } else if (jpeg) {
    flags->is_screenshot_format = 2;
    *scene = SCENE_VIEW;
  }
  return format;
}

int saveImg(flagsScene *flags, int* scene) {
  int screenCount = 0;
  char file[100] = {0};
  DIR* dir = opendir("screenshots");
  struct dirent *dp;
  if(!dir)
    mkdir("screenshots", 0777);
  else {
    while ((dp = readdir(dir)) != NULL) {
        if (strstr(dp->d_name, "screenshot") == dp->d_name) { 
            int num = atoi(dp->d_name + strlen("screenshot")); 
            if (num > screenCount) { 
                screenCount = num;
            }
        }
    }
    screenCount++;
    closedir(dir);
  }
  if (flags->is_screenshot_format == 1)
    sprintf(file, "screenshots/screenshot%d.bmp", screenCount);
  else
    sprintf(file, "screenshots/screenshot%d.jpg", screenCount);
  TakeScreenshot(file);
  flags->is_screenshot_format = 0;
  *scene = SCENE_SUCCESS;
  return 0;
}

int successDraw(int status, flagsScene flags){
  int i = 100;
  while(i) {
    initBack(flags);
    BeginDrawing();
    if (status == GIF_ERR || status == IMG_ERR)
    DrawText("Error when saved!", 260, 450 / 2 - 30, 45, RED);
    else 
    DrawText("Successfully saved!", 260, 450 / 2 - 30, 45, GREEN);
    EndDrawing();
    i--;
  }
  return 0;
}

int saveGif(int* gif_counter, flagsScene* flags, int* scene){
  int status = NONE;
  int a = 0;
  if(!*gif_counter) a = system("convert -v");
  if(a){
    status = GIF_ERR;
    *scene = SCENE_SUCCESS;
    flags->is_gif = 0;
  }
  else {
    DIR* dir = opendir("tmp");
    if(!dir){
      mkdir("tmp", 0777);
      *gif_counter = 300;
    } else if(*gif_counter == 0){
      int gifCount = 0;
      DIR* dir = opendir("gif");
      struct dirent *dp;
      if(!dir)
        mkdir("gif", 0777);
      else {
        while ((dp = readdir(dir)) != NULL) {
          if (strstr(dp->d_name, "mygif") == dp->d_name) {
              int num = atoi(dp->d_name + strlen("mygif")); 
              if (num > gifCount) { 
                gifCount = num; 
              }
          }
        }
        gifCount++;
        closedir(dir);
      }
      char command[700] = {0};
      sprintf(command, "convert -delay 10 -loop 0 tmp/50.jpg tmp/49.jpg tmp/48.jpg tmp/47.jpg tmp/46.jpg tmp/45.jpg tmp/44.jpg tmp/43.jpg tmp/42.jpg tmp/41.jpg tmp/40.jpg tmp/39.jpg tmp/38.jpg tmp/37.jpg tmp/36.jpg tmp/35.jpg tmp/34.jpg tmp/33.jpg tmp/32.jpg tmp/31.jpg tmp/30.jpg tmp/29.jpg tmp/28.jpg tmp/27.jpg tmp/26.jpg tmp/25.jpg tmp/24.jpg tmp/23.jpg tmp/22.jpg tmp/21.jpg tmp/20.jpg tmp/19.jpg tmp/18.jpg tmp/17.jpg tmp/16.jpg tmp/15.jpg tmp/14.jpg tmp/13.jpg tmp/12.jpg tmp/11.jpg tmp/10.jpg tmp/9.jpg tmp/8.jpg tmp/7.jpg tmp/6.jpg tmp/5.jpg tmp/4.jpg tmp/3.jpg tmp/2.jpg tmp/1.jpg -resize 640x480 -layers Optimize gif/mygif%d.gif", gifCount);
      status = system(command);
      if(status){
        status = GIF_ERR;
      } else {
        status = GIF_SUCCSESS;
      }
      system("rm -rf tmp");

      flags->is_gif = 0;
      *scene = SCENE_SUCCESS;
    } 
    if(*gif_counter%6 == 0 && flags->is_gif){
      int i = *gif_counter/6;
      char dest[20] = {0};
      sprintf(dest, "tmp/%d.jpg", i);
      TakeScreenshot(dest);
    }
    (*gif_counter)--;
  }
  return status;
}