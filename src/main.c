#include <include/project.h>
#include <dirent.h>
#include <sys/stat.h>

int main() {
  facet* indices = calloc(1, sizeof(facet) * 1000000);

  Camera camera = {0};
  camera.position = (Vector3){5.0f, 10.0f, 15.0f};  // Camera position
  camera.target = (Vector3){5.0f, 3.0f, 0.0f};      // Camera looking at point
  camera.up = (Vector3){0.0f, 1.0f,
                        0.0f};  // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;          // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE;  // Camera mode type

  int scene = 0;
  
  MeshObj mesh = initMesh();
  InitWindow(950, 460, "My Window");
  SetTargetFPS(60);

  Color color = GREEN;
  flagsScene flags = {0};
  flags.is_view_central = 1;
  flags.is_color = 1;
  int gif_counter = 0;
  int status = NONE;

  elem* element = initGui(&mesh.transform.move, &mesh.transform.rotate,
                          &mesh.transform.scale);
  while (!WindowShouldClose()) {
    initBack(flags);
    switch (scene) {
      case SCENE_START:
        scene_loads_file(&scene, &mesh, &flags);
        break;
      case SCENE_FORMAT:
        BeginDrawing();
        DrawText("Choose format", 330, 450 / 2 - 50, 45, GREEN);
        chooseFormat(&scene, &flags);
        EndDrawing();
        break;
      case SCENE_VIEW:
        BeginDrawing();
        BeginMode3D(camera);
        draw_model(&mesh, flags);
        EndMode3D();
        if (flags.is_screenshot_format) {
          status = saveImg(&flags, &scene);
        } else if(flags.is_gif){
          status = saveGif(&gif_counter, &flags, &scene);
        }
        scene_draft(&scene, element, &mesh, &flags);
        EndDrawing();
        break;
      case SCENE_SUCCESS:
        status = successDraw(status, flags);
        scene = SCENE_VIEW;
        break;
      default:
        scene_draft(&scene, element, &mesh, &flags);
        break;
    }
    if (flags.is_view_central)
    {
      camera.projection = CAMERA_PERSPECTIVE;
    } else if (flags.is_view_parale) {
            camera.projection = CAMERA_ORTHOGRAPHIC;
    }
    save_tr(mesh.transform);
  }
  CloseWindow();
  free(indices);
  free(element);
  return 0;
}