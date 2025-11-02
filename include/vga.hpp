#ifndef SYMBOL_VGA_HPP
#define SYMBOL_VGA_HPP

#include <cstdint>

inline constexpr auto VGA_WIDTH = 80u;
inline constexpr auto VGA_HEIGHT = 25u;
inline constexpr auto VGA_MEMORY = 0xB8000u;

enum class VGAColour : uint8_t
{
    Black,
    Blue,
    Green,
    Cyan,
    Red,
    Magenta,
    Brown,
    LightGrey,
    DarkGrey,
    LightBlue,
    LightGreen,
    LightCyan,
    LightRed,
    LightMagenta,
    LightBrown,
    White
};

VGAColour vga_entry_colour(const VGAColour foreground, const VGAColour background);
uint16_t vga_entry(const unsigned char character, const VGAColour colour);

#endif // SYMBOL_VGA_HPP
