#include <cstdint>

#include "symbollib.hpp"
#include "vga.hpp"

namespace Terminal
{
    namespace
    {
        std::size_t terminal_row;
        std::size_t terminal_column;
        VGAColour terminal_colour;
        uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;

    }

    /** \brief Initialise the terminal
     */
    void initialise()
    {
        terminal_row = 0;
        terminal_column = 0;
        terminal_colour = vga_entry_colour(VGAColour::White, VGAColour::Blue);
        for (auto y = 0u; y < VGA_HEIGHT; y++)
        {
            for (auto x = 0u; x < VGA_WIDTH; x++)
            {
                const auto index = y * VGA_WIDTH + x;
                terminal_buffer[index] = vga_entry(' ', terminal_colour);
            }
        }
    }

    /** \brief Set the terminal colour
     * \param colour The new terminal colour
     */
    void set_colour(const VGAColour colour)
    {
        terminal_colour = colour;
    }

    /** \brief Put a character entry at a specific position
     * \param character The character
     * \param colour The colour
     * \param x The x position
     * \param y The y position
     */
    void put_entry_at(const char character, const VGAColour colour, const std::size_t x, const std::size_t y)
    {
        const auto index = y * VGA_WIDTH + x;
        terminal_buffer[index] = vga_entry(character, colour);
    }

    /** \brief Scroll the terminal up by one line
     */
    void scroll()
    {
        for (auto y = 1u; y < VGA_HEIGHT; y++)
        {
            for (auto x = 0u; x < VGA_WIDTH; x++)
            {
                const auto from_index = y * VGA_WIDTH + x;
                const auto to_index = (y - 1) * VGA_WIDTH + x;
                terminal_buffer[to_index] = terminal_buffer[from_index];
            }
        }
        for (auto x = 0u; x < VGA_WIDTH; x++)
        {
            const auto index = (VGA_HEIGHT - 1) * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_colour);
        }
    }

    /** \brief Put a character entry at the current cursor position
     * \param character The character
     */
    void put_character(const char character)
    {
        if (character == '\n')
        {
            terminal_column = 0;
            if (++terminal_row == VGA_HEIGHT)
            {
                terminal_row = VGA_HEIGHT - 1;
                scroll();
            }
            return;
        }
        Terminal::put_entry_at(character, terminal_colour, terminal_column, terminal_row);
        if (++terminal_column == VGA_WIDTH)
        {
            terminal_column = 0;
            if (++terminal_row == VGA_HEIGHT)
            {
                terminal_row = VGA_HEIGHT - 1;
                scroll();
            }
        }
    }

    /** \brief Write data to the terminal
     * \param data The data to write
     * \param size The size of the data
     */
    void write(const char* data, const std::size_t size)
    {
        for (auto i = 0u; i < size; i++)
        {
            Terminal::put_character(data[i]);
        }
    }

    /** \brief Write a null-terminated string to the terminal
     * \param data The string to write
     */
    void write_string(const char* data)
    {
        Terminal::write(data, String::length(data));
    }
    
    /** \brief Write a line to the terminal
     * \param data The string to write
     */
    void write_line(const char* data)
    {
        Terminal::write_string(data);
        Terminal::put_character('\n');
    }
}
