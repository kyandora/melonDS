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

#include <stdio.h> //needed for something
#include "../Platform.h"
#include "../Slot2.hpp"

u16 RumblePak::Read16(u32 addr)
{
    // GBATEK: For detection, AD1 seems to be pulled low when reading from it... (while) the other AD lines are open bus (containing the halfword address)...
    // GBATEK with bit 6 set is based on empirical data...
    // This should allow commercial games to properly detect the Rumble Pak.
    // Credit to rzumer for coming up with this algorithm...
    u16 lodata = ((addr | 0x40) & 0xFD);
    return (addr & 1) ? addr : lodata;
}

void RumblePak::Write16(u32 addr, u16 val)
{
    // Ported from GBE+...
    if (addr == 0x8000000 || addr == 0x8001000 && RumbleState != val)
    {
        Platform::StopRumble();
        RumbleState = val;
        Platform::StartRumble();
        printf("brr\n");
    }
};
