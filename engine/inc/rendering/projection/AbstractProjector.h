#ifndef CRUSTENGINE_ABSTRACTPROJECTOR_H
#define CRUSTENGINE_ABSTRACTPROJECTOR_H

#include <cstdint>
#include "objects/Camera.h"
#include "objects/LightSource.h"
#include "objects/RenderObject.h"
#include "math/Matrix.h"
#include "math/Vector3.h"
#include "math/Vector4.h"
#include <random>
#include <algorithm>


namespace Crust {


    /**
     * @brief A projector base class. Defines basic operations that can be implemented based on different projection models.
     */
    class AbstractProjector {
    public:

        /**
         * @brief Construct a new Projector object with the specified width and height.
         *
         * @param p_width The width of the projector.
         * @param p_height The height of the projector.
         */
        AbstractProjector(uint16_t p_width, uint16_t p_height) : m_width(p_width), m_height(p_height) {
            m_aspect_ratio = (float) p_height / (float) p_width;
        }

        /**
         * @brief Destroy the Projector object.
         */
        virtual ~AbstractProjector() = default;

        typedef struct ProjectionData {
            Vector3 v1;
            Vector3 v2;
            Vector3 v3;
            uint8_t r, g, b, a;
            uint8_t light = 0;
        } ProjectionData_t;

        double cross2D(const Vector3 &a, const Vector3 &b) {
            return a.x() * b.y() - a.y() * b.x();
        }

        bool
        linesIntersect(const Vector3 &p1, const Vector3 &p2, const Vector3 &q1, const Vector3 &q2,
                       Vector3 &intersection) {
            Vector3 r = p2 - p1;
            Vector3 s = q2 - q1;
            double rxs = cross2D(r, s);
            Vector3 qp = q1 - p1;
            double t = cross2D(qp, s) / rxs;
            double u = cross2D(qp, r) / rxs;

            if (rxs != 0 && t >= 0 && t <= 1 && u >= 0 && u <= 1) {
                intersection = p1 + r * t;
                return true;
            }
            return false;
        }

        bool pointInTriangle(const Vector3 &pt, const ProjectionData_t &tri) {
            auto sign = [](const Vector3 &p1, const Vector3 &p2, const Vector3 &p3) {
                return (p1.x() - p3.x()) * (p2.y() - p3.y()) - (p2.x() - p3.x()) * (p1.y() - p3.y());
            };

            double d1 = sign(pt, tri.v1, tri.v2);
            double d2 = sign(pt, tri.v2, tri.v3);
            double d3 = sign(pt, tri.v3, tri.v1);

            bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
            bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

            return !(has_neg && has_pos);
        }

        std::vector<Vector3> findIntersections(const ProjectionData_t &t1, const ProjectionData_t &t2) {
            std::vector<Vector3> intersections;
            Vector3 intersection;

            if (linesIntersect(t1.v1, t1.v2, t2.v1, t2.v2, intersection)) intersections.push_back(intersection);
            if (linesIntersect(t1.v1, t1.v2, t2.v2, t2.v3, intersection)) intersections.push_back(intersection);
            if (linesIntersect(t1.v1, t1.v2, t2.v3, t2.v1, intersection)) intersections.push_back(intersection);

            if (linesIntersect(t1.v2, t1.v3, t2.v1, t2.v2, intersection)) intersections.push_back(intersection);
            if (linesIntersect(t1.v2, t1.v3, t2.v2, t2.v3, intersection)) intersections.push_back(intersection);
            if (linesIntersect(t1.v2, t1.v3, t2.v3, t2.v1, intersection)) intersections.push_back(intersection);

            if (linesIntersect(t1.v3, t1.v1, t2.v1, t2.v2, intersection)) intersections.push_back(intersection);
            if (linesIntersect(t1.v3, t1.v1, t2.v2, t2.v3, intersection)) intersections.push_back(intersection);
            if (linesIntersect(t1.v3, t1.v1, t2.v3, t2.v1, intersection)) intersections.push_back(intersection);

            return intersections;
        }

