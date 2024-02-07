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

    // Parity flag, check if the last bit is set
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
    uint8_t  upperdec;
    uint8_t lowerdec;

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

        case 0x14: //INR D
            state->d += 1;
            state->f.z = state->d == 0;
            state->f.s = 0x80 == (state->d & 0x80);
            state->f.p = Parity(state->d);
            state->f.ac = 1;
            break;

        case 0x15: //DCR D
            state->d -= 1;
            state->f.z = state->d == 0;
            state->f.s = 0x80 == (state->d & 0x80);
            state->f.p = Parity(state->d);
            state->f.ac = 1;
            break;

        case 0x16: //MVI D, d8
            state->d = opcode[1];
            state->pc += 1;
            break;

        case 0x17: //RAL
            result = 0x80 == (state->a & 0x80); //Stores highest bit
            state->a = state->a << 1;

            if (state->f.cy)
            {
              state->a = state->a | 1 << 0;
            }

            state->f.cy = result;
            break;

        case 0x18: //NOP
            break;

        case 0x19: //DAD D
            de = (state->d << 8) | state->e;
            hl = (state->h << 8) | state->l;
            result = de + hl;
            state->d = de >> 8;
            state->e = (de - (state->d << 8));
            state->h = hl >> 8;
            state->l = (hl - (state->h << 8));
            state->f.cy = (result > 0xffff);
            hl = result & 0xffff;
            break;

        case 0x1A: //LDAX D
            de = (state->d << 8) | state->e;
            state->a = state->mem[de];
            break;

        case 0x1B: //DCX D
            de = (state->d << 8) | state->e;
            de -= 1;
            state->d = de >> 8;
            state->e = (de - (state->d << 8));
            break;

        case 0x1C: //INR E
            state->e += 1;
            state->f.z = state->e == 0;
            state->f.s = 0x80 == (state->e & 0x80);
            state->f.p = Parity(state->e);
            state->f.ac = 1;
            break;

        case 0x1D: //DCR E
            state->e -= 1;
            state->f.z = state->e == 0;
            state->f.s = 0x80 == (state->e & 0x80);
            state->f.p = Parity(state->e);
            state->f.ac = 1;
            break;

        case 0x1E: //MVI E, d8
            state->e = opcode[1];
            state->pc += 1;
            break;

        case 0x1F: //RAR
            result = 0x01 == (state->a & 0x01); //Stores lowest bit
            state->a = state->a >> 1;

            if (state->f.cy)
            {
               state->a = state->a | 1 << 7;
            }
            state->f.cy = result;
            break;

        case 0x20: //NOP
            break;

        case 0x21: //LXI H, d16
            state->h = opcode[2];
            state->l = opcode[1];
            state->pc += 2;
            break;

        case 0x22: //SHLD a16
            result = (opcode[2] << 8) | opcode[1];
            state->mem[result] = state->l;
            result += 1;
            state->mem[result] = state->h;
            state->pc += 2;
            break;

        case 0x23: //INX H
            hl = (state->h << 8) | state->l;
            hl += 1;
            state->h = hl >> 8;
            state->l = (hl - (state->h << 8));
            break;

        case 0x24: //INR H
            state->h += 1;
            state->f.z = state->h == 0;
            state->f.s = 0x80 == (state->h & 0x80);
            state->f.p = Parity(state->h);
            state->f.ac = 1;
            break;

        case 0x25: //DCR H
            state->h -= 1;
            state->f.z = state->h == 0;
            state->f.s = 0x80 == (state->h & 0x80);
            state->f.p = Parity(state->h);
            state->f.ac = 1;
            break;

        case 0x26: //MVI H, d8
            state->h = opcode[1];
            state->pc += 1;
            break;

        case 0x27: //DAA (DEPENDENT ON AC FLAG, MAKE SURE AC FLAG SET UP RIGHT)
            lowerdec = state->a & 0x0F;

            if (lowerdec > 9 || state->f.ac == 1)
            {
                state->a += 6;
                state->f.ac = lowerdec > 15;
            }

            upperdec = state->a >> 4;
            lowerdec = state->a & 0x0F;

            if (upperdec > 9 || state->f.cy == 1)
            {
                upperdec += 6;
                state->f.cy = upperdec > 15;
            }

            state->a = upperdec << 4 | lowerdec;
            state->f.p = Parity(state->a);
            state->f.z = 0 == state->a;
            state->f.s = 0x80 == (state->h & 0x80);
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
            state->d = state->b;
            break;

        case 0x51:
            state->d = state->c;
            break;

        case 0x52:
            // state->d = state->d; This operation does nothing MOV D, D
            break;

        case 0x53:
            state->d = state->e;
            break;

        case 0x54:
            state->d = state->h;
            break;

        case 0x55:
            state->d = state->l;
            break;

        case 0x56:
            // MOV D,M moves the number stored in the address at HL to register D
            // shift H left by 8 bits and do an or operator with L
            hl = (state->h<<8)| (state->l);
            state->d = state->mem[hl];
            break;

        case 0x57:
            state->d = state->a;
            break;

        case 0x58:
            state->e = state->b;
            break;

        case 0x59:
            state->e = state->c;
            break;

        case 0x5A:
            state->e = state->d;
            break;

        case 0x5B:
            // state->e = state->e; this code does nothing
            break;

        case 0x5C:
            state->e = state->h;
            break;

        case 0x5D:
            state->e = state->l;
            break;

        case 0x5E:
            hl = (state->h<<8)|(state->l);
            state->e = state->mem[hl];
            break;

        case 0x5F:
            state->e = state->a;
            break;

        case 0x60:
            state->h = state->b;
            break;

        case 0x61:
            state->h = state->c;
            break;

        case 0x62:
            state->h = state->d;
            break;

        case 0x63:
            state->h = state->e;
            break;

        case 0x64:
            state->h = state->h;
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

        case 0x79: //MOV A, C
            state->a = state->c;
            break;

        case 0x7A: //MOV A, D
            state->a = state->d;
            break;

        case 0x7B: //MOV A, E
            state->a = state->e;
            break;

        case 0x7C: //MOV A, H
            state->a = state->h;
            break;

        case 0x7D: //MOV A, L
            state->a = state->l;
            break;

        case 0x7E: //MOV A, M
            hl = (state->h << 8) | state->l;
            state->a = state->mem[hl];
            break;

        case 0x7F: //MOV A, A
            state->a = state->a;
            break;

        case 0x80: //ADD B
            lowerdec = state->a & 0x0F; //Pulls register A low 4 bit nibble
            upperdec = state->b & 0x0F; //Pulls added register low 4 bit nibble

            result = state->a + state->b;
            state->f.z = (0 == (result & 0xFF)); //Accounts for potential carry out of range of register A
            state->f.s = (0x80 == (result & 0x80));
            state->f.cy = (result > 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;

            result = lowerdec + upperdec; //Add lower 4 bit pairs to see if carry from bit 3 into bit 4
            state->f.ac = result > 15; // If result greater 4 bit capacity, set AC flag, clears otherwise
            break;

        case 0x81: //ADD C
            lowerdec = state->a & 0x0F; //Pulls register A low 4 bit nibble
            upperdec = state->c & 0x0F; //Pulls added register low 4 bit nibble

            result = state->a + state->c;
            state->f.z = (0 == (result & 0xFF)); //Accounts for potential carry out of range of register A
            state->f.s = (0x80 == (result & 0x80));
            state->f.cy = (result > 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;

            result = lowerdec + upperdec; //Add lower 4 bit pairs to see if carry from bit 3 into bit 4
            state->f.ac = result > 15; // If result greater 4 bit capacity, set AC flag, clears otherwise
            break;

        case 0x82: //ADD D
            lowerdec = state->a & 0x0F; //Pulls register A low 4 bit nibble
            upperdec = state->d & 0x0F; //Pulls added register low 4 bit nibble

            result = state->a + state->d;
            state->f.z = (0 == (result & 0xFF)); //Accounts for potential carry out of range of register A
            state->f.s = (0x80 == (result & 0x80));
            state->f.cy = (result > 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;

            result = lowerdec + upperdec; //Add lower 4 bit pairs to see if carry from bit 3 into bit 4
            state->f.ac = result > 15; // If result greater 4 bit capacity, set AC flag, clears otherwise
            break;

        case 0x83: //ADD E
            lowerdec = state->a & 0x0F; //Pulls register A low 4 bit nibble
            upperdec = state->e & 0x0F; //Pulls added register low 4 bit nibble

            result = state->a + state->e;
            state->f.z = (0 == (result & 0xFF)); //Accounts for potential carry out of range of register A
            state->f.s = (0x80 == (result & 0x80));
            state->f.cy = (result > 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;

            result = lowerdec + upperdec; //Add lower 4 bit pairs to see if carry from bit 3 into bit 4
            state->f.ac = result > 15; // If result greater 4 bit capacity, set AC flag, clears otherwise
            break;

        case 0x84: //ADD H
            lowerdec = state->a & 0x0F; //Pulls register A low 4 bit nibble
            upperdec = state->h & 0x0F; //Pulls added register low 4 bit nibble

            result = state->a + state->h;
            state->f.z = (0 == (result & 0xFF)); //Accounts for potential carry out of range of register A
            state->f.s = (0x80 == (result & 0x80));
            state->f.cy = (result > 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;

            result = lowerdec + upperdec; //Add lower 4 bit pairs to see if carry from bit 3 into bit 4
            state->f.ac = result > 15; // If result greater 4 bit capacity, set AC flag, clears otherwise
            break;

        case 0x85: //ADD L
            lowerdec = state->a & 0x0F; //Pulls register A low 4 bit nibble
            upperdec = state->l & 0x0F; //Pulls added register low 4 bit nibble

            result = state->a + state->l;
            state->f.z = (0 == (result & 0xFF)); //Accounts for potential carry out of range of register A
            state->f.s = (0x80 == (result & 0x80));
            state->f.cy = (result > 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;

            result = lowerdec + upperdec; //Add lower 4 bit pairs to see if carry from bit 3 into bit 4
            state->f.ac = result > 15; // If result greater 4 bit capacity, set AC flag, clears otherwise
            break;

        case 0x86: //ADD M
            hl = (state->h << 8) | state->l;
            lowerdec = state->a & 0x0F; //Pulls register A low 4 bit nibble
            upperdec = state->mem[hl] & 0x0F; //Pulls mem value low 4 bit nibble

            result = state->a + state->mem[hl];
            state->f.z = (0 == (result & 0xFF)); //Accounts for potential carry out of range of register A
            state->f.s = (0x80 == (result & 0x80));
            state->f.cy = (result > 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;

            result = lowerdec + upperdec; //Add lower 4 bit pairs to see if carry from bit 3 into bit 4
            state->f.ac = result > 15; // If result greater 4 bit capacity, set AC flag, clears otherwise
            break;

        case 0x87: //ADD A
            lowerdec = state->a & 0x0F; //Pulls register A low 4 bit nibble
            upperdec = state->a & 0x0F; //Pulls added register low 4 bit nibble

            result = state->a + state->a;
            state->f.z = (0 == (result & 0xFF)); //Accounts for potential carry out of range of register A
            state->f.s = (0x80 == (result & 0x80));
            state->f.cy = (result > 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;

            result = lowerdec + upperdec; //Add lower 4 bit pairs to see if carry from bit 3 into bit 4
            state->f.ac = result > 15; // If result greater 4 bit capacity, set AC flag, clears otherwise
            break;

        case 0x88: //ADC B
            lowerdec = state->a & 0x0F; //Pulls register A low 4 bit nibble
            upperdec = (state->b & 0x0F) + state->f.cy; //Pulls added register low 4 bit nibble, adds CY value

            result = state->a + state->b + state->f.cy;
            state->f.z = (0 == (result & 0xFF)); //Accounts for potential carry out of range of register A
            state->f.s = (0x80 == (result & 0x80));
            state->f.cy = (result > 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;

            result = lowerdec + upperdec; //Add lower 4 bit pairs to see if carry from bit 3 into bit 4
            state->f.ac = result > 15; // If result greater 4 bit capacity, set AC flag, clears otherwise
            break;

        case 0x89: //ADC C
            lowerdec = state->a & 0x0F; //Pulls register A low 4 bit nibble
            upperdec = (state->c & 0x0F) + state->f.cy; //Pulls added register low 4 bit nibble, adds CY value

            result = state->a + state->c + state->f.cy;
            state->f.z = (0 == (result & 0xFF)); //Accounts for potential carry out of range of register A
            state->f.s = (0x80 == (result & 0x80));
            state->f.cy = (result > 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;

            result = lowerdec + upperdec; //Add lower 4 bit pairs to see if carry from bit 3 into bit 4
            state->f.ac = result > 15; // If result greater 4 bit capacity, set AC flag, clears otherwise
            break;

        case 0x8A: //ADC D
            lowerdec = state->a & 0x0F; //Pulls register A low 4 bit nibble
            upperdec = (state->d & 0x0F) + state->f.cy; //Pulls added register low 4 bit nibble, adds CY value

            result = state->a + state->d + state->f.cy;
            state->f.z = (0 == (result & 0xFF)); //Accounts for potential carry out of range of register A
            state->f.s = (0x80 == (result & 0x80));
            state->f.cy = (result > 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;

            result = lowerdec + upperdec; //Add lower 4 bit pairs to see if carry from bit 3 into bit 4
            state->f.ac = result > 15; // If result greater 4 bit capacity, set AC flag, clears otherwise
            break;

        case 0x8B: //ADC E
            lowerdec = state->a & 0x0F; //Pulls register A low 4 bit nibble
            upperdec = (state->e & 0x0F) + state->f.cy; //Pulls added register low 4 bit nibble, adds CY value

            result = state->a + state->e + state->f.cy;
            state->f.z = (0 == (result & 0xFF)); //Accounts for potential carry out of range of register A
            state->f.s = (0x80 == (result & 0x80));
            state->f.cy = (result > 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;

            result = lowerdec + upperdec; //Add lower 4 bit pairs to see if carry from bit 3 into bit 4
            state->f.ac = result > 15; // If result greater 4 bit capacity, set AC flag, clears otherwise
            break;

        case 0x8C: //ADC H
            lowerdec = state->a & 0x0F; //Pulls register A low 4 bit nibble
            upperdec = (state->h & 0x0F) + state->f.cy; //Pulls added register low 4 bit nibble, adds CY value

            result = state->a + state->h + state->f.cy;
            state->f.z = (0 == (result & 0xFF)); //Accounts for potential carry out of range of register A
            state->f.s = (0x80 == (result & 0x80));
            state->f.cy = (result > 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;

            result = lowerdec + upperdec; //Add lower 4 bit pairs to see if carry from bit 3 into bit 4
            state->f.ac = result > 15; // If result greater 4 bit capacity, set AC flag, clears otherwise
            break;

        case 0x8D: //ADC L
            lowerdec = state->a & 0x0F; //Pulls register A low 4 bit nibble
            upperdec = (state->l & 0x0F) + state->f.cy; //Pulls added register low 4 bit nibble, adds CY value

            result = state->a + state->l + state->f.cy;
            state->f.z = (0 == (result & 0xFF)); //Accounts for potential carry out of range of register A
            state->f.s = (0x80 == (result & 0x80));
            state->f.cy = (result > 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;

            result = lowerdec + upperdec; //Add lower 4 bit pairs to see if carry from bit 3 into bit 4
            state->f.ac = result > 15; // If result greater 4 bit capacity, set AC flag, clears otherwise
            break;

        case 0x8E: //ADC M
            hl = (state->h << 8) | state->l;
            lowerdec = state->a & 0x0F; //Pulls register A low 4 bit nibble
            upperdec = (state->mem[hl] & 0x0F) + state->f.cy; //Pulls added mem low 4 bit nibble, adds CY value

            result = state->a + state->mem[hl] + state->f.cy;
            state->f.z = (0 == (result & 0xFF)); //Accounts for potential carry out of range of register A
            state->f.s = (0x80 == (result & 0x80));
            state->f.cy = (result > 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;

            result = lowerdec + upperdec; //Add lower 4 bit pairs to see if carry from bit 3 into bit 4
            state->f.ac = result > 15; // If result greater 4 bit capacity, set AC flag, clears otherwise
            break;

        case 0x8F: //ADC A
            lowerdec = state->a & 0x0F; //Pulls register A low 4 bit nibble
            upperdec = (state->a & 0x0F) + state->f.cy; //Pulls added register low 4 bit nibble, adds CY value

            result = state->a + state->a + state->f.cy;
            state->f.z = (0 == (result & 0xFF)); //Accounts for potential carry out of range of register A
            state->f.s = (0x80 == (result & 0x80));
            state->f.cy = (result > 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;

            result = lowerdec + upperdec; //Add lower 4 bit pairs to see if carry from bit 3 into bit 4
            state->f.ac = result > 15; // If result greater 4 bit capacity, set AC flag, clears otherwise
            break;

        case 0x90: //SUB B
            result = state->a + (~state->b) + 1; //2s complement subtraction
            state->f.ac = ((state->a & 0x0F) + ((~state->b) & 0x0F) + 1) > 0x0F; //Apparently they don't bother flipping this
            state->f.cy = state->b > state->a;
            state->f.s = 0x80 == (result & 0x80);
            state->f.z = 0 == (result & 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;
            break;

        case 0x91: //SUB C
            result = state->a + (~state->c) + 1; //2s complement subtraction
            state->f.ac = ((state->a & 0x0F) + ((~state->c) & 0x0F) + 1) > 0x0F; //Apparently they don't bother flipping this
            state->f.cy = state->c > state->a;
            state->f.s = 0x80 == (result & 0x80);
            state->f.z = 0 == (result & 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;
            break;

        case 0x92: //SUB D
            result = state->a + (~state->d) + 1; //2s complement subtraction
            state->f.ac = ((state->a & 0x0F) + ((~state->d) & 0x0F) + 1) > 0x0F; //Apparently they don't bother flipping this
            state->f.cy = state->d > state->a;
            state->f.s = 0x80 == (result & 0x80);
            state->f.z = 0 == (result & 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;
            break;

        case 0x93: //SUB E
            result = state->a + (~state->e) + 1; //2s complement subtraction
            state->f.ac = ((state->a & 0x0F) + ((~state->e) & 0x0F) + 1) > 0x0F; //Apparently they don't bother flipping this
            state->f.cy = state->e > state->a;
            state->f.s = 0x80 == (result & 0x80);
            state->f.z = 0 == (result & 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;
            break;

        case 0x94: //SUB H
            result = state->a + (~state->h) + 1; //2s complement subtraction
            state->f.ac = ((state->a & 0x0F) + ((~state->h) & 0x0F) + 1) > 0x0F; //Apparently they don't bother flipping this
            state->f.cy = state->h > state->a;
            state->f.s = 0x80 == (result & 0x80);
            state->f.z = 0 == (result & 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;
            break;

        case 0x95: //SUB L
            result = state->a + (~state->l) + 1; //2s complement subtraction
            state->f.ac = ((state->a & 0x0F) + ((~state->l) & 0x0F) + 1) > 0x0F; //Apparently they don't bother flipping this
            state->f.cy = state->l > state->a;
            state->f.s = 0x80 == (result & 0x80);
            state->f.z = 0 == (result & 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;
            break;

        case 0x96: //SUB M
            hl = (state->h << 8) | state->l;
            result = state->a + (~state->mem[hl]) + 1; //2s complement subtraction
            state->f.ac = ((state->a & 0x0F) + ((~state->mem[hl]) & 0x0F) + 1) > 0x0F; //Apparently they don't bother flipping this
            state->f.cy = state->mem[hl] > state->a;
            state->f.s = 0x80 == (result & 0x80);
            state->f.z = 0 == (result & 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;
            break;

        case 0x97: //SUB A
            result = state->a + (~state->a) + 1; //2s complement subtraction
            state->f.ac = ((state->a & 0x0F) + ((~state->a) & 0x0F) + 1) > 0x0F; //Apparently they don't bother flipping this
            state->f.cy = 0;
            state->f.s = 0x80 == (result & 0x80);
            state->f.z = 0 == (result & 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;
            break;

        case 0x98: //SBB B
            result = state->a + (~state->b) + (~state->f.cy); //2s complement subtraction, flips state of CY flag
            state->f.ac = ((state->a & 0x0F) + ((~state->b) & 0x0F) + (~state->f.cy)) > 0x0F; //Apparently they don't bother flipping this
            state->f.cy = state->b > state->a;
            state->f.s = 0x80 == (result & 0x80);
            state->f.z = 0 == (result & 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;
            break;

        case 0x99: //SBB C
            result = state->a + (~state->c) + (~state->f.cy); //2s complement subtraction, flips state of CY flag
            state->f.ac = ((state->a & 0x0F) + ((~state->c) & 0x0F) + (~state->f.cy)) > 0x0F; //Apparently they don't bother flipping this
            state->f.cy = state->c > state->a;
            state->f.s = 0x80 == (result & 0x80);
            state->f.z = 0 == (result & 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;
            break;

        case 0x9A: //SBB D
            result = state->a + (~state->d) + (~state->f.cy); //2s complement subtraction, flips state of CY flag
            state->f.ac = ((state->a & 0x0F) + ((~state->d) & 0x0F) + (~state->f.cy)) > 0x0F; //Apparently they don't bother flipping this
            state->f.cy = state->d > state->a;
            state->f.s = 0x80 == (result & 0x80);
            state->f.z = 0 == (result & 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;
            break;

        case 0x9B: //SBB E
            result = state->a + (~state->e) + (~state->f.cy); //2s complement subtraction, flips state of CY flag
            state->f.ac = ((state->a & 0x0F) + ((~state->e) & 0x0F) + (~state->f.cy)) > 0x0F; //Apparently they don't bother flipping this
            state->f.cy = state->e > state->a;
            state->f.s = 0x80 == (result & 0x80);
            state->f.z = 0 == (result & 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;
            break;

        case 0x9C: //SBB H
            result = state->a + (~state->h) + (~state->f.cy); //2s complement subtraction, flips state of CY flag
            state->f.ac = ((state->a & 0x0F) + ((~state->h) & 0x0F) + (~state->f.cy)) > 0x0F; //Apparently they don't bother flipping this
            state->f.cy = state->h > state->a;
            state->f.s = 0x80 == (result & 0x80);
            state->f.z = 0 == (result & 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;
            break;

        case 0x9D: //SBB L
            result = state->a + (~state->l) + (~state->f.cy); //2s complement subtraction, flips state of CY flag
            state->f.ac = ((state->a & 0x0F) + ((~state->l) & 0x0F) + (~state->f.cy)) > 0x0F; //Apparently they don't bother flipping this
            state->f.cy = state->l > state->a;
            state->f.s = 0x80 == (result & 0x80);
            state->f.z = 0 == (result & 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;
            break;

        case 0x9E: //SBB M
            hl = (state->h << 8) | state->l;
            result = state->a + (~state->mem[hl]) + (~state->f.cy); //2s complement subtraction, flips state of CY flag
            state->f.ac = ((state->a & 0x0F) + ((~state->mem[hl]) & 0x0F) + (~state->f.cy)) > 0x0F; //Apparently they don't bother flipping this
            state->f.cy = state->mem[hl] > state->a;
            state->f.s = 0x80 == (result & 0x80);
            state->f.z = 0 == (result & 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;
            break;

        case 0x9F: //SBB A
            result = state->a + (~state->a) + (~state->f.cy); //2s complement subtraction, flips state of CY flag
            state->f.ac = ((state->a & 0x0F) + ((~state->a) & 0x0F) + (~state->f.cy)) > 0x0F; //Apparently they don't bother flipping this
            state->f.cy = 0;
            state->f.s = 0x80 == (result & 0x80);
            state->f.z = 0 == (result & 0xFF);
            state->f.p = Parity(result & 0xFF);
            state->a = result & 0xFF;
            break;

        case 0xA0: //ANA B
            lowerdec = state->a & 0x08; //Isolate bit 3 from A register
            upperdec = state->b & 0x08; //Isolate bit 3 from AND register

            state->f.cy = 0; //ANA clears carry
            state->f.ac = 0x08 == (lowerdec | upperdec); //AC flag set to OR of bit 3s from involved registers
            state->a = state->a & state->b;
            state->f.z = 0 == state->a;
            state->f.s = 0x80 == (state->a & 0x80);
            state->f.p = Parity(state->a);
            break;

        case 0xA1: //ANA C
            lowerdec = state->a & 0x08; //Isolate bit 3 from A register
            upperdec = state->c & 0x08; //Isolate bit 3 from AND register

            state->f.cy = 0; //ANA clears carry
            state->f.ac = 0x08 == (lowerdec | upperdec); //AC flag set to OR of bit 3s from involved registers
            state->a = state->a & state->c;
            state->f.z = 0 == state->a;
            state->f.s = 0x80 == (state->a & 0x80);
            state->f.p = Parity(state->a);
            break;

        case 0xA2: //ANA D
            lowerdec = state->a & 0x08; //Isolate bit 3 from A register
            upperdec = state->d & 0x08; //Isolate bit 3 from AND register

            state->f.cy = 0; //ANA clears carry
            state->f.ac = 0x08 == (lowerdec | upperdec); //AC flag set to OR of bit 3s from involved registers
            state->a = state->a & state->d;
            state->f.z = 0 == state->a;
            state->f.s = 0x80 == (state->a & 0x80);
            state->f.p = Parity(state->a);
            break;

        case 0xA3: //ANA E
            lowerdec = state->a & 0x08; //Isolate bit 3 from A register
            upperdec = state->e & 0x08; //Isolate bit 3 from AND register

            state->f.cy = 0; //ANA clears carry
            state->f.ac = 0x08 == (lowerdec | upperdec); //AC flag set to OR of bit 3s from involved registers
            state->a = state->a & state->e;
            state->f.z = 0 == state->a;
            state->f.s = 0x80 == (state->a & 0x80);
            state->f.p = Parity(state->a);
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
