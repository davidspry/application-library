//! @date 5/10/21
//! @author David Spry

#pragma once

#include <ostream>
#include <type_traits>

namespace ds::ui {

//! @struct A two-component vector representing a point, (x, y).

template<typename T>
struct Point {
public:
    union {
        T x;
        T w;
    };

    union {
        T y;
        T h;
    };

public:
    //! @brief Create the zero point, (0, 0).

    Point(): Point(static_cast<T>(0), static_cast<T>(0)) {
    }

    //! @brief Create the point (x, y).
    //! @param x The x-coordinate of the desired point.
    //! @param y The y-coordinate of the desired point.

    template<typename K>
    Point(K x, K y): Point(static_cast<T>(x), static_cast<T>(y)) {
    }

    //! @brief Create the point (x, y).
    //! @param x The x-coordinate of the desired point.
    //! @param y The y-coordinate of the desired point.

    Point(T x, T y): x(x), y(y) {
    }

public:
    friend std::ostream& operator<<(std::ostream& stream, Point const& xy) {
        stream << '(' << xy.x << ", " << xy.y << ')';
        return stream;
    }

public:
    inline Point operator-() const {
        return {-x, -y};
    }

public:
    //! @brief Create a Point<int> using the Point's components.

    [[nodiscard]] inline Point<int> toInt() const {
        return {static_cast<int>(x), static_cast<int>(y)};
    }

    //! @brief Create a Point<float> using the Point's components.

    [[nodiscard]] inline Point<float> toFloat() const {
        return {static_cast<float>(x), static_cast<float>(y)};
    }

    //! @brief Create a Point<double> using the Point's components.

    [[nodiscard]] inline Point<double> toDouble() const {
        return {static_cast<double>(x), static_cast<double>(y)};
    }

public:
    template<typename K>
    inline Point operator+(K const& k) const {
        static_assert(std::is_arithmetic_v<K>);
        return {
                x + static_cast<T>(k),
                y + static_cast<T>(k)
        };
    }

    template<typename K>
    inline Point operator-(K const& k) const {
        static_assert(std::is_arithmetic_v<K>);
        return {
                x - static_cast<T>(k),
                y - static_cast<T>(k)
        };
    }

    template<typename K>
    inline Point operator*(K const& k) const {
        static_assert(std::is_arithmetic_v<K>);
        return {
                x * static_cast<T>(k),
                y * static_cast<T>(k)
        };
    }

    template<typename K>
    inline Point operator/(K const& k) const {
        static_assert(std::is_arithmetic_v<K>);
        return {
                x / static_cast<T>(k),
                y / static_cast<T>(k)
        };
    }

public:
    inline Point operator+(Point const& other) const {
        return {x + other.x, y + other.y};
    }

    inline Point operator-(Point const& other) const {
        return {x - other.x, y - other.y};
    }

    inline Point operator*(Point const& other) const {
        return {x * other.x, y * other.y};
    }

    inline Point operator/(Point const& other) const {
        return {x / other.x, y / other.y};
    }

public:
    template<typename K>
    inline Point& operator+=(K const& k) const {
        static_assert(std::is_arithmetic_v<K>);
        x += static_cast<T>(k);
        y += static_cast<T>(k);
        return *this;
    }

    template<typename K>
    inline Point& operator-=(K const& k) const {
        static_assert(std::is_arithmetic_v<K>);
        x -= static_cast<T>(k);
        y -= static_cast<T>(k);
        return *this;
    }

    template<typename K>
    inline Point& operator*=(K const& k) const {
        static_assert(std::is_arithmetic_v<K>);
        x *= static_cast<T>(k);
        y *= static_cast<T>(k);
        return *this;
    }

    template<typename K>
    inline Point& operator/=(K const& k) const {
        static_assert(std::is_arithmetic_v<K>);
        x /= static_cast<T>(k);
        y /= static_cast<T>(k);
        return *this;
    }

public:
    inline bool operator==(Point const& other) const {
        return x == other.x && y == other.y;
    }

    inline bool operator!=(Point const& other) const {
        return x != other.x or y != other.y;
    }

    inline Point& operator+=(Point const& other) const {
        x += other.x;
        y += other.y;
        return *this;
    }

    inline Point& operator-=(Point const& other) const {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    inline Point& operator*=(Point const& other) const {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    inline Point& operator/=(Point const& other) const {
        x /= other.x;
        y /= other.y;
        return *this;
    }
};

}