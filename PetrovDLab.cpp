
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "PetrovDLab.h"
#include <limits>
#include <unordered_map>
#include <vector>

using namespace std;
int pipe_total;
int station_total;

int intCheck(int min = 0, int max = INT_MAX)
{
    while (1)
    {
        int num;
        cin >> num;
        if (cin.fail() or num < min or num > max or cin.peek() != '\n')
        {
            cin.clear();
            cin.ignore(100000000, '\n');
            cout << "Invalid input" << endl << endl;
        }
        else
        {
            return num;
        }
    }
}

string stringCheck()
{
    while (1)
    {
        string str;
        cin >> ws;
        getline(cin, str);
        return str;
    }
}

float floatCheck(float min = 0, float max = FLT_MAX)
{
    while (1)
    {
        float num;
        cin >> num;
        if (cin.fail() or num < min or num > max or cin.peek() != '\n')
        {
            cin.clear();
            cin.ignore(100000000, '\n');
            cout << "Invalid input. Plese input the number according to the format 'X.X'" << endl << endl;
        }
        else
        {
            return num;
        }
    }
}

bool booleanCheck()
{
    while (1)
    {
        bool boolean;
        cin >> boolean;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(100000000, '\n');
            cout << "Invalid input." << endl << endl;
        }
        else
        {
            return boolean;
        }
    }
}

class Pipe
{
public:
    int id;
    int d;
    float l;
    bool Repair;

    void PipeOutput()
    {
        cout << "Pipe ID:" << id << endl;
        cout << "Pipe diameter:" << d << endl;
        cout << "Pipe length:" << l << endl;
        cout << "Pipe repair status:" << Repair << endl;
    }

    void EditPipe(int& a)
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
};

class Station
{
public:
    int id;
    string station_name;
    int total_divisions;
    int working_divisions;
    int efficiency;

    void StationOutput()
    {
        cout << "Station ID:" << id << endl;
        cout << "Station name:" << station_name << endl;
        cout << "Total divisions:" << total_divisions << endl;
        cout << "Working divisions:" << working_divisions << endl;
        cout << "Efficiency:" << efficiency << endl;
    }

    void EditStation(int& a)
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
};

void LoadFile(unordered_map<float, Pipe>& pipes, unordered_map<float, Station>& stations, int& retflag)
{
    retflag = 1;
    {
        ifstream file;
        file.open("data.txt", ios::in);
        if (file.good())
        {
            while (!file.eof())
            {
                string str;
                getline(file, str);
                if (str == "pipeline_data")
                {
                    string value;
                    getline(file, value);
                    int pipe_keys = stoi(value);
                    getline(file, value);
                    pipe_total = stoi(value);
                    for (int i = 1; i <= pipe_keys; i++)
                    {
                        getline(file, value);
                        float dynam_key = stof(value);
                        pipes.insert({ dynam_key, {} });
                        getline(file, value);
                        pipes[dynam_key].id = stoi(value);
                        getline(file, value);
                        pipes[dynam_key].d = stoi(value);
                        getline(file, value);
                        pipes[dynam_key].l = stof(value);
                        getline(file, value);
                        pipes[dynam_key].Repair = value == "1";
                    }
                }
                if (str == "station_data")
                {
                    string value;
                    getline(file, value);
                    int station_keys = stoi(value);
                    getline(file, value);
                    station_total = stoi(value);
                    for (int i = 1; i <= station_keys; i++)
                    {
                        getline(file, value);
                        float dynam_key = stof(value);
                        stations.insert({ dynam_key,{} });
                        getline(file, value);
                        stations[dynam_key].id = stoi(value);
                        getline(file, value);
                        stations[dynam_key].station_name = value;
                        getline(file, value);
                        stations[dynam_key].total_divisions = stoi(value);
                        getline(file, value);
                        stations[dynam_key].working_divisions = stoi(value);
                        getline(file, value);
                        stations[dynam_key].efficiency = stoi(value);
                    }
                }
            }
            cout << "Loading complete" << endl;
            { retflag = 2; return; };
        }
    }
}

void SaveFile(int pipe_total, unordered_map<float, Pipe>& pipes, int station_total, unordered_map<float, Station>& stations)
{
    {
        ofstream file;
        file.open("data.txt", ios_base::out);
        if (file.good())
        {
            if (pipes.empty() == false)
            {
                file << "pipeline_data" << endl << pipes.size()<< endl << pipe_total << endl;
                for (auto kv : pipes)
                {
                    file << kv.first << endl << pipes[kv.first].id << endl << pipes[kv.first].d << endl << pipes[kv.first].l << endl << pipes[kv.first].Repair << endl;
                }
            }
            else
            {
                cout << "No pipelines created" << endl;
            }
            if (stations.empty() == false)
            {
                file << "station_data" << endl << stations.size() << endl << station_total << endl;
                for (auto kv : stations)
                {
                    file << kv.first << endl << stations[kv.first].id << endl << stations[kv.first].station_name << endl << stations[kv.first].total_divisions << endl << stations[kv.first].working_divisions << endl << stations[kv.first].efficiency << endl;
                }
            }
            else
            {
                cout << "No stations created" << endl;
            }
        }
        file.close();
        cout << "Save successful" << endl;
    }
}

