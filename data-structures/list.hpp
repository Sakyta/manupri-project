#pragma once
#include <iostream>

struct doublylinkedlist
{
    long long persenan;
    std::string label;
    doublylinkedlist* next;
    doublylinkedlist* prev;  
};

typedef doublylinkedlist* list;

void createList(list &head)
{
    head = nullptr;
}

void createListElement(list &newNode, long long persenan, std::string label)
{
    newNode = new doublylinkedlist;
    newNode->persenan = persenan;
    newNode->label = label;
    newNode->next = nullptr;
    newNode->prev = nullptr;
}

void insertLast(list &head, list newNode)
{
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        list help = head;
        while (help->next != nullptr)
        {
            help = help->next;
        }
        help->next = newNode;
        newNode->prev = help;
    }
}