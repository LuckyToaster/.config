#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include <iostream>

#include "screen.hpp"
#include "camera.hpp"

int main() {
    Screen screen = new Screen("Learning OpenGL", 1200, 600);  
    Camera c = Camera::getDefault();

    while (screen.input(c)) {
        screen.update();
        screen.clear();
    }
    return 0;
}