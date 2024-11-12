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

    }
    
    return 0;
}
