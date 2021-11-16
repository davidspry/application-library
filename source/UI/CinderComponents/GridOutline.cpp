//! @date 25/10/21
//! @author David Spry

#include "GridOutline.hpp"

namespace ds::ui {

void GridOutline::init() {
    auto const grid = ci::gl::VertBatch::create(GL_LINES);

    for (int const& row: {0, dimensions().y}) {
        auto const x = static_cast<float>(size().x);
        auto const y = static_cast<float>(row) * spacing().h;
        grid->vertex(0, y, 0);
        grid->vertex(x, y, 0);
    }

    for (int const& col: {0, dimensions().x}) {
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

void GridOutline::draw() {
    draw(0.0f, 0.0f);
}

void GridOutline::draw(Point<float> const& offset) {
    draw(offset.x, offset.y);
}

void GridOutline::draw(float const offsetX, float const offsetY) {
    if (shouldRedraw) {
        shouldRedraw = false;
        init();
    }

    RuledGrid::draw(offsetX, offsetY);
}

}