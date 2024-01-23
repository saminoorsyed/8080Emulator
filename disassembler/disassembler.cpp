// Author: Sami Syed
// Date: Jan 22, 2024
// Purpose: Dissasembler for Space invaders

#include <iostream>
using namespace std;

using namespace std;

int Disassemble8080Op(unsigned char *codebuffer, int pc)
{
    unsigned char *code = &codebuffer[pc];
    int opbytes = 1;
    printf("%04x ", pc);
    switch (*code)
    {
    case 0x00:
        printf("NOP");
        break;
    case 0x01:
        printf("LXI    B,#$%02x%02x", code[2], code[1]);
        opbytes = 3;
        break;
    case 0x02:
        printf("STAX   B");
        break;
    case 0x03:
        printf("INX    B");
        break;
    case 0x04:
        printf("INR    B");
        break;
    case 0x05:
        printf("DCR    B");
        break;
    case 0x06:
        printf("MVI    B,#$%02x", code[1]);
        opbytes = 2;
        break;
    case 0x07:
        printf("RLC");
        break;
    case 0x08:
        printf("NOP");
        break;
    /* ........ */
    case 0x3e:
        printf("MVI    A,#0x%02x", code[1]);
        opbytes = 2;
        break;
    /* ........ */
    case 0xc3:
        printf("JMP    $%02x%02x", code[2], code[1]);
        opbytes = 3;
        break;
        /* ........ */
    }

    printf("\n");

    return opbytes;
}

int main()
{
    // Code for the main function
    // Read the code into a buffer

    // Get a pointer to the beginning of the buffer

    // Use the byte at the pointer to determine the opcode

    // Print out the name of the opcode using the bytes after the opcode as data,
    // if applicable

    // Advance the pointer the number of bytes used by that instruction(1, 2, or 3 bytes)

    // If not at the end of the buffer,
    // go to step 3

    return 0; // Indicates successful execution
}
