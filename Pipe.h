#pragma once

#include <iostream>
#include "Station.h"

class Pipe
{
private:
    int id;
public:
    static int NextID;
    int d;
    float l;
    bool Repair;
    int start;
    int end;

    void EditPipe(int& a);

    int give_id();

    friend std::istream& operator >> (std::istream& in, Pipe& pipe);

    friend std::ostream& operator << (std::ostream& out, const Pipe& pipe);

    Pipe();
};
