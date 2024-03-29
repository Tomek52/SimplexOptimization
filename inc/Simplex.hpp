#pragma once
#include <iostream>
#include <vector>
#include <utility>

class Simplex
{
    private:
    std::vector<double> objectiveFunction;
    std::vector<std::vector<double>> constraintFunctions;

    public:
    std::vector<double> getObjectiveFunction() const;
    void setObjectiveFunction(std::vector<double> objectiveFunction);
    std::vector<double> getConstraintFunction(unsigned int functionNumber) const;
    void addConstraintFunction(std::vector<double> newConstraintFunction);
    bool checkObjectiveFunctionIsSolvableByDualSimplex() const;
    bool checkSolutionIsOptimal() const;
    int findValueEq0InObjectiveFunction();
    bool checkIfSetOfSolutionsIsUnconstrained(const int& secondCoordinateOfCenterPoint) const;
    std::pair<int, int> findCenterPointForPrimalSimplex(const int& secondCoordinateOfCenterPoint);
    std::vector<std::vector<double>> gauss_Jordan_Elimination(std::pair<int, int> centralPoint);
};
