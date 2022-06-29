//! @file TestPoint.hpp
//! @date 3/10/21
//! @author David Spry

#pragma once

#include <gtest/gtest.h>
#include <UI/Point.hpp>

TEST(Point, DefaultConstructor) {
    auto const point = ds::ui::Point<float> {};

    EXPECT_FLOAT_EQ(point.x, 0.0f);
    EXPECT_FLOAT_EQ(point.y, 0.0f);
}

TEST(Point, ParameterisedConstructor) {
    for (auto i = 0; i < 25; ++i) {
        auto random = testing::internal::Random(i);
        auto x = static_cast<int>(random.Generate(25e3) - 10e3);
        auto y = static_cast<int>(random.Generate(25e3) - 10e3);
        auto const point = ds::ui::Point {x, y};

        EXPECT_EQ(point.x, x);
        EXPECT_EQ(point.y, y);
        EXPECT_EQ(point.x, point.w);
        EXPECT_EQ(point.y, point.h);
    }
}

TEST(Point, ArithmeticWithPoint) {
    for (auto i = 0; i < 25; ++i) {
        auto random = testing::internal::Random(i);
        auto const a = ds::ui::Point {
                static_cast<int>(random.Generate(25e3) - 10e3),
                static_cast<int>(random.Generate(25e3) - 10e3)
        };

        auto const b = ds::ui::Point {
                static_cast<int>(random.Generate(25e3) - 10e3),
                static_cast<int>(random.Generate(25e3) - 10e3)
        };

        if (b.x == 0 or b.y == 0) {
            continue;
        }

        auto const addition = a + b;
        EXPECT_EQ(addition.x, a.x + b.x);
        EXPECT_EQ(addition.y, a.y + b.y);

        auto const subtract = a - b;
        EXPECT_EQ(subtract.x, a.x - b.x);
        EXPECT_EQ(subtract.y, a.y - b.y);

        auto const multiply = a * b;
        EXPECT_EQ(multiply.x, a.x * b.x);
        EXPECT_EQ(multiply.y, a.y * b.y);

        auto const division = a / b;
        EXPECT_EQ(division.x, a.x / b.x);
        EXPECT_EQ(division.y, a.y / b.y);
    }
}

TEST(Point, ArithmeticWithValue) {
    for (auto i = 0; i < 25; ++i) {
        auto random = testing::internal::Random(i);
        auto const k = static_cast<float>(random.Generate(25e3) - 10e3);
        auto const a = ds::ui::Point {
                static_cast<int>(random.Generate(25e3) - 10e3),
                static_cast<int>(random.Generate(25e3) - 10e3)
        };

        if (k == 0) {
            continue;
        }

        auto const addition = a + k;
        EXPECT_EQ(addition.x, a.x + static_cast<int>(k));
        EXPECT_EQ(addition.y, a.y + static_cast<int>(k));

        auto const subtract = a - k;
        EXPECT_EQ(subtract.x, a.x - static_cast<int>(k));
        EXPECT_EQ(subtract.y, a.y - static_cast<int>(k));

        auto const multiply = a * k;
        EXPECT_EQ(multiply.x, a.x * static_cast<int>(k));
        EXPECT_EQ(multiply.y, a.y * static_cast<int>(k));

        auto const division = a / k;
        EXPECT_EQ(division.x, a.x / static_cast<int>(k));
        EXPECT_EQ(division.y, a.y / static_cast<int>(k));
    }
}

TEST(Point, EqualityAndInequality) {
    for (auto i = 0; i < 50; ++i) {
        auto random = testing::internal::Random(i);
        auto const x = static_cast<int>(random.Generate(25e3) - 10e3);
        auto const y = static_cast<int>(random.Generate(25e3) - 10e3);

        auto const a = ds::ui::Point {x, y};
        auto const b = ds::ui::Point {x, y};
        auto const c = ds::ui::Point {x - 1, y + 1};

        EXPECT_EQ(a, b);
        EXPECT_EQ(b, a);
        EXPECT_NE(a, c);
        EXPECT_NE(c, a);
    }
}