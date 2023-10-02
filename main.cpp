#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

// Screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Function to initialize SDL
bool initSDL(SDL_Window*& window, SDL_Renderer*& renderer) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create a window
    window = SDL_CreateWindow("SDL2 and SDL2_ttf Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create a renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return false;
    }

    // Initialize SDL2_ttf
    if (TTF_Init() == -1) {
        std::cerr << "SDL2_ttf initialization failed: " << TTF_GetError() << std::endl;
        return false;
    }

    return true;
}

// Function to load a font
TTF_Font* loadFont(const std::string& fontFile, int fontSize) {
    TTF_Font* font = TTF_OpenFont(fontFile.c_str(), fontSize);
    if (font == nullptr) {
        std::cerr << "Font loading failed: " << TTF_GetError() << std::endl;
    }
    return font;
}

// Function to render text
void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, SDL_Color textColor) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (textSurface == nullptr) {
        std::cerr << "Text rendering failed: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == nullptr) {
        std::cerr << "Texture creation from surface failed: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        return;
    }

    SDL_Rect renderRect = { x, y, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, textTexture, nullptr, &renderRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

int main(int argc, char* argv[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!initSDL(window, renderer)) {
        return 1;
    }

    std::string currentDir = argv[0];
    size_t found = currentDir.find_last_of("/\\");
    std::string fontPath;

    if (found != std::string::npos) {
        // Append the relative path to the .ttf file
        fontPath = currentDir.substr(0, found + 1) + "Pacifico.ttf";
    } else {
        std::cerr << "Unable to determine current directory." << std::endl;
        return 1;
    }

    TTF_Font* font = loadFont(fontPath, 28);
    if (font == nullptr) {
        return 1;
    }

    SDL_Color textColor = { 255, 255, 255, 255 };

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        renderText(renderer, font, "Hello, SDL2 and SDL2_ttf!", 100, 100, textColor);

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

