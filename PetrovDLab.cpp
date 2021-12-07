
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "PetrovDLab.h"
#include <limits>
#include <unordered_map>
#include <vector>
#include "Pipe.h"
#include "Checks.h"
#include "Station.h"
#include <functional>

using namespace std;

void PrintMenu()
{
    cout << endl << "Choose option:" << endl << endl
        << "1. Add pipe" << endl
        << "2. Add station" << endl
        << "3. List objects" << endl
        << "4. Edit pipe" << endl
        << "5. Edit station" << endl
        << "6. Delete pipe" << endl
        << "7. Delete station" << endl
        << "8. Save" << endl
        << "9. Load" << endl
        << "10. Search" << endl
        //<< "11. Batch editing" << endl
        << "12. Connect pipe" << endl
        << "13. Disconnect pipe" << endl
        << "0. Exit" << endl;
}

void LoadFile(unordered_map<int, Pipe>& pipes, unordered_map<int, Station>& stations)
{
    {
        pipes.clear();
        stations.clear();
        Pipe::NextID = 0;
        Station::NextID = 0;
        cout << "Input file name:" << endl;
        string name = stringCheck();
        ifstream file;
        file.open(name, ios::in);
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
                    Pipe::NextID = stoi(value);
                    for (int i = 1; i <= pipe_keys; i++)
                    {
                        getline(file, value);
                        int dynam_key = stoi(value);
                        pipes.insert({ dynam_key, {} });
                        file >> pipes[dynam_key];
                    }
                }
                if (str == "station_data")
                {
                    string value;
                    getline(file, value);
                    int station_keys = stoi(value);
                    getline(file, value);
                    Station::NextID = stoi(value);
                    for (int i = 1; i <= station_keys; i++)
                    {
                        getline(file, value);
                        int dynam_key = stoi(value);
                        stations.insert({ dynam_key, {} });
                        file >> stations[dynam_key];
                    }
                }
            }
            cout << "Loading complete" << endl;
        }
        else
            cout << "File not found" << endl;
    }
}

