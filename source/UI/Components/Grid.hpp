//! @date 25/10/21
//! @author David Spry

#pragma once

#include "UI/Component.hpp"

namespace ds::ui {

class Grid: public ds::ui::Component {
public:
    //! @brief Create a grid with the given dimensions and a cell size of 20.
    //! @param rows The desired number of rows.
    //! @param columns The desired number of columns.

    Grid(int const rows, int const columns):
            Grid(rows, columns, ds::ui::Size<float>(20.0f, 20.0f)) {
    }

    //! @brief Create a grid with the given dimensions and the given cell size.
    //! @param rows The desired number of rows.
    //! @param columns The desired number of columns.
    //! @param cellSize The desired cell size in pixels.

    Grid(int const rows, int const columns, ds::ui::Size<float> const& cellSize):
            ds::ui::Component(static_cast<float>(columns) * cellSize.w,
                              static_cast<float>(rows) * cellSize.h),
            m_dimensions(columns, rows),
            m_spacing(cellSize) {
    }

public:
    //! @brief Get the size of the grid's constituent cells.

    [[nodiscard]] inline ds::ui::Size<float> const& spacing() const {
        return m_spacing;
    }

    //! @brief Get the grid's dimensions in terms of rows and columns.

    [[nodiscard]] inline ds::ui::Size<int> const& dimensions() const {
        return m_dimensions;
    }

public:
    //! @brief Set the size of the grid's constituent cells.
    //! @param rowSpacing The space between each row.
    //! @param columnSpacing The space between each column.

    inline void setSpacing(float const rowSpacing, float const columnSpacing) {
        m_spacing.y = rowSpacing;
        m_spacing.x = columnSpacing;

        setSizeFromOrigin(static_cast<float>(dimensions().w) * spacing().w,
                          static_cast<float>(dimensions().h) * spacing().h);

        setShouldRedraw(true);
    }

    //! @brief Set the size of the grid's constituent cells.
    //! @param gridSpacing The size of each cell.

    inline void setSpacing(ds::ui::Size<float> const& gridSpacing) {
        setSpacing(gridSpacing.y, gridSpacing.x);
    }

    //! @brief Set the size of the grid in terms of rows and columns.
    //! @param rows The desired number of rows.
    //! @param columns The desired number of columns.

    inline void setDimensions(int const rows, int const columns) {
        m_dimensions.y = rows;
        m_dimensions.x = columns;

        setSizeFromOrigin(static_cast<float>(dimensions().w) * spacing().w,
                          static_cast<float>(dimensions().h) * spacing().h);

        setShouldRedraw(true);
    }

    //! @brief Set the size of the grid in terms of rows and columns.
    //! @param gridDimensions The desired number of rows and columns.

    inline void setDimensions(ds::ui::Size<int> const& gridDimensions) {
        setDimensions(gridDimensions.h, gridDimensions.w);
    }

public:
    //! @brief Get the pixel offset of the given grid position from the origin.
    //! @param gridPosition The grid position whose pixel offset should be computed.

    [[nodiscard]] ds::ui::Point<int> getGridPositionAsPixelOffset(ds::ui::Point<int> const& gridPosition) const;

    //! @brief Get the grid position nearest to the given screen coordinate.
    //! @param xy The screen position to be tested.

    [[nodiscard]] virtual ds::ui::Point<int> getGridPositionAtPoint(ds::ui::Point<int> const& xy) const;

protected:
    ds::ui::Size<float> m_spacing;
    ds::ui::Size<int> m_dimensions;
};

}