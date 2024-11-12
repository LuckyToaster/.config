#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "camera.hpp"
#include "screen.hpp"

int main() {
    Screen screen = Screen("Learning OpenGL", 1200, 600);  
    Camera c = Camera::getDefault();

    while (screen.input(c)) {
        screen.update();
        screen.clear();
    }
    return 0;
}