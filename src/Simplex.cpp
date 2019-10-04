#include "Simplex.hpp"
#include <algorithm>

std::vector<double> Simplex::getObjectiveFunction() const
{
    return objectiveFunction;
}

void Simplex::setObjectiveFunction(std::vector<double> objectiveFunction)
{
    this->objectiveFunction = objectiveFunction;
}

std::vector<double> Simplex::getConstraintFunction(int functionNumber) const
{
    if(constraintFunctions.empty() or constraintFunctions.size() < functionNumber) 
        return {};
    return constraintFunctions[functionNumber];
}

void Simplex::addConstraintFunction(std::vector<double> newConstraintFunction)
{
    constraintFunctions.emplace_back(newConstraintFunction);
}

bool Simplex::checkObjectiveFunctionIsSolvableByDualSimplex() const
{
    if(objectiveFunction.empty()) return false;
    else if(std::any_of(objectiveFunction.begin(), objectiveFunction.end(), 
        [](const auto& iterator){ return iterator<0; }))
        return false;
    else return true;
}

bool Simplex::checkSolutionIsOptimal() const
{
    if(constraintFunctions.empty()) return true;
    else if(std::any_of(constraintFunctions.begin(), constraintFunctions.end(),
        [](const auto& iterator) { return iterator.at(0)<0; }))
        return false;
    else return true;
}
