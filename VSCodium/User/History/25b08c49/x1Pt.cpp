#include <iostream>
#include "raylib.h"

void handle_player_and_camera(Rectangle &p, Camera2D &c) {
    // player movement
    if (IsKeyDown(KEY_RIGHT)) p.x += 2;
    if (IsKeyDown(KEY_LEFT)) p.x -= 2;
    if (IsKeyDown(KEY_UP)) p.y -= 2;
    if (IsKeyDown(KEY_DOWN)) p.y += 2;

    c.target = (Vector2) { p.x, p.y }; // camera follows player

    if (IsKeyDown(KEY_A)) c.rotation++;
    if (IsKeyDown(KEY_D)) c.rotation--;

    // Camera zoom controls
    c.zoom += ((float) GetMouseWheelMove() * 0.05f);
    if (c.zoom > 3.0f) c.zoom = 3.0f;
    else if (c.zoom < 0.1f) c.zoom = 0.1f;

    // Camera reset (zoom and rotation)
    if (IsKeyPressed(KEY_R)) {
        c.zoom = 1.0f;
        c.rotation = 0.0f;
    }
}


int main(void) {
    const int screenWidth = 1600;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);               

    Rectangle player = { 400, 280, 40, 40 };

    Camera2D camera = { 0 };
    camera.target = (Vector2) { player.x + 20.0f, player.y + 20.0f };
    camera.offset = (Vector2) { screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while (!WindowShouldClose()) {
        handle_player_and_camera(player, camera);
        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode2D(camera);
                DrawRectangle(-6000, 320, 13000, 8000, DARKGRAY); // the floor
                DrawRectangleRec(player, RED);
                DrawLine((int) camera.target.x, -screenHeight * 10, (int) camera.target.x, screenHeight * 10, GREEN);
                DrawLine(-screenWidth * 10, (int) camera.target.y, screenWidth * 10, (int) camera.target.y, GREEN);
            EndMode2D();

            DrawRectangle(0, 0, screenWidth, 5, RED);
            DrawRectangle(0, 5, 5, screenHeight - 10, RED);
            DrawRectangle(screenWidth - 5, 5, 5, screenHeight - 10, RED);
            DrawRectangle(0, screenHeight - 5, screenWidth, 5, RED);
            DrawRectangle( 10, 10, 400, 210, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines( 10, 10, 400, 210, BLUE);

            DrawText("Free 2d camera controls:", 20, 20, 20, BLACK);
            DrawText("- Right/Left to move Offset", 40, 45, 20, DARKGRAY);
            DrawText("- Mouse Wheel to Zoom in-out", 40, 70, 20, DARKGRAY);
            DrawText("- A / S to Rotate", 40, 95, 20, DARKGRAY);
            DrawText("- R to reset Zoom and Rotation", 40, 120, 20, DARKGRAY);
            DrawText(TextFormat("Player x: %02f", player.x), 20, 145, 20, BLACK);
            DrawText(TextFormat("Player y: %02f", player.y), 20, 170, 20, BLACK);
            DrawText(TextFormat("FPS: %02i", GetFPS()), 20, 195, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();        
    return 0;
}
