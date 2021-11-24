#pragma once

#include <iostream>

class Station
{
public:
    int id;
    static int NextID;
    std::string station_name;
    int total_divisions;
    int working_divisions;
    int efficiency;

    void StationOutput();

    void EditStation(int& a);

    int give_id();
};