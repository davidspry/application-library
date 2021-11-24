//! @date 24/11/21
//! @author David Spry

#include "Rule.hpp"

namespace ds::ui {

void Rule::init() {
    auto const border = ci::geom::Rect({0.0f, 0.0f, size().w, 1.0f});
    auto const colour = cinder::gl::ShaderDef().color();
    auto const shader = cinder::gl::getStockShader(colour);

    rule = cinder::gl::Batch::create(border, shader);
}

void Rule::draw() {
    draw(0.0f, 0.0f);
}

void Rule::draw(Point<float> const& offset) {
    draw(offset.x, offset.y);
}

void Rule::draw(float offsetX, float offsetY) {
    if (shouldRedraw) {
        shouldRedraw = false;
        init();
    }

    cinder::gl::pushModelMatrix();
    cinder::gl::translate(offsetX, offsetY);
    cinder::gl::translate(origin().x, origin().y);
    cinder::gl::translate(0.0f, 0.5f * (size().h - thickness));
    cinder::gl::scale(1.0f, thickness);
    cinder::gl::color(1.0f, 1.0f, 1.0f);

    rule->draw();

    cinder::gl::popModelMatrix();
}

}