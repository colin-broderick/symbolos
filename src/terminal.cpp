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
    void initialise()
    {
        terminal_row = 0;
        terminal_column = 0;
        terminal_colour = vga_entry_colour(VGAColour::LightGrey, VGAColour::Black);
        for (auto y = 0u; y < VGA_HEIGHT; y++)
        {
            for (auto x = 0u; x < VGA_WIDTH; x++)
            {
                const auto index = y * VGA_WIDTH + x;
                terminal_buffer[index] = vga_entry(' ', terminal_colour);
            }
        }
    }
    
    void setcolour(const VGAColour colour)
    {
        terminal_colour = colour;
    }
    
    void put_entry_at(const char c, const VGAColour colour, const std::size_t x, const std::size_t y)
    {
        const auto index = y * VGA_WIDTH + x;
        terminal_buffer[index] = vga_entry(c, colour);
    }
    
    void put_character(const char c)
    {
        if (c == '\n')
        {
            terminal_column = 0;
            if (++terminal_row == VGA_HEIGHT)
            {
                terminal_row = 0;
            }
            return;
        }
        Terminal::put_entry_at(c, terminal_colour, terminal_column, terminal_row);
        if (++terminal_column == VGA_WIDTH)
        {
            terminal_column = 0;
            if (++terminal_row == VGA_HEIGHT)
            {
                terminal_row = 0;
            }
        }
    }
    
    void write(const char* data, const std::size_t size)
    {
        for (auto i = 0u; i < size; i++)
        {
            Terminal::put_character(data[i]);
        }
    }
    
    void write_string(const char* data)
    {
        Terminal::write(data, strlen(data));
    }
    
    void write_line(const char* data)
    {
        Terminal::write_string(data);
        Terminal::put_character('\n');
    }
}
