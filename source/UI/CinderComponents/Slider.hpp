//! @date 24/11/21
//! @author David Spry

#pragma once

#include <atomic>
#include <cinder/gl/gl.h>
#include <UI/CinderComponents/Rule.hpp>
#include <UI/Constructs/SliderState.hpp>

namespace ds::ui {

template <typename Type = float>
class Slider: public Rule,
              public SliderState<Type> {
public:
    //! @brief Create a slider that synchronises with the given variable.
    //! @param sliderStateVariable The variable that should be synchronised with the slider's value.
    //! @param minimumValue The minimum value of the slider's range.
    //! @param maximumValue The maximum value of the slider's range.

    Slider(Type& sliderStateVariable,
           Type minimumValue,
           Type maximumValue):
            Slider([&](Type const sliderValue) {
                sliderStateVariable = sliderValue;
            }, minimumValue, sliderStateVariable, maximumValue) {
    }

    //! @brief Create a slider that synchronises with the given variable.
    //! @param sliderStateVariable The variable that should be synchronised with the slider's value.
    //! @param minimumValue The minimum value of the slider's range.
    //! @param maximumValue The maximum value of the slider's range.

    Slider(std::atomic<Type>& sliderStateVariable,
           Type minimumValue,
           Type maximumValue):
            Slider([&](Type const sliderValue) {
                sliderStateVariable.store(sliderValue);
            }, minimumValue, sliderStateVariable.load(), maximumValue) {
    }

    //! @brief Create a slider that invokes the given function when its state changes.
    //! @param callback The function that should be invoked when the slider's state changes.
    //! @param minimumValue The minimum value of the slider's range.
    //! @param initialValue The slider's initial value.
    //! @param maximumValue The maximum value of the slider's range.

    Slider(std::function<void(Type)> callback,
           Type minimumValue,
           Type initialValue,
           Type maximumValue):
            Rule(1, 4),
            SliderState<Type>(minimumValue, initialValue, maximumValue, std::move(callback)) {
        init();
    }

private:
    inline void init() {
        auto const trackShape = ci::geom::Rect({0.0f, 0.0f, 1.0f, 1.0f});
        auto const colour = ci::gl::ShaderDef().color();
        auto const shader = ci::gl::getStockShader(colour);
        auto const circle = ci::geom::Circle()
                .radius(spacing().y * 0.35f)
                .subdivisions(32);

        track = cinder::gl::Batch::create(trackShape, shader);
        handle = cinder::gl::Batch::create(circle, shader);
    }

public:
    inline void draw() override {
        draw(0.0f, 0.0f);
    }

    inline void draw(Point<float> const& offset) override {
        draw(offset.x, offset.y);
    }

    inline void draw(float const offsetX, float const offsetY) override {
        if (shouldRedraw) {
            init();
        }

        Rule::draw(offsetX, offsetY);

        cinder::gl::pushModelMatrix();
        cinder::gl::translate(offsetX, offsetY);
        cinder::gl::translate(origin().x, origin().y);
        cinder::gl::translate(0.0f, 0.5f * size().h);

        auto const position = SliderState<Type>::getSliderPosition() * size().w;
        drawSliderTrack(position);
        drawSliderHandle(position);

        cinder::gl::popModelMatrix();
    }

private:
    inline void drawSliderTrack(float const trackLength) const {
        cinder::gl::pushModelMatrix();
        cinder::gl::translate(0.0f, -0.5f * thickness);
        cinder::gl::scale(trackLength, thickness);
        cinder::gl::color(trackColour);

        track->draw();

        cinder::gl::popModelMatrix();
    }

    inline void drawSliderHandle(float const handleOffset) const {
        cinder::gl::pushModelMatrix();
        cinder::gl::translate(handleOffset, 0.0f);
        cinder::gl::color(1.0f, 1.0f, 1.0f);

        if (SliderState<Type>::isCursorHovering()) {
            auto const k = SliderState<Type>::isBeingPressed() ? 0.5f : 0.8f;
            cinder::gl::color(k, k, k);
        }

        handle->draw();

        cinder::gl::popModelMatrix();
    }

public:
    //! @brief Set the slider's track colour.
    //! @param colour The desired track colour.

    inline void setTrackColour(cinder::Color8u const& colour) {
        trackColour = colour;
    }

    //! @brief Set the slider's track colour.
    //! @param red The red component of the desired track colour.
    //! @param green The green component of the desired track colour.
    //! @param blue The blue component of the desired track colour.

    inline void setTrackColour(uint8_t const red, uint8_t const green, uint8_t const blue) {
        setTrackColour({red, green, blue});
    }

protected:
    [[nodiscard]] inline bool isCursorInBounds(CursorEvent const& event) const override {
        auto const radius = spacing().y * 0.4f;
        auto const handleCentre = origin().x + SliderState<Type>::value * size().w;
        auto const handleDistance = (event.xy.x - handleCentre) *
                                    (event.xy.x - handleCentre) +
                                    (event.xy.y - centre().y) *
                                    (event.xy.y - centre().y);
        return handleDistance <= radius * radius;
    }

    [[nodiscard]] inline float sliderOriginX() const override {
        return origin().x;
    }

    [[nodiscard]] inline float sliderWidthInPixels() const override {
        return size().w;
    }

protected:
    cinder::Color8u trackColour {75, 200, 155};

protected:
    cinder::gl::BatchRef track {};
    cinder::gl::BatchRef handle {};
};

}