#include "SimplexTestSuite.hpp"
#include <vector>

std::vector<std::vector<double>> generateConstraintFunctionsParams(int numOfParam);

INSTANTIATE_TEST_CASE_P(
        cenetrPointConstraintFunctionsAndObjectiveFunctionParams,
        testSimplexFind0InObjectiveFuncParametersTestsFixture,
        ::testing::Values(
                std::make_tuple(0, std::vector<double> {}),
                std::make_tuple(0, std::vector<double> {0, 1, 3}),
                std::make_tuple(1, std::vector<double> {0, 0, 3}),
                std::make_tuple(2, std::vector<double> {0, 1, 0, 4.2, 0}),
                std::make_tuple(1, std::vector<double> {-13, 0, 3}),
                std::make_tuple(1, std::vector<double> {-3, 0, 4}),
                std::make_tuple(2, std::vector<double> {-5, 1, 0})
                ));

TEST_P(testSimplexFind0InObjectiveFuncParametersTestsFixture, xDDDDDD) {
    int expected = std::get<0>(GetParam());
    simplex.setObjectiveFunction(std::get<1>(GetParam()));

    ASSERT_EQ(expected, simplex.findValueEq0InObjectiveFunction());
}

INSTANTIATE_TEST_CASE_P(
        cenetrPointConstraintFunctionsAndObjectiveFunctionParams,
        testSimplexCheckIfSetOfSolutionsIsUnconstrainedParametersTestsFixture,
        ::testing::Values(
                std::make_tuple(true, generateConstraintFunctionsParams(0), std::vector<double> {-13, 0, 3}),
                std::make_tuple(false, generateConstraintFunctionsParams(1), std::vector<double> {-3, 0, 4}),
                std::make_tuple(false, generateConstraintFunctionsParams(2), std::vector<double> {-5, 1, 0})
                ));

TEST_P(testSimplexCheckIfSetOfSolutionsIsUnconstrainedParametersTestsFixture, xDDDDDD) {
    bool expected = std::get<0>(GetParam());
    auto constraintFunctionsParams = std::get<1>(GetParam());
    for(auto& constraintFunction : constraintFunctionsParams)
    {
        simplex.addConstraintFunction(constraintFunction);
    }
    simplex.setObjectiveFunction(std::get<2>(GetParam()));
    ASSERT_EQ(expected, simplex.checkIfSetOfSolutionsIsUnconstrained());
}

INSTANTIATE_TEST_CASE_P(
        cenetrPointConstraintFunctionsAndObjectiveFunctionParams,
        testSimplexFindCenterPointParametersTestsFixture,
        ::testing::Values(
                std::make_tuple(std::make_pair(0,0), generateConstraintFunctionsParams(0), std::vector<double> {-13, 0, 3}),
                std::make_tuple(std::make_pair(1,1), generateConstraintFunctionsParams(1), std::vector<double> {-3, 0, 4}),
                std::make_tuple(std::make_pair(2,2), generateConstraintFunctionsParams(2), std::vector<double> {-5, 1, 0})
                ));

TEST_P(testSimplexFindCenterPointParametersTestsFixture, xDDDDDD) {
    auto expected = std::get<0>(GetParam());
    auto constraintFunctionsParams = std::get<1>(GetParam());
    for(auto& constraintFunction : constraintFunctionsParams)
    {
        simplex.addConstraintFunction(constraintFunction);
    }
    simplex.setObjectiveFunction(std::get<2>(GetParam()));
    ASSERT_EQ(expected, simplex.findCenterPointForPrimalSimplex());
}
 
std::vector<std::vector<double>> generateConstraintFunctionsParams(int numOfParam)
{
    std::vector<std::vector<double>> constraintFunctionsParams;
 
    switch(numOfParam)
    {
        case 0:
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