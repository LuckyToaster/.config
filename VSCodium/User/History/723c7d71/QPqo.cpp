#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include "screen.hpp"
#include "camera.hpp"

int main() {
    Screen screen = new Screen("Learning OpenGL", 1200, 600);  
    Camera c = new Camera();
    return 0;
}