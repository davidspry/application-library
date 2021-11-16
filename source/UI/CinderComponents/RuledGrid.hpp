//! @date 25/10/21
//! @author David Spry

#pragma once

#include <UI/Components/Grid.hpp>
#include <Shaders/Lines.hpp>
#include <cinder/app/app.h>
#include <cinder/gl/gl.h>
#include <algorithm>

namespace ds::ui {

class RuledGrid: public Grid {
public:
    RuledGrid(int const rows, int const columns):
            Grid(rows, columns) {
        init();
    }

    RuledGrid(int const rows, int const columns, ds::ui::Size<float> const& cellSize):
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
    //! @brief Get the thickness of the grid's lines in pixels.

    [[nodiscard]] inline float getLineThickness() const {
        return thickness * 2.0f;
    }

    //! @brief Set the thickness of the grid's lines.
    //! @param lineThickness The desired thickness in pixels.

    void setLineThickness(float lineThickness);

protected:
    float thickness {2.0f};

protected:
    cinder::gl::BatchRef rules;
};

}