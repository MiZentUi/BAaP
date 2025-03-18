#include <gtest/gtest.h>

#include "date.h"

TEST(duration, test_1)
{
    ASSERT_EQ(Date(2025, 1, 1).duration(Date(2025, 1, 1)), 0);
}

TEST(duration, test_2)
{
    ASSERT_EQ(Date(2025, 1, 31).duration(Date(2025, 1, 1)), 30);
}

TEST(duration, test_3)
{
    ASSERT_EQ(Date(2025, 2, 23).duration(Date(2025, 1, 1)), 53);
}

TEST(weekNumber, test_1)
{
    ASSERT_EQ(Date(2025, 1, 6).weekNumber(), 2);
}

TEST(weekNumber, test_2)
{
    ASSERT_EQ(Date(2025, 2, 4).weekNumber(), 6);
}

TEST(weekNumber, test_3)
{
    ASSERT_EQ(Date(2025, 12, 31).weekNumber(), 53);
}

TEST(weekNumber, test_4)
{
    ASSERT_EQ(Date(2024, 1, 1).weekNumber(), 1);
}

TEST(weekNumber, test_5)
{
    ASSERT_EQ(Date(2024, 2, 2).weekNumber(), 5);
}

TEST(birthday, test_1)
{
    ASSERT_EQ(Date(2025, 3, 12).daysTillYourBithday(Date(2006, 11, 12)), 245);
}

TEST(bitthday, test_2)
{
    ASSERT_EQ(Date(2025, 3, 12).daysTillYourBithday(Date(2006, 1, 12)), 306);
}