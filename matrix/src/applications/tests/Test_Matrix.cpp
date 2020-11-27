#include <gtest/gtest.h>
#include <Matrix.h>

namespace
{
    template <typename T>
    bool checkEquality(const matrix::Matrix<T>& mToCheck, T value)
    {
        for (size_t i = 0; i < mToCheck.getRowsNum(); ++i)
        {
            for (size_t j = 0; j < mToCheck.getColsNum(); ++j)
            {
                if (mToCheck[i][j] != value)
                {
                    return false;
                }
            }
        }
        return true;
    }
}

namespace UT
{

TEST(TestMatrix, CreateUnit)
{
    constexpr size_t cols = 5u;
    constexpr size_t rows = 3u;
    std::vector<int> filler(15, 3);

    matrix::Matrix<size_t> m1{ cols, rows, 1u };
    matrix::Matrix<size_t> m2{ cols, rows, filler.begin(), filler.end() };
    matrix::Matrix<size_t> m3 = matrix::Matrix<size_t>::eye(cols, rows);
    matrix::Matrix<size_t> m4{ m3 };
    matrix::Matrix<size_t> m5 = m4;

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            EXPECT_EQ(m1[i][j], 1u);
            EXPECT_EQ(m2[i][j], 3u);
            if (i == j)
            {
                EXPECT_EQ(m3[i][j], 1u);
                EXPECT_EQ(m4[i][j], 1u);
                EXPECT_EQ(m5[i][j], 1u);
            }
            else
            {
                EXPECT_EQ(m3[i][j], 0u);
                EXPECT_EQ(m4[i][j], 0u);
                EXPECT_EQ(m5[i][j], 0u);
            }
        }
    }
}

TEST(TestMatrix, EqualUnit)
{
    constexpr size_t cols = 3u;
    constexpr size_t rows = 3u;

    matrix::Matrix<size_t> m1{ cols, rows, 1u };
    matrix::Matrix<size_t> m2 = m1;
    matrix::Matrix<size_t> m3 = matrix::Matrix<size_t>::eye(cols, rows);

    EXPECT_TRUE(m1.haveEqualSize(m2));
    EXPECT_TRUE(m1.identical(m2));
    EXPECT_TRUE(m1.haveEqualSize(m3));
    EXPECT_FALSE(m1.identical(m3));
}

class TestElementWiseOps : public ::testing::Test
{
protected:
	void SetUp()
	{
	}
	void TearDown()
	{
	}

    const size_t cols { 3u };
    const size_t rows1 { 3u };
    const size_t rows2 { 5u };

    matrix::Matrix<size_t> m1{ cols, rows1, 1u };
    matrix::Matrix<size_t> m2{ cols, rows1, 2u };
    matrix::Matrix<size_t> m3{ cols, rows2, 3u };
    matrix::Matrix<size_t> m4{ cols, rows1, 0u };

    matrix::Matrix<int> mInt{ cols, rows1, 1 };
};

TEST_F(TestElementWiseOps, SumUnit)
{
    EXPECT_THROW(m1 += m3, std::runtime_error);
    
    m1 += m2;
    EXPECT_TRUE(checkEquality(m1, static_cast<size_t>(3)));
}

TEST_F(TestElementWiseOps, MinusUnit)
{
    EXPECT_THROW(m1 -= m3, std::runtime_error);
    
    m2 -= m1;
    EXPECT_TRUE(checkEquality(m2, static_cast<size_t>(1)));
}

TEST_F(TestElementWiseOps, MulUnit)
{
    EXPECT_THROW(m1 *= m3, std::runtime_error);
    
    m2 *= m1;
    EXPECT_TRUE(checkEquality(m2, static_cast<size_t>(2)));
}

TEST_F(TestElementWiseOps, DivisionUnit)
{
    EXPECT_THROW(m1 /= m3, std::runtime_error);
    EXPECT_THROW(m1 /= m4, std::runtime_error);
    
    m1 /= m2;
    EXPECT_TRUE(checkEquality(m1, static_cast<size_t>(0.5)));
}

TEST_F(TestElementWiseOps, MulByValueUnit)
{
    mInt *= -5;
    EXPECT_TRUE(checkEquality(mInt, -5));

    mInt *= 3;
    EXPECT_TRUE(checkEquality(mInt, -15));
}

TEST_F(TestElementWiseOps, NegateUnit)
{    
    mInt.negate();
    EXPECT_TRUE(checkEquality(mInt, -1));

    mInt.negate();
    EXPECT_TRUE(checkEquality(mInt, 1));

    auto m3 = -mInt;
    EXPECT_TRUE(checkEquality(m3, -1));
}

