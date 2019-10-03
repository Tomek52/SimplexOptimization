#include "Simplex.hpp"

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
    if(constraintFunctions.size() == 0 or constraintFunctions.size() < functionNumber) 
        return {};
    return constraintFunctions[functionNumber];
}

void Simplex::addConstraintFunction(std::vector<double> newConstraintFunction)
{
    constraintFunctions.emplace_back(newConstraintFunction);
}
