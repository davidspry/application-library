//! @date 15/11/21
//! @author David Spry

#include "RuledGridWithCursor.hpp"

namespace ds::ui {

void RuledGridWithCursor::init() {
    auto const position = getCursorPosition().toFloat();
    auto const border = ci::Rectf(position.x, position.y, spacing().x, spacing().y);
    auto const colour = ci::gl::ShaderDef().color();
    auto const shader = ci::gl::getStockShader(colour);
    auto const button = ci::geom::Rect(border);

    cursor = cinder::gl::Batch::create(button, shader);
}

void RuledGridWithCursor::draw() {
    draw(0.0f, 0.0f);
}

void RuledGridWithCursor::draw(Point<float> const& offset) {
    draw(offset.x, offset.y);
}

void RuledGridWithCursor::draw(float const offsetX, float const offsetY) {
    if (shouldRedraw) {
        init();
    }

    auto const position = origin() + spacing() * getCursorPosition().toFloat();

    cinder::gl::pushModelMatrix();
    cinder::gl::translate(offsetX, offsetY);
    cinder::gl::translate(position.x, position.y);
    cinder::gl::color(1.0f, 1.0f, 1.0f);

    cursor->draw();

    cinder::gl::popModelMatrix();

    RuledGrid::draw(offsetX, offsetY);
}

void RuledGridWithCursor::moveCursor(GridPosition::Direction const&& direction) {
    switch (direction) {
    case Direction::Up: {
        position.y = std::max(position.y - 1, 0);
        break;
    }

    case Direction::Right: {
        position.x = std::min(position.x + 1, dimensions().w - 1);
        break;
    }

    case Direction::Down: {
        position.y = std::min(position.y + 1, dimensions().h - 1);
        break;
    }

    case Direction::Left: {
        position.x = std::max(position.x - 1, 0);
        break;
    }
    }
}

void RuledGridWithCursor::moveCursorTo(Point<int> const& screenPosition) {
    auto const gridPosition = getGridPositionAtPoint(screenPosition);
    position.x = gridPosition.x;
    position.y = gridPosition.y;
}

bool RuledGridWithCursor::isCursorInBounds(CursorEvent const& event) const {
    return contains(event.xy);
}

void RuledGridWithCursor::targetWasPressed(CursorEvent const& event) {
    moveCursorTo(event.xy);
}

void RuledGridWithCursor::cursorDidDrag(CursorEvent const& event) {
    if (isBeingPressed()) {
        moveCursorTo(event.xy);
    }
}

}