TEST(TestMatrix, TraceUnit)
{
    constexpr size_t cols = 3u;
    constexpr size_t rows = 3u;

    matrix::Matrix<size_t> m1{ cols, rows, 1u };
    matrix::Matrix<size_t> m3 = matrix::Matrix<size_t>::eye(cols, rows);

    EXPECT_EQ(m1.trace(), 3u);
    EXPECT_EQ(m3.trace(), 3u);
}

TEST(TestMatrix, MatMulFailUnit)
{
    constexpr size_t cols1 = 3u;
    constexpr size_t rows1 = 5u;
    constexpr size_t cols2 = 4u;
    constexpr size_t rows2 = 5u;

    matrix::Matrix<size_t> m1{ cols1, rows2, 1u };
    matrix::Matrix<size_t> m2{ cols2, rows2, 1u };

    EXPECT_THROW(m1.matMul(m2), std::runtime_error);
}

TEST(TestMatrix, MatMulSimpleUnit)
{
    constexpr size_t cols1 = 2u;
    constexpr size_t rows1 = 2u;
    constexpr size_t cols2 = 2u;
    constexpr size_t rows2 = 2u;

    matrix::Matrix<size_t> m1{ cols1, rows1, 1u };
    matrix::Matrix<size_t> m2{ cols2, rows2, 1u };

    m1.matMul(m2);
    EXPECT_TRUE(checkEquality(m1, static_cast<size_t>(2)));
}

TEST(TestMatrix, MatMulUnit)
{
    // see matmul.py
    constexpr size_t cols1 = 7u;
    constexpr size_t rows1 = 5u;
    constexpr size_t cols2 = 9u;
    constexpr size_t rows2 = 7u;

    matrix::Matrix<size_t> m1{ cols1, rows1, matrix::FILL_TYPE::SEQUENTIAL };
    matrix::Matrix<size_t> m2{ cols2, rows2, matrix::FILL_TYPE::SEQUENTIAL };

    // Correct result
    std::vector<size_t> correctFiller{ 819, 840, 861, 882, 903, 924, 945, 966, 987, 2142, 2212, 2282, 2352, 2422, 2492, 2562, 2632, 2702, 3465, 3584, 3703, 3822, 3941,
        4060, 4179, 4298, 4417, 4788, 4956, 5124, 5292, 5460, 5628, 5796, 5964, 6132, 6111, 6328, 6545, 6762, 6979, 7196, 7413, 7630, 7847 };
    matrix::Matrix<size_t> correctResult{ cols2, rows1, correctFiller.begin(), correctFiller.end() };

    m1.matMul(m2);
    EXPECT_TRUE(m1.identical(correctResult));
}


TEST(TestMatrix, TransposeSimpleUnit)
{
    constexpr size_t cols = 2u;
    constexpr size_t rows = 2u;
    std::vector<int> filler{ 1, 2, 3, 4 };
    std::vector<int> fillerToCheck{ 1, 3, 2, 4 };

    matrix::Matrix<int> m1{ cols, rows, filler.begin(), filler.end() };
    EXPECT_TRUE(m1.transpose().identical(matrix::Matrix<int>{ cols, rows, fillerToCheck.begin(), fillerToCheck.end() }));
}

TEST(TestMatrix, TransposeUnit)
{
    // see transpose.py
    constexpr size_t cols = 11u;
    constexpr size_t rows = 7u;
    // Correct answer
    std::vector<int> correctFiller{ 0, 11, 22, 33, 44, 55, 66, 1, 12, 23, 34, 45, 56, 67, 2, 13, 24, 35, 46, 57, 68, 3, 14, 25, 36, 47, 58, 69, 4,
        15, 26, 37, 48, 59, 70, 5, 16, 27, 38, 49, 60, 71, 6, 17, 28, 39, 50, 61, 72, 7, 18, 29, 40, 51, 62, 73, 8, 19, 30, 41, 52, 63, 74, 9, 20, 31,
        42, 53, 64, 75, 10, 21, 32, 43, 54, 65, 76 };
    
    matrix::Matrix<int> correctResult{ rows, cols, correctFiller.begin(), correctFiller.end() };
    matrix::Matrix<int> m{ cols, rows, matrix::FILL_TYPE::SEQUENTIAL };

    m.transpose();
    EXPECT_TRUE(m.identical(correctResult));
}

}