        std::vector<ProjectionData_t> splitTriangle(const ProjectionData_t &t1, const ProjectionData_t &t2) {
            std::vector<Vector3> points;

            points.push_back(t1.v1);
            points.push_back(t1.v2);
            points.push_back(t1.v3);

            auto intersections = findIntersections(t1, t2);
            points.insert(points.end(), intersections.begin(), intersections.end());

            for (const auto &vert: {t2.v1, t2.v2, t2.v3}) {
                if (pointInTriangle(vert, t1)) {
                    points.push_back(vert);
                }
            }

            std::vector<ProjectionData_t> result;
            for (size_t i = 0; i < points.size(); ++i) {
                for (size_t j = i + 1; j < points.size(); ++j) {
                    for (size_t k = j + 1; k < points.size(); ++k) {
                        ProjectionData_t newTriangle = {points[i], points[j], points[k], t1.r, t1.g, t1.b, t1.a,
                                                        t1.light};
                        bool valid = true;
                        for (size_t m = 0; m < points.size(); ++m) {
                            if (m != i && m != j && m != k) {
                                if (pointInTriangle(points[m], newTriangle)) {
                                    valid = false;
                                    break;
                                }
                            }
                        }
                        if (valid) {
                            result.push_back(newTriangle);
                        }
                    }
                }
            }

            return result;
        }

        Vector3 crossProduct(Vector3 a, Vector3 b) {
            Vector3 result;
            result.x() = a.y() * b.z() - a.z() * b.y();
            result.y() = a.z() * b.x() - a.x() * b.z();
            result.z() = a.x() * b.y() - a.y() * b.x();
            return result;
        }

// Funkcja pomocnicza do obliczania różnicy wektorów
        Vector3 subtract(Vector3 a, Vector3 b) {
            Vector3 result;
            result.x() = a.x() - b.x();
            result.y() = a.y() - b.y();
            result.z() = a.z() - b.z();
            return result;
        }

// Funkcja pomocnicza do obliczania iloczynu skalarnego
        double dotProduct(Vector3 a, Vector3 b) {
            return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
        }

// Funkcja pomocnicza do projekcji punktu na oś
        double project(Vector3 axis, Vector3 point) {
            return dotProduct(axis, point);
        }

// Funkcja do sprawdzania, czy dwie projekcje nachodzą na siebie
        bool overlap(double minA, double maxA, double minB, double maxB) {
            return !(maxA < minB || maxB < minA);
        }

// Funkcja główna sprawdzająca, czy dwa trójkąty nachodzą na siebie
        bool trianglesOverlap(ProjectionData_t t1, ProjectionData_t t2) {
            Vector3 axes[6];
            Vector3 edges1[3] = {subtract(t1.v2, t1.v1), subtract(t1.v3, t1.v2), subtract(t1.v1, t1.v3)};
            Vector3 edges2[3] = {subtract(t2.v2, t2.v1), subtract(t2.v3, t2.v2), subtract(t2.v1, t2.v3)};

            for (int i = 0; i < 3; ++i) {
                axes[i] = crossProduct(edges1[i], (Vector3) {0, 0, 1});
                axes[i + 3] = crossProduct(edges2[i], (Vector3) {0, 0, 1});
            }

            for (int i = 0; i < 6; ++i) {
                Vector3 axis = axes[i];

                double minA = project(axis, t1.v1);
                double maxA = minA;
                for (int j = 1; j < 3; ++j) {
                    double proj = project(axis, ((Vector3 *) &t1)[j]);
                    if (proj < minA) minA = proj;
                    if (proj > maxA) maxA = proj;
                }

                double minB = project(axis, t2.v1);
                double maxB = minB;
                for (int j = 1; j < 3; ++j) {
                    double proj = project(axis, ((Vector3 *) &t2)[j]);
                    if (proj < minB) minB = proj;
                    if (proj > maxB) maxB = proj;
                }

                if (!overlap(minA, maxA, minB, maxB)) {
                    return false; // Znaleziono oś separacji, trójkąty się nie nachodzą
                }
            }

            return true; // Nie znaleziono osi separacji, trójkąty się nachodzą
        }

