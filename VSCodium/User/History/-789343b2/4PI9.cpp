/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

For a C++ project simply rename the file to .cpp and re-run the build script 

-- Copyright (c) 2020-2024 Jeffery Myers
--
--This software is provided "as-is", without any express or implied warranty. In no event 
--will the authors be held liable for any damages arising from the use of this software.

--Permission is granted to anyone to use this software for any purpose, including commercial 
--applications, and to alter it and redistribute it freely, subject to the following restrictions:

--  1. The origin of this software must not be misrepresented; you must not claim that you 
--  wrote the original software. If you use this software in a product, an acknowledgment 
--  in the product documentation would be appreciated but is not required.
--
--  2. Altered source versions must be plainly marked as such, and must not be misrepresented
--  as being the original software.
--
--  3. This notice may not be removed or altered from any source distribution.

*/

#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

int main () {
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI); // Tell the window to use vysnc and work on high DPI displays
	InitWindow(1280, 800, "Hello Raylib"); // Create the window and OpenGL context
	SearchAndSetResourceDir("resources"); // Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	Texture wabbit = LoadTexture("wabbit_alpha.png"); // Load a texture from the resources directory
	
	// run the loop untill the user presses ESCAPE or presses the Close button on the window
	while (!WindowShouldClose()) {
		BeginDrawing();
			ClearBackground(BLACK);
			DrawText("Hello Raylib niggers", 200,200,20,WHITE);
			DrawTexture(wabbit, 400, 200, WHITE);
		EndDrawing();
	}

	UnloadTexture(wabbit); // unload our texture so it can be cleaned up
	CloseWindow(); // destory the window and cleanup the OpenGL context
	return 0;
}