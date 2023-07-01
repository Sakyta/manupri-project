#pragma once

#include <iostream>

struct element
{
    long long operand;
    element* next;
};

typedef element* stack;

bool isEmpty(stack top)
{
    if (top == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void createStack(stack &top)
{
    top = nullptr;
}

void createStackElement(stack &newStack, long long operand)
{
    newStack = new element;
    newStack->operand = operand;
    newStack->next = nullptr;
}

void push(stack &top, stack newStack)
{
    if (isEmpty(top))
    {
        top = newStack;
    }
    else
    {
        newStack->next = top;
        top = newStack;
    }
}

long long pop(stack &top)
{
    stack pDel = top;
    long long num = pDel->operand;
    top = top->next;
    delete pDel;

    return num;
}