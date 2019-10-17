#include "SimplexTestSuite.hpp"
#include <vector>
#include<complex>

std::vector<std::vector<double>> generateConstraintFunctionsParams(int numOfParam);
bool CompareExpectedValueWithValueAfterJordanGaussElimination(
    std::vector<std::vector<double>> expectedValue, 
    std::vector<std::vector<double>> testedValue);

INSTANTIATE_TEST_CASE_P(
        positionOf0AndObjectiveFunctionParams,
        testSimplexFind0InObjectiveFuncParametersTestsFixture,
        ::testing::Values(
                std::make_tuple(0, std::vector<double> {}),
                std::make_tuple(0, std::vector<double> {0, 1, 3}),
                std::make_tuple(1, std::vector<double> {0, 0, 3}),
                std::make_tuple(2, std::vector<double> {0, 1, 0, 4.2, 0}),
                std::make_tuple(1, std::vector<double> {-13, 0, 3}),
                std::make_tuple(1, std::vector<double> {-3, 0, 4}),
                std::make_tuple(1, std::vector<double> {-3, 0, 4}),
                std::make_tuple(0, std::vector<double> {99999.999, 4, 4, -9999999.9999}),
                std::make_tuple(1, std::vector<double> {0, 0, 0, 0, 0, 0, 0}),
                std::make_tuple(2, std::vector<double> {-5, 1, 0})
                ));

TEST_P(testSimplexFind0InObjectiveFuncParametersTestsFixture, shouldReturnPositionOf0) {
    int expected = std::get<0>(GetParam());
    simplex.setObjectiveFunction(std::get<1>(GetParam()));
    ASSERT_EQ(expected, simplex.findValueEq0InObjectiveFunction());
}

INSTANTIATE_TEST_CASE_P(
        isUnconstrainedConstraintFunctionsAndSecondCenterPointCoordinate,
        testSimplexCheckIfSetOfSolutionsIsUnconstrainedParametersTestsFixture,
        ::testing::Values(
                std::make_tuple(true, generateConstraintFunctionsParams(0), 1),
                std::make_tuple(false, generateConstraintFunctionsParams(1), 1),
                std::make_tuple(false, generateConstraintFunctionsParams(2), 2)
                ));

TEST_P(testSimplexCheckIfSetOfSolutionsIsUnconstrainedParametersTestsFixture, shouldReturnTrueWhenSetOfSolutionsIsUnconstrained) {
    bool expected = std::get<0>(GetParam());
    auto constraintFunctionsParams = std::get<1>(GetParam());
    for(auto& constraintFunction : constraintFunctionsParams)
    {
        simplex.addConstraintFunction(constraintFunction);
    }
    int secondCoordinateOfCenterPoint = std::get<2>(GetParam());
    ASSERT_EQ(expected, simplex.checkIfSetOfSolutionsIsUnconstrained(secondCoordinateOfCenterPoint));
}

INSTANTIATE_TEST_CASE_P(
        cenetrPointConstraintFunctionsAndObjectiveFunctionParams,
        testSimplexFindCenterPointParametersTestsFixture,
        ::testing::Values(
                std::make_tuple(std::make_pair(1,1), generateConstraintFunctionsParams(1), 1),
                std::make_tuple(std::make_pair(2,2), generateConstraintFunctionsParams(2), 2)
                ));

TEST_P(testSimplexFindCenterPointParametersTestsFixture, givenCorrectParamsFindCenterPointForPrimalSimplexShouldReturnExpectedCoordinates) {
    auto expected = std::get<0>(GetParam());
    auto constraintFunctionsParams = std::get<1>(GetParam());
    for(auto& constraintFunction : constraintFunctionsParams)
    {
        simplex.addConstraintFunction(constraintFunction);
    }
    int secondCoordinateOfCenterPoint = std::get<2>(GetParam());
    ASSERT_EQ(expected, simplex.findCenterPointForPrimalSimplex(secondCoordinateOfCenterPoint));
}


TEST_F(testSimplexFixture, testGaussJordanElimination)
{
    //Given
    std::vector<double> vec1 = {5, 1, 1};
    std::vector<double> vec2 = {0, -1, 1};
    std::vector<double> vec3 = {21, 6, 2};
    std::vector<double> obj = {0, -2, -1};
    std::vector<std::vector<double>> expected = {
        {1.5, -0.166667, 0.666667},
        {3.5, 0.166667, 1.33333},
        {3.5, 0.166667, 0.333333}
    };
    //When
    simplex.setObjectiveFunction(obj);
    simplex.addConstraintFunction(vec1);
    simplex.addConstraintFunction(vec2);
    simplex.addConstraintFunction(vec3);
    //Then
    ASSERT_TRUE(CompareExpectedValueWithValueAfterJordanGaussElimination(expected, simplex.gauss_Jordan_Elimination({2,1})));
}

std::vector<std::vector<double>> generateConstraintFunctionsParams(int numOfParam)
{
    std::vector<std::vector<double>> constraintFunctionsParams;

    switch(numOfParam)
    {
        case 0: //Unconstrained
            constraintFunctionsParams.emplace_back(std::initializer_list<double>{10, -3, 2});
            constraintFunctionsParams.emplace_back(std::initializer_list<double>{20, -4, 5});
            constraintFunctionsParams.emplace_back(std::initializer_list<double>{20, -3, 6});
            break;
        case 1:
            constraintFunctionsParams.emplace_back(std::initializer_list<double>{12, -2, 2});
            constraintFunctionsParams.emplace_back(std::initializer_list<double>{1, 1, 4});
            constraintFunctionsParams.emplace_back(std::initializer_list<double>{8, 8, 6});
            break;
        case 2:
            constraintFunctionsParams.emplace_back(std::initializer_list<double>{3, 1, -0.1});
            constraintFunctionsParams.emplace_back(std::initializer_list<double>{2, 4, -3});
            constraintFunctionsParams.emplace_back(std::initializer_list<double>{9, 5, 1});
            break;
        default:
            constraintFunctionsParams = {};
    }

    return constraintFunctionsParams;
}

bool CompareExpectedValueWithValueAfterJordanGaussElimination(
    std::vector<std::vector<double>> expectedValue, 
    std::vector<std::vector<double>> testedValue)
{
    const double delta = 0.0000000000000000000005;
    int iFloopIncrement = 0;
    for(const auto& iterator : expectedValue)
    {
        for(const auto& element : iterator)
        {
            int jFlopIncrement = 0;
            if(!(element - testedValue.at(iFloopIncrement).at(jFlopIncrement) < delta))
                return false;
            ++jFlopIncrement;
        }
        ++iFloopIncrement;
    }
    return true;    
}
