
#include <iostream>
using namespace std;
struct Pipe
{
    int id;
    int d;
    float l;
    bool Repair;
};

struct Station
{
    int id;
    int total_divisions;
    int working_divisions;
};

void PipeOutput(Pipe& pipe1);

Pipe Create_pipe()
{
    Pipe p = {}; //pipe is set up and values are zeroed
    p.id = 0;
    p.Repair = 1;
    cout << "Input pipe diameter:";
    cin >> p.d;
    cout << "Input pipe length:";
    cin >> p.l;
    return p;
}

int main()
{
    Pipe pipe1 = Create_pipe();

    PipeOutput(pipe1);

}

void PipeOutput(Pipe& pipe1)
{
    cout << "Pipe ID:" << pipe1.id << endl;
    cout << "Pipe diameter:" << pipe1.d << endl;
    cout << "Pipe length:" << pipe1.l << endl;
}
