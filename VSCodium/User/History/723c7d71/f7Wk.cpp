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


Screen::Screen(const char* name, int width, int height) {
    this->width = width;
    this->height = height;

    if (!glfwInit()) cerr << "Failed to initialize GLFW" << endl;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Request at least OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Use core profile
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    this->window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (window == NULL) cerr << "Failed to create GLFW window" << endl;

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1); // vsync

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) 
        cerr << "Failed to initialize GLAD" << endl;

    glad_glViewport(0, 0, width, height); 
    glad_glMatrixMode(GL_PROJECTION);
    glad_glLoadIdentity();
    glad_glOrtho(0, width, 0, height, 0, 1);
    glad_glMatrixMode(GL_MODELVIEW);
    glad_glLoadIdentity();
    cout << glad_glGetString(GL_VERSION) << endl;
}

int main() {
    
    return 0;
}