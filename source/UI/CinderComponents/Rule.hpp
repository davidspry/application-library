//! @date 24/11/21
//! @author David Spry

#pragma once

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <Shaders/Lines.hpp>
#include <UI/Components/Grid.hpp>

namespace ds::ui {

class Rule: public Grid {
public:
    //! @brief Rule a line that spans the given numbers of grid columns.
    //! @param columns The number of grid columns that the ruled line should span.

    explicit Rule(int const columns):
            Grid(1, columns) {
        init();
    }

    //! @brief Rule a line that spans the given numbers of grid rows and grid columns.
    //! @param rows The number of grid rows that the ruled line should span.
    //! @param columns The number of grid columns that the ruled line should span.

    Rule(int const rows, int const columns):
            Grid(rows, columns) {
        init();
    }

    //! @brief Rule a line that spans the given numbers of grid rows and grid columns.
    //! @param rows The number of grid rows that the ruled line should span.
    //! @param columns The number of grid columns that the ruled line should span.
    //! @param cellSize The desired grid cell size.

    Rule(int const rows, int const columns, ds::ui::Size<float> const& cellSize):
            Grid(rows, columns, cellSize) {
        init();
    }

private:
    void init();

public:
    void draw() override;
    void draw(Point<float> const& offset) override;
    void draw(float offsetX, float offsetY) override;
    void adjustToLayout() override;

public:
    //! @brief Get the thickness of the ruled line in pixels.

    [[nodiscard]] inline float getLineThickness() const {
        return thickness * 2.0f;
    }

    //! @brief Set the thickness of the ruled line.
    //! @param lineThickness The desired thickness in pixels.

    void setLineThickness(float lineThickness);

protected:
    float thickness {2.0f};

protected:
    cinder::gl::BatchRef rule;
};

}