//! @date 12/11/21
//! @author David Spry

#include "Button.hpp"

namespace ds::ui {

void Button::init() {
    auto const border = ci::Rectf(0.0f, 0.0f, size().w, size().h);
    auto const colour = ci::gl::ShaderDef().color();
    auto const shader = ci::gl::getStockShader(colour);
    auto const button = ci::geom::Rect(border);

    buttonFill = cinder::gl::Batch::create(button, shader);
}

void Button::draw() {
    draw(0.0f, 0.0f);
}

void Button::draw(Point<float> const& offset) {
    draw(offset.x, offset.y);
}

void Button::draw(float const offsetX, float const offsetY) {
    if (shouldRedraw) {
        shouldRedraw = false;
        init();
    }

    if (isButtonPressed() or isCursorHovering() or isBeingPressed()) {
        cinder::gl::pushModelMatrix();
        cinder::gl::translate(offsetX, offsetY);
        cinder::gl::translate(origin().x, origin().y);

        if (isButtonPressed()) {
            cinder::gl::color(activeColour);
            buttonFill->draw();
        }

        if (isCursorHovering()) {
            cinder::gl::color(1.0f, 1.0f, 1.0f, isBeingPressed() ? 0.50f : 0.30f);
            buttonFill->draw();
        }

        cinder::gl::popModelMatrix();
    }

    GridOutline::draw(offsetX, offsetY);
}

bool Button::isCursorInBounds(CursorEvent const& event) const {
    return contains(event.xy);
}

}