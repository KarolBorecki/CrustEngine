#include "math/Math.h"
#include <iostream>

namespace Crust {
    bool Math::equal(float p_a, float p_b, float p_epsilon) {
        return Math::abs(p_a - p_b) < p_epsilon;
    }

    float Math::abs(float p_a) {
        return p_a < 0 ? -p_a : p_a;
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
                                   const Vector3 &p_line_end) {
        Vector3 plane_n_norm = p_plane_n.normalized();
        float plane_d = -plane_n_norm.dot(p_plane_p);
        float ad = p_line_start.dot(plane_n_norm);
        float bd = p_line_end.dot(plane_n_norm);
        float p_t = (-plane_d - ad) / (bd - ad);
        return p_line_start + (p_line_end - p_line_start) * p_t;
    }

    uint8_t Math::triangleClipAgainstPlane(const Crust::Vector3 &p_plane_p, const Crust::Vector3 &p_plane_n,
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

        for (uint8_t i = 0; i < n_inside_points; i++) {
            std::cout << "inside_points: " << *inside_points[i] << std::endl;
        }
        std::cout << std::endl;
        for (uint8_t i = 0; i < n_outside_points; i++) {
            std::cout << "outside_points: " << *outside_points[i] << std::endl;
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
            p_out_tri1.setVertex(1,
                                 Math::v3IntersectPlane(p_plane_p, p_plane_n, *inside_points[0], *outside_points[0]));
            p_out_tri1.setVertex(2,
                                 Math::v3IntersectPlane(p_plane_p, p_plane_n, *inside_points[0], *outside_points[1]));
            return 1;
        }

        if (n_inside_points == 2 && n_outside_points == 1) {
            p_out_tri1.setVertex(0, *inside_points[0]);
            p_out_tri1.setVertex(1, *inside_points[1]);
            p_out_tri1.setVertex(2,
                                 Math::v3IntersectPlane(p_plane_p, p_plane_n, *inside_points[0], *outside_points[0]));

            p_out_tri2.setVertex(0, *inside_points[1]);
            p_out_tri2.setVertex(1, p_out_tri1.getVertex(2));
            p_out_tri2.setVertex(2,
                                 Math::v3IntersectPlane(p_plane_p, p_plane_n, *inside_points[1], *outside_points[0]));
            return 2;
        }

    }
}