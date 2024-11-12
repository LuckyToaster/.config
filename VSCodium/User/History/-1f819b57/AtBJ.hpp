using std::cout;
using std::cerr;
using std::endl;
using std::vector;

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


// ==============
// IMPLEMENTATION
// ==============

Screen::Screen(const char* name, int width, int height) {
    this->width = width;
    this->height = height;

    if (!glfwInit()) cerr << "Failed to initialize GLFW" << endl;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Request at least OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Use core profile
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    this->window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (window == NULL) cerr << "Failed to create GLFW window" << endl;

    glfwMakeContextCurrent(window);
    //glfwSwapInterval(1); // vsync

    // Initialize GLEW
    if (glewInit() != GLEW_OK) cerr << "Failed to initialize GLEW\n" << endl;

    glViewport(0, 0, width, height); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, 0, 1);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // Set background color to black (or any color you prefer)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    cout << glGetString(GL_VERSION) << endl;
}


void Screen::draw(vector<GLfloat>& vertices) {
    glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices.data());
        glDrawArrays(GL_LINES, 0, vertices.size() / 3);
    glDisableClientState(GL_VERTEX_ARRAY);
}


void Screen::update() {
    glfwSwapBuffers(window);
}

void Screen::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


bool Screen::input(Camera& c) {
    glfwPollEvents(); // gotta call this somewhere

    if (glfwWindowShouldClose(window)) return false; 
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) return false; 

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cout << "lol w key" << endl;
        c.pos.z -= 9.0;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        c.pos.z += 9.0;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        c.pos.x -= 9.0;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        c.pos.x += 9.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        c.pos.y += 9.0;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        c.pos.y -= 9.0;
    }

    // arrows?
    return true; // Keep the window open by default
}