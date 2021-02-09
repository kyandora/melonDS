/*
    Copyright 2019 Arisotura

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

#include <string>
#include "../Slot2.hpp"

// Code ported from shonumi

u8 SegaCardReader::Read8(u32 addr)
{
    if (addr < 0x8020000)
    {
        if (addr & 1) return 0xFD;
        else return (0xF0 | ((addr & 0x1F) >> 1));
    }
    else if (addr == 0xA000000) return HCVControl;
    else if ((addr >= 0xA000010) && (addr <= 0xA00001F)) return HCVData[addr & 0xF];
    else return 0xFF;
}

u16 SegaCardReader::Read16(u32 addr)
{
    return (((u16)Read8(addr+1) << 8) | (u16) Read8(addr));
}      

u32 SegaCardReader::Read32(u32 addr)
{
    return (((u32)Read8(addr+3) << 24) | ((u32)Read8(addr+2) << 16) | ((u32)Read8(addr+1) << 8) | (u32) Read8(addr));
}

void SegaCardReader::Write8(u32 addr, u8 val)
{
    if (addr == 0xA000000) HCVControl = val;
}

void SegaCardReader::Scan(std::string barcode)
{
    HCVData = std::string(barcode, 0, 15) + std::string((16 - barcode.length()), '_');
    HCVControl = 0;
}
