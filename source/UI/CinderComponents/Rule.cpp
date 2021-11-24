//! @date 24/11/21
//! @author David Spry

#include "Rule.hpp"

namespace ds::ui {

void Rule::init() {
    auto const line = ci::gl::VertBatch::create(GL_LINES);

    line->vertex(0, centre().y);
    line->vertex(size().w, centre().y);

    auto const program = cinder::gl::GlslProg::Format().version(150)
                                                       .vertex(ds::ui::shader::LinesVertex())
                                                       .fragment(ds::ui::shader::LinesFragment())
                                                       .geometry(ds::ui::shader::LinesGeometry());

    auto const shader = cinder::gl::GlslProg::create(program);

    shader->uniform("LineThickness", thickness);
    shader->uniform("ViewportScale", ci::vec2(cinder::app::getWindowSize()));

    rule = cinder::gl::Batch::create(*line, shader);
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
    cinder::gl::color(1.0f, 1.0f, 1.0f);

    rule->draw();

    cinder::gl::popModelMatrix();
}

void Rule::adjustToLayout() {
    rule->getGlslProg()->uniform("ViewportScale", ci::vec2(cinder::app::getWindowSize()));
}

void Rule::setLineThickness(float const lineThickness) {
    thickness = std::max(0.5f, lineThickness * 0.5f);
    rule->getGlslProg()->uniform("LineThickness", thickness);
}

}