        /**
         * @brief Gets the camera ready for the frame. Prepares projection and view matrixes.
         *
         * @param camera - main camera on the scene from which projection will be done.
         */
        virtual void setupCamera(Camera &camera) = 0;

        /**
         * @brief Setups the lightning on the scene. Saves the direction of the perpendicular rays (currently on this is supported).
         *
         * @param p_light - Light source which emits the light on the scene.
         */
        virtual void setupLightning(LightSource &p_light) = 0; // TODO handle multiple lights?

        /**
         * @brief Projects the Render object and saves projected faces to the #m_projection_data vector.
         *
         * @param p_object - object to project.
         */
        virtual void project(RenderObject &p_object) = 0;

        /**
         * @brief Retrieve the projection data, which is the data of the projections made in the current frame.
         *
         * @return std::vector<ProjectionData_t> The projection data.
         */
        inline virtual std::vector<ProjectionData_t> retrieveProjections() {
#ifndef CRUST_STOP_TRIANGLE_DIVISION_IN_PROJECTION_SORTING
            std::vector<ProjectionData_t> result;
            for (size_t i = 0; i < m_projection_data.size(); ++i) {
                for (size_t j = i + 1; j < m_projection_data.size(); ++j) {
                    if (trianglesOverlap(m_projection_data[i], m_projection_data[j])) {
                        auto split1 = splitTriangle(m_projection_data[i], m_projection_data[j]);
                        auto split2 = splitTriangle(m_projection_data[j], m_projection_data[i]);

                        for (const auto &t: split1) {
                            result.push_back({t});
                        }
                        for (const auto &t: split2) {
                            result.push_back({t});
                        }
                    } else {
                        result.push_back(m_projection_data[i]);
                        result.push_back(m_projection_data[j]);
                    }
                }
            }
#endif

            sort(result.begin(), result.end(),
                 [](const ProjectionData &a, const ProjectionData &b) {
                     /* https://en.wikipedia.org/wiki/Painter%27s_algorithm */
                     double za = (a.v1.z() + a.v2.z() + a.v3.z()) / 3;
                     double zb = (b.v1.z() + b.v2.z() + b.v3.z()) / 3;
                     return za > zb;
                 });

            return result;
        }

        /**
         * @brief Deletes projection performed during last frame. This is obligatory to run after frame end. Without it old projections stays in the memory and gets drawn each frame which results in overflowing the stack.
         */
        inline void clearProjections() {
            m_projection_data.clear();
        }

        /**
         * @brief Set according on what window size calculations will be made.
         *
         * @param p_width The width of the window.
         * @param p_height The height of the window.
         */
        inline void resize(uint16_t p_width, uint16_t p_height) {
            m_width = p_width;
            m_height = p_height;
            m_aspect_ratio = (float) p_height / (float) p_width;
        }

    protected:
        float m_aspect_ratio{0}; /** !< The aspect ratio of the projector. */
        uint16_t m_width{0}; /** !< The width of the projector. */
        uint16_t m_height{0}; /** !< The height of the projector. */

        std::vector<ProjectionData_t> m_projection_data; /** !< The data of the projection. Holds all projections made in current frame */

        Matrix4x4f m_projection_matrix; /** !< The projection matrix. */
        Matrix4x4f m_view_matrix; /** !< The view matrix. */
        Matrix4x4f m_translation_matrix; /** !< The translation matrix. */

        Vector3 m_light_direction; /** !< The direction of the light source. */
    };

}

#endif /* CRUSTENGINE_ABSTRACTPROJECTOR_H */
