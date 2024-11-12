#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

SDL_Window* window;
SDL_Event event;
SDL_GLContext context;

const Uint8* key = SDL_GetKeyboardState(0);

int main() {
    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    context = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(SDL_FALSE);

    while (window != NULL) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) window = NULL;
        }

        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glViewport(0, 0, 800, 600); 
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, 800, 600, 0, -10, 10);

        /*glPushMatrix();
        glTranslatef(0, 0, 0);
        glBegin(GL_QUADS);
            glColor3ub(255, 0, 0);
            glVertex2f(0, 0);
            glVertex2f(100, 0);
            glVertex2f(100, 100);
            glVertex2f(0, 100);
        glEnd();
        glPopMatrix();
        */

        double x1 = 10;
        double y1 = 10;
        double x2 = 20;
        double y2 = 20;

        x1 = 2*x1 / 800 - 1;
        y1 = 2*y1 / 600 - 1;

        x2 = 2*x2 / 800 - 1;
        y2 = 2*y2 / 600 - 1;

        glBegin(GL_LINES);
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
        glEnd();

        SDL_GL_SwapWindow(window);
    }
    
    return 0;
}
