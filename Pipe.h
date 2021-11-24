#pragma once

#include <iostream>

class Pipe
{
public:
    int id;
    static int NextID;
    int d;
    float l;
    bool Repair;

    void PipeOutput();

    void EditPipe(int& a);

    int give_id();
};
