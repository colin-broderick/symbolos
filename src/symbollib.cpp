#include <cstdint>

namespace String
{
    std::size_t length(const char* string)
    {
        std::size_t length = 0;
        while (string[length])
        {
            length++;
        }
        return length;
    }
}
