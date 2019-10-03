#pragma once
#include <iostream>
#include <vector>

class Simplex
{
    private:
    std::vector<double> objectiveFunction;
    std::vector<std::vector<double>> constraintFunctions;
    public:
    std::vector<double> getObjectiveFunction() const;
    void setObjectiveFunction(std::vector<double> objectiveFunction);
    std::vector<double> getConstraintFunction(int functionNumber) const;
    void addConstraintFunction(std::vector<double> newConstraintFunction);
};