//! @date 25/10/21
//! @author David Spry

#pragma once

#include <string>

namespace ds::ui::shader {

//! @author Paul Houx
//! @url License: https://github.com/paulhoux/Cinder-Samples/tree/master/GeometryShader

inline std::string LinesVertex() {
    static std::string const Vertex = R"(
    #version 150

    uniform mat4 ciModelViewProjection;

    in vec4 ciPosition;
    in vec3 ciColor;

    out VertexData{
        vec3 mColor;
    } VertexOut;

    void main(void)
    {
        VertexOut.mColor = ciColor;
        gl_Position = ciModelViewProjection * ciPosition;
    }
    )";

    return Vertex;
}

//! @author Paul Houx
//! @url License: https://github.com/paulhoux/Cinder-Samples/tree/master/GeometryShader

inline std::string LinesFragment() {
    static std::string const Fragment = R"(
    #version 150

    in VertexData {
        vec2 mTexCoord;
        vec3 mColor;
    } VertexIn;

    out vec4 fragColor;

    void main(void)
    {
        fragColor = vec4(VertexIn.mColor, 1.0f);
    }
    )";

    return Fragment;
}

//! @author Paul Houx
//! @url License: https://github.com/paulhoux/Cinder-Samples/tree/master/GeometryShader

inline std::string LinesGeometry() {
    static std::string const Geometry = R"(
    #version 150

    uniform float LineThickness;
    uniform vec2  ViewportScale;

    layout (lines) in;
    layout (triangle_strip, max_vertices = 4) out;

    in VertexData {
        vec3 mColor;
    } VertexIn[2];

    out VertexData {
        vec2 mTexCoord;
        vec3 mColor;
    } VertexOut;

    vec2 toScreenSpace(vec4 vertex)
    {
        return vec2(vertex.xy / vertex.w) * ViewportScale;
    }

    void main(void)
    {
        // Obtain the points of the previous, current, and next line segments:
        vec2 Point0 = toScreenSpace(gl_in[0].gl_Position);
        vec2 Point1 = toScreenSpace(gl_in[1].gl_Position);

        // Naive culling
        vec2 Area = ViewportScale * 1.2;
        if (Point1.x < -Area.x || Point1.x > Area.x) return;
        if (Point1.y < -Area.y || Point1.y > Area.y) return;

        // Determine the direction of each of the previous, current, and next line segments.
        vec2 Vector = normalize(Point1 - Point0);

        // Determine the normal vector of each line segment.
        vec2 Normal = vec2(-Vector.y, Vector.x);

        // Generate a triangle strip
        VertexOut.mTexCoord = vec2(0, 0);
        VertexOut.mColor = VertexIn[0].mColor;
        gl_Position = vec4((Point0 - Vector * LineThickness - Normal * LineThickness) / ViewportScale, 0.0, 1.0);
        EmitVertex();

        VertexOut.mTexCoord = vec2(0, 1);
        VertexOut.mColor = VertexIn[0].mColor;
        gl_Position = vec4((Point0 - Vector * LineThickness + Normal * LineThickness) / ViewportScale, 0.0, 1.0);
        EmitVertex();

        VertexOut.mTexCoord = vec2(0, 0);
        VertexOut.mColor = VertexIn[1].mColor;
        gl_Position = vec4((Point1 + Vector * LineThickness - Normal * LineThickness) / ViewportScale, 0.0, 1.0);
        EmitVertex();

        VertexOut.mTexCoord = vec2(0, 1);
        VertexOut.mColor = VertexIn[1].mColor;
        gl_Position = vec4((Point1 + Vector * LineThickness + Normal * LineThickness) / ViewportScale, 0.0, 1.0);
        EmitVertex();

        EndPrimitive();
    }
    )";

    return Geometry;
}

}