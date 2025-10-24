#include <cstdint>

#include "vga.hpp"

VGAColour vga_entry_colour(const VGAColour foreground, const VGAColour background)
{
    return static_cast<VGAColour>((static_cast<uint8_t>(background) << 4) | static_cast<uint8_t>(foreground));
}

uint16_t vga_entry(const unsigned char uc, const VGAColour colour)
{
    return static_cast<uint16_t>(uc) | (static_cast<uint16_t>(colour) << 8);
}
