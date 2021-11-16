//! @date 5/10/21
//! @author David Spry

#pragma once

#include "Bounds.hpp"

namespace ds::ui {

//! @brief A drawable component with a rectangular bounding box.

class Component: public ds::ui::Bounds<float> {
public:
    //! @brief Create an empty component.

    Component() = default;

    //! @brief Create a component with the given size and the origin point (0, 0).
    //! @param width The desired width, anchored at the origin.
    //! @param height The desired height, anchored at the origin.

    Component(float const width, float const height):
            ds::ui::Bounds<float>(width, height) {
    }

    virtual ~Component() = default;

public:
    //! @brief Draw the component.
    //! @param offsetX The x component of the desired translation vector for the current draw.
    //! @param offsetY The y component of the desired translation vector for the current draw.

    virtual void draw(float offsetX, float offsetY) = 0;

    //! @brief Draw the component.
    //! @param offset A translation vector for the current draw.

    virtual inline void draw(ds::ui::Point<float> const& offset) {
        draw(offset.x, offset.y);
    }

    //! @brief Draw the component.

    virtual inline void draw() {
        draw(0.0f, 0.0f);
    }

public:
    //! @brief Indicate that the component should be redrawn.

    inline void setShouldRedraw(bool const componentShouldRedraw) {
        shouldRedraw = componentShouldRedraw;
    }

    //! @brief Indicate that the component should adjust after resizing.

    virtual inline void adjustAfterResize() {
    }

protected:
    bool shouldRedraw {false};
};

}