
#include <iostream>
#include <stdlib.h>
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
    int efficiency;
};

Pipe Create_pipe()
{
    Pipe p = {}; //pipe is set up and values are zeroed
    p.id = 0;
    p.Repair = 0;
    cout << "Input pipe diameter: ";
    cin >> p.d;
    cout << "Input pipe length: ";
    cin >> p.l;
    return p;
}

Station Create_station()
{
    Station s = {};
    s.id = 0;
    cout << "Input total station divisions: ";
    cin >> s.total_divisions;
    cout << "Input working divisions: ";
    cin >> s.working_divisions;
    cout << "Input station efficiency: ";
    cin >> s.efficiency;
    return s;
}

void PipeOutput(Pipe& p)
{
    cout << "Pipe ID:" << p.id << endl;
    cout << "Pipe diameter:" << p.d << endl;
    cout << "Pipe length:" << p.l << endl;
    cout << "Pipe repair status:" << p.Repair << endl;
}

void StationOutput(Station& s)
{
    cout << "Station ID:" << s.id << endl;
    cout << "Total divisions:" << s.total_divisions << endl;
    cout << "Working divisions:" << s.working_divisions << endl;
    cout << "Efficiency:" << s.efficiency << endl;
}

int main()
{
    int pipe_total = 0;
    int station_total = 0;
    while (1)
    {
        int a = 0;
        cout << "Choose option:" << endl << endl << "1. Add pipe" << endl << "2. Add station" << endl << "3. List info on all objects" << endl << "4. Edit pipe" << endl << "5. Edit station" << endl << "6. Save" << endl << "7. Load" << endl << "0. Exit"<<endl;
        cin >> a;
        switch (a)
        {
        case 1: 
            Pipe p = Create_pipe();
            cout << "Pipe created"<<endl;
            if (pipe_total == 0)
            {
                ++pipe_total;
            }
            break;
        case 2:
            Station s = Create_station();
            cout << "Station created"<<endl;
            if (station_total == 0)
            {
                ++station_total;
            }
            break;
        case 3:
            cout << "Total pipes: " << pipe_total << endl << "Total stations: " << station_total << endl<< endl;
            if (pipe_total > 0)
            {
                PipeOutput(p);
            }
            if (station_total > 0)
            {
                StationOutput(s);
            }
            break;
        case 4:
            if (pipe_total > 0)
            {
                cout << "Choose option:" << endl << endl << "1. Change diameter" << endl << "2. Change length" << endl << "3. Change repair status" << endl << "0. Back";
                cin >> a;
                switch (a)
                {
                case 1:
                    cout << "Input diameter:" << endl;
                    cin >> p.d;
                    break;
                case 2:
                    cout << "Input length:" << endl;
                    cin >> p.l;
                    break;
                case 3:
                    cout << "Input repair status:" << endl;
                    cin >> p.Repair;
                    break;
                case 0:
                    break;
                }
            }
        case 5:
            if (station_total > 0)
            {
                cout << "Choose option:" << endl << endl << "1. Change total divisions" << endl << "2. Change working divisions" << endl << "3. Change efficiency" << endl << "0. Back";
                cin >> a;
                switch (a)
                {
                case 1:
                    cout << "Input total divisions:" << endl;
                    cin >> s.total_divisions;
                    break;
                case 2:
                    cout << "Input working divisions:" << endl;
                    cin >> s.working_divisions;
                    break;
                case 3:
                    cout << "Input efficiency:" << endl;
                    cin >> s.efficiency;
                    break;
                case 0:
                    break;
                }
            }
        }
    }
}
