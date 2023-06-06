#pragma once

#include <iostream>
#include "function.hpp"

void menu_input_pemasukkan(double &pemasukkan)
{
    std::cout << "[Manupri]\n\n"
              << "[Input Pemasukkan]\n\n";
    int input;
    if (pemasukkan != 0)
    {
        std::cout << "Kamu Udah Input Pemasukkan Kamu Kok!\n";
        std::cout << "Pemasukkan Kamu Bulan Ini Adalah : Rp " << pemasukkan << "\n";
        std::cout << "\n(1) Edit Pemasukkan\n";
        std::cout << "(2) Kembali\n\n>> ";
        std::cin >> input;
        std::cout << "\n";
        switch (input)
        {
        case 1:
            refresh_ui();
            pemasukkan = 0;
            return menu_input_pemasukkan(pemasukkan);
            break;
        default:
            refresh_ui();
            return;
            break;
        }
    }
    std::cout << "Input Pemasukkan : ";
    std::cin >> pemasukkan;

    if (pemasukkan < 0)
    {
        error_handling("Input Harus Positif");
        return menu_input_pemasukkan(pemasukkan);
    }

    refresh_ui();
}

void menu_input_tagihan(queue &q)
{
    std::cout << "[Manupri]\n\n"
              << "[Input Tagihan]\n\n";
    getBill(q);
}

void menu_cek_tagihan(queue q)
{
    std::cout << "[Manupri]\n\n"
              << "[Cek Tagihan]\n\n";
    printTagihan(q);
}

void menu_calculate(list head, queue q, double &income)
{
    std::cout << "[Manupri]\n\n"
              << "[Calculate]\n\n";
    calculate(head, q, income);
}

void menu()
{
    double pemasukkan = 0;
    queue tagihan;
    createQueue(tagihan);
    list budget;
    createList(budget);

    int pilihan;
    do
    {
        std::cout << "[Manupri]\n\n"
                  << "Pemasukkan       : ";
        print_main_menu(pemasukkan);
        std::cout << "\nTotal Tagihan    : " << count_tagihan(tagihan) << "\n\n"
                  << "1. Input Pemasukkan\n"
                  << "2. Input Budgeting\n"
                  << "3. Input Tagihan\n"
                  << "4. Cek Tagihan\n"
                  << "5. Calculate\n"
                  << "0. Exit Program\n\n"
                  << ">> ";
        std::cin >> pilihan;
        refresh_ui();

        switch (pilihan)
        {
        case 1:
            menu_input_pemasukkan(pemasukkan);
            break;
        case 2:
            getPercentage(budget);
            break;
        case 3:
            menu_input_tagihan(tagihan);
            break;
        case 4:
            menu_cek_tagihan(tagihan);
            break;
        case 5:
            menu_calculate(budget, tagihan, pemasukkan);
            break;
        case 0:
            break;
        default:
            std::cout << "[Manupri]\n\n";
            error_handling("Pilihan Tidak Valid");

            refresh_ui();
            break;
        }
    } while (pilihan != 0);
}