#pragma once

#include <cstdint>
#include "../emulator/emulator_shell.h"

class Renderer {

public:
    Renderer();

    const int XPixelCount = 224;
    const int YPixelCount = 256;

    void RenderPixels(CPU::State8080* state);

    void drawPixel(int xPos, int yPos);

};