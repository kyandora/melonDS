/*
    Copyright 2019 Arisotura, Buenia0

    This file is part of melonDS.

    melonDS is free software: you can redistribute it and/or modify it under
    the terms of the GNU General Public License as published by the Free
    Software Foundation, either version 3 of the License, or (at your option)
    any later version.

    melonDS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with melonDS. If not, see http://www.gnu.org/licenses/.
*/

#ifndef SLOT2_H
#define SLOT2_H

#include "types.h"
#include <memory>
#include <string>
#include <vector>

// Slot 2 base class

class Slot2Cartridge {
    public:
        virtual u8 Read8(u32 addr);
        virtual u16 Read16(u32 addr);
        virtual u32 Read32(u32 addr);
        virtual void Write8(u32 addr, u8 val);
        virtual void Write16(u32 addr, u16 val);
        virtual void Write32(u32 addr, u32 val);
};

// Game Pak

class GamePak: public Slot2Cartridge {
    public:
        GamePak();
        u8 Read8(u32 addr) override;
        u16 Read16(u32 addr) override;
        u32 Read32(u32 addr) override;
    private:
        u8* ROM;
};

// Guitar Grip

enum class GuitarKeys : int
{
    Green = 0x40,
    Red = 0x20,
    Yellow = 0x10,
    Blue = 0x08,
};

class GuitarGrip: public Slot2Cartridge {
    public:
        u8 Read8(u32 addr) override;
        u16 Read16(u32 addr) override;
        void SetGripKey(GuitarKeys key, bool val);
    private:
        u8 GuitarKeyStatus = 0x00;
};

// Memory Expanion Pak

class MemoryExpansionPak: public Slot2Cartridge {
    public:
        u8 Read8(u32 addr) override;
        u16 Read16(u32 addr) override;
        u32 Read32(u32 addr) override;
        void Write8(u32 addr, u8 val) override;
        void Write16(u32 addr, u16 val) override;
        void Write32(u32 addr, u32 val) override;
    private:
        const u8 MemPakHeader[16] = 
        {
            0xFF, 0xFF, 0x96, 0x00,
            0x00, 0x24, 0x24, 0x24,
            0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0x7F
        };
        u8 MemPakMemory[0x800000];
        bool MemPakRAMLock = true;
};

// Rumble Pak

class RumblePak: public Slot2Cartridge {
    public:
        u16 Read16(u32 addr) override;
        void Write16(u32 addr, u16 val) override;
    private:
        u16 RumbleState = 0;
};

// SEGA Card Reader

class SegaCardReader: public Slot2Cartridge {
    public:
        u8 Read8(u32 addr) override;
        u16 Read16(u32 addr) override;
        u32 Read32(u32 addr) override;
        void Write8(u32 addr, u8 val) override;
        void Scan(std::string barcode);
    private:
        u8 HCVControl = 0;
        std::string HCVData = "________________";
};

#endif // SLOT2_H
