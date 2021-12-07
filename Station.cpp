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

    /*void Station::EditStation(int& a)
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
    }*/

void Station::EditStation(string& name)
{
    station_name = name;
}

void Station::EditStation(int& eff)
{
    efficiency = eff;
}

void Station::EditStation(bool& flag)
{
    if (flag == true && working_divisions != total_divisions)
        working_divisions++;
    else if (flag == false && working_divisions != 0)
        working_divisions--;
    else
        cout << "Working stations can't be more than total stations or less than 0." << endl;
}

int Station::give_id()
{
    return id;
}

int Station::give_td()
{
    return total_divisions;
}

std::istream& operator >> (std::istream& in, Station& station)
{
    string value;
    getline(in, value);
    station.id = stoi(value);
    getline(in, value);
    station.station_name = value;
    getline(in, value);
    station.total_divisions = stoi(value);
    getline(in, value);
    station.working_divisions = stoi(value);
    getline(in, value);
    station.efficiency = stoi(value);
    getline(in, value);
    station.connectnum = stoi(value);
    return in;
}

std::ostream& operator << (std::ostream& out, const Station& station)
{
    out << "Station ID:" << station.id << endl << "Station name:" << station.station_name << endl << "Total divisions:" << station.total_divisions << endl << "Working divisions:" << station.working_divisions << endl << "Efficiency:" << station.efficiency << endl;
    return out;
}

Station::Station(void) :id(Station::NextID)
{

}