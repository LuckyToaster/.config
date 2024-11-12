//#include <SDL2/SDL.h>
#include <GLFW/glfw3.h>

using std::cout;
using std::cerr;
using std::endl;

class Screen {
    public:
        //SDL_Event e;
        //SDL_GLContext context; 
        //SDL_Window* window;
        GLFWwindow* window;
        int width, height;
        const char* name;
        Screen(const char* name, int width, int height);
        void draw(vector<GLfloat>& vertices); 
        void update();
        void clear();
        //bool input(Camera& camera);
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
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    this->window = glfwCreateWindow(width, height, name, )


    /*this->window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    if (!this->window) cerr << "failed to create window" << endl;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    this->context = SDL_GL_CreateContext(window);
    if (!this->context) cerr << "failed to create context" << endl;

    if (!gladLoadGL()) cerr << "Failed to initialize OpenGL with GLAD" << endl;
    SDL_GL_SetSwapInterval(1); // VSYNC
    glad_glViewport(0, 0, width, height); 
    glad_glMatrixMode(GL_PROJECTION);
    glad_glLoadIdentity();
    glad_glOrtho(0, width, 0, height, 0, 1);
    glad_glMatrixMode(GL_MODELVIEW);
    glad_glLoadIdentity();
    cout << glad_glGetString(GL_VERSION) << endl;*/   
}


void Screen::draw(vector<GLfloat>& vertices) {
    glad_glEnableClientState(GL_VERTEX_ARRAY);
        glad_glVertexPointer(3, GL_FLOAT, 0, vertices.data());
        glad_glDrawArrays(GL_LINES, 0, vertices.size() / 3);
    glad_glDisableClientState(GL_VERTEX_ARRAY);
}


void Screen::update() {
    SDL_GL_SwapWindow(this->window);
}


void Screen::clear() {
    glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


/*bool Screen::input(Camera& camera) {
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {
            SDL_GL_DeleteContext(context); 
            SDL_DestroyWindow(window);
            SDL_Quit();
            return false;
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_w: camera.pos.z -= 9.0; break; // forward / backward is Z axis
                case SDLK_s: camera.pos.z += 9.0; break;
                case SDLK_a: camera.pos.x += 9.0; break; // left / right is X axis 
                case SDLK_d: camera.pos.x -= 9.0; break;
                case SDLK_q: camera.pos.y += 9.0; break; // up / down is Y axis
                case SDLK_e: camera.pos.y -= 9.0; break;
                case SDLK_UP: camera.orientation.z += 3.5; break;
                case SDLK_DOWN: camera.orientation.z -= 3.5; break;
                case SDLK_LEFT: camera.orientation.x -= 3.5; break;
                case SDLK_RIGHT: camera.orientation.x += 3.5; break;
                default: std::cout << "some other key pressed" << std::endl; break;
            }
        }
    }
    return true;
}*/