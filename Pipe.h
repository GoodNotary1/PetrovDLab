#pragma once

#include <iostream>

class Pipe
{
private:
    int id;
public:
    static int NextID;
    int d;
    float l;
    bool Repair;

    void PipeOutput();

    void EditPipe(int& a);

    int give_id();

    friend std::istream& operator >> (std::istream& in, Pipe& Pipe);

    Pipe();

    Pipe& Create_pipe(Pipe& p);
};
