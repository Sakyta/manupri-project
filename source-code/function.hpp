#pragma once

#include "../data-structures/list.hpp"
#include "../data-structures/queue.hpp"
#include "../data-structures/stack.hpp"
#include "global-menu.hpp"
#include <iomanip>
#include <limits>

std::string make_rupiah(long long angka)
{
    std::string output = std::to_string(angka);
    int panjang = output.length();
    int jumlah_titik = panjang / 3;

    for (int i = 1; i <= jumlah_titik; i++)
    {
        if (panjang != 3 * i)
        {
            output.insert(panjang - (3 * i), ".");
        }
    }

    return output;
}

list makeBudgeting()
{
    list newHead;
    createList(newHead);

    list newNode;
    createListElement(newNode, 0, "Makan & Minum");
    insertLast(newHead, newNode);
    createListElement(newNode, 0, "Transportasi");
    insertLast(newHead, newNode);
    createListElement(newNode, 0, "Hiburan");
    insertLast(newHead, newNode);
    createListElement(newNode, 0, "Kesehatan & Olahraga");
    insertLast(newHead, newNode);
    createListElement(newNode, 0, "Belanja");
    insertLast(newHead, newNode);
    createListElement(newNode, 0, "Edukasi");
    insertLast(newHead, newNode);
    createListElement(newNode, 0, "Dana Darurat");
    insertLast(newHead, newNode);

    return newHead;
}

void printBudgeting(list head)
{
    list curr = head;
    while (curr != nullptr)
    {
        std::cout << curr->label << " : " << curr->persenan << "%\n";
        
        curr = curr->next;
    }
}

void getPercentage(list &head)
{
    list temp = makeBudgeting(), nList;
    int counter = 100;
    int inputNumber, input;

    std::cout << "[Manupri]\n\n"
              << "[Budgeting]\n\n";

    if (head != nullptr)
    {
        std::cout << "Kamu Udah Set Budget Kamu!\n";
        printBudgeting(head);
        std::cout << "\n(1) Edit Budgeting\n";
        std::cout << "(2) Kembali\n\n>> ";
        std::cin >> input;
        std::cout << "\n";
        switch (input)
        {
        case 1:
            refresh_ui();
            head = nullptr;
            return getPercentage(head);
            break;
        default:
            refresh_ui();
            return;
            break;
        }
    }

    while (temp != nullptr)
    {
        if (counter <= 0)
        {
            massage_handling("Budget Sudah Terbagi Rata\n");
            return;
        }

        std::cout << "Masukan Persentase Budget Untuk " << temp->label << " (" << counter << "%)\n>> ";
        std::cin >> inputNumber;
        if (inputNumber <= counter)
        {
            counter -= inputNumber;
            createListElement(nList, inputNumber, temp->label);
            insertLast(head, nList);
        }
        else
        {
            std::cout << "\n";
            error_handling("Budget Tidak Dapat Dibagi Rata\n");
            head = nullptr;
            return getPercentage(head);
        }

        temp = temp->next;
    }

    std::cout << "\n";
    refresh_ui();
}

int count_tagihan(queue q)
{
    queue help = q;
    int counter = 0;
    while (help.head != nullptr)
    {
        counter++;
        help.head = help.head->next;
    }

    return counter;
}

void getPriority(int &priority)
{
    int pilihan, bulanDepan;
    std::cout << "Pada bulan apa tagihan harus dibayar?\n"
              << "(1) Bulan Ini\n"
              << "(2) Bulan Berikutnya\n>> ";
    std::cin >> pilihan;
    if (pilihan == 1)
    {
        priority = 1;
    }
    else
    {
        std::cout << "Berapa Bulan Lagi Tagihan Harus Dibayar\n>> ";
        std::cin >> bulanDepan;
        priority = bulanDepan + 1;
    }
}

void getBill(queue &q)
{
    pointerQ newQ;

    long long besaran;
    std::string label;
    int priority;

    std::cout << "Nama Tagihan\n>> ";
    std::cin.ignore();
    std::getline(std::cin, label);
    std::cout << "Besaran Tagihan\n>> ";
    std::cin >> besaran;

    if (std::cin.fail())
    {
        std::cout << "\n";
        error_handling("Input Harus Merupakan Angka!\n");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "[Manupri]\n\n"
                  << "[Input Tagihan]\n\n";
        return getBill(q);
    }

    if (besaran < 0)
    {
        std::cout << "\n";
        error_handling("Besaran Harus Positif\n");

        std::cout << "[Manupri]\n\n"
                  << "[Input Tagihan]\n\n";
        return getBill(q);
    }
    getPriority(priority);

    createQueueElement(newQ, besaran, label, priority);
    enqueue(q, newQ);

    std::cout << "\n";
    refresh_ui();
}

