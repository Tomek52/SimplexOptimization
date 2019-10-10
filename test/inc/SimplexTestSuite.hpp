#pragma once
#include <gtest/gtest.h>
#include "Simplex.hpp"

struct testSimplexFixture : public ::testing::Test
{
    //Given
    Simplex simplex;
    std::vector<double> emptyVector;
    std::vector<double> vectorOf2Doubles = {1.43, 2};
    std::vector<double> vectorOf4Doubles = {3.23, 4, -0.001, 9999999.1234};
    std::vector<double> vectorOf5Doubles = {1.3, 7.55, -0.001, -0, 0.000000008};
    std::vector<double> vectorOf3Doubles = {-0.5, 6.01, 1};
};

struct testSimplexFind0InObjectiveFuncParametersTestsFixture :
        public testSimplexFixture,
        public ::testing::WithParamInterface<std::tuple<
                                                int,
                                                std::vector<double>
                                            >>
{
};

struct testSimplexCheckIfSetOfSolutionsIsUnconstrainedParametersTestsFixture :
        public testSimplexFixture,
        public ::testing::WithParamInterface<std::tuple<
                                                bool,
                                                std::vector<std::vector<double>>,
                                                int
                                            >>
{
};

struct testSimplexFindCenterPointParametersTestsFixture :
        public testSimplexFixture,
        public ::testing::WithParamInterface<std::tuple<
                                                std::pair<int, int>,
                                                std::vector<std::vector<double>>,
                                                int
                                            >>
{
};
