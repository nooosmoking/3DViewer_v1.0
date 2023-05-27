#include <include/project.h>
#define GUI_FILE_DIALOG_IMPLEMENTATION
#include "gui_file_dialog.h"


int draw_dialog(char *fileNameToLoad){
        GuiFileDialogState fileDialogState = InitGuiFileDialog(GetWorkingDirectory());
        fileDialogState.windowActive = true;
        while(fileDialogState.windowActive){
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        BeginDrawing();
            GuiFileDialog(&fileDialogState);
        EndDrawing();
        };
        strcpy(fileNameToLoad, TextFormat("%s/%s", fileDialogState.dirPathText, fileDialogState.fileNameText));
        return fileDialogState.SelectFilePressed;
} 