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

#include "../Slot2.hpp"

// Code (mostly) ported from Desmume

u8 MemoryExpansionPak::Read8(u32 addr)
{
    if ((addr >= 0x80000B0)  && (addr < 0x80000C0))
    {
        return *(u8*)&MemPakHeader[(addr & 0xF)];
    }
    else if ((addr >= 0x9000000) && (addr < 0x9800000))
    {
        return *(u8*)&MemPakMemory[(addr - 0x9000000)];
    }
		
    return 0xFF;
}

u16 MemoryExpansionPak::Read16(u32 addr)
{
    if ((addr >= 0x80000B0)  && (addr < 0x80000C0))
    {
        return *(u16*)&MemPakHeader[(addr & 0xF)];
    }
    else if (addr == 0x801FFFC)
    {
        return 0x7FFF;
    }
    else if (addr == 0x8240002)
    {
        return 0x0000;
    }
    else if ((addr >= 0x9000000) && (addr < 0x9800000))
    {
        return *(u16*)&MemPakMemory[(addr - 0x9000000)];
    }

    return 0xFFFF;
}

u32 MemoryExpansionPak::Read32(u32 addr)
{
    if ((addr >= 0x80000B0) && (addr < 0x80000C0))
    {
        return *(u32*)&MemPakHeader[(addr & 0xF)];
    }
    else if ((addr >= 0x9000000) && (addr < 0x9800000))
    {
        return *(u32*)&MemPakMemory[(addr - 0x9000000)];
    }
    
    return 0xFFFFFFFF;
}

void MemoryExpansionPak::Write8(u32 addr, u8 val)
{
    if (MemPakRAMLock == true)
    {
        return;
    }

    if ((addr >= 0x9000000) && (addr < 0x9800000))
    {
        *(u8*)&MemPakMemory[(addr - 0x9000000)] = val;
    }
}

void MemoryExpansionPak::Write16(u32 addr, u16 val)
{
    if (addr == 0x8240000)
    {
        MemPakRAMLock = !(val & 0x1);
        return;
    }

    if (MemPakRAMLock == true)
    {
        return;
    }

    if ((addr >= 0x9000000) && (addr < 0x9800000))
    {
        *(u16*)&MemPakMemory[(addr - 0x9000000)] = val;
    }
}

void MemoryExpansionPak::Write32(u32 addr, u32 val)
{
    if (MemPakRAMLock == true)
    {
        return;
    }

    if ((addr >= 0x9000000) && (addr < 0x9800000))
    {
        *(u32*)&MemPakMemory[(addr - 0x9000000)] = val;
    }
}

/*void DoSavestate(Savestate* file)
{
    file->Section("MemExpansionPack");
    file->Var8((u8*)&MemPakRAMLock);
    file->VarArray(MemPakMemory, 0x800000);
}*/
