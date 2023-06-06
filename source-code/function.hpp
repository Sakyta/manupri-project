#pragma once

#include "../data-structures/list.hpp"
#include "../data-structures/queue.hpp"
#include "../data-structures/stack.hpp"
#include "global-menu.hpp"
#include <iomanip>

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
              << "[Input Budgeting]\n\n";

    if (head != nullptr)
    {
        std::cout << "Kamu Udah Set Budget Kamu Kok!\n";
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
            massage_handling("Budget Sudah Terbagi Rata");
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
            error_handling("Budget Tidak Dapat Dibagi Rata");
            head == nullptr;
            return getPercentage(head);
        }

        temp = temp->next;
    }

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

    std::cout << "Tagihan Apa\n>> ";
    std::cin.ignore();
    std::getline(std::cin, label);
    std::cout << "Tagihannya Berapa\n>> ";
    std::cin >> besaran;

    if (besaran < 0)
    {
        error_handling("Besaran Harus Positif");
        return getBill(q);
    }
    getPriority(priority);

    createQueueElement(newQ, besaran, label, priority);
    enqueue(q, newQ);

    refresh_ui();
}

void print_main_menu(long long data)
{
    if (data == 0)
    {
        std::cout << '-';
    }
    else
    {
        std::cout << "Rp " << std::to_string(data);
    }
}

void printTagihan(queue &q)
{
    pointerQ current = q.head;
    int count = 1;

    const int countWidth = 5;
    const int labelWidth = 20;
    const int besaranWidth = 16;

    if (q.head == nullptr)
    {
        massage_handling("Belum Ada Tagihan!\n");
        return;
    }

    std::cout << std::left << std::setw(countWidth) << "No."
              << std::setw(besaranWidth) << "Besaran Tagihan"
              << std::setw(labelWidth) << "Keterangan Tagihan"
              << "\n";

    while (current != nullptr)
    {
        std::cout << std::setw(countWidth) << count
                  << std::setw(besaranWidth) << current->besaran
                  << std::setw(current->label.length()) << current->label
                  << "\n";

        current = current->next;
        count++;
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
    pushBack(top, newStack);
}

stack make_operand(list head, queue q)
{
    stack operation;
    createStack(operation);

    pointerQ temp = q.head;
    stack nStack;
    
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

    list tempL = head;

    while (tempL != nullptr)
    {
        insertForTimes(operation, nStack, tempL);

        tempL = tempL->next;
    }

    return operation;
}

void calculate(list head, queue q, long long income)
{
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

    std::cout << "Keuangan Kamu Bulan Ini Adalah : " << std::to_string(income) << "\n\n";

    while (label != nullptr)
    {
        if (temp == nullptr)
        {
            break;
        }
        long long perhitungan = (temp->operand * income) / 100;
        std::cout << "Keuangan Kamu Untuk " << label->label << " Adalah : " << std::to_string(perhitungan) << "\n";

        label = label->next;
        temp = temp->next;
    }
    
    refresh_ui();
}