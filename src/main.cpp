// ImGui and SDL imports
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer2.h"
#include <SDL2/SDL.h>

// Custom Elements/Widgets inclusions
#include "custom_elements.hpp"

// ImGui Extension inclusions
#include "implot.h"

// Stadard C++ inclusions
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct ScrollingBuffer {
    int max, offset;
    ImVector<ImVec2> data;

    ScrollingBuffer(int max_size = 2000) {
        max = max_size;
        offset = 0;
        data.reserve(max);
    }

    void add_point(float x, float y) {
        if (data.size() < max) {
            data.push_back(ImVec2(x, y));
        } else {
            data[offset] = ImVec2(x, y);
            offset = (offset + 1) % max;
        }
    }

    void erase() {
        if (data.size() > 0) {
            data.shrink(0);
            offset = 0;
        }
    }
};



int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        return -1;
    }

    // Create SDL window
    SDL_Window* window = SDL_CreateWindow("Base ImGui SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    bool teststate = false;
    float testval = 0.5f;

    int inittoggle = 1;
    int mcinittoggle = 1;
    std::vector<std::string> initoptions = {"autonomous", "disabled", "teleop"};
    std::vector<BASE_COLORS> cols = {BASE_COLORS::BLUE, BASE_COLORS::RED, BASE_COLORS::GREEN};

    ToggleButton toggle("testing", "test label", &teststate);
    MultiToggle mtoggle(&inittoggle, initoptions, "multitest", "multi test label");
    MultiToggle mctoggle(&mcinittoggle, initoptions, "multitest-color", "multi test color label");
    mctoggle.SetColors(cols);

    TextOutput to("test1");
    TextOutput to1("test2", BASE_COLORS::GREEN);

    int buffersize = 50;
    char buf1[buffersize] = {};
    TextInput ti("input1", buf1, &buffersize);

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) running = false;
        }

        // Start ImGui frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // // Render GUI
        // ImGui::Begin("Hello, ImGui!");
        // ImGui::Text("This is a sample window.");
        // ImGui::End();

        // ImGui::Begin("Text input test");
        // int bufsize = 48;
        // char buf1[bufsize] = {};
        // ImGui::InputText("##text1", buf1, bufsize);
        // ImGui::Text(buf1);
        // ImGui::End();

        ImGui::SetNextItemWidth(200.0f);
        ImGui::Begin("Toggle switch Examples");
        // toggle.Render();
        toggle.Render();

        if (teststate) {
            ImGui::SetNextItemWidth(100.0f);
            ImGui::SliderFloat("Testing:", &testval, 0.0f, 1.0f);
            ImGui::SameLine();
            ImGui::Text(" %.3f units", testval);
        }

        mtoggle.Render();
        mctoggle.Render();

        to.Render();
        to1.Render();

        ti.Render();

        ImGui::End();

        // Rendering
        ImGui::Render();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
