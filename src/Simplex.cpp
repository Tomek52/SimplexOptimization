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

std::vector<double> Simplex::getConstraintFunction(unsigned int functionNumber) const
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

bool Simplex::checkIfSetOfSolutionsIsUnconstrained(const int& secondCoordinateOfCenterPoint) const
{
    if(std::all_of(constraintFunctions.begin(), constraintFunctions.end(),
        [&secondCoordinateOfCenterPoint](const auto& iterator) { return iterator.at(secondCoordinateOfCenterPoint)<0; }))
        return true;
    else return false;

}

std::pair<int, int> Simplex::findCenterPointForPrimalSimplex(const int& secondCoordinateOfCenterPoint)
{
    double minValue = INT_MAX;
    double newMinValue = 0;
    int firstCoordinateOfCenterPoint = 0;
    auto centerPoint = std::make_pair(firstCoordinateOfCenterPoint, secondCoordinateOfCenterPoint);

    for(const auto& constraintFunction : constraintFunctions)
    {
        if(constraintFunction.at(centerPoint.second) > 0)
        {
            newMinValue = constraintFunction[0]/constraintFunction[centerPoint.second];
            if(newMinValue<minValue)
            {
                minValue = newMinValue;
                centerPoint.first = firstCoordinateOfCenterPoint;
            }
        }
        firstCoordinateOfCenterPoint++;
    }
    return centerPoint;
}

std::vector<std::vector<double>> Simplex::gauss_Jordan_Elimination(std::pair<int, int> centralPoint)
{
    std::vector<double> nextObjectiveFunction;
    std::vector<std::vector<double>> nextConstraintFunctions;

        for(auto iterator = objectiveFunction.begin(); iterator != objectiveFunction.end(); ++iterator)
        {
            if(std::distance(objectiveFunction.begin(), iterator) == centralPoint.second)
            {
                nextObjectiveFunction.emplace_back(-objectiveFunction.at(centralPoint.second) 
                / constraintFunctions.at(centralPoint.first).at(centralPoint.second));
            }
            else 
            {
                nextObjectiveFunction.emplace_back(*iterator - (objectiveFunction.at(centralPoint.second) 
                * constraintFunctions.at(centralPoint.first).at(std::distance(objectiveFunction.begin(), iterator)) 
                / constraintFunctions.at(centralPoint.first).at(centralPoint.second)));
            }
        }
        int yCoordinate = 0;
        nextConstraintFunctions = constraintFunctions;
        for(auto iterYCoordinate = constraintFunctions.begin(); iterYCoordinate != constraintFunctions.end(); ++iterYCoordinate, ++yCoordinate)
        {
            int xCoordinate = 0;
            for(auto iterXCoordinate = iterYCoordinate->begin(); iterXCoordinate != iterYCoordinate->end(); ++iterXCoordinate, ++xCoordinate)
            {
                if(std::distance(iterYCoordinate->begin(), iterXCoordinate) == centralPoint.second && std::distance(constraintFunctions.begin(), iterYCoordinate) == centralPoint.first)
                { 
                    nextConstraintFunctions[yCoordinate][xCoordinate] = (1 / double(*iterXCoordinate));
                } 
                else if(std::abs((std::distance(iterYCoordinate->begin(), iterXCoordinate))) != centralPoint.second && std::abs(std::distance(constraintFunctions.begin(), iterYCoordinate)) == centralPoint.first)
                {
                    nextConstraintFunctions[yCoordinate][xCoordinate] = (double(*iterXCoordinate) / constraintFunctions.at(centralPoint.first).at(centralPoint.second));
                }
                else if(std::abs((std::distance(iterYCoordinate->begin(), iterXCoordinate))) == centralPoint.second && std::abs(std::distance(constraintFunctions.begin(), iterYCoordinate)) != centralPoint.first)
                {
                    nextConstraintFunctions[yCoordinate][xCoordinate] = (-double(*iterXCoordinate) / constraintFunctions.at(centralPoint.first).at(centralPoint.second));
                }     
                else
                {
                    nextConstraintFunctions[yCoordinate][xCoordinate] = (*iterXCoordinate - (constraintFunctions[yCoordinate].at(centralPoint.second) * constraintFunctions[centralPoint.first][std::distance(iterYCoordinate->begin(), iterXCoordinate)] / constraintFunctions[centralPoint.first][centralPoint.second]));
                };
            }
        }
        objectiveFunction = nextObjectiveFunction;
        constraintFunctions = nextConstraintFunctions;
       return constraintFunctions;
}
