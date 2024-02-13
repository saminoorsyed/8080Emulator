#include <fstream>
#include <filesystem>

using namespace std;
namespace FileSystem = std::filesystem;

#include "emulator_shell.h" 

void ReadFileIntoMemoryAt(CPU::State8080 *state, char *filename, uint32_t offset)
{
    FILE *f;
    FileSystem::path romPath = "../ROM/invaders";
    string filepath = FileSystem::absolute(romPath).string();
    const char *rawFilePath = filepath.c_str();
#ifdef _WIN32
    errno_t err = fopen_s(&f, filename, "rb");
#else
    f = fopen(filename, "rb");
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
    CPU::State8080 *state = (CPU::State8080*)calloc(1, sizeof(CPU::State8080));
    state->mem = (u_int8_t*)malloc(0x10000); // 16K
    return state;
}

int main(int argc, char **argv)
{
    int done = 0;
    CPU::State8080 *state = Init8080();
    // store the beginning of the memory for state
    u_int8_t* mem_start = state->mem;
    ReadFileIntoMemoryAt(state, "../ROM/invaders.h", 0);
    ReadFileIntoMemoryAt(state, "../ROM/invaders.g", 0x800);
    ReadFileIntoMemoryAt(state, "../ROM/invaders.f", 0x1000);
    ReadFileIntoMemoryAt(state, "../ROM/invaders.e", 0x1800);
    CPU cpu_instance;
    while (done == 0)
    {
        done = cpu_instance.Emulate8080Codes(state);
    }
    Free8080(mem_start);
    return 0;
}