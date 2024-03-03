#include <fstream>
#include <chrono>
#include "../renderer8080/renderer.h"
#include <filesystem>
#include <thread>

using namespace std;
using namespace std::chrono;
namespace FileSystem = std::filesystem;

#include "emulator_shell.h" 

void ReadFileIntoMemoryAt(CPU::State8080 *state, const char *filename, uint32_t offset)
{
    FILE *f;
    std::filesystem::path romPath = filename;
    string filepath = FileSystem::absolute(romPath).string();
    const char *rawFilePath = filepath.c_str();
    const char* mode = "rb";
#ifdef _WIN32
    errno_t err = fopen_s(&f, rawFilePath, mode);
#else
    f = fopen(rawFilePath, mode);
#endif
    if (f == NULL)
    {
        printf("error: Couldn't open %s\n", filename);
        exit(1);
    }
    fseek(f, 0L, SEEK_END);
    int fsize = ftell(f);
    fseek(f, 0L, SEEK_SET);

    uint8_t *buffer = &state->mem[offset];
    fread(buffer, fsize, 1, f);
    fclose(f);
}

CPU::State8080 *Init8080(void)
{   
    // allocate initialized data for cpu state
    CPU::State8080 *state = (CPU::State8080*)calloc(1, sizeof(CPU::State8080));
    // point state->mem toward 16k of memory
    state->mem = (uint8_t*)malloc(0x10000); // 16K
    return state;
}

void RenderGraphics(CPU::State8080* state)
{
    milliseconds startingTime, currentTime = duration_cast<milliseconds>(chrono::system_clock::now().time_since_epoch());
    const int frameTime = 100;
    SDL_Event event;
    Renderer8080* vRender = new Renderer8080();
    vRender->init();
    bool terminate = false;
    while (!terminate)
    {
        currentTime = duration_cast<milliseconds>(chrono::system_clock::now().time_since_epoch());
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                terminate = true;
        }
        if (currentTime.count() - startingTime.count() > frameTime)
        {
            vRender->RenderPixels(state);
            startingTime = duration_cast<milliseconds>(chrono::system_clock::now().time_since_epoch());
        }
    }
    vRender->destory();
}


int main(int argc, char **argv)
{
    int done = 0;
    CPU::State8080 *state = Init8080();
    // store the beginning of the memory for state
    uint8_t* mem_start = state->mem;
    // load the rom files into memory
    ReadFileIntoMemoryAt(state, "../ROM/invaders.h", 0);
    ReadFileIntoMemoryAt(state, "../ROM/invaders.g", 0x800);
    ReadFileIntoMemoryAt(state, "../ROM/invaders.f", 0x1000);
    ReadFileIntoMemoryAt(state, "../ROM/invaders.e", 0x1800);
    // we need an instance of CPU to call the Emulator8080 codes 
    CPU cpu_instance;

    //Run Graphics on Graphics thread
    thread RenderThread(RenderGraphics, state);

    //Run CPU on Main Thread
    while (done == 0)
    {
        for (int i = 0; i < 10000; i++)
        {
            done = cpu_instance.Emulate8080Codes(state);
        }
        cpu_instance.PerformInterrupt(state);
        this_thread::sleep_for(milliseconds(25));
    }
    free(mem_start);
    return 0;
}