//! @date 1/12/21
//! @author David Spry

#pragma once

#include <cmath>
#include <string>
#include <string_view>
#include <cinder/Font.h>
#include <cinder/gl/gl.h>
#include <UI/CinderComponents/GridOutline.hpp>

namespace ds::ui {

class Label: public GridOutline {
public:
    Label():
            Label("Label") {
    }

    explicit Label(std::string_view labelText, cinder::Font const& labelFont = cinder::Font()):
            Label(1, 1, labelText, labelFont) {
        setDimensions(1, getColumnSpanForText(labelText));
    }

    Label(int const rows, int const columns, std::string_view labelText, cinder::Font const& labelFont):
            GridOutline(rows, columns),
            backgroundColour(cinder::ColorA8u(0, 0, 0, 1)),
            labelTextColour(cinder::Color::white()),
            text(labelText) {
        init(labelFont);
    }

private:
    void init();
    void init(cinder::Font const& labelFont);

public:
    void draw() override;
    void draw(Point<float> const& offset) override;
    void draw(float offsetX, float offsetY) override;
    void adjustToLayout() override;

public:
    void setText(std::string_view newLabelText);
    void setFont(cinder::Font const& newFont);
    void setTextColour(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
    void setTextColour(cinder::ColorA8u const& newTextColour);
    void setBackgroundColour(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
    void setBackgroundColour(cinder::ColorA8u const& newBackgroundColour);
    void setShouldDrawBorder(bool shouldDrawBorder);

protected:
    void didUpdateLabel();

private:
    int getColumnSpanForText(std::string_view labelText);

private:
    ci::TextBox textBox;
    ci::gl::TextureRef texture;
    ci::gl::BatchRef background;

private:
    bool shouldDrawOutline {false};
    ci::ColorA8u labelTextColour;
    ci::ColorA8u backgroundColour;

private:
    std::string_view text;
};

}