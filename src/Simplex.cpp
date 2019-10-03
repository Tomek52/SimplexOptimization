#include "Simplex.hpp"

std::vector<double> Simplex::getObjectiveFunction() const
{
    return objectiveFunction;
}

void Simplex::setObjectiveFunction(std::vector<double> objectiveFunction)
{
    this->objectiveFunction = objectiveFunction;
}
