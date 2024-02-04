#include <iostream>
#include "emulator_shell.h"

using namespace std;

CPU::CPU() {}

// Return true if even parity and false if odd parity
bool CPU::Parity(uint16_t number) {
    bool parity = true;
    while (number) {
        parity = !parity;
        number = number & (number - 1);
    }
    return parity;
}

// Placeholder function for currently unimplemented instructions
// Lets us track where we are with getting instruction function up and working
void CPU::UnimplementedInstruction(State8080 *state) {
    //Undoes incrementing of pc register
    (state->pc)--;
    cout << "Error: Currently unimplemented instruction" << endl;
    exit(1);
}

CPU::FlagCodes CPU::SetFlags(uint16_t result) {
    FlagCodes ResultCodes;
    //check if zero flag should be set
    ResultCodes.z = (result == 0);

    // Sign flag - most significant bit is set
    ResultCodes.s = 0x80 == (result & 0x80);

    // Pariaty flag, check if the last bit is set
    ResultCodes.p = Parity(result);

    // Carry flag will be true if result > 255 (1111 1111)
    ResultCodes.cy = (result > 0xff);

    // Aux carry is not used in space invaders, pending implementation
    ResultCodes.ac = 1;

    return ResultCodes;
}

bool CPU::IsAuxFlagSet(uint16_t number) {
    return true;
}

