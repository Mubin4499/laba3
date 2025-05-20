#include <gtest/gtest.h>
#include "../src/Calculator.h"

// Тестовый класс с доступом к protected методам
template<typename T>
class TestableFiestaCalculator : public FiestaCalculator<T> {
public:
    using FiestaCalculator<T>::checkDivision;
};

template<typename T>
class FiestaCalculatorTest : public ::testing::Test {};

using TestTypes = ::testing::Types<int, float, double>;
TYPED_TEST_SUITE(FiestaCalculatorTest, TestTypes);

TYPED_TEST(FiestaCalculatorTest, AddVectors) {
    FiestaCalculator<TypeParam> calc;
    std::vector<TypeParam> a = {1, 2};
    std::vector<TypeParam> b = {3, 4};
    auto result = calc.add(a, b);
    ASSERT_EQ(result.size(), 4);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[2], 3);
}

TYPED_TEST(FiestaCalculatorTest, MultiplyVector) {
    FiestaCalculator<TypeParam> calc;
    // Для целых чисел используем целые значения
    if constexpr (std::is_integral_v<TypeParam>) {
        std::vector<TypeParam> vec = {1, 2};
        auto result = calc.multiply(vec, 2);
        EXPECT_EQ(result[0], 2);
    } else {
        std::vector<TypeParam> vec = {1.5, 2.5};
        auto result = calc.multiply(vec, 2);
        EXPECT_DOUBLE_EQ(result[0], 3.0);
    }
}

TYPED_TEST(FiestaCalculatorTest, DivisionByZero) {
    TestableFiestaCalculator<TypeParam> calc;
    EXPECT_THROW(calc.checkDivision(0), std::runtime_error);
}