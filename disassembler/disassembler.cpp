// Date: Jan 22, 2024
// Purpose: DisasSembler for Space invaders

#include <iostream>
using namespace std;

using namespace std;

int Disassemble8080Op(unsigned char *codebuffer, int pc)
{
    unsigned char *code = &codebuffer[pc];
    // opbyte  = 1 is the most common
    int opBytes = 1;

    printf("%04x ", pc);
    switch (*code)
    {
    // case structure:
    // print statements should output the opcode and the following Data associated
    // assign the  opBytes if other than 1
    case 0x00:
        printf("NOP");
        break;
    case 0x01:
        printf("LXI    B, #$%02x%02x", code[2], code[1]);
        opBytes = 3;
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
        printf("MVI    B, #$%02x", code[1]);
        opBytes = 2;
        break;
    case 0x07:
        printf("RLC");
        break;
    case 0x08:
        printf("NOP");
        break;
    case 0x09:
        printf("DAD     B");
        break;
    case 0x0A:
        printf("LDAX    B");
        break;
    case 0x0B:
        printf("DCX     B");
        break;
    case 0x0C:
        printf("INR     C");
        break;
    case 0x0D:
        printf("DCR     C");
        break;
    case 0x0E:
        printf("MVI     C, #$%02x", code[1]);
        opBytes = 2;
        break;
    case 0x0F:
        printf("RRC");
        break;
    case 0x10:
        printf("NOP");
        break;
    case 0x11:
        printf("LXI     D, #$%02x%02x", code[1], code[2]);
        opBytes = 3;
        break;
    case 0x12:
        printf("STAX    D");
        break;
    case 0x13:
        printf("INX     D");
        break;
    case 0x14:
        printf("INR     D");
        break;
    case 0x15:
        printf("DCR     D");
        break;
    case 0x16:
        printf("MVI     D, #$%02x", code[1]);
        opBytes = 2;
        break;
    case 0x17:
        printf("RAL");
        break;
    case 0x18:
        printf("NOP");
        break;
    case 0x19:
        printf("DAD     D");
        break;
    case 0x1A:
        printf("LDAX    D");
        break;
    case 0x1B:
        printf("DCX     D");
        break;
    case 0x1C:
        printf("INR     E");
        break;
    case 0x1D:
        printf("DCR     E");
        break;
    case 0x1E:
        printf("MVI     E, #$%02x", code[1]);
        opBytes = 2;
        break;
    case 0x1F:
        printf("RAR");
        break;
    case 0x20:
        printf("NOP");
        break;
    case 0x21:
        printf("LXI     H, #$%02x%02x", code[1], code[2]);
        opBytes = 3;
        break;
    case 0x22:
        printf("SHLD    adr, #$%02x%02x", code[1], code[2]);
        opBytes = 3;
        break;
    case 0x23:
        printf("INX     H");
        break;
    case 0x24:
        printf("INR     H");
        break;
    case 0x25:
        printf("DCR     H");
        break;
    case 0x26:
        printf("MVI     H, #$%02x", code[1]);
        opBytes = 2;
        break;
    case 0x27:
        printf("DAA");
        break;
    case 0x28:
        printf("NOP");
        break;
    case 0x29:
        printf("DAD     H");
        break;
    case 0x2A:
        printf("LHLD     adr, #$%02x%02x", code[1], code[2]);
        opBytes = 3;
        break;
    case 0x2B:
        printf("DCX     H");
        break;
    case 0x2C:
        printf("INR     L");
        break;
    case 0x2D:
        printf("DCR     L");
        break;
    case 0x2E:
        printf("MVI     L, #$%02x", code[1]);
        opBytes = 2;
        break;
    case 0x2F:
        printf("CMA");
        break;
    case 0x30:
        printf("NOP");
        break;
    case 0x31:
        printf("LXI     SP, #$%02x%02x", code[1], code[2]);
        opBytes = 3;
        break;
    case 0x32:
        printf("STA     adr, #$%02x%02x", code[1], code[2]);
        opBytes = 3;
        break;
    case 0x33:
        printf("INX     SP");
        break;
    case 0x34:
        printf("INR     M");
        break;
    case 0x35:
        printf("DCR     M");
        break;
    case 0x36:
        printf("MVI     M, #$%02x", code[1]);
        opBytes = 2;
        break;
    case 0x37:
        printf("STC");
        break;
    case 0x38:
        printf("NOP");
        break;
    case 0x39:
        printf("DAD     SP");
        break;
    case 0x3A:
        printf("LDA     adr, #$%20x%20x", code[1], code[2]);
        opBytes = 3;
        break;
    case 0x3B:
        printf("DCX     SP");
        break;
    case 0x3C:
        printf("INR     A");
        break;
    case 0x3D:
        printf("DCR     A");
        break;
    case 0x3E:
        printf("MVI     A, #$%02x", code[1]);
        opBytes = 2;
        break;
    case 0x3F:
        printf("CMC");
        break;
    case 0x40:
        printf();
        break;
    case 0x41:
        printf();
        break;
    case 0x42:
        printf();
        break;
    case 0x43:
        printf();
        break;
    case 0x44:
        printf();
        break;
    case 0x45:
        printf();
        break;
    case 0x46:
        printf();
        break;
    case 0x47:
        printf();
        break;
    case 0x48:
        printf();
        break;
    case 0x49:
        printf();
        break;
    case 0x4A:
        printf();
        break;
    case 0x4B:
        printf();
        break;
    case 0x4C:
        printf();
        break;
    case 0x4D:
        printf();
        break;
    case 0x4E:
        printf();
        break;
    case 0x4F:
        printf();
        break;
    case 0x50:
        printf();
        break;
    case 0x51:
        printf();
        break;
    case 0x52:
        printf();
        break;
    case 0x53:
        printf();
        break;
    case 0x54:
        printf();
        break;
    case 0x55:
        printf();
        break;
    case 0x56:
        printf();
        break;
    case 0x57:
        printf();
        break;
    case 0x58:
        printf();
        break;
    case 0x59:
        printf();
        break;
    case 0x5A:
        printf();
        break;
    case 0x5B:
        printf();
        break;
    case 0x5C:
        printf();
        break;
    case 0x5D:
        printf();
        break;
    case 0x5E:
        printf();
        break;
    case 0x5F:
        printf();
        break;
    case 0x60:
        printf();
        break;
    case 0x61:
        printf();
        break;
    case 0x62:
        printf();
        break;
    case 0x63:
        printf();
        break;
    case 0x64:
        printf();
        break;
    case 0x65:
        printf();
        break;
    case 0x66:
        printf();
        break;
    case 0x67:
        printf();
        break;
    case 0x68:
        printf();
        break;
    case 0x69:
        printf();
        break;
    case 0x6A:
        printf();
        break;
    case 0x6B:
        printf();
        break;
    case 0x6C:
        printf();
        break;
    case 0x6D:
        printf();
        break;
    case 0x6E:
        printf();
        break;
    case 0x6F:
        printf();
        break;
    case 0x70:
        printf();
        break;
    case 0x71:
        printf();
        break;
    case 0x72:
        printf();
        break;
    case 0x73:
        printf();
        break;
    case 0x74:
        printf();
        break;
    case 0x75:
        printf();
        break;
    case 0x76:
        printf();
        break;
    case 0x77:
        printf();
        break;
    case 0x78:
        printf();
        break;
    case 0x79:
        printf();
        break;
    case 0x7A:
        printf();
        break;
    case 0x7B:
        printf();
        break;
    case 0x7C:
        printf();
        break;
    case 0x7D:
        printf();
        break;
    case 0x7E:
        printf();
        break;
    case 0x7F:
        printf();
        break;
    case 0x80:
        printf();
        break;
    case 0x81:
        printf();
        break;
    case 0x82:
        printf();
        break;
    case 0x83:
        printf();
        break;
    case 0x84:
        printf();
        break;
    case 0x85:
        printf();
        break;
    case 0x86:
        printf();
        break;
    case 0x87:
        printf();
        break;
    case 0x88:
        printf();
        break;
    case 0x89:
        printf();
        break;
    case 0x8A:
        printf();
        break;
    case 0x8B:
        printf();
        break;
    case 0x8C:
        printf();
        break;
    case 0x8D:
        printf();
        break;
    case 0x8E:
        printf();
        break;
    case 0x8F:
        printf();
        break;
    case 0x90:
        printf();
        break;
    case 0x91:
        printf();
        break;
    case 0x92:
        printf();
        break;
    case 0x93:
        printf();
        break;
    case 0x94:
        printf();
        break;
    case 0x95:
        printf();
        break;
    case 0x96:
        printf();
        break;
    case 0x97:
        printf();
        break;
    case 0x98:
        printf();
        break;
    case 0x99:
        printf();
        break;
    case 0x9A:
        printf();
        break;
    case 0x9B:
        printf();
        break;
    case 0x9C:
        printf();
        break;
    case 0x9D:
        printf();
        break;
    case 0x9E:
        printf();
        break;
    case 0x9F:
        printf();
        break;
    case 0xA0:
        printf();
        break;
    case 0xA1:
        printf();
        break;
    case 0xA2:
        printf();
        break;
    case 0xA3:
        printf();
        break;
    case 0xA4:
        printf();
        break;
    case 0xA5:
        printf();
        break;
    case 0xA6:
        printf();
        break;
    case 0xA7:
        printf();
        break;
    case 0xA8:
        printf();
        break;
    case 0xA9:
        printf();
        break;
    case 0xAA:
        printf();
        break;
    case 0xAB:
        printf();
        break;
    case 0xAC:
        printf();
        break;
    case 0xAD:
        printf();
        break;
    case 0xAE:
        printf();
        break;
    case 0xAF:
        printf();
        break;
    case 0xB0:
        printf();
        break;
    case 0xB1:
        printf();
        break;
    case 0xB2:
        printf();
        break;
    case 0xB3:
        printf();
        break;
    case 0xB4:
        printf();
        break;
    case 0xB5:
        printf();
        break;
    case 0xB6:
        printf();
        break;
    case 0xB7:
        printf();
        break;
    case 0xB8:
        printf();
        break;
    case 0xB9:
        printf();
        break;
    case 0xBA:
        printf();
        break;
    case 0xBB:
        printf();
        break;
    case 0xBC:
        printf();
        break;
    case 0xBD:
        printf();
        break;
    case 0xBE:
        printf();
        break;
    case 0xBF:
        printf();
        break;
    case 0xC0:
        printf();
        break;
    case 0xC1:
        printf();
        break;
    case 0xC2:
        printf();
        break;
    case 0xC3:
        printf();
        break;
    case 0xC4:
        printf();
        break;
    case 0xC5:
        printf();
        break;
    case 0xC6:
        printf();
        break;
    case 0xC7:
        printf();
        break;
    case 0xC8:
        printf();
        break;
    case 0xC9:
        printf();
        break;
    case 0xCA:
        printf();
        break;
    case 0xCB:
        printf();
        break;
    case 0xCC:
        printf();
        break;
    case 0xCD:
        printf();
        break;
    case 0xCE:
        printf();
        break;
    case 0xCF:
        printf();
        break;
    case 0xD0:
        printf();
        break;
    case 0xD1:
        printf();
        break;
    case 0xD2:
        printf();
        break;
    case 0xD3:
        printf();
        break;
    case 0xD4:
        printf();
        break;
    case 0xD5:
        printf();
        break;
    case 0xD6:
        printf();
        break;
    case 0xD7:
        printf();
        break;
    case 0xD8:
        printf();
        break;
    case 0xD9:
        printf();
        break;
    case 0xDA:
        printf();
        break;
    case 0xDB:
        printf();
        break;
    case 0xDC:
        printf();
        break;
    case 0xDD:
        printf();
        break;
    case 0xDE:
        printf();
        break;
    case 0xDF:
        printf();
        break;
    case 0xE0:
        printf();
        break;
    case 0xE1:
        printf();
        break;
    case 0xE2:
        printf();
        break;
    case 0xE3:
        printf();
        break;
    case 0xE4:
        printf();
        break;
    case 0xE5:
        printf();
        break;
    case 0xE6:
        printf();
        break;
    case 0xE7:
        printf();
        break;
    case 0xE8:
        printf();
        break;
    case 0xE9:
        printf();
        break;
    case 0xEA:
        printf();
        break;
    case 0xEB:
        printf();
        break;
    case 0xEC:
        printf();
        break;
    case 0xED:
        printf();
        break;
    case 0xEE:
        printf();
        break;
    case 0xEF:
        printf();
        break;
    case 0xF0:
        printf();
        break;
    case 0xF1:
        printf();
        break;
    case 0xF2:
        printf();
        break;
    case 0xF3:
        printf();
        break;
    case 0xF4:
        printf();
        break;
    case 0xF5:
        printf();
        break;
    case 0xF6:
        printf();
        break;
    case 0xF7:
        printf();
        break;
    case 0xF8:
        printf();
        break;
    case 0xF9:
        printf();
        break;
    case 0xFA:
        printf();
        break;
    case 0xFB:
        printf();
        break;
    case 0xFC:
        printf();
        break;
    case 0xFD:
        printf();
        break;
    case 0xFE:
        printf();
        break;
    case 0xFF:
        printf();
        break;

    /* ........ */
    case 0x3e:
        printf("MVI    A, #0x%02x", code[1]);
        opBytes = 2;
        break;
    /* ........ */
    case 0xc3:
        printf("JMP    $%02x%02x", code[2], code[1]);
        opBytes = 3;
        break;
        /* ........ */
    }

    printf("\n");

    return opBytes;
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
