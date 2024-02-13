#include "renderer.h"
#include <iostream>

using namespace std;

Renderer::Renderer() {}

/* Render pixels from VRam, scanning from the bottom left to the top right. Each segment of y comprises 8 bits to examine. */
void Renderer::RenderPixels(CPU::State8080* state)
{
	int vRamAddress = 0x2400;
	// We render from the bottom of column one to the top of column one, then proceed to the next column
	for (int xPixel = 0; xPixel < XPixelCount; ++xPixel)
	{
		for (int yPixel = 0; yPixel < YPixelCount; yPixel += 8) // increment one byte per pass
		{
			uint8_t videoByte = state->mem[vRamAddress];
			vRamAddress += 1;

			// draw the pixels
			for (int bitIndex = 0; bitIndex < 8; ++bitIndex)
			{
				// get the right most bit by itself, if 1 draw pixel is true else false
				bool drawPixel = videoByte & 0x1;
				int yPos = (yPixel + 8) - bitIndex;
				int xPos = xPixel;
				if (drawPixel)
				{
					// TODO - draw gameobject color pixel at xPos and yPos
				}
				else
				{
					// TODO - draw background color pixel at xPos and yPos
				}
				// so shift right to check the next bit
				videoByte = videoByte >> 1;
			}
		}
	}
}

void Renderer::drawPixel(int xPos, int yPos)
{
	// TODO - Implement function on per platform basis
#if _WIN32
	// windows draw logic
#else
	// other draw logic
#endif
}
