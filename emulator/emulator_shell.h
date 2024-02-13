#pragma once

#include <cstdint>

class CPU {

public:
    CPU();

// Defines FlagCodes structure for tracking/adjusting flags in F register
// pad variable for bits 5, 3, and 1 which retain set value (not used)
// bit 5 always 0, bit 3 always 0, bit 1 always 1
    typedef struct FlagCodes {
        uint8_t s: 1;
        uint8_t z: 1;
        uint8_t ac: 1;
        uint8_t p: 1;
        uint8_t cy: 1;
        uint8_t pad: 3;
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
        FlagCodes f;
    } State8080;

    void UnimplementedInstruction(State8080 *state);

    int Emulate8080Codes(State8080 *state);

    FlagCodes SetFlags(uint16_t result);

    bool Parity(uint16_t number);

    uint8_t FlagCalc(FlagCodes flagState);
  
    bool IsAuxFlagSet(uint16_t number);
  
};

void Free8080(u_int8_t* mem_address)
{
    if (mem_address != nullptr)
    {
      
        free(mem_address);
        mem_address = nullptr; // Set pointer to null to avoid dangling pointer
    }
    free(mem_address);
}
