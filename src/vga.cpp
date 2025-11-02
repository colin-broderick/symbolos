#include <cstdint>

#include "vga.hpp"

/** \brief Get the VGA colour entry for a given foreground and background colour
 * \param foreground The foreground colour
 * \param background The background colour
 * \return The combined VGA colour
 */
VGAColour vga_entry_colour(const VGAColour foreground, const VGAColour background)
{
    return static_cast<VGAColour>((static_cast<uint8_t>(background) << 4) | static_cast<uint8_t>(foreground));
}

/** \brief Get the VGA entry for a given character and colour
 * \param character The character
 * \param colour The colour
 * \return The combined VGA entry
 */
uint16_t vga_entry(const unsigned char character, const VGAColour colour)
{
    return static_cast<uint16_t>(character) | (static_cast<uint16_t>(colour) << 8);
}
