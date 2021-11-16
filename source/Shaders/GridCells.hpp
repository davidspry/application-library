//! @date 25/10/21
//! @author David Spry

#pragma once

#include <string>

namespace ds::ui::shader {

inline std::string GridCellsVertex() {
    static std::string const Vertex = R"(
    #version 150

    uniform mat4 ciModelViewProjection;
    uniform vec2 gridSpacing;

    in vec4 iPositionAndRadius;
    in vec4 ciPosition;
    in vec4 ciColor;

    out vec4 vertColor;

    void main(void) {
        vec4 position = ciPosition;
        position.xyz *= iPositionAndRadius.w;
        position.xyz += iPositionAndRadius.xyz * vec3(gridSpacing, 1.0f);
        position.xy  += gridSpacing * 0.5;

        vertColor   = ciColor;
        gl_Position = ciModelViewProjection * position;
    }
    )";

    return Vertex;
}

inline std::string GridCellsFragment() {
    static std::string const Fragment = R"(
    #version 150

    in  vec4 vertColor;
    out vec4 fragColor;

    void main(void) {
        fragColor = vertColor;
    }
    )";

    return Fragment;
}

}