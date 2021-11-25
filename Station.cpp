#include "Station.h"
#include <string>
#include <iostream>
#include "Checks.h"
using namespace std;

int Station::NextID = 0;

    void Station::StationOutput()
    {
        cout << "Station ID:" << id << endl;
        cout << "Station name:" << station_name << endl;
        cout << "Total divisions:" << total_divisions << endl;
        cout << "Working divisions:" << working_divisions << endl;
        cout << "Efficiency:" << efficiency << endl;
    }

    void Station::EditStation(int& a)
    {
        {
            cout << "Choose option:" << endl << endl << "0. Back" << endl << "1. Change name" << endl << "2. Change efficiency" << endl << "3. Change stations" << endl;
            a = intCheck();
            switch (a)
            {
            case 0:
                break;
            case 1:
                cout << "Input name:" << endl;
                station_name = stringCheck();
                break;
            case 2:
                cout << "Input efficiency:" << endl;
                efficiency = intCheck(0, 100);
                break;
            case 3:
                while (1)
                {
                    cout << "Input total station divisions: ";
                    total_divisions = intCheck();
                    cout << "Input working divisions: ";
                    working_divisions = intCheck();
                    if (working_divisions > total_divisions)
                        cout << "Input error. Can't be more working divisions than total divisions" << endl;
                    else break;
                }
            }
        }
    }

    int Station::give_id()
    {
        return id;
    }

    std::istream& operator >> (std::istream& in, Station& Station)
    {
        string value;
        getline(in, value);
        Station.id = stoi(value);
        return in;
    }

    Station::Station(void):id(Station::NextID++)
    {

    }

    Station& Station::Create_station(Station& s)
    {
        cout << "Input name: ";
        s.station_name = stringCheck();
        while (1)
        {
            cout << "Input total station divisions: ";
            s.total_divisions = intCheck();
            cout << "Input working divisions: ";
            s.working_divisions = intCheck();
            if (s.working_divisions <= s.total_divisions)
                break;
            else
                cout << "Input error. Can't be more working divisions than total divisions" << endl;
        }
        cout << "Input station efficiency: ";
        s.efficiency = intCheck(0, 100);
        return s;
    }