void SaveFile(int pipe_total, unordered_map<int, Pipe>& pipes, int station_total, unordered_map<int, Station>& stations)
{
    {
        cout << "Input file name:" << endl;
        string name = stringCheck();
        ofstream file;
        file.open(name, ios_base::out);
        if (file.good())
        {
            if (pipes.empty() == false)
            {
                file << "pipeline_data" << endl << pipes.size()<< endl << pipe_total << endl;
                for (auto kv : pipes)
                {
                    file << kv.first << endl << pipes[kv.first].give_id() << endl << pipes[kv.first].d << endl << pipes[kv.first].l << endl << pipes[kv.first].Repair << endl << pipes[kv.first].start << endl << pipes[kv.first].end << endl;
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
                    file << kv.first << endl << stations[kv.first].give_id() << endl << stations[kv.first].station_name << endl << stations[kv.first].give_td() << endl << stations[kv.first].working_divisions << endl << stations[kv.first].efficiency << endl << stations[kv.first].connectnum << endl;
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

using PFilter = std::function<vector<int>(unordered_map<int, Pipe>& pipes, bool Status)>;

void PipeSearchEdit(unordered_map<int, Pipe>& pipes, bool Status, PFilter result)
{
    auto batch = result(pipes, Status);
    for (int id : batch)
        cout << id << " ";
    cout << endl;
    cout << "Manipulate? 1 - yes, 2 - no" << endl;
    if (intCheck(1, 2) == 2)
        return;

    vector<bool> selector(batch.size(), true);

    cout << "Currently selected pipes:" << endl;
    for (int i = 0; i < batch.size(); i++)
        cout << i+1 << "(" << batch[i] << ")" << (selector[i] ? "(+) " : "(-) ");
    cout << endl;
    cout << "Input index to toggle selection, input 0 to finish selection" << endl;
    while (int index = intCheck(0, selector.size()))
    {
        selector[index - 1] = !selector[index - 1];
        for (int i = 0; i < batch.size(); i++)
            cout << i+1 << "(" << batch[i] << ")" << (selector[i] ? "(+) " : "(-) ");
    }
    cout << "Input 1 to flip repair status, input 2 to delete pipes: " << endl;
    if (intCheck() == 1)
    {
        for (int i = 0; i < batch.size(); i++)
            if (selector[i] == true)
                pipes[batch[i]].Repair = !pipes[batch[i]].Repair;
    }
    else
    {
        for (int i = 0; i < batch.size(); i++)
            if (selector[i] == true)
                if (pipes[batch[i]].start == -1 and pipes[batch[i]].end == -1)
                    pipes.erase(batch[i]);
    }
}

vector<int> PipeSearch(unordered_map<int, Pipe>& pipes, bool Status)
{
    vector<int> result = {};
    for (auto kv : pipes)
    {
        if (pipes[kv.first].Repair == Status)
        {
            cout << kv.first << endl;
            cout << kv.second;
            result.push_back(kv.first);
        }
        cout << endl;
    }
    return result;
}

using StFilter = std::function<vector<int>(unordered_map<int, Station>& stations, string name, int percent_low, int percent_high, bool parameter_indicator)>;

void StationSearchBatchEdit(unordered_map<int, Station>& stations, string name, int percent_low, int percent_high, bool parameter_indicator, StFilter result)
{
    auto batch = result(stations, name, percent_low, percent_high, parameter_indicator);
    for (int id : batch)
        cout << id << " ";
    cout << endl;
    cout << "Manipulate? 1 - yes, 2 - no" << endl;
    if (intCheck(1, 2) == 2)
        return;

    vector<bool> selector = {};
    for (int i = 0; i < batch.size(); i++)
        selector.push_back(true);
    while (1)
    {
        cout << "Currently selected stations:" << endl;
        for (int i = 0; i < batch.size(); i++)
            if (selector[i] == true)
                cout << batch.at(i) << "(+) ";
            else
                cout << batch.at(i) << "(-) ";
        cout << endl;
        cout << "Input 1 to toggle selection, input 2 to finish selection" << endl;
        if (intCheck(1, 2) == 2)
            break;
        cout << "Input number of station in the sequence:" << endl;
        int toggler = intCheck(1, selector.size());
        selector[toggler - 1] = !selector[toggler - 1];
    }
    cout << "Input 1 to add a working station, input 2 to subtract a working station, input 3 to delete stations: ";
    int a = intCheck(1, 3);
    if (a == 1)
    {
        for (int i = 0; i < batch.size(); i++)
            if (selector[i] == true)
                if (stations[batch[i]].working_divisions != stations[batch[i]].give_td())
                    stations[batch[i]].working_divisions++;
    }
    else if (a == 2)
    {
        for (int i = 0; i < batch.size(); i++)
            if (selector[i] == true)
                if (stations[batch[i]].working_divisions != 0)
                    stations[batch[i]].working_divisions--;
    }
    else
    {
        for (int i = 0; i < batch.size(); i++)
            if (selector[i] == true)
                if (stations[batch[i]].connectnum == 0)
                    stations.erase(batch[i]);
                else
                    cout << "Station " << batch[i] << " is connected and cannot be deleted." << endl;
    }
}

vector<int> StationsFilter(unordered_map<int, Station>& stations, string name, int percent_low, int percent_high, bool parameter_indicator)
{
    vector<int> result = {};
    if (parameter_indicator == true)
    {
        for (auto kv : stations)
        {
            if (stations[kv.first].station_name == name)
            {
                cout << kv.first << endl;
                cout << kv.second;
                result.push_back(kv.first);
            }
            cout << endl;
        }
    }
    else
    {
        for (auto kv : stations)
        {
            float division_percent = (stations[kv.first].working_divisions / (float)stations[kv.first].give_td()) * 100;
            if (division_percent >= percent_low && division_percent <= percent_high)
            {
                cout << kv.first;
                cout << kv.second;
                result.push_back(kv.first);
            }
            cout << endl;
        }
    }
    return result;
}

void Connect(Pipe& p, unordered_map<int, Station>& stations)
{
    if (p.start == -1 and p.end == -1)
    {
        while (1)
        {
            cout << "Input id of starting station:" << endl;
            int start_buff = intCheck();
            cout << "Input id of ending station:" << endl;
            int end_buff = intCheck();
            if (stations.find(start_buff) != stations.end() and stations.find(end_buff) != stations.end() and start_buff != end_buff)
            {
                p.start = start_buff;
                p.end = end_buff;
                stations[start_buff].connectnum++;
                stations[end_buff].connectnum++;
                break;
            }
            else
            {
                cout << "Error. Input IDs of existing stations. Start and end can't be the same station." << endl;
                break;
            }
        }
    }
    else
    {
        cout << "Pipe is already connected. Disconnect the pipe to proceed." << endl;
    }
}

void Disconnect(Pipe& p, unordered_map<int, Station>& stations)
{
    if (p.start == -1 and p.end == -1)
        cout << "Pipe not connected." << endl;
    else
    {
        stations[p.start].connectnum--;
        stations[p.end].connectnum--;
        p.start = -1;
        p.end = -1;
    }
}

int main()
{
    unordered_map <int, Pipe> pipes = {};
    unordered_map <int, Station> stations = {};
    while (1)
    {
        PrintMenu();
        int a = 0;
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
            Pipe pipe;
            pipe.start = -1;
            pipe.end = -1;
            pipe.Repair = false;
            cout << "Input pipe diameter: ";
            pipe.d = intCheck();
            cout << "Input pipe length: ";
            pipe.l = floatCheck(0);
            pipes.insert({Pipe::NextID, pipe});
            Pipe::NextID++;
            cout << "Pipe created" << endl;
            break;
        }
        case 2:
        {
            Station station;
            cout << "Input name: " << endl;
            station.station_name = stringCheck();
            while (1)
            {
                cout << "Input total station divisions: " << endl;
                station.total_divisions = intCheck();
                cout << "Input working divisions: " << endl;
                station.working_divisions = intCheck();
                if (station.working_divisions <= station.total_divisions)
                    break;
                else
                    cout << "Input error. Can't be more working divisions than total divisions" << endl;
            }
            cout << "Input station efficiency: " << endl;
            station.efficiency = intCheck(0, 100);
            station.connectnum = 0;
            stations.insert({Station::NextID, station});
            Station::NextID++;
            cout << "Station created" << endl;
            break;
        }
        case 3:
        {
            cout << "Total pipes created: " << Pipe::NextID << endl << endl;
            if (pipes.empty() == false)
            {
                for (auto kv : pipes)
                {
                    cout << kv.first << endl;
                    cout << kv.second << endl;
                    cout << endl;
                }
            }
            cout << "Total stations created: " << Station::NextID << endl << endl;
            if (stations.empty() == false)
            {
                for (auto kv : stations)
                {
                    cout << kv.first << endl;
                    cout << kv.second << endl;
                    cout << endl;
                }
            }
            break;
        }
        case 4:
        {
            if (pipes.empty() == false)
            {
                cout << "Input pipe ID to edit repair status: " << endl;
                int input_id = intCheck();
                if (pipes.find(input_id) != pipes.end())
                {
                    pipes[input_id].EditPipe(a);
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
                if (stations.find(input_id) != stations.end())
                {
                    cout << "Input 1 to change name, 2 - to change efficiency, 3 - to add working division, 4 - to subtract division" << endl;
                    switch (a)
                    {
                    case(1):
                    {
                        cout << "Input name" << endl;
                        string name = stringCheck();
                        stations[input_id].EditStation(name);
                        break;
                    }
                    case(2):
                    {
                        cout << "Input efficiewncy" << endl;
                        int eff = intCheck(0, 100);
                        stations[input_id].EditStation(eff);
                        break;
                    }
                    case(3):
                    {
                        bool flag = true;
                        stations[input_id].EditStation(flag);
                        break;
                    }
                    case(4):
                    {
                        bool flag = false;
                        stations[input_id].EditStation(flag);
                        break;
                    }
                    }
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
                if (pipes.find(input_id) != pipes.end())
                {
                    if (pipes[input_id].start == -1 and pipes[input_id].end == -1)
                    {
                        pipes.erase(input_id);
                        break;
                    }
                    else
                    {
                        cout << "Pipe is connected. Disconnect pipe." << endl;
                        break;
                    }
                }
                else
                {
                    cout << "No matching ID found" << endl;
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
                if (stations.find(input_id) != stations.end())
                {
                    if (stations[input_id].connectnum == 0)              
                    {
                        stations.erase(input_id);
                        break;
                    }
                    else
                    {
                        cout << "Station is connected. Disconnect all pipes from this station." << endl;
                        break;
                    }
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
            SaveFile(Pipe::NextID, pipes, Station::NextID, stations);
            break;
        }
        case 9:
        {
            LoadFile(pipes, stations);
            break;
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
                    PipeSearchEdit(pipes, repair_search, PipeSearch);
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
                    string name_search = "";
                    int percent_search_low = 0;
                    int percent_search_high = 0;
                    cout << "Input 1 to search by name. Input 2 to search by percent of working stations:" << endl;
                    a = intCheck(1, 2);
                    if (a == 1)
                    {
                        bool parameter_indicator = true;
                        cout << "Input name:" << endl;
                        string name_search = stringCheck();
                        StationSearchBatchEdit(stations, name_search, percent_search_low, percent_search_high, parameter_indicator, StationsFilter);
                        break;
                    }
                    else
                    {
                        while (1)
                        {
                            bool parameter_indicator = false;
                            cout << "Input lower boundary for percent:" << endl;
                            int percent_search_low = intCheck(0, 100);
                            cout << "Input higher boundary for percent:" << endl;
                            int percent_search_high = intCheck(0, 100);
                            if (percent_search_low <= percent_search_high)
                            {
                                StationSearchBatchEdit(stations, name_search, percent_search_low, percent_search_high, parameter_indicator, StationsFilter);
                                break;
                            }
                            else
                                cout << "Lower boundary must be lower or equal compared to the higher boundary." << endl;
                        }
                        break;
                    }
                }
                else
                {
                    cout << "There are no stations." << endl;
                    break;
                }
            }
        }
        /*case 11:
        {
            vector<int> batch = {};
            cout << "Input 1 to edit pipes or 2 to edit stations:" << endl;
            a = intCheck(1, 2);
            if (a == 1)
            {
                cout << "Input pipe IDs:" << endl;
                while(1)
                {
                    int vect_buff = intCheck();
                    if (pipes.find(vect_buff) != pipes.end())
                    {
                        batch.push_back(vect_buff);
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
                    if (stations.find(vect_buff) != stations.end())
                    {
                        batch.push_back(vect_buff);
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
                                stations[batch[i]].total_division = total_buff;
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
        }*/
        case 12:
        {
            cout << "Input pipe id:" << endl;
            int id_buff = intCheck();
            if (pipes.find(id_buff) != pipes.end())
                Connect(pipes[id_buff], stations);
            else cout << "No such pipe found." << endl;
            break;
        }
        case 13:
        {
            cout << "Input pipe id:" << endl;
            int id_buff = intCheck();
            if (pipes.find(id_buff) != pipes.end())
                if (pipes[id_buff].start != -1 and pipes[id_buff].end != -1)
                    Disconnect(pipes[id_buff], stations);
                else cout << "Pipe is already disonnected." << endl;
            else cout << "No such pipe found." << endl;
            break;
        }
        }
    }
}