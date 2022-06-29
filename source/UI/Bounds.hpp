//! @date 5/10/21
//! @author David Spry

#pragma once

#include "Size.hpp"
#include "Point.hpp"

namespace ds::ui {

//! @class A rectangular bounding box.

template <typename T>
class Bounds {
public:
    //! @brief Construct an empty bounds at position (0, 0).

    Bounds():
            Bounds(0, 0, 0, 0) {
    }

    //! @brief Construct a bounds with the given size at position (0, 0).
    //! @param size The desired size.

    explicit Bounds(ds::ui::Size<T> const& size):
            Bounds(0, 0, size.w, size.h) {
    }

    //! @brief Construct a bounds with the given size at position (0, 0).
    //! @param width The desired width.
    //! @param height The desired height.

    Bounds(T const width, T const height):
            Bounds(0, 0, width, height) {
    }

    //! @brief Construct a bounds with the given size at the given origin point.
    //! @param origin The desired origin point.
    //! @param size The desired size.

    Bounds(ds::ui::Point<T> const& origin, ds::ui::Size<T> const& size):
            Bounds(origin.x, origin.y, size.w, size.h) {
    }

    //! @brief Construct a bounds with the given size at the given origin point.
    //! @param x The x-coordinate of the desired origin point.
    //! @param y The y-coordinate of the desired origin point.
    //! @param width The desired width.
    //! @param height The desired height.

    Bounds(T const x, T const y, T const width, T const height) {
        setPositionWithOrigin(x, y);
        setSizeFromOrigin(width, height);
    }

    virtual ~Bounds() = default;

public:
    //! @brief Get the size of the bounds.

    inline ds::ui::Size<T> const& size() const {
        return m_size;
    }

    //! @brief Get the origin point.

    inline ds::ui::Point<T> const& origin() const {
        return m_origin;
    }

    //! @brief Get the centre point.

    inline ds::ui::Point<T> const& centre() const {
        return m_centre;
    }

    //! @brief Indicate whether the given point falls within the bounds.
    //! @param xy The point to be tested.

    template <typename K>
    inline bool contains(ds::ui::Point<K> const& xy) const {
        static_assert(std::is_integral_v<K> or std::is_floating_point_v<K>,
                      "The given type must either be an integral or a floating point type.");

        return static_cast<T>(xy.x) >= m_origin.x &&
               static_cast<T>(xy.y) >= m_origin.y &&
               static_cast<T>(xy.x) <= m_origin.x + m_size.w &&
               static_cast<T>(xy.y) <= m_origin.y + m_size.h;
    }

public:
    //! @brief Get the upper left point (i.e., the origin).

    inline ds::ui::Point<T> getUpperLeft() const {
        return origin();
    }

    //! @brief Get the upper right point.

    inline ds::ui::Point<T> getUpperRight() const {
        return origin() + ds::ui::Point<T>(size().w, 0);
    }

    //! @brief Get the lower left point.

    inline ds::ui::Point<T> getLowerLeft() const {
        return origin() + ds::ui::Point<T>(0, size().h);
    }

    //! @brief Get the lower right point.

    inline ds::ui::Point<T> getLowerRight() const {
        return origin() + size();
    }

public:
    //! @brief Produce a copy with the given origin.
    //! @param x The x-coordinate of the desired origin point.
    //! @param y The y-coordinate of the desired origin point.

    [[nodiscard]] inline ds::ui::Bounds<T> withOrigin(T const x, T const y) const {
        return {x, y, size().w, size().h};
    }

    //! @brief Produce a copy with the given origin.
    //! @param xy The desired origin point.

    [[nodiscard]] inline ds::ui::Bounds<T> withOrigin(ds::ui::Point<T> const& xy) const {
        return withOrigin(xy.x, xy.y);
    }

    //! @brief Produce a copy with the given centre point.
    //! @param x The x-coordinate of the desired centre point.
    //! @param y The y-coordinate of the desired centre point.

    [[nodiscard]] inline ds::ui::Bounds<T> withCentre(T const x, T const y) const {
        return {x - size().w / static_cast<T>(2), y - size().h / static_cast<T>(2), size().w, size().h};
    }

    //! @brief Produce a copy with the given centre point.
    //! @param xy The desired centre point.

    [[nodiscard]] inline ds::ui::Bounds<T> withCentre(ds::ui::Point<T> const& xy) const {
        return withCentre(xy.x, xy.y);
    }

    //! @brief Produce a copy with the given translation.
    //! @param x The x component of the desired translation vector.
    //! @param y The y component of the desired translation vector.

    [[nodiscard]] inline ds::ui::Bounds<T> withTranslation(T const x, T const y) const {
        return {origin().x + x, origin().y + y, size().w, size().h};
    }

    //! @brief Produce a copy with the given translation.
    //! @param xy The desired translation vector.

    [[nodiscard]] inline ds::ui::Bounds<T> withTranslation(ds::ui::Point<T> const& xy) const {
        return withTranslation(xy.x, xy.y);
    }

