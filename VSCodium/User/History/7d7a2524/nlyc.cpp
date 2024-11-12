#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

/*
WHY GLAD? even though that i can use opengl functions by importing opengl (SDL2/SDL_opengl.h in this case) 
a function that is only available on a certain opengl version or that is simply not supported by the 
graphics driver might be called, and glad will load all the opengl functions that are supported 
the driver and the opengl version because it will load the definitions in a 'glad.h' file.
This facilitates working with opengl because we don't have to do manual checking to see if something will work 
and we will have a list of all the functions we can call
*/
#include "glad/glad.h" 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "camera.hpp"
#include "projector.hpp"
#include "shape.hpp"
#include "screen.hpp"

using std::cout;
using std::endl;
using std::chrono::milliseconds;
using std::this_thread::sleep_for;
//using std::chrono::steady_clock;
//using std::chrono::duration;


int main() {
    Screen screen("Muh sooper dooper fast renderer", 1200, 600);
    Camera c = Camera::getDefault();
    vec3 surface(400.0f, 200.0f, 200.0f);
    Shape shape = Shape::getCube();

    std::chrono::steady_clock::time_point lastFrameTime = std::chrono::steady_clock::now();
    double deltaTime = 0.0; // To store the time difference between frames

    while (screen.input(c)) {
        for (auto i = 0; i < shape.vertices.size(); i++) {
            shape.vertices[i] = rotateXYZ(shape.vertices[i], 2.0f, 2.0f, 2.0f);
            shape.projected[i] = project(shape.vertices[i], c.pos, c.orientation, c.surface);
        }

        vector<GLfloat> projected = shape.getProjectedAsGLfloat();
        screen.draw(projected);
        screen.update();
        sleep_for(milliseconds(16)); // ~60hz or use SDL_Delay(16);
        screen.clear();

        std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
        deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - lastFrameTime).count();
        lastFrameTime = currentTime;
    } 
    return 0;
}