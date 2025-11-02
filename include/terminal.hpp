#ifndef SYMBOL_TERMINAL_HPP
#define SYMBOL_TERMINAL_HPP

namespace Terminal
{
    void initialise();
    void write_string(const char* data);
    void write_line(const char* data);
    void scroll();
}

#endif // SYMBOL_TERMINAL_HPP