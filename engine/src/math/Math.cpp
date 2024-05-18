#include "math/Math.h"
#include <iostream>

#include <iomanip> // TODO delete

namespace Crust {
    bool Math::equal(float p_a, float p_b, float p_epsilon) {
        return Math::abs(p_a - p_b) < p_epsilon;
    }

    bool Math::vectorEqual(const Crust::Vector3 &p_a, const Crust::Vector3 &p_b, float p_epsilon) {
        return Math::equal(p_a.x(), p_b.x(), p_epsilon) &&
               Math::equal(p_a.y(), p_b.y(), p_epsilon) &&
               Math::equal(p_a.z(), p_b.z(), p_epsilon);
    }

    bool Math::isVectorZero(const Crust::Vector3 &p_a, float p_epsilon) {
        return Math::equal(p_a.x(), 0.0, p_epsilon) &&
               Math::equal(p_a.y(), 0.0, p_epsilon) &&
               Math::equal(p_a.z(), 0.0, p_epsilon);
    }

    float Math::abs(float p_a) {
        return p_a < 0 ? -p_a : p_a;
    }

    float Math::pow2(float p_a) {
        return p_a * p_a;
    }

    float Math::sqrt(float p_a) {
        return std::sqrt(p_a);
    }

    float Math::degreesToRadians(int p_degrees) {
        return p_degrees * (Math::PI / 180.0);
    }

    int Math::radiansToDegrees(float p_radians) {
        return p_radians * (180.0 / Math::PI);
    }

    float Math::tan(float p_t) {
        return std::tan(p_t);
    }

    float Math::sin(float p_t) {
        return std::sin(p_t);
    }

    float Math::cos(float p_t) {
        return std::cos(p_t);
    }

    //TODO now we can propably optimize it
    Vector3 Math::normal(const Vector3 &p_a, const Vector3 &p_b, const Vector3 &p_c) {
        auto normalMatrix = (p_b - p_a).cross(p_c - p_a).normalized();
        return {normalMatrix.x(), normalMatrix.y(), normalMatrix.z()};
    }

    Vector3 Math::v3IntersectPlane(const Vector3 &p_plane_p, const Vector3 &p_plane_n, const Vector3 &p_line_start,
                                   Vector3 &p_line_end) {
        Vector3 plane_n_norm = p_plane_n.normalized();
        float plane_d = -plane_n_norm.dot(p_plane_p);
        float ad = p_line_start.dot(plane_n_norm);
        float bd = p_line_end.dot(plane_n_norm);
        float p_t = (-plane_d - ad) / (bd - ad);
        return p_line_start + (p_line_end - p_line_start) * p_t;
    }

    Vector3 Math::v3IntersectEdge(const Vector3 &p_edge_start, const Vector3 &p_edge_end,
                                  const Vector3 &p_line_start, const Vector3 &p_line_end,
                                  const Vector3 &p_default_value) {

        float a1 = (p_edge_end.y() - p_edge_start.y()) / (p_edge_end.x() - p_edge_start.x());
        float b1 = p_edge_start.y() - a1 * p_edge_start.x();
        float a2 = (p_line_end.y() - p_line_start.y()) / (p_line_end.x() - p_line_start.x());
        float b2 = p_line_start.y() - a2 * p_line_start.x();

        if (a1 == a2) {
//            Logger::warning("Lines are parallel or collinear!");
            return p_default_value;
        }

        float x = (b2 - b1) / (a1 - a2);
        float y = a1 * x + b1;

        return Vector3(x, y, (p_line_start.z() + p_line_end.z()) / 2.0);
    }


