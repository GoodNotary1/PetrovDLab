#include "Pipe.h"
#include "Checks.h"
#include <iostream>
#include "Station.h"
#include <unordered_map>

using namespace std;

int Pipe::NextID = 0;

void Pipe::EditPipe(int& a)
{
    cout << "Input repair status (1 - curently repairing; 0 - not repairing):" << endl;
    Repair = booleanCheck();
}

int Pipe::give_id()
{
    return id;
}

std::istream& operator >> (std::istream& in, Pipe& pipe)
{
    string value;
    getline(in, value);
    pipe.id = stoi(value);
    getline(in, value);
    pipe.d = stoi(value);
    getline(in, value);
    pipe.l = stof(value);
    getline(in, value);
    pipe.Repair = stoi(value);
    getline(in, value);
    pipe.start = stoi(value);
    getline(in, value);
    pipe.end = stoi(value);
    return in;
}

std::ostream& operator << (std::ostream& out, const Pipe& pipe)
{
    if (pipe.start == -1 and pipe.end == -1)
        out << "Pipe ID:" << pipe.id << endl
        << "Pipe diameter:" << pipe.d << endl
        << "Pipe length:" << pipe.l << endl
        << "Pipe repair status:" << pipe.Repair << endl
        << "Pipe unconnected" << endl;
    else
        out << "Pipe ID:" << pipe.id << endl 
        << "Pipe diameter:" << pipe.d << endl 
        << "Pipe length:" << pipe.l << endl 
        << "Pipe repair status:" << pipe.Repair << endl 
        << "Pipe start:" << pipe.start << endl 
        << "Pipe end:" << pipe.end << endl;
    return out;
}

Pipe::Pipe(void) :id(Pipe::NextID)
{

}