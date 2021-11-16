//! @date 15/11/21
//! @author David Spry

#include "RuledGridWithSelection.hpp"

namespace ds::ui {

void RuledGridWithSelection::init() {
    auto const border = ci::Rectf(0.0f, 0.0f, 1.0f, 1.0f);
    auto const colour = ci::gl::ShaderDef().color();
    auto const shader = ci::gl::getStockShader(colour);
    auto const button = ci::geom::Rect(border);

    marquee = cinder::gl::Batch::create(button, shader);
}

void RuledGridWithSelection::draw() {
    draw(0.0f, 0.0f);
}

void RuledGridWithSelection::draw(Point<float> const& offset) {
    draw(offset.x, offset.y);
}

void RuledGridWithSelection::draw(float const offsetX, float const offsetY) {
    if (shouldRedraw) {
        shouldRedraw = false;
        init();
    }

    if (selection.containsSelection()) {
        auto const scaleFactor = selection.size().toFloat() * spacing();
        auto const translation = selection.origin().toFloat() * spacing() + origin();

        cinder::gl::pushModelMatrix();
        cinder::gl::translate(offsetX, offsetY);
        cinder::gl::translate(translation.x, translation.y);
        cinder::gl::scale(scaleFactor.x, scaleFactor.y);
        cinder::gl::color(1.0f, 1.0f, 1.0f, 0.6f);

        marquee->draw();

        cinder::gl::popModelMatrix();
    }

    RuledGridWithCursor::draw(offsetX, offsetY);
}

void RuledGridWithSelection::moveCursor(GridPosition::Direction const&& direction) {
    RuledGridWithCursor::moveCursor(std::forward<GridPosition::Direction const>(direction));

    selection.resetSelection();
}

void RuledGridWithSelection::moveCursor(GridPosition::Direction const&& direction, bool const shouldExtendSelection) {
    if (shouldExtendSelection) {
        selection.buildSelection(position);
        RuledGridWithCursor::moveCursor(std::forward<const Direction>(direction));
        selection.buildSelection(position);
    } else {
        return moveCursor(std::forward<const Direction>(direction));
    }
}

void RuledGridWithSelection::cursorWasDown(CursorEvent const& event) {
    RuledGridWithCursor::cursorWasDown(event);

    if (isCursorHovering()) {
        selection.resetSelection();
    }
}

void RuledGridWithSelection::targetWasPressed(CursorEvent const& event) {
    RuledGridWithCursor::targetWasPressed(event);
    processCursorEvent(event);
}

void RuledGridWithSelection::cursorDidDrag(CursorEvent const& event) {
    RuledGridWithCursor::cursorDidDrag(event);

    if (isBeingPressed()) {
        processCursorEvent(event);
    }
}

void RuledGridWithSelection::processCursorEvent(CursorEvent const& event) {
    if (event.leftButtonIsPressed) {
        selection.resetSelection();
    } else if (event.rightButtonIsPressed) {
        auto const xy = getGridPositionAtPoint(event.xy);
        selection.buildSelection(xy);
    }
}

}