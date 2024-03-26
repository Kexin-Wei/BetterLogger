#include "src/Logger.h"
#include <iostream>

using Logger = ultrast::infrastructure::utility::Logger;
int main()
{
    std::cout << "Hello, World!" << std::endl;
    Logger::trace("Hello, World!");
    return 0;
}