    //! @brief Produce a copy with the given size, anchored at the centre.
    //! @param width The desired width.
    //! @param height The desired height.

    [[nodiscard]] inline ds::ui::Bounds<T> withSizeFromCentre(T const width, T const height) const {
        return {centre().x - width * static_cast<T>(0.5), centre().y - height * static_cast<T>(0.5), width, height};
    }

    //! @brief Produce a copy with the given size, anchored at the centre.
    //! @param size The desired size.

    [[nodiscard]] inline ds::ui::Bounds<T> withSizeFromCentre(Size<T> const& size) const {
        return withSizeFromCentre(size.w, size.h);
    }

    //! @brief Produce a copy with the given size, anchored at the origin.
    //! @param width The desired width.
    //! @param height The desired height.

    [[nodiscard]] inline ds::ui::Bounds<T> withSizeFromOrigin(T const width, T const height) const {
        return {origin().x, origin().y, width, height};
    }

    //! @brief Produce a copy with the given size, anchored at the origin.
    //! @param size The desired size.

    [[nodiscard]] inline ds::ui::Bounds<T> withSizeFromOrigin(Size<T> const& size) const {
        return withSizeFromOrigin(size.w, size.h);
    }

    //! @brief Produce a copy with the given width, anchored at the origin.
    //! @param width The desired width.

    [[nodiscard]] inline ds::ui::Bounds<T> withWidthFromOrigin(T const width) const {
        return withSizeFromOrigin(width, size().h);
    }

    //! @brief Produce a copy with the given width, anchored at the centre.
    //! @param width The desired width.

    [[nodiscard]] inline ds::ui::Bounds<T> withWidthFromCentre(T const width) const {
        return withSizeFromCentre(width, size().h);
    }

    //! @brief Produce a copy with the given height, anchored at the origin.
    //! @param height The desired height.

    [[nodiscard]] inline ds::ui::Bounds<T> withHeightFromOrigin(T const height) const {
        return withSizeFromOrigin(size().w, height);
    }

    //! @brief Produce a copy with the given height, anchored at the centre.
    //! @param height The desired height.

    [[nodiscard]] inline ds::ui::Bounds<T> withHeightFromCentre(T const height) const {
        return withSizeFromCentre(size().w, height);
    }

public:
    //! @brief Set the size of the bounds, anchored at the origin.
    //! @param width The desired width.
    //! @param height The desired height.

    inline void setSizeFromOrigin(T const width, T const height) {
        m_size.w = std::max(static_cast<T>(0), width);
        m_size.h = std::max(static_cast<T>(0), height);
        setPositionWithOrigin(m_origin.x, m_origin.y);
    }

    //! @brief Set the size of the bounds, anchored at the origin.
    //! @param size The desired size.

    inline void setSizeFromOrigin(Point<T> const& size) {
        setSizeFromOrigin(size.w, size.h);
    }

    //! @brief Set the size of the bounds, anchored at the centre point.
    //! @param width The desired width.
    //! @param height The desired height.

    inline void setSizeFromCentre(T const width, T const height) {
        m_size.w = std::max(static_cast<T>(0), width);
        m_size.h = std::max(static_cast<T>(0), height);
        setPositionWithCentre(m_centre.x, m_centre.y);
    }

    //! @brief Set the size of the bounds, anchored at the centre point.
    //! @param size The desired size.

    inline void setSizeFromCentre(Point<T> const& size) {
        setSizeFromCentre(size.w, size.h);
    }

public:
    //! @brief Translate the position of the bounds.
    //! @param deltaX The x component of the desired translation vector.
    //! @param deltaY The y component of the desired translation vector.

    inline void translate(T const deltaX, T const deltaY) {
        setPositionWithOrigin(origin().x + deltaX, origin().y + deltaY);
    }

    //! @brief Set the x-coordinate of the origin point.
    //! @param x The x-coordinate of the desired origin point.

    inline void setOriginX(T const x) {
        setPositionWithOrigin(x, origin().y);
    }

    //! @brief Set the y-coordinate of the origin point.
    //! @param y The y-coordinate of the desired origin point.

    inline void setOriginY(T const y) {
        setPositionWithOrigin(origin().x, y);
    }

    //! @brief Set the x-coordinate of the centre point.
    //! @param x The x-coordinate of the desired centre point.

    inline void setCentreX(T const x) {
        setPositionWithCentre(x, centre().y);
    }

    //! @brief Set the x-coordinate of the centre point.
    //! @param x The x-coordinate of the desired centre point.

    inline void setCentreY(T const y) {
        setPositionWithCentre(centre().x, y);
    }

public:
    //! @brief Set the position from the given origin point.
    //! @param x The x-coordinate of the desired origin point.
    //! @param y The y-coordinate of the desired origin point.

    inline void setPositionWithOrigin(T const x, T const y) {
        m_origin.x = x;
        m_origin.y = y;
        m_centre.x = x + static_cast<T>(static_cast<float>(m_size.w) * 0.5f);
        m_centre.y = y + static_cast<T>(static_cast<float>(m_size.h) * 0.5f);
    }

