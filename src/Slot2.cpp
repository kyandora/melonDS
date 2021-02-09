#include "Config.h"
#include <memory>
#include <iostream>
#include "CRC32.h"
#include "Platform.h"
#include <cstring>
#include "Slot2.hpp"
#include "NDS.h"

// Slot 2 base class

u8 Slot2Cartridge::Read8(u32 addr) { return 0xFF; };

u16 Slot2Cartridge::Read16(u32 addr) { return 0xFFFF; };

u32 Slot2Cartridge::Read32(u32 addr) { return 0xFFFFFFFF; };

void Slot2Cartridge::Write8(u32 addr, u8 val) { };

void Slot2Cartridge::Write16(u32 addr, u16 val) { };

void Slot2Cartridge::Write32(u32 addr, u32 val) { };

// Game Pak

GamePak::GamePak()
{
    FILE* f = Platform::OpenFile(Config::GBAPath, "rb");
    if (!f) { throw("file not found"); }

    fseek(f, 0xFF, SEEK_END);
    u32 len = (u32)ftell(f);

    u32 CartROMSize = 0x200;
    while (CartROMSize < len)
        CartROMSize <<= 1;

    char gamecode[5] = { '\0' };
    fseek(f, 0xAC, SEEK_SET);
    fread(&gamecode, 1, 4, f);
    printf("Game code: %s\n", gamecode);

    ROM = new u8[CartROMSize];
    memset(ROM, 0, CartROMSize);
    fseek(f, 0, SEEK_SET);
    fread(ROM, 1, len, f);

    fclose(f);
    
    /*for (int i = 0; i < sizeof(SOLAR_SENSOR_GAMECODES)/sizeof(SOLAR_SENSOR_GAMECODES[0]); i++)
    {
        if (strcmp(gamecode, SOLAR_SENSOR_GAMECODES[i]) == 0) HasSolarSensor = true;
    }

    if (HasSolarSensor)
    {
        GPIO = new GamePakGPIO(ROM);
        printf("GBA solar sensor support detected!\n");
    }*/

    u32 CartCRC = CRC32(ROM, CartROMSize);
    printf("ROM CRC32: %08X\n", CartCRC);

    // save
    //printf("Save file: %s\n", sram);
    //GBACart_SRAM::LoadSave(sram);
}

u8 GamePak::Read8(u32 addr) { return *(u8*)&ROM[addr - 0x08000000]; };

u16 GamePak::Read16(u32 addr) { return *(u16*)&ROM[addr - 0x08000000]; };

u32 GamePak::Read32(u32 addr) { return *(u32*)&ROM[addr - 0x08000000]; };

// Guitar Grip

// Code ported from Desmume

u8 GuitarGrip::Read8(u32 addr)
{
    if (addr == 0xA000000)
    {
        return ~GuitarKeyStatus;
    }

    return ((addr & 1) ? 0xF9 : 0xFF);
}

u16 GuitarGrip::Read16(u32 addr)
{
    return 0xF9FF;
}

void GuitarGrip::SetGripKey(GuitarKeys key, bool val)
{
    if (val == true)
    {
        GuitarKeyStatus |= static_cast<int>(key);
    }
    else
    {
        GuitarKeyStatus &= ~static_cast<int>(key);
    }
} 
