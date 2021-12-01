#include "Pipe.h"
#include "Checks.h"
#include <iostream>
#include "Station.h"
#include <unordered_map>

using namespace std;

int Pipe::NextID = 0;

    void Pipe::PipeOutput()
    {
        cout << "Pipe ID:" << id << endl;
        cout << "Pipe diameter:" << d << endl;
        cout << "Pipe length:" << l << endl;
        cout << "Pipe repair status:" << Repair << endl;
        if (start == -1 and end == -1)
            cout << "Pipe unconnected" << endl;
        else
        {
            cout << "Pipe start:" << start << endl;
            cout << "Pipe end:" << end << endl;
        }
    }

    void Pipe::EditPipe(int& a)
    {
        {
            cout << "Choose option:" << endl << endl << "1. Change diameter" << endl << "2. Change length" << endl << "3. Change repair status" << endl << "0. Back" << endl;
            a = intCheck();
            switch (a)
            {
            case 1:
                cout << "Input diameter:" << endl;
                d = intCheck();
                break;
            case 2:
                cout << "Input length:" << endl;
                l = floatCheck();
                break;
            case 3:
                cout << "Input repair status (1 - curently repairing; 0 - not repairing):" << endl;
                Repair = booleanCheck();
                break;
            case 0:
                break;
            }
        }
    }

    int Pipe::give_id()
    {
        return id;
    }

    std::istream& operator >> (std::istream& in, Pipe& Pipe)
    {
        string value;
        getline(in, value);
        Pipe.id = stoi(value);
        return in;
    }

    Pipe::Pipe(void):id(Pipe::NextID)
    {
        
    }

    Pipe& Pipe::Create_pipe(Pipe& p)
    {
        p.start = -1;
        p.end = -1;
        p.Repair = false;
        cout << "Input pipe diameter: ";
        p.d = intCheck();
        cout << "Input pipe length: ";
        p.l = floatCheck(0);
        return p;
    }