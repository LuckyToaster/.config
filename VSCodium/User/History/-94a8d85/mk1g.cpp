#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

SDL_Window* window;
SDL_Event event;
SDL_GLContext context;

const Uint8* key = SDL_GetKeyboardState(0);
const float WIDTH = 800.0f;
const float HEIGHT = 800.0f;

int main() {
    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    context = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(SDL_FALSE);
    
    glViewport(0, 0, WIDTH, HEIGHT); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, WIDTH, 0, HEIGHT, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat vertices[] = {200, 100, 0, 100, 300, 0 };

    while (window != NULL) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) window = NULL;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glClearColor(0, 0, 0, 0);


        glPushMatrix();
        glTranslatef(0, 0, 0);
        glBegin(GL_QUADS);
            glColor3ub(255, 0, 0);
            glVertex2f(0, 0);
            glVertex2f(100, 0);
            glVertex2f(100, 100);
            glVertex2f(0, 100);
        glEnd();
        glPopMatrix();
        SDL_GL_SwapWindow(window);
    }
    
    return 0;
}
