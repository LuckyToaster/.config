#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "camera.hpp"
#include "screen.hpp"
#include "projector.hpp"
#include "shape.hpp"

using std::cout;
using std::endl;
using std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::duration;
using std::chrono::duration_cast;


int main() {
    Screen screen("Muh sooper dooper fast renderer", 1200, 600);
    Camera c = Camera::getDefault();
    vec3 surface(400.0f, 200.0f, 200.0f);
    Shape shape = Shape::getCube();

    double delta_t = 0.0; 
    time_point start = steady_clock::now();

    while (screen.input(c)) {
        time_point end = steady_clock::now();
        delta_t = duration_cast<duration<double>>(end - start).count();
        start = end;

        for (auto i = 0; i < shape.vertices.size(); i++) {
            shape.vertices[i] = rotateXYZ(shape.vertices[i], 2.0f, 2.0f, 2.0f);
            shape.projected[i] = project(shape.vertices[i], c.pos, c.orientation, c.surface);
            //cout << "vertex " << i << ": " << shape.vertices[i].x << endl;
            //cout << "projected vertex " << i << ": " << shape.projected[i].x << endl;
        }

        vector<GLfloat> projected = shape.getProjectedAsGLfloat();
        screen.draw(projected);
        screen.update();
        screen.clear();
        start = steady_clock::now();
    } 
    return 0;
}