// Function for emulating 8080 opcodes, has case for each of our opcodes
// Unimplemented instructions will call UnimplementedInstruction function
int CPU::Emulate8080Codes(State8080 *state){
    unsigned char *opcode = &state->mem[state->pc];
    uint32_t  result;

    // Combined registers 
    // needs to be calculated at usage time
    uint16_t bc;
    uint16_t hl;
    uint16_t de;

    switch(*opcode){
        case 0x00:
            break; // NOP

        case 0x01: // LXI B,D16
            state->b = opcode[2];
            state->c = opcode[1];
            state->pc += 2;
            break;

        case 0x02: // STAX B
            // to create bc shift bits left by 8, creating an empty 8 right bits.
            // Add state->c to the right bits with bitwise or.
            bc = (state->b << 8) | state->c;
            state->mem[bc] = state->a;
            break;

        case 0x03: // INX B
            bc = (state->b << 8) | state->c;
            bc += 1;
            state->b = bc >> 8; // delete the last 8 bits to get b alone
            state->c = (bc - (state->b << 8)); // subtract the first 8 bits to get c alone
            break;

        case 0x04: // INR B
            state->b += 1;
            result = state->b;
            state->f = SetFlags(result);
            break;

        case 0x05: // DCR B
            state->b -= 1;
            result = state->b;
            state->f = SetFlags(result);
            break;

        case 0x06: // MVI B, D8
            state->b = opcode[1];
            state->pc += 1;
            break;

        case 0x07: // RLC
            result = 0x80 == (state->a & 0x80); // get most significant bit
            state->a = state->a << 1;
            state->f.cy = result;
            break;

        case 0x08: // NOP
            break;

        case 0x09: // DAD B
            bc = (state->b << 8) | state->c;
            hl = (state->h << 8) | state->l;
            result = bc + hl;
            hl = result & 0xffff;
            state->h = hl >> 8;
            state->l = (hl - (state->h << 8));
            state->f.cy = result > 0xffff;
            break;

        case 0x0A: // LDAX B
            bc = (state->b << 8) | state->c;
            state->a = state->mem[bc];
            break;

        case 0x0B: // DCX B
            bc = (state->b << 8) | state->c;
            bc -= 1;
            state->b = bc >> 8;
            state->c = (bc - (state->b << 8));
            break;

        case 0x0C: // INR C
            state->c += 1;
            state->f.z = state->c == 0;
            state->f.s = 0x80 == (state->c & 0x80);
            state->f.p = Parity(state->c);
            state->f.ac = 1;
            break;

        case 0x0D: // DCR C
            state->c -= 1;
            state->f.z = state->c == 0;
            state->f.s = 0x80 == (state->c & 0x80);
            state->f.p = Parity(state->c);
            state->f.ac = 1;
            break;

        case 0x0E: // MVI C,D8
            state->c = opcode[1];
            state->pc += 1;
            break;

        case 0x0F: // RRC
            // the least significant bit is always 1 for odd numbers
            result = (state->a % 2 != 0);
            state->a = state->a >> 1;
            state->f.cy = result;
            break;

        case 0x10: // NOP
            break;

        case 0x11: // LXI D,D16
            state->d = opcode[2];
            state->e = opcode[1];
            state->pc += 2;
            break;

        case 0x12: // STAX D
            de = (state->d << 8) | state->e;
            state->mem[de] = state->a;
            break;

        case 0x13: // INX D
            de = (state->d << 8) | state->e;
            de += 1;
            state->d = de >> 8;
            state->e = (de - (state->d << 8));
            break;

        case 0x14:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x15:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x16:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x17:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x18:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x19:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x1A:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x1B:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x1C:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x1D:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x1E:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x1F:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x20:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x21:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x22:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x23:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x24:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x25:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x26:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x27:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x28:
            break; // NOP

        case 0x29: // DAD H
            hl = (state->h << 8) | state->l;
            result = hl + hl;
            state->f.cy = (result > 0xffff);
            hl = result & 0xffff; // we need to strip off any overflow bits
            state->h = hl >> 8;
            state->l = (hl - (state->h << 8));
            break;

        case 0x2A: // LHLD adr
            result = (opcode[2] << 8) | opcode[1];
            state->l = state->mem[result];
            state->h = state->mem[result + 1];
            state->pc += 2;
            break;

        case 0x2B: // DCX H
            hl = (state->h << 8) | state->l;
            hl -= 1;
            state->h = hl >> 8;
            state->l = (hl - (state->h << 8));
            break;

        case 0x2C: // INR L
            state->l += 1;
            state->f.p = Parity(state->l);
            state->f.z = 0 == state->l;
            state->f.s = 0x80 == (state->l & 0x80);
            state->f.ac = 1;
            break;

        case 0x2D: // DCR L
            state->l -= 1;
            state->f.p = Parity(state->l);
            state->f.z = 0 == state->l;
            state->f.s = 0x80 == (state->l & 0x80);
            state->f.ac = 1;
            break;

        case 0x2E: // MVI L, D8
            state->l = opcode[1];
            state->pc += 1;
            break;

        case 0x2F: // CMA
            state->a = state->a ^ 0xffff; // inverse bits using XOR
            break;

        case 0x30: // NOP
            break;

        case 0x31: // LXI SP, D16
            state->sp = (opcode[2] << 8) | opcode[1];
            state->pc += 2;
            break;

        case 0x32: // STA adr
            result = (opcode[2] << 8) | opcode[1];
            state->mem[result] = state->a;
            state->pc += 2;
            break;

        case 0x33: // INX SP
            state->sp += 1;
            break;

        case 0x34: // INR M
            hl = (state->h << 8) | state->l;
            state->mem[hl] = state->mem[hl] + 1;
            state->f.p = Parity(state->mem[hl]);
            state->f.z = 0 == state->mem[hl];
            state->f.s = 0x8000 == (state->mem[hl] & 0x8000);
            state->f.ac = 1;
            break;

        case 0x35: // DCR M
            hl = (state->h << 8) | state->l;
            state->mem[hl] = state->mem[hl] - 1;
            state->f.p = Parity(state->mem[hl]);
            state->f.z = 0 == state->mem[hl];
            state->f.s = 0x8000 == (state->mem[hl] & 0x8000);
            state->f.ac = 1;
            break;

        case 0x36: // MVI M,D8
            hl = (state->h << 8) | state->l;
            state->mem[hl] = opcode[1];
            state->pc += 1;
            break;

        case 0x37: // STC
            state->f.cy = 1;
            break;

        case 0x38: // NOP
            break;

        case 0x39: // DAD SP
            hl = (state->h << 8) | state->l;
            result = hl + state->sp;
            state->f.cy = (hl > 0xffff);
            hl = result & 0xffff;
            state->h = hl >> 8;
            state->l = (hl - (state->h << 8));
            break;

        case 0x3A: // LDA adr
            result = (opcode[2] << 8) | opcode[1];
            state->a = state->mem[result];
            state->pc += 2;
            break;

        case 0x3B: // DCX SP
            state->sp -= 1;
            break;

        case 0x3C:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x3D:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x3E:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x3F:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x40:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x41:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x42:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x43:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x44:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x45:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x46:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x47:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x48:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x49:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x4A:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x4B:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x4C:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x4D:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x4E:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x4F:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x50:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x51:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x52:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x53:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x54:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x55:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x56:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x57:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x58:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x59:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x5A:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x5B:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x5C:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x5D:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x5E:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x5F:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x60:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x61:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x62:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x63:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x64:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x65:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x66:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x67:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x68:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x69:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x6A:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x6B:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x6C:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x6D:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x6E:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x6F:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x70:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x71:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x72:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x73:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x74:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x75:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x76:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x77:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x78:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x79:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x7A:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x7B:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x7C:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x7D:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x7E:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x7F:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x80:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x81:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x82:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x83:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x84:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x85:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x86:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x87:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x88:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x89:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x8A:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x8B:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x8C:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x8D:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x8E:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x8F:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x90:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x91:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x92:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x93:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x94:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x95:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x96:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x97:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x98:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x99:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x9A:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x9B:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x9C:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x9D:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x9E:
            CPU::UnimplementedInstruction(state);
            break;

        case 0x9F:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xA0:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xA1:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xA2:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xA3:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xA4:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xA5:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xA6:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xA7:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xA8:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xA9:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xAA:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xAB:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xAC:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xAD:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xAE:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xAF:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xB0:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xB1:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xB2:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xB3:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xB4:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xB5:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xB6:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xB7:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xB8:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xB9:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xBA:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xBB:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xBC:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xBD:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xBE:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xBF:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xC0:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xC1:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xC2:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xC3:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xC4:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xC5:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xC6:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xC7:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xC8:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xC9:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xCA:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xCB:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xCC:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xCD:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xCE:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xCF:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xD0:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xD1:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xD2:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xD3:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xD4:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xD5:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xD6:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xD7:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xD8:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xD9:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xDA:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xDB:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xDC:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xDD:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xDE:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xDF:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xE0:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xE1:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xE2:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xE3:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xE4:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xE5:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xE6:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xE7:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xE8:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xE9:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xEA:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xEB:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xEC:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xED:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xEE:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xEF:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xF0:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xF1:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xF2:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xF3:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xF4:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xF5:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xF6:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xF7:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xF8:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xF9:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xFA:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xFB:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xFC:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xFD:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xFE:
            CPU::UnimplementedInstruction(state);
            break;

        case 0xFF:
            CPU::UnimplementedInstruction(state);
            break;
    }
    (state->pc)++;

    //Potentially short term return, expect failed cases will return 1?
    return 0;
}