    //! @brief Set the position from the given origin point.
    //! @param xy The desired origin point.

    inline void setPositionWithOrigin(Point<T> const& xy) {
        setPositionWithOrigin(xy.x, xy.y);
    }

    //! @brief Set the position from the given centre point.
    //! @param x The x-coordinate of the desired centre point.
    //! @param y The y-coordinate of the desired centre point.

    inline void setPositionWithCentre(T const x, T const y) {
        m_centre.x = x;
        m_centre.y = y;
        m_origin.x = x - static_cast<T>(static_cast<float>(m_size.w) * 0.5f);
        m_origin.y = y - static_cast<T>(static_cast<float>(m_size.h) * 0.5f);
    }

    //! @brief Set the position from the given centre point.
    //! @param xy The desired centre point.

    inline void setPositionWithCentre(Point<T> const& xy) {
        setPositionWithCentre(xy.x, xy.y);
    }

public:
    //! @brief Set the position from the given upper-left point (i.e., the origin).
    //! @param x The x-coordinate of the desired point.
    //! @param y The y-coordinate of the desired point.

    inline void setPositionWithUpperLeft(T const x, T const y) {
        setPositionWithOrigin(x - size().w, y);
    }

    //! @brief Set the position from the given upper-left point (i.e., the origin).
    //! @param xy The desired point.

    inline void setPositionWithUpperLeft(Point<T> const& xy) {
        setPositionWithUpperRight(xy.x, xy.y);
    }

    //! @brief Set the position from the given upper-right point.
    //! @param x The x-coordinate of the desired point.
    //! @param y The y-coordinate of the desired point.

    inline void setPositionWithUpperRight(T const x, T const y) {
        setPositionWithOrigin(x - size().w, y);
    }

    //! @brief Set the position from the given upper-right point.
    //! @param xy The desired point.

    inline void setPositionWithUpperRight(Point<T> const& xy) {
        setPositionWithUpperRight(xy.x, xy.y);
    }

    //! @brief Set the position from the given lower-left point.
    //! @param x The x-coordinate of the desired point.
    //! @param y The y-coordinate of the desired point.

    inline void setPositionWithLowerLeft(T const x, T const y) {
        setPositionWithOrigin(x, y - size().h);
    }

    //! @brief Set the position from the given lower-left point.
    //! @param xy The desired point.

    inline void setPositionWithLowerLeft(Point<T> const& xy) {
        setPositionWithLowerLeft(xy.x, xy.y);
    }

    //! @brief Set the position from the given lower-right point.
    //! @param x The x-coordinate of the desired point.
    //! @param y The y-coordinate of the desired point.

    inline void setPositionWithLowerRight(T const x, T const y) {
        setPositionWithOrigin(x - size().w, y - size().h);
    }

    //! @brief Set the position from the given lower-right point.
    //! @param xy The desired point.

    inline void setPositionWithLowerRight(Point<T> const& xy) {
        setPositionWithLowerRight(xy.x, xy.y);
    }

public:
    //! @brief Trim the given amount from each side equally.
    //! @param amountToTrim The amount to be trimmed from each side.

    Bounds& trim(T const amountToTrim) {
        setSizeFromCentre(size() - amountToTrim * static_cast<T>(2));

        return *this;
    }

    //! @brief Trim the given amount from the top side and return the trimmed area.
    //! @param amountToTrim The amount to be trimmed from the top side.

    Bounds trimFromTop(T const amountToTrim) {
        setSizeFromOrigin(size().w, size().h - amountToTrim);
        translate(static_cast<T>(0), amountToTrim);

        return {origin().x, origin().y - amountToTrim, size().w, amountToTrim};
    }

    //! @brief Trim the given amount from the left side and return the trimmed area.
    //! @param amountToTrim The amount to be trimmed from the left side.

    Bounds trimFromLeft(T const amountToTrim) {
        setSizeFromOrigin(size().w - amountToTrim, size().h);
        translate(amountToTrim, static_cast<T>(0));

        return {origin().x - amountToTrim, origin().y, amountToTrim, size().h};
    }

    //! @brief Trim the given amount from the right side and return the trimmed area.
    //! @param amountToTrim The amount to be trimmed from the right side.

    Bounds trimFromRight(T const amountToTrim) {
        setSizeFromOrigin(size().w - amountToTrim, size().h);

        return {origin().x + size().w, origin().y, amountToTrim, size().h};
    }

    //! @brief Trim the given amount from the bottom side and return the trimmed area.
    //! @param amountToTrim The amount to be trimmed from the bottom side.

    Bounds trimFromBottom(T const amountToTrim) {
        setSizeFromOrigin(size().w, size().h - amountToTrim);

        return {origin().x, origin().y + size().h, size().w, amountToTrim};
    }

protected:
    ds::ui::Size<T> m_size {};
    ds::ui::Point<T> m_origin {};
    ds::ui::Point<T> m_centre {};
};

}