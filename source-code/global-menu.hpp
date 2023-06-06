#pragma once

#include <iostream>
#include <conio.h>

void refresh_ui()
{
    std::cout << "Tekan Apapun Untuk Melanjutkan...\n";
    getch();
    std::cout << "\033[2J\033[1;1H";
}

void error_handling(std::string s)
{
    std::cout << "ERROR\n";
    std::cout << s << "\n";
    refresh_ui();
}

void massage_handling(std::string s)
{
    std::cout << s << "\n";
    refresh_ui();
}