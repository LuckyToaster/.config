#include <GLFW/glfw3.h>
#include <GL/glew.h>


class Screen {
    public:
        GLFWwindow* window;
        int width, height;
        Screen(const char* name, int width, int height);
        void draw(vector<GLfloat>& vertices); 
        void update();
        void clear();
        bool input(Camera& camera);
};

int main() {
    return 0;
}