void print_main_menu(double data)
{
    if (data == 0)
    {
        std::cout << '-';
    }
    else
    {
        std::cout << "Rp " << make_rupiah(data);
    }
}

void printTagihan(queue q)
{
    pointerQ current = q.head;
    int count = 1;

    const int countWidth = 5;
    const int labelWidth = 20;
    const int besaranWidth = 16;
    const int bulanWidth = 11;

    if (q.head == nullptr)
    {
        massage_handling("Belum Ada Tagihan!\n");
        return;
    }

    std::cout << "Tagihan Bulan Ini\n\n";

    std::cout << std::left << std::setw(countWidth) << "No."
              << std::setw(besaranWidth) << "Besaran Tagihan"
              << std::setw(labelWidth) << "Keterangan Tagihan"
              << "\n";

    if (current->priority > 1)
    {
        std::cout << "Belum Ada Tagihan!\n";
    }

    while (current != nullptr)
    {
        if (current->priority > 1)
        {
            break;
        }
        if (current->priority == 1)
        {
            std::cout << std::setw(countWidth) << count
                      << std::setw(besaranWidth) << make_rupiah(current->besaran)
                      << std::setw(current->label.length()) << current->label
                      << "\n";

            current = current->next;
            count++;
        }
        else
        {
            break;
        }
    }
    
    if (current == nullptr)
    {
        std::cout << "\nTagihan Bulan Selanjutnya\n\n";
        std::cout << "Belum Ada Tagihan!\n";
    }
    else
    {
        count = 1;
        std::cout << "\nTagihan Bulan Selanjutnya\n\n";

        std::cout << std::left << std::setw(countWidth) << "No."
                  << std::setw(besaranWidth) << "Besaran Tagihan"
                  << std::setw(bulanWidth) << "Sisa Bulan"
                  << std::setw(labelWidth) << "Keterangan Tagihan"
                  << "\n";

        while (current != nullptr)
        {
            int bulan = current->priority - 1;
            std::cout << std::setw(countWidth) << count
                      << std::setw(besaranWidth) << make_rupiah(current->besaran)
                      << std::setw(bulanWidth) << bulan
                      << std::setw(current->label.length()) << current->label
                      << "\n";

            current = current->next;
            count++;
        }
    }
    std::cout << "\n";

    refresh_ui();
}

void insertForSubtracting(stack &top, stack &newStack, pointerQ q)
{
    createStackElement(newStack, q->besaran);
    push(top, newStack);
}

void insertForTimes(stack &top, stack &newStack, list head)
{
    createStackElement(newStack, head->persenan);
    push(top, newStack);
}

stack make_operand(list head, queue q)
{
    stack operation;
    createStack(operation);

    pointerQ temp = q.head;
    stack nStack;

    list tempL = head;

    while (tempL->next != nullptr)
    {
        tempL = tempL->next;
    }

    while (tempL != nullptr)
    {
        insertForTimes(operation, nStack, tempL);

        tempL = tempL->prev;
    }

    while (temp != nullptr)
    {
        if (temp->priority != 1)
        {
            break;
        }
        else
        {
            insertForSubtracting(operation, nStack, temp);

            temp = temp->next;
        }
    }

    return operation;
}

void calculate(list head, queue q, long long income)
{
    if (income == 0)
    {
        error_handling("Mohon Input Pemasukkan Anda Terlebih Dahulu!\n");
        return;
    }

    if (head == nullptr)
    {
        error_handling("Mohon Buat Budgeting Terlebih Dahulu!\n");
        return;
    }
    
    stack operation = make_operand(head, q);

    stack temp = operation;
    list label = head;

    if (temp->operand > income)
    {
        massage_handling("Keuangan Kamu Over Budget!!!\n");
        return;
    }

    while (temp != nullptr)
    {   
        if (temp->operand > 1000)
        {
            long long num = pop(temp);
            income -= num;
        }
        else
        {
            break;
        }
    }

    std::cout << "Keuangan Kamu Bulan Ini Adalah : Rp " << make_rupiah(income) << "\n\n";

    long long sisa;
    while (label != nullptr)
    {
        if (temp == nullptr)
        {
            break;
        }
        long long perhitungan = (temp->operand * income) / 100;
        sisa += perhitungan;
        std::cout << "Keuangan Kamu Untuk " << label->label << " Adalah : Rp " << make_rupiah(perhitungan) << "\n";

        label = label->next;
        temp = temp->next;
    }

    if (sisa != income)
    {
        std::cout << "\nSisa Uang Kamu Sebesar : Rp " << income - sisa << "\n\n";
    }
    
    std::cout << "\n";
    refresh_ui();
}