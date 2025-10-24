#include <cstdint>

#include "vga.hpp"
#include "terminal.hpp"

extern "C" void kernel_main()
{
    Terminal::initialise();
    Terminal::write_line("Hello, kernel!");
    Terminal::write_line("And another line of text.");
}
