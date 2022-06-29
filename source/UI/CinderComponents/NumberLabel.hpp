//! @date 26/10/21
//! @author David Spry

#pragma once

#include <string>
#include <iomanip>
#include <sstream>
#include <cinder/Font.h>
#include <cinder/gl/gl.h>
#include <UI/Constructs/ScrollableValue.hpp>
#include <UI/CinderComponents/GridOutline.hpp>

namespace ds::ui {

//! @class A scrollable number label whose size is set in terms of grid rows and columns.

template <typename T>
class NumberLabel: public ds::ui::GridOutline,
                   public ds::ui::ScrollableValue<T> {
public:
    NumberLabel(T const minimumValue, T const initialValue, T const maximumValue):
            NumberLabel(minimumValue, initialValue, maximumValue, {}) {
    }

    NumberLabel(T const minimumValue, T const initialValue, T const maximumValue, cinder::Font const& labelFont):
            ds::ui::GridOutline(1, 3),
            ds::ui::ScrollableValue<T>(minimumValue, initialValue, maximumValue) {
        init(labelFont);
    }

private:
    void init() {
        textBox.size(size().w, ci::TextBox::GROW)
               .alignment(ci::TextBox::CENTER)
               .color(ci::Color::white())
               .premultiplied(false);

        auto const colour = cinder::gl::ShaderDef().color();
        auto const shader = cinder::gl::getStockShader(colour);
        auto const border = ci::Rectf(0.0f, 0.0f, size().w, size().h);
        auto const geometry = ci::geom::Rect(border);

        hoverBatch = cinder::gl::Batch::create(geometry, shader);

        didUpdateScrollableValue();
    }

    void init(cinder::Font const& labelFont) {
        textBox.font(labelFont);
        init();
    }

public:
    void draw() override {
        draw(0.0f, 0.0f);
    }

    void draw(Point<float> const& offset) override {
        draw(offset.x, offset.y);
    }

    void draw(float const offsetX, float const offsetY) override {
        if (shouldRedraw) {
            init();
        }

        cinder::gl::pushModelMatrix();
        cinder::gl::translate(offsetX, offsetY);
        cinder::gl::translate(origin().x, origin().y);

        if (ScrollableValue<T>::isCursorHovering()) {
            cinder::gl::color(0.5f, 0.5f, 0.5f);
            hoverBatch->draw();
        }

        cinder::gl::translate(0.0f, 0.5f * (size().h - static_cast<float>(texture->getHeight())));
        cinder::gl::color(1.0f, 1.0f, 1.0f);
        cinder::gl::draw(texture);
        cinder::gl::popModelMatrix();

        ds::ui::GridOutline::draw(offsetX, offsetY);
    }

public:
    NumberLabel& setCurrentValue(T const newValue) {
        ScrollableValue<T>::setValue(newValue);
        return *this;
    }

    NumberLabel& setMinimumValue(T const minimumValue) {
        ScrollableValue<T>::setMinimumScrollableValue(minimumValue);
        return *this;
    }

    NumberLabel& setMaximumValue(T const maximumValue) {
        ScrollableValue<T>::setMaximumScrollableValue(maximumValue);
        return *this;
    }

protected:
    void didUpdateScrollableValue() override {
        valueString.str("");
        valueString << std::fixed << std::setprecision(2);
        valueString << ScrollableValue<T>::getValue();

        textBox.setText(valueString.str());
        texture = ci::gl::Texture::create(textBox.render());
    }

protected:
    bool isCursorInBounds(CursorEvent const& event) const override {
        return contains(event.xy);
    }

protected:
    ci::TextBox textBox;
    ci::gl::BatchRef hoverBatch;
    ci::gl::TextureRef texture;

protected:
    std::stringstream valueString;
};

}