//! @date 25/10/21
//! @author David Spry

#include "RuledGrid.hpp"

namespace ds::ui {

void RuledGrid::init() {
    auto const grid = ci::gl::VertBatch::create(GL_LINES);

    for (int row = 0; row <= dimensions().y; ++row) {
        auto const x = static_cast<float>(size().x);
        auto const y = static_cast<float>(row) * spacing().h;
        grid->vertex(0, y, 0);
        grid->vertex(x, y, 0);
    }

    for (int col = 0; col <= dimensions().x; ++col) {
        auto const x = static_cast<float>(col) * spacing().w;
        auto const y = static_cast<float>(size().y);
        grid->vertex(x, 0, 0);
        grid->vertex(x, y, 0);
    }

    auto const program = cinder::gl::GlslProg::Format().version(150)
                                                       .vertex(ds::ui::shader::LinesVertex())
                                                       .fragment(ds::ui::shader::LinesFragment())
                                                       .geometry(ds::ui::shader::LinesGeometry());

    auto const shader = cinder::gl::GlslProg::create(program);

    shader->uniform("LineThickness", thickness);
    shader->uniform("ViewportScale", ci::vec2(cinder::app::getWindowSize()));

    rules = cinder::gl::Batch::create(*grid, shader);
}

void RuledGrid::draw() {
    draw(0.0f, 0.0f);
}

void RuledGrid::draw(Point<float> const& offset) {
    draw(offset.x, offset.y);
}

void RuledGrid::draw(float const offsetX, float const offsetY) {
    if (shouldRedraw) {
        shouldRedraw = false;
        init();
    }

    cinder::gl::pushModelMatrix();
    cinder::gl::translate(offsetX, offsetY);
    cinder::gl::translate(origin().x, origin().y);
    cinder::gl::color(1.0f, 1.0f, 1.0f);

    rules->draw();

    cinder::gl::popModelMatrix();
}

void RuledGrid::adjustToLayout() {
    rules->getGlslProg()->uniform("ViewportScale", ci::vec2(cinder::app::getWindowSize()));
}

void RuledGrid::setLineThickness(float const lineThickness) {
    thickness = std::max(0.5f, lineThickness * 0.5f);
    rules->getGlslProg()->uniform("LineThickness", thickness);
}

}