    uint8_t Math::triangle3DClipAgainstPlane(const Crust::Vector3 &p_plane_p, const Crust::Vector3 &p_plane_n,
                                             Crust::Triangle &p_in_tri, Crust::Triangle &p_out_tri1,
                                             Crust::Triangle &p_out_tri2) {
        Vector3 plane_n = p_plane_n.normalized();

        // Return signed shortest distance from point to plane, plane normal must be normalised
        auto distance_from_plane = [&](const Vector3 &p_point) {
            return plane_n.dot(p_point) - plane_n.dot(p_plane_p);
        };

        Vector3 *inside_points[3];
        Vector3 *outside_points[3];
        uint8_t n_inside_points = 0;
        uint8_t n_outside_points = 0;

        float d0 = distance_from_plane(p_in_tri.getVertex(0));
        float d1 = distance_from_plane(p_in_tri.getVertex(1));
        float d2 = distance_from_plane(p_in_tri.getVertex(2));

        if (d0 >= 0) {
            inside_points[n_inside_points++] = &p_in_tri.getVertex(0);
        } else {
            outside_points[n_outside_points++] = &p_in_tri.getVertex(0);
        }

        if (d1 >= 0) {
            inside_points[n_inside_points++] = &p_in_tri.getVertex(1);
        } else {
            outside_points[n_outside_points++] = &p_in_tri.getVertex(1);
        }

        if (d2 >= 0) {
            inside_points[n_inside_points++] = &p_in_tri.getVertex(2);
        } else {
            outside_points[n_outside_points++] = &p_in_tri.getVertex(2);
        }

        if (n_inside_points == 0) {
            return 0;
        }

        if (n_inside_points == 3) {
            p_out_tri1 = p_in_tri;
            return 1;
        }

        if (n_inside_points == 1 && n_outside_points == 2) {
            p_out_tri1.setVertex(0, *inside_points[0]);
            Vector3 p1 = Math::v3IntersectPlane(p_plane_p, p_plane_n, *inside_points[0], *outside_points[0]);
            Vector3 p2 = Math::v3IntersectPlane(p_plane_p, p_plane_n, *inside_points[0], *outside_points[1]);
            p_out_tri1.setVertex(1, p1);
            p_out_tri1.setVertex(2, p2);
            return 1;
        }

        if (n_inside_points == 2 && n_outside_points == 1) {
            Vector3 p1 = Math::v3IntersectPlane(p_plane_p, p_plane_n, *inside_points[0], *outside_points[0]);
            Vector3 p2 = Math::v3IntersectPlane(p_plane_p, p_plane_n, *inside_points[1], *outside_points[0]);

            p_out_tri1.setVertex(2, *inside_points[1]);
            p_out_tri1.setVertex(1, p1);
            p_out_tri1.setVertex(0, *inside_points[0]);

            p_out_tri2.setVertex(2, *inside_points[1]);
            p_out_tri2.setVertex(1, p2);
            p_out_tri2.setVertex(0, p1);
            return 2;
        }

        return 0;
    }

