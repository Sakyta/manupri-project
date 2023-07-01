#pragma once

#include "function.hpp"

void menu_input_pemasukkan(double &pemasukkan)
{
    std::cout << "[Manupri]\n\n";
    int input;
    if (pemasukkan != 0)
    {
        std::cout << "[Edit/Tambah Pemasukkan]\n\n";
        std::cout << "Pemasukkan Kamu Bulan Ini Adalah : Rp " << pemasukkan << "\n";
        std::cout << "\n(1) Edit Pemasukkan\n";
        std::cout << "(2) Tambah Pemasukkan\n";
        std::cout << "(3) Kembali\n\n>> ";
        std::cin >> input;
        std::cout << "\n";
        switch (input)
        {
        case 1:
            refresh_ui();
            pemasukkan = 0;
            return menu_input_pemasukkan(pemasukkan);
            break;
        case 2:
            refresh_ui();
            std::cout << "[Manupri]\n\n"
                      << "[Tambah Pemasukkan]\n\n";
            int temp;
            std::cout << "Input Pemasukkan Tambahan : ";
            std::cin >> temp;
            std::cout << "\n";
            pemasukkan += temp;
            refresh_ui();
            return;
            break;
        default:
            refresh_ui();
            return;
            break;
        }
    }

    std::cout << "[Input Pemasukkan]\n\n";
    std::cout << "Input Pemasukkan : ";
    std::cin >> pemasukkan;
    std::cout << "\n";

    if (std::cin.fail())
    {
        error_handling("Input Harus Merupakan Angka!\n");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return menu_input_pemasukkan(pemasukkan);
    }

    if (pemasukkan < 0)
    {
        error_handling("Input Harus Positif\n");
        pemasukkan = 0;
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
        std::cout << "\nTotal Tagihan    : " << count_tagihan(tagihan) << "\n\n";
        if (pemasukkan == 0)
        {
            std::cout << "1. Input Pemasukkan\n";
        }
        else
        {
            std::cout << "1. Edit/Tambah Pemasukkan\n";
        }
        std::cout << "2. Budgeting\n"
                  << "3. Input Tagihan\n"
                  << "4. Cek Tagihan\n"
                  << "5. Calculate\n"
                  << "0. Exit Program\n\n"
                  << ">> ";
        std::cin >> pilihan;
        std::cout << "\n";
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
            error_handling("Pilihan Tidak Valid\n");
            break;
        }
    } while (pilihan != 0);
}