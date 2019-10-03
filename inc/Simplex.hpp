#pragma once
#include <iostream>
#include <vector>

class Simplex
{
    private:
    std::vector<double> objectiveFunction;
    public:
    std::vector<double> getObjectiveFunction() const;
    void setObjectiveFunction(std::vector<double> objectiveFunction);
};