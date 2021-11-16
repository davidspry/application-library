//! @file TestMain.cpp
//! @author David Spry

#include <gtest/gtest.h>
#include "TestPoint.hpp"
#include "TestBounds.hpp"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}