#include "Simplex.hpp"
#include <algorithm>
#include <iterator>
#include <climits>

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

int Simplex::findValueEq0InObjectiveFunction()
{
    auto valueEq0 = std::find(std::begin(objectiveFunction) + 1, std::end(objectiveFunction), 0);
    if(valueEq0 != objectiveFunction.end())
        return std::distance(objectiveFunction.begin(), valueEq0);
    else 
        return 0;
}

bool Simplex::checkIfSetOfSolutionsIsUnconstrained()
{
    int index = findValueEq0InObjectiveFunction();
    if(std::all_of(constraintFunctions.begin(), constraintFunctions.end(),
        [&index](const auto& iterator) { return iterator.at(index)<0; }))
        return true;
    else return false;
    
}

std::pair<int, int> Simplex::findCenterPointForPrimalSimplex()
{
    if(checkIfSetOfSolutionsIsUnconstrained())
        return std::make_pair(0, 0);

    double minValue = INT_MAX;
    double newMinValue = 0;
    int indexOfConstraintFunction = 0;
    auto centerPoint = std::make_pair(indexOfConstraintFunction, findValueEq0InObjectiveFunction());

    for(const auto& constraintFunction : constraintFunctions)
    {
        if(constraintFunction.at(centerPoint.second) > 0)
        {
            newMinValue = constraintFunction[0]/constraintFunction[centerPoint.second];
            if(newMinValue<minValue) 
            {
                minValue = newMinValue;
                centerPoint.first = indexOfConstraintFunction;
            }
        }
        indexOfConstraintFunction++;
    }
    return centerPoint;
}
