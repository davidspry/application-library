//! @date 25/10/21
//! @author David Spry

#include "DotGrid.hpp"

namespace ds::ui {

void DotGrid::init() {
    auto const cells = dimensions().x * dimensions().y;

    struct Dot {
        ci::vec4 position;
        ci::vec4 color;
    };

    ci::geom::BufferLayout layout;
    layout.append(ci::geom::Attrib::COLOR, 4, sizeof(Dot), offsetof(Dot, color), 1);
    layout.append(ci::geom::Attrib::CUSTOM_0, 4, sizeof(Dot), offsetof(Dot, position), 1);

    std::vector<Dot> dots;
    for (auto row = 0; row < dimensions().y; ++row) {
        for (auto col = 0; col < dimensions().x; ++col) {
            auto& dot = dots.emplace_back();
            dot.color = {ci::vec3(1.0f), 1.0f};
            dot.position.w = dotRadius;
            dot.position.x = static_cast<float>(col);
            dot.position.y = static_cast<float>(row);
        }
    }

    auto const sizeInBytes = cells * static_cast<int>(sizeof(Dot));
    auto const vbo = ci::gl::Vbo::create(GL_ARRAY_BUFFER, sizeInBytes, dots.data(), GL_STATIC_DRAW);
    auto const circles = ci::geom::Circle().center(ci::vec2(0)).radius(1.0f).subdivisions(32);
    auto const vboMesh = ci::gl::VboMesh::create(circles);
    vboMesh->appendVbo(layout, vbo);

    using namespace ds::ui::shader;
    auto const source = ci::gl::GlslProg::Format().vertex(GridCellsVertex()).fragment(GridCellsFragment());
    auto const shader = ci::gl::GlslProg::create(source);
    shader->uniform("gridSpacing", ci::vec2(spacing().x, spacing().y));

    batch = ci::gl::Batch::create(vboMesh, shader, {
            {ci::geom::Attrib::CUSTOM_0, "iPositionAndRadius"}
    });
}

void DotGrid::draw() {
    draw(0.0f, 0.0f);
}

void DotGrid::draw(Point<float> const& offset) {
    draw(offset.x, offset.y);
}

void DotGrid::draw(float const offsetX, float const offsetY) {
    if (shouldRedraw) {
        shouldRedraw = false;
        init();
    }

    cinder::gl::pushModelMatrix();
    cinder::gl::translate(offsetX, offsetY);
    cinder::gl::translate(origin().x, origin().y);
    cinder::gl::color(1.0f, 1.0f, 1.0f);

    batch->drawInstanced(dimensions().x * dimensions().y);

    cinder::gl::popModelMatrix();
}

}