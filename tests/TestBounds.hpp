//! @file TestBounds.hpp
//! @date 3/10/21
//! @author David Spry

#pragma once

#include <gtest/gtest.h>
#include <UI/Bounds.hpp>

TEST(Rectangle, DefaultConstructor) {
    auto const r = ds::ui::Bounds<int> {};

    EXPECT_EQ(r.size().w, 0);
    EXPECT_EQ(r.size().h, 0);

    EXPECT_EQ(r.origin().x, 0);
    EXPECT_EQ(r.origin().y, 0);

    EXPECT_EQ(r.centre().x, 0);
    EXPECT_EQ(r.centre().y, 0);
}

TEST(Rectangle, ParameterisedConstructor) {
    auto const r = ds::ui::Bounds {5, 5, 10, 20};

    EXPECT_EQ(r.origin().x, 5);
    EXPECT_EQ(r.origin().y, 5);

    EXPECT_EQ(r.centre().x, 10);
    EXPECT_EQ(r.centre().y, 15);

    EXPECT_EQ(r.size().w, 10);
    EXPECT_EQ(r.size().h, 20);
}

TEST(Rectangle, SetSizeFromOrigin) {
    auto r = ds::ui::Bounds {10, 10, 0, 0};
    auto const origin = r.origin();
    auto const centre = r.centre();

    r.setSizeFromOrigin(10, 20);
    EXPECT_EQ(r.size().w, 10);
    EXPECT_EQ(r.size().h, 20);
    EXPECT_EQ(origin, r.origin());
    EXPECT_NE(centre, r.centre());

    r.setSizeFromOrigin(0, 0);
    EXPECT_EQ(r.size().w, 0);
    EXPECT_EQ(r.size().h, 0);
    EXPECT_EQ(origin, r.origin());
    EXPECT_EQ(centre, r.centre());

    r.setPositionWithOrigin(25, 45);
    r.setSizeFromOrigin(50, 0);
    EXPECT_EQ(r.size().w, 50);
    EXPECT_EQ(r.size().h, 0);
    EXPECT_EQ(r.origin().x, 25);
    EXPECT_EQ(r.origin().y, 45);
    EXPECT_EQ(r.centre().x, 50);
    EXPECT_EQ(r.centre().y, 45);
}

TEST(Rectangle, SetSizeFromCentre) {
    auto r = ds::ui::Bounds {0.0f, 0.0f, 20.0f, 20.0f};
    auto const origin = r.origin();
    auto const centre = r.centre();

    r.setSizeFromCentre(50, 50);
    EXPECT_EQ(r.size().w, 50);
    EXPECT_EQ(r.size().h, 50);
    EXPECT_NE(origin, r.origin());
    EXPECT_EQ(centre, r.centre());

    r.setSizeFromCentre(0, 0);
    EXPECT_EQ(r.size().w, 0);
    EXPECT_EQ(r.size().h, 0);
    EXPECT_NE(origin, r.origin());
    EXPECT_EQ(centre, r.centre());

    r.setPositionWithCentre(60, 20);
    r.setSizeFromCentre(40, 40);
    EXPECT_EQ(r.size().w, 40);
    EXPECT_EQ(r.size().h, 40);
    EXPECT_EQ(r.origin().x, 40);
    EXPECT_EQ(r.origin().y, 0);
    EXPECT_EQ(r.centre().x, 60);
    EXPECT_EQ(r.centre().y, 20);
}

TEST(Rectangle, SetPositionWithOrigin) {
    auto r = ds::ui::Bounds<float> {};

    for (auto i = 0; i < 25; ++i) {
        auto random = testing::internal::Random(i);
        auto const x = static_cast<float>(random.Generate(25e3) - 10e3);
        auto const y = static_cast<float>(random.Generate(25e3) - 10e3);
        r.setPositionWithOrigin(x, y);
        EXPECT_EQ(r.origin().x, x);
        EXPECT_EQ(r.origin().y, y);

        auto const xy = ds::ui::Point<float>(x, y);
        r.setPositionWithOrigin(xy);
        EXPECT_EQ(r.origin().x, x);
        EXPECT_EQ(r.origin().y, y);
    }
}

TEST(Rectangle, SetPositionWithCentre) {
    auto r = ds::ui::Bounds<float> {};

    for (auto i = 0; i < 25; ++i) {
        auto random = testing::internal::Random(i);
        auto x = static_cast<float>(random.Generate(25e3) - 10e3);
        auto y = static_cast<float>(random.Generate(25e3) - 10e3);
        r.setPositionWithCentre(x, y);
        EXPECT_EQ(r.centre().x, x);
        EXPECT_EQ(r.centre().y, y);

        auto const xy = ds::ui::Point {x, y};
        r.setPositionWithCentre(xy);
        EXPECT_EQ(r.centre().x, x);
        EXPECT_EQ(r.centre().y, y);
    }
}