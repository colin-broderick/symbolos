#ifndef SYMBOL_TERMINAL_HPP
#define SYMBOL_TERMINAL_HPP

namespace Terminal
{
    void initialise();
    void setcolour(const VGAColour colour);
    void write_string(const char* data);
    void write_line(const char* data);
}

#endif // SYMBOL_TERMINAL_HPP