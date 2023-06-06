#pragma once

#include <iostream>

struct nodeQ
{
    long long besaran;
    std::string label;
    int priority;
    nodeQ* next;
};

typedef nodeQ* pointerQ;

struct queue
{
    pointerQ head;
    pointerQ tail;
};

void createQueue(queue &q)
{
    q.head = nullptr;
    q.tail = nullptr;
}

void createQueueElement(pointerQ &newQ, long long besaran, std::string label, int priority)
{
    newQ = new nodeQ;
    newQ->besaran = besaran;
    newQ->priority = priority;
    newQ->label = label;
    newQ->next = nullptr;
}

void enqueue(queue &q, pointerQ newQ)
{
    if (q.head == nullptr)
    {
        q.head = newQ;
        q.tail = newQ;
        return;
    }
    
    pointerQ temp = q.head;
    pointerQ tempPrev = nullptr;

    while (temp->next != nullptr && newQ->priority >= temp->priority)
    {
        tempPrev = temp;
        temp = temp->next;
    }

    if (newQ->priority < temp->priority)
    {
        if (temp == q.head)
        {
            newQ->next = q.head;
            q.head = newQ;
        }
        else
        {
            tempPrev->next = newQ;
            newQ->next = temp;
        }
    }
    else
    {
        temp->next = newQ;
        q.tail = newQ;
    }
}