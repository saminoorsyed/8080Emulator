#include <iostream>
#include <cstdint>

using namespace std;


// Defines FlagCodes structure for tracking/adjusting flags in F register
// pad variable for bits 5, 3, and 1 which retain set value (not used)
// bit 5 always 0, bit 3 always 0, bit 1 always 1
typedef struct FlagCodes {
    uint8_t s:1;
    uint8_t z:1;
    uint8_t ac:1;
    uint8_t p:1;
    uint8_t cy:1;
    uint8_t pad:3;
} FlagCodes;

// Defines structure for tracking each of the registers found in Intel's 8080
// Also includes instance of FlagCodes struct to serve as our f register for flags
typedef struct State8080 {
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t h;
    uint8_t l;
    uint16_t sp;
    uint16_t pc;
    uint8_t *mem;
    uint8_t int_enable;
    struct FlagCodes  f;
} State8080;

// Placeholder function for currently unimplemented instructions
// Lets us track where we are with getting instruction function up and working
void UnimplementedInstruction(State8080 *state) {
    //Undoes incrementing of pc register
    (state->pc)--;
    cout << "Error: Currently unimplemented instruction" << endl;
    exit(1);
}

// Function for emulating 8080 opcodes, has case for each of our opcodes
// Unimplemented instructions will call UnimplementedInstruction function
int Emulate8080Codes(State8080 *state){
    unsigned char *opcode = &state->mem[state->pc];

    switch(*opcode){
        case 0x00:
            UnimplementedInstruction(state);
            break;

        case 0x01:
            UnimplementedInstruction(state);
            break;

        case 0x02:
            UnimplementedInstruction(state);
            break;

        case 0x03:
            UnimplementedInstruction(state);
            break;

        case 0x04:
            UnimplementedInstruction(state);
            break;

        case 0x05:
            UnimplementedInstruction(state);
            break;

        case 0x06:
            UnimplementedInstruction(state);
            break;

        case 0x07:
            UnimplementedInstruction(state);
            break;

        case 0x08:
            UnimplementedInstruction(state);
            break;

        case 0x09:
            UnimplementedInstruction(state);
            break;

        case 0x0A:
            UnimplementedInstruction(state);
            break;

        case 0x0B:
            UnimplementedInstruction(state);
            break;

        case 0x0C:
            UnimplementedInstruction(state);
            break;

        case 0x0D:
            UnimplementedInstruction(state);
            break;

        case 0x0E:
            UnimplementedInstruction(state);
            break;

        case 0x0F:
            UnimplementedInstruction(state);
            break;

        case 0x10:
            UnimplementedInstruction(state);
            break;

        case 0x11:
            UnimplementedInstruction(state);
            break;

        case 0x12:
            UnimplementedInstruction(state);
            break;

        case 0x13:
            UnimplementedInstruction(state);
            break;

        case 0x14:
            UnimplementedInstruction(state);
            break;

        case 0x15:
            UnimplementedInstruction(state);
            break;

        case 0x16:
            UnimplementedInstruction(state);
            break;

        case 0x17:
            UnimplementedInstruction(state);
            break;

        case 0x18:
            UnimplementedInstruction(state);
            break;

        case 0x19:
            UnimplementedInstruction(state);
            break;

        case 0x1A:
            UnimplementedInstruction(state);
            break;

        case 0x1B:
            UnimplementedInstruction(state);
            break;

        case 0x1C:
            UnimplementedInstruction(state);
            break;

        case 0x1D:
            UnimplementedInstruction(state);
            break;

        case 0x1E:
            UnimplementedInstruction(state);
            break;

        case 0x1F:
            UnimplementedInstruction(state);
            break;

        case 0x20:
            UnimplementedInstruction(state);
            break;

        case 0x21:
            UnimplementedInstruction(state);
            break;

        case 0x22:
            UnimplementedInstruction(state);
            break;

        case 0x23:
            UnimplementedInstruction(state);
            break;

        case 0x24:
            UnimplementedInstruction(state);
            break;

        case 0x25:
            UnimplementedInstruction(state);
            break;

        case 0x26:
            UnimplementedInstruction(state);
            break;

        case 0x27:
            UnimplementedInstruction(state);
            break;

        case 0x28:
            UnimplementedInstruction(state);
            break;

        case 0x29:
            UnimplementedInstruction(state);
            break;

        case 0x2A:
            UnimplementedInstruction(state);
            break;

        case 0x2B:
            UnimplementedInstruction(state);
            break;

        case 0x2C:
            UnimplementedInstruction(state);
            break;

        case 0x2D:
            UnimplementedInstruction(state);
            break;

        case 0x2E:
            UnimplementedInstruction(state);
            break;

        case 0x2F:
            UnimplementedInstruction(state);
            break;

        case 0x30:
            UnimplementedInstruction(state);
            break;

        case 0x31:
            UnimplementedInstruction(state);
            break;

        case 0x32:
            UnimplementedInstruction(state);
            break;

        case 0x33:
            UnimplementedInstruction(state);
            break;

        case 0x34:
            UnimplementedInstruction(state);
            break;

        case 0x35:
            UnimplementedInstruction(state);
            break;

        case 0x36:
            UnimplementedInstruction(state);
            break;

        case 0x37:
            UnimplementedInstruction(state);
            break;

        case 0x38:
            UnimplementedInstruction(state);
            break;

        case 0x39:
            UnimplementedInstruction(state);
            break;

        case 0x3A:
            UnimplementedInstruction(state);
            break;

        case 0x3B:
            UnimplementedInstruction(state);
            break;

        case 0x3C:
            UnimplementedInstruction(state);
            break;

        case 0x3D:
            UnimplementedInstruction(state);
            break;

        case 0x3E:
            UnimplementedInstruction(state);
            break;

        case 0x3F:
            UnimplementedInstruction(state);
            break;

        case 0x40:
            UnimplementedInstruction(state);
            break;

        case 0x41:
            UnimplementedInstruction(state);
            break;

        case 0x42:
            UnimplementedInstruction(state);
            break;

        case 0x43:
            UnimplementedInstruction(state);
            break;

        case 0x44:
            UnimplementedInstruction(state);
            break;

        case 0x45:
            UnimplementedInstruction(state);
            break;

        case 0x46:
            UnimplementedInstruction(state);
            break;

        case 0x47:
            UnimplementedInstruction(state);
            break;

        case 0x48:
            UnimplementedInstruction(state);
            break;

        case 0x49:
            UnimplementedInstruction(state);
            break;

        case 0x4A:
            UnimplementedInstruction(state);
            break;

        case 0x4B:
            UnimplementedInstruction(state);
            break;

        case 0x4C:
            UnimplementedInstruction(state);
            break;

        case 0x4D:
            UnimplementedInstruction(state);
            break;

        case 0x4E:
            UnimplementedInstruction(state);
            break;

        case 0x4F:
            UnimplementedInstruction(state);
            break;

        case 0x50:
            UnimplementedInstruction(state);
            break;

        case 0x51:
            UnimplementedInstruction(state);
            break;

        case 0x52:
            UnimplementedInstruction(state);
            break;

        case 0x53:
            UnimplementedInstruction(state);
            break;

        case 0x54:
            UnimplementedInstruction(state);
            break;

        case 0x55:
            UnimplementedInstruction(state);
            break;

        case 0x56:
            UnimplementedInstruction(state);
            break;

        case 0x57:
            UnimplementedInstruction(state);
            break;

        case 0x58:
            UnimplementedInstruction(state);
            break;

        case 0x59:
            UnimplementedInstruction(state);
            break;

        case 0x5A:
            UnimplementedInstruction(state);
            break;

        case 0x5B:
            UnimplementedInstruction(state);
            break;

        case 0x5C:
            UnimplementedInstruction(state);
            break;

        case 0x5D:
            UnimplementedInstruction(state);
            break;

        case 0x5E:
            UnimplementedInstruction(state);
            break;

        case 0x5F:
            UnimplementedInstruction(state);
            break;

        case 0x60:
            UnimplementedInstruction(state);
            break;

        case 0x61:
            UnimplementedInstruction(state);
            break;

        case 0x62:
            UnimplementedInstruction(state);
            break;

        case 0x63:
            UnimplementedInstruction(state);
            break;

        case 0x64:
            UnimplementedInstruction(state);
            break;

        case 0x65:
            UnimplementedInstruction(state);
            break;

        case 0x66:
            UnimplementedInstruction(state);
            break;

        case 0x67:
            UnimplementedInstruction(state);
            break;

        case 0x68:
            UnimplementedInstruction(state);
            break;

        case 0x69:
            UnimplementedInstruction(state);
            break;

        case 0x6A:
            UnimplementedInstruction(state);
            break;

        case 0x6B:
            UnimplementedInstruction(state);
            break;

        case 0x6C:
            UnimplementedInstruction(state);
            break;

        case 0x6D:
            UnimplementedInstruction(state);
            break;

        case 0x6E:
            UnimplementedInstruction(state);
            break;

        case 0x6F:
            UnimplementedInstruction(state);
            break;

        case 0x70:
            UnimplementedInstruction(state);
            break;

        case 0x71:
            UnimplementedInstruction(state);
            break;

        case 0x72:
            UnimplementedInstruction(state);
            break;

        case 0x73:
            UnimplementedInstruction(state);
            break;

        case 0x74:
            UnimplementedInstruction(state);
            break;

        case 0x75:
            UnimplementedInstruction(state);
            break;

        case 0x76:
            UnimplementedInstruction(state);
            break;

        case 0x77:
            UnimplementedInstruction(state);
            break;

        case 0x78:
            UnimplementedInstruction(state);
            break;

        case 0x79:
            UnimplementedInstruction(state);
            break;

        case 0x7A:
            UnimplementedInstruction(state);
            break;

        case 0x7B:
            UnimplementedInstruction(state);
            break;

        case 0x7C:
            UnimplementedInstruction(state);
            break;

        case 0x7D:
            UnimplementedInstruction(state);
            break;

        case 0x7E:
            UnimplementedInstruction(state);
            break;

        case 0x7F:
            UnimplementedInstruction(state);
            break;

        case 0x80:
            UnimplementedInstruction(state);
            break;

        case 0x81:
            UnimplementedInstruction(state);
            break;

        case 0x82:
            UnimplementedInstruction(state);
            break;

        case 0x83:
            UnimplementedInstruction(state);
            break;

        case 0x84:
            UnimplementedInstruction(state);
            break;

        case 0x85:
            UnimplementedInstruction(state);
            break;

        case 0x86:
            UnimplementedInstruction(state);
            break;

        case 0x87:
            UnimplementedInstruction(state);
            break;

        case 0x88:
            UnimplementedInstruction(state);
            break;

        case 0x89:
            UnimplementedInstruction(state);
            break;

        case 0x8A:
            UnimplementedInstruction(state);
            break;

        case 0x8B:
            UnimplementedInstruction(state);
            break;

        case 0x8C:
            UnimplementedInstruction(state);
            break;

        case 0x8D:
            UnimplementedInstruction(state);
            break;

        case 0x8E:
            UnimplementedInstruction(state);
            break;

        case 0x8F:
            UnimplementedInstruction(state);
            break;

        case 0x90:
            UnimplementedInstruction(state);
            break;

        case 0x91:
            UnimplementedInstruction(state);
            break;

        case 0x92:
            UnimplementedInstruction(state);
            break;

        case 0x93:
            UnimplementedInstruction(state);
            break;

        case 0x94:
            UnimplementedInstruction(state);
            break;

        case 0x95:
            UnimplementedInstruction(state);
            break;

        case 0x96:
            UnimplementedInstruction(state);
            break;

        case 0x97:
            UnimplementedInstruction(state);
            break;

        case 0x98:
            UnimplementedInstruction(state);
            break;

        case 0x99:
            UnimplementedInstruction(state);
            break;

        case 0x9A:
            UnimplementedInstruction(state);
            break;

        case 0x9B:
            UnimplementedInstruction(state);
            break;

        case 0x9C:
            UnimplementedInstruction(state);
            break;

        case 0x9D:
            UnimplementedInstruction(state);
            break;

        case 0x9E:
            UnimplementedInstruction(state);
            break;

        case 0x9F:
            UnimplementedInstruction(state);
            break;

        case 0xA0:
            UnimplementedInstruction(state);
            break;

        case 0xA1:
            UnimplementedInstruction(state);
            break;

        case 0xA2:
            UnimplementedInstruction(state);
            break;

        case 0xA3:
            UnimplementedInstruction(state);
            break;

        case 0xA4:
            UnimplementedInstruction(state);
            break;

        case 0xA5:
            UnimplementedInstruction(state);
            break;

        case 0xA6:
            UnimplementedInstruction(state);
            break;

        case 0xA7:
            UnimplementedInstruction(state);
            break;

        case 0xA8:
            UnimplementedInstruction(state);
            break;

        case 0xA9:
            UnimplementedInstruction(state);
            break;

        case 0xAA:
            UnimplementedInstruction(state);
            break;

        case 0xAB:
            UnimplementedInstruction(state);
            break;

        case 0xAC:
            UnimplementedInstruction(state);
            break;

        case 0xAD:
            UnimplementedInstruction(state);
            break;

        case 0xAE:
            UnimplementedInstruction(state);
            break;

        case 0xAF:
            UnimplementedInstruction(state);
            break;

        case 0xB0:
            UnimplementedInstruction(state);
            break;

        case 0xB1:
            UnimplementedInstruction(state);
            break;

        case 0xB2:
            UnimplementedInstruction(state);
            break;

        case 0xB3:
            UnimplementedInstruction(state);
            break;

        case 0xB4:
            UnimplementedInstruction(state);
            break;

        case 0xB5:
            UnimplementedInstruction(state);
            break;

        case 0xB6:
            UnimplementedInstruction(state);
            break;

        case 0xB7:
            UnimplementedInstruction(state);
            break;

        case 0xB8:
            UnimplementedInstruction(state);
            break;

        case 0xB9:
            UnimplementedInstruction(state);
            break;

        case 0xBA:
            UnimplementedInstruction(state);
            break;

        case 0xBB:
            UnimplementedInstruction(state);
            break;

        case 0xBC:
            UnimplementedInstruction(state);
            break;

        case 0xBD:
            UnimplementedInstruction(state);
            break;

        case 0xBE:
            UnimplementedInstruction(state);
            break;

        case 0xBF:
            UnimplementedInstruction(state);
            break;

        case 0xC0:
            UnimplementedInstruction(state);
            break;

        case 0xC1:
            UnimplementedInstruction(state);
            break;

        case 0xC2:
            UnimplementedInstruction(state);
            break;

        case 0xC3:
            UnimplementedInstruction(state);
            break;

        case 0xC4:
            UnimplementedInstruction(state);
            break;

        case 0xC5:
            UnimplementedInstruction(state);
            break;

        case 0xC6:
            UnimplementedInstruction(state);
            break;

        case 0xC7:
            UnimplementedInstruction(state);
            break;

        case 0xC8:
            UnimplementedInstruction(state);
            break;

        case 0xC9:
            UnimplementedInstruction(state);
            break;

        case 0xCA:
            UnimplementedInstruction(state);
            break;

        case 0xCB:
            UnimplementedInstruction(state);
            break;

        case 0xCC:
            UnimplementedInstruction(state);
            break;

        case 0xCD:
            UnimplementedInstruction(state);
            break;

        case 0xCE:
            UnimplementedInstruction(state);
            break;

        case 0xCF:
            UnimplementedInstruction(state);
            break;

        case 0xD0:
            UnimplementedInstruction(state);
            break;

        case 0xD1:
            UnimplementedInstruction(state);
            break;

        case 0xD2:
            UnimplementedInstruction(state);
            break;

        case 0xD3:
            UnimplementedInstruction(state);
            break;

        case 0xD4:
            UnimplementedInstruction(state);
            break;

        case 0xD5:
            UnimplementedInstruction(state);
            break;

        case 0xD6:
            UnimplementedInstruction(state);
            break;

        case 0xD7:
            UnimplementedInstruction(state);
            break;

        case 0xD8:
            UnimplementedInstruction(state);
            break;

        case 0xD9:
            UnimplementedInstruction(state);
            break;

        case 0xDA:
            UnimplementedInstruction(state);
            break;

        case 0xDB:
            UnimplementedInstruction(state);
            break;

        case 0xDC:
            UnimplementedInstruction(state);
            break;

        case 0xDD:
            UnimplementedInstruction(state);
            break;

        case 0xDE:
            UnimplementedInstruction(state);
            break;

        case 0xDF:
            UnimplementedInstruction(state);
            break;

        case 0xE0:
            UnimplementedInstruction(state);
            break;

        case 0xE1:
            UnimplementedInstruction(state);
            break;

        case 0xE2:
            UnimplementedInstruction(state);
            break;

        case 0xE3:
            UnimplementedInstruction(state);
            break;

        case 0xE4:
            UnimplementedInstruction(state);
            break;

        case 0xE5:
            UnimplementedInstruction(state);
            break;

        case 0xE6:
            UnimplementedInstruction(state);
            break;

        case 0xE7:
            UnimplementedInstruction(state);
            break;

        case 0xE8:
            UnimplementedInstruction(state);
            break;

        case 0xE9:
            UnimplementedInstruction(state);
            break;

        case 0xEA:
            UnimplementedInstruction(state);
            break;

        case 0xEB:
            UnimplementedInstruction(state);
            break;

        case 0xEC:
            UnimplementedInstruction(state);
            break;

        case 0xED:
            UnimplementedInstruction(state);
            break;

        case 0xEE:
            UnimplementedInstruction(state);
            break;

        case 0xEF:
            UnimplementedInstruction(state);
            break;

        case 0xF0:
            UnimplementedInstruction(state);
            break;

        case 0xF1:
            UnimplementedInstruction(state);
            break;

        case 0xF2:
            UnimplementedInstruction(state);
            break;

        case 0xF3:
            UnimplementedInstruction(state);
            break;

        case 0xF4:
            UnimplementedInstruction(state);
            break;

        case 0xF5:
            UnimplementedInstruction(state);
            break;

        case 0xF6:
            UnimplementedInstruction(state);
            break;

        case 0xF7:
            UnimplementedInstruction(state);
            break;

        case 0xF8:
            UnimplementedInstruction(state);
            break;

        case 0xF9:
            UnimplementedInstruction(state);
            break;

        case 0xFA:
            UnimplementedInstruction(state);
            break;

        case 0xFB:
            UnimplementedInstruction(state);
            break;

        case 0xFC:
            UnimplementedInstruction(state);
            break;

        case 0xFD:
            UnimplementedInstruction(state);
            break;

        case 0xFE:
            UnimplementedInstruction(state);
            break;

        case 0xFF:
            UnimplementedInstruction(state);
            break;
    }
    (state->pc)++;

    //Potentially short term return, expect failed cases will return 1?
    return 0;
}


int main(){
    return 0;
}
