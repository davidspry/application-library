//! @date 1/12/21
//! @author David Spry

#include "Label.hpp"

namespace ds::ui {

void Label::init() {
    textBox.size(static_cast<int>(size().w), ci::TextBox::GROW)
           .alignment(ci::TextBox::CENTER)
           .color(ci::Color::white())
           .premultiplied(false);

    auto const colour = cinder::gl::ShaderDef().color();
    auto const shader = cinder::gl::getStockShader(colour);
    auto const border = ci::Rectf(0.0f, 0.0f, size().w, size().h);
    auto const geometry = ci::geom::Rect(border);

    background = cinder::gl::Batch::create(geometry, shader);

    didUpdateLabel();
}

void Label::init(cinder::Font const& labelFont) {
    textBox.font(labelFont);
    init();
}

void Label::draw() {
    draw(0.0f, 0.0f);
}

void Label::draw(Point<float> const& offset) {
    draw(offset.x, offset.y);
}

void Label::draw(float const offsetX, float const offsetY) {
    if (shouldRedraw) {
        init();
    }

    cinder::gl::pushModelMatrix();
    cinder::gl::translate(offsetX, offsetY);
    cinder::gl::translate(origin().x, origin().y);
    cinder::gl::color(backgroundColour);
    background->draw();

    cinder::gl::translate(0.0f, 0.5f * (size().h - static_cast<float>(texture->getHeight())));
    cinder::gl::color(1.0f, 1.0f, 1.0f);
    cinder::gl::draw(texture);
    cinder::gl::popModelMatrix();

    if (shouldDrawOutline) {
        GridOutline::draw(offsetX, offsetY);
    }
}

void Label::adjustToLayout() {
    textBox.size(static_cast<int>(size().w), ci::TextBox::GROW);
    GridOutline::adjustToLayout();
}

int Label::getColumnSpanForText(std::string_view labelText) {
    auto const& priorSize = textBox.getSize();
    auto const columnSpan = static_cast<float>(textBox.size(0, 0).text(std::string(labelText)).measure().x) /
                            static_cast<float>(spacing().x);

    textBox.size(priorSize).text(std::string(text));

    return static_cast<int>(std::ceil(columnSpan));
}

void Label::setText(std::string_view newLabelText) {
    text = newLabelText;
    didUpdateLabel();
}

void Label::setFont(cinder::Font const& newFont) {
    textBox.font(newFont);
    didUpdateLabel();
}

void Label::setTextColour(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
    setTextColour(cinder::ColorA8u(red, green, blue, alpha));
}

void Label::setTextColour(cinder::ColorA8u const& newTextColour) {
    labelTextColour = newTextColour;
    didUpdateLabel();
}

void Label::setBackgroundColour(uint8_t const red, uint8_t const green, uint8_t const blue, uint8_t const alpha) {
    return setBackgroundColour(cinder::ColorA8u(red, green, blue, alpha));
}

void Label::setBackgroundColour(cinder::ColorA8u const& newBackgroundColour) {
    backgroundColour = newBackgroundColour;
}

void Label::setShouldDrawBorder(bool const shouldDrawBorder) {
    shouldDrawOutline = shouldDrawBorder;
}

void Label::didUpdateLabel() {
    textBox.color(labelTextColour);
    textBox.setText(std::string(text));
    texture = cinder::gl::Texture::create(textBox.render());
}

}