    uint8_t Math::triangle2DClipAgainstEdge(Vector3 &p_edge_p1, Vector3 &p_edge_p2,
                                            Triangle &p_in_tri,
                                            Triangle &p_out_tri1, Triangle &p_out_tri2, Triangle &p_out_tri3) {
        Vector3 *inside_points[3];
        Vector3 *outside_points[3];
        Vector3 *line_points[3];
        uint8_t n_inside_points = 0;
        uint8_t n_outside_points = 0;
        uint8_t n_line_points = 0;

        auto distance_from_edge = [&](const Vector3 &p_point) {
            return ((p_edge_p2.x() - p_edge_p1.x()) * (p_point.y() - p_edge_p1.y()) -
                    (p_point.x() - p_edge_p1.x()) * (p_edge_p2.y() - p_edge_p1.y())) /
                   (Math::sqrt(Math::pow2(p_edge_p2.x() - p_edge_p1.x()) +
                               Math::pow2(p_edge_p2.y() - p_edge_p1.y())));
        };

        float d1 = distance_from_edge(p_in_tri.getVertex(0));
        float d2 = distance_from_edge(p_in_tri.getVertex(1));
        float d3 = distance_from_edge(p_in_tri.getVertex(2));

//        std::cout << "distance from edge 1: " << d1 << std::endl;
//        std::cout << "distance from edge 2: " << d2 << std::endl;
//        std::cout << "distance from edge 3: " << d3 << std::endl;

        if (d1 > 0) {
            inside_points[n_inside_points++] = &p_in_tri.getVertex(0);
        } else if (d1 < 0) {
            outside_points[n_outside_points++] = &p_in_tri.getVertex(0);
        } else {
            line_points[n_line_points++] = &p_in_tri.getVertex(0);
        }

        if (d2 > 0) {
            inside_points[n_inside_points++] = &p_in_tri.getVertex(1);
        } else if (d2 < 0) {
            outside_points[n_outside_points++] = &p_in_tri.getVertex(1);
        } else {
            line_points[n_line_points++] = &p_in_tri.getVertex(1);
        }

        if (d3 > 0) {
            inside_points[n_inside_points++] = &p_in_tri.getVertex(2);
        } else if (d3 < 0) {
            outside_points[n_outside_points++] = &p_in_tri.getVertex(2);
        } else {
            line_points[n_line_points++] = &p_in_tri.getVertex(2);
        }

        if (n_inside_points == 3 || n_outside_points == 3 || n_line_points == 2) {
            p_out_tri1 = p_in_tri;
            return 1;
        }

        if (n_inside_points == 1 && n_outside_points == 1) {
            Vector3 p1 = Math::v3IntersectEdge(p_edge_p1, p_edge_p2, *inside_points[0], *outside_points[0],
                                               *outside_points[0]);

            p_out_tri1.setVertex(0, *outside_points[0]);
            p_out_tri1.setVertex(1, p1);
            p_out_tri1.setVertex(2, *line_points[0]);

            p_out_tri1.setVertex(0, *inside_points[0]);
            p_out_tri1.setVertex(1, p1);
            p_out_tri1.setVertex(2, *line_points[0]);

            return 2;
        }

        if (n_inside_points == 1 && n_outside_points == 2) {
            Vector3 p1 = Math::v3IntersectEdge(p_edge_p1, p_edge_p2, *inside_points[0], *outside_points[0],
                                               *outside_points[0]);
            Vector3 p2 = Math::v3IntersectEdge(p_edge_p1, p_edge_p2, *inside_points[0], *outside_points[1],
                                               *outside_points[1]);

            p_out_tri1.setVertex(0, *outside_points[0]);
            p_out_tri1.setVertex(1, p1);
            p_out_tri1.setVertex(2, *outside_points[1]);

            p_out_tri2.setVertex(0, p1);
            p_out_tri2.setVertex(1, p2);
            p_out_tri2.setVertex(2, *outside_points[1]);

            p_out_tri3.setVertex(0, p2);
            p_out_tri3.setVertex(1, p1);
            p_out_tri3.setVertex(2, *inside_points[0]);

            return 3;
        }

        if (n_inside_points == 2 && n_outside_points == 1) {
            Vector3 p1 = Math::v3IntersectEdge(p_edge_p1, p_edge_p2, *inside_points[0], *outside_points[0],
                                               *outside_points[0]);
            Vector3 p2 = Math::v3IntersectEdge(p_edge_p1, p_edge_p2, *inside_points[1], *outside_points[0],
                                               *outside_points[0]);

            p_out_tri1.setVertex(1, p1);
            p_out_tri1.setVertex(2, p2);
            p_out_tri1.setVertex(0, *outside_points[0]);

            p_out_tri2.setVertex(0, p1);
            p_out_tri2.setVertex(1, *inside_points[1]);
            p_out_tri2.setVertex(2, p2);

            p_out_tri3.setVertex(0, p1);
            p_out_tri3.setVertex(1, *inside_points[0]);
            p_out_tri3.setVertex(2, *inside_points[1]);

            return 3;
        }

        p_out_tri1 = p_in_tri;
        return 1;
    }

    uint8_t Math::triangle2DClipAgainstTriangle(Triangle &p_clip_tri, Triangle &p_in_tri,
                                                Triangle &p_out_tri1, Triangle &p_out_tri2, Triangle &p_out_tri3,
                                                Triangle &p_out_tri4, Triangle &p_out_tri5, Triangle &p_out_tri6,
                                                Triangle &p_out_tri7, Triangle &p_out_tri8, Triangle &p_out_tri9) {
        uint8_t n_clipped_triangles_1 = Math::triangle2DClipAgainstEdge(p_clip_tri.getVertex(0),
                                                                        p_clip_tri.getVertex(1),
                                                                        p_in_tri,
                                                                        p_out_tri1,
                                                                        p_out_tri2,
                                                                        p_out_tri3);
        uint8_t n_clipped_triangles_2 = Math::triangle2DClipAgainstEdge(p_clip_tri.getVertex(0),
                                                                        p_clip_tri.getVertex(2),
                                                                        p_in_tri,
                                                                        p_out_tri4,
                                                                        p_out_tri5,
                                                                        p_out_tri6);
        uint8_t n_clipped_triangles_3 = Math::triangle2DClipAgainstEdge(p_clip_tri.getVertex(1),
                                                                        p_clip_tri.getVertex(2),
                                                                        p_in_tri,
                                                                        p_out_tri7,
                                                                        p_out_tri8,
                                                                        p_out_tri9);

        return n_clipped_triangles_1 + n_clipped_triangles_2 + n_clipped_triangles_3;
    }
}