#include <cstddef>      // ensures byte is defined first
#include <iostream>
#include <string>
#include <memory>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>    // required for console color
#ifdef byte
#undef byte             // prevent conflict with std::byte
#endif

#include "ui/cli/CLI.hpp"

int main() {
    // Enable ANSI escape codes on Windows 10+
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        }
    }

    ui::CLI cli;
    cli.run();
    return 0;
}