Pipe Create_pipe()
{
    Pipe p = {};
    p.id = pipe_total;
    p.Repair = false;
    cout << "Input pipe diameter: ";
    p.d = intCheck();
    cout << "Input pipe length: ";
    p.l = floatCheck(0);
    return p;
}

Station Create_station()
{
    Station s = {};
    s.id = station_total;
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

unordered_map <float, Pipe> pipes = {};
unordered_map <float, Station> stations = {};

int main()

{
    while (1)
    {
        int a = 0;
        cout << "Choose option:" << endl << endl << "1. Add pipe" << endl << "2. Add station" << endl << "3. List objects" << endl << "4. Edit pipe" << endl << "5. Edit station" << endl << "6. Delete pipe" << endl << "7. Delete station" << endl << "8. Save" << endl << "9. Load" << endl << "10. Search" << endl << "11. Batch editing" << endl << "0. Exit" << endl;
        a = intCheck();
        switch (a)
        {
        case 0:
        {
            return 0;
            break;
        }
        case 1:
        {
            pipes.insert({pipe_total+0.1, Create_pipe() });
            cout << "Pipe created" << endl;
            ++pipe_total;
            break;
        }
        case 2:
        {
            stations.insert({station_total+0.2 , Create_station() });
            cout << "Station created" << endl;
            ++station_total;
            break;
        }
        case 3:
        {
            cout << "Total pipes created: " << pipe_total << endl << endl;
            if (pipes.empty() == false)
            {
                for (auto kv : pipes)
                {
                    cout << kv.first << endl;
                    pipes[kv.first].PipeOutput();
                    cout << endl;
                }
            }
            cout << "Total stations created: " << station_total << endl << endl;
            if (stations.empty() == false)
            {
                for (auto kv : stations)
                {
                    cout << kv.first << endl;
                    stations[kv.first].StationOutput();
                    cout << endl;
                }
            }
            break;
        }
        case 4:
        {
            if (pipes.empty() == false)
            {
                cout << "Input pipe ID to edit: " << endl;
                int input_id = intCheck();
                if (pipes.find(input_id+0.1) != pipes.end())
                {
                    pipes[input_id + 0.1].EditPipe(a);
                }
                else
                {
                    cout << "No matching ID found" << endl;
                    break;
                }
            }
            else
            {
                cout << "No pipes to edit" << endl;
                break;
            }
        }
        case 5:
        {
            if (stations.empty() == false)
            {
                cout << "Input station ID to edit: " << endl;
                int input_id = intCheck();
                if (stations.find(input_id+0.2) != stations.end())
                {
                    int retflag = 1;
                    stations[input_id + 0.2].EditStation(a);
                    if (retflag == 2) break;
                    break;
                }
                else
                {
                    cout << "No matching ID found" << endl;
                    break;
                }
            }
            else
            {
                cout << "No stations to edit" << endl;
                break;
            }
        }
        case 6:
        {
            if (pipes.empty() == false)
            {
                cout << "Input pipe ID:" << endl;
                int input_id = intCheck();
                if (pipes.find(input_id+0.1) != pipes.end())
                {
                    pipes.erase(input_id+0.1);
                    break;
                }
                else
                {
                    cout << "No matching ID found";
                    break;
                }
            }
            else
            {
                cout << "No pipes to delete" << endl;
                break;
            }
        }
        case 7:
        {
            if  (stations.empty() == false)
            {
                cout << "Input station ID:" << endl;
                int input_id = intCheck();
                if (stations.find(input_id+0.2) != stations.end())
                {
                    stations.erase(input_id+0.2);
                    break;
                }
                else
                {
                    cout << "No matching ID found";
                    break;
                }
            }
            else
            {
                cout << "No stations to delete" << endl;
                break;
            }
        }
        case 8:
        {
            SaveFile(pipe_total, pipes, station_total, stations);
            break;
        }
        case 9:
        {
            int retflag;
            LoadFile(pipes, stations, retflag);
            if (retflag == 2) break;
        }
        case 10:
        {
            cout << "Select object type (1 - pipes, 2 - stations):" << endl;
            a = intCheck(1, 2);
            if (a == 1)
            {
                if (pipes.empty() == false)
                {
                    cout << "Input repair status to search:" << endl;
                    bool repair_search = booleanCheck();
                    for (auto kv : pipes)
                    {
                        if (pipes[kv.first].Repair == repair_search)
                            pipes[kv.first].PipeOutput();
                        cout << endl;
                    }
                    break;
                }
                else
                {
                    cout << "There are no pipes." << endl;
                    break;
                }
            }
            else
            {
                if (stations.empty() == false)
                {
                    cout << "Input 1 to search by name. Input 2 to search by percent of working stations:" << endl;
                    a = intCheck(1, 2);
                    if (a == 1)
                    {
                        cout << "Input name:" << endl;
                        string name_search = stringCheck();
                        for (auto kv : stations)
                        {
                            if (stations[kv.first].station_name == name_search)
                                stations[kv.first].StationOutput();
                            cout << endl;
                        }
                        break;
                    }
                    else
                    {
                        while (1)
                        {
                            cout << "Input lower boundary for percent:" << endl;
                            int percent_search_low = intCheck(0, 100);
                            cout << "Input higher boundary for percent:" << endl;
                            int percent_search_high = intCheck(0, 100);
                            if (percent_search_low <= percent_search_high)
                            {
                                for (auto kv : stations)
                                {
                                    float division_percent = (stations[kv.first].working_divisions / (float)stations[kv.first].total_divisions) * 100;
                                    if ( division_percent >= percent_search_low && division_percent <= percent_search_high)
                                        stations[kv.first].StationOutput();
                                    cout << endl;
                                }
                                break;
                            }
                            else
                                cout << "Lower boundary must be lower or equal compared to the higher boundary." << endl;
                        }
                    }
                }
                else
                {
                    cout << "There are no stations." << endl;
                    break;
                }
            }
        }
        case 11:
        {
            vector<float> batch = {};
            cout << "Input 1 to edit pipes or 2 to edit stations:" << endl;
            a = intCheck(1, 2);
            if (a == 1)
            {
                cout << "Input pipe IDs:" << endl;
                while(1)
                {
                    int vect_buff = intCheck();
                    if (pipes.find(vect_buff+0.1) != pipes.end())
                    {
                        batch.push_back(vect_buff+0.1);
                    }
                    else
                    {
                        cout << "ID not found" << endl;
                    }
                    cout << "Is the batch complete? For yes input 1, for no - 2:" << endl;
                    a = intCheck(1, 2);
                    if (a == 1)
                        break;
                }
                if (batch.empty())
                {
                    cout << "Batch is empty." << endl;
                    break;
                }
                cout << "Input 1 to edit length and 2 to edit repair status" << endl;
                a = intCheck(1, 2);
                if (a == 1)
                {
                    cout << "Input length:" << endl;
                    float length_buff = floatCheck();
                    for (int i = 0; i <= batch.size()-1; i++)
                        pipes[batch[i]].l = length_buff;
                    batch = {};
                    break;
                }
                else
                {
                    cout << "Input repair status:" << endl;
                    bool repair_buff = booleanCheck();
                    for (int i = 0; i <= batch.size()-1; i++)
                        pipes[batch[i]].Repair = repair_buff;
                    batch = {};
                    break;
                }
            }
            else
            {
                cout << "Input station IDs:" << endl;
                while (1)
                {
                    int vect_buff = intCheck();
                    if (stations.find(vect_buff+0.2) != stations.end())
                    {
                        batch.push_back(vect_buff + 0.2);
                    }
                    else
                    {
                        cout << "ID not found" << endl;
                    }
                    cout << "Is the batch complete? For yes input 1, for no - 2:" << endl;
                    a = intCheck(1, 2);
                    if (a == 1)
                        break;
                }
                if (batch.empty())
                {
                    cout << "Batch is empty." << endl;
                    break;
                }
                cout << "Input 1 to edit name, 2 to edit divisions, 3 to edit efficiency:" << endl;
                a = intCheck();
                if (a == 1)
                {
                    cout << "Input name:" << endl;
                    string name_buff = stringCheck();
                    for (int i = 0; i <= batch.size()-1; i++)
                        stations[batch[i]].station_name = name_buff;
                    batch = {};
                    break;
                }
                if (a == 2)
                {
                    while (1)
                    {
                        cout << "Input total stations:" << endl;
                        int total_buff = intCheck();
                        cout << "Input working stations:" << endl;
                        int working_buff = intCheck();
                        if (total_buff < working_buff)
                            cout << "Input error. Can't be more working divisions than total divisions" << endl;
                        else
                        {
                            for (int i = 0; i <= batch.size()-1; i++)
                            {
                                stations[batch[i]].total_divisions = total_buff;
                                stations[batch[i]].working_divisions = working_buff;
                            }
                            break;
                        }   
                    }
                    batch = {};
                    break;
                }
                else
                {
                    cout << "Input efficiency:" << endl;
                    int efficiency_buff = intCheck();
                    for (int i = 0; i <= batch.size()-1; i++)
                        stations[batch[i]].efficiency = efficiency_buff;
                    batch = {};
                    break;
                }
            }
        }
        }
    }
}





