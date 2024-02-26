#ifndef CRUSTENGINE_OBJECT_H
#define CRUSTENGINE_OBJECT_H

#include "Transform.h"
#include "scripting/Script.h"
#include "static/Definitions.h"

namespace Crust {
    /**
     * @brief The base class for all objects in the engine.
     */
    class Object {
    public:
        /**
         * @brief Construct a new Object object with default transform.
         */
        Object();

        /**
         * @brief Construct a new Object object with the specified transform.
         *
         * @param p_transform The transform of the object.
         */
        ~Object();

        /**
         * @brief Get the id of the object.
         *
         * @return The id of the object.
         */
        uint32_t getId() const;

        /**
         * @brief Get if the object is active.
         *
         * @return The active state of the object.
         */
        bool isActive() const;

        /**
         * @brief Set the active state of the object.
         *
         * @param p_active The active state of the object.
         */
        void setActive(bool p_active);

        /**
         * @brief Get the transform of the object.
         *
         * @return The transform of the object.
         */
        Transform& getTransform() const;

        /**
         * @brief Get the scripts attached to the object.
         *
         * @return The scripts attached to the object.
         */
        std::vector<Script*> getScripts() const;

        /**
         * @brief Attach the script to the object.
         *
         * @param p_script The script to attach.
         * @return Status The status of the operation.
         */
        Status attachScript(Script& script);

    private:
        uint32_t m_id { 0 }; /**< The id of the object. */
        bool m_active { true }; /**< Wheter object is active: is rendered, it's scripts are performed etc. If not active it behaves like it not exists. */

        Transform& m_transform; /**< The transform of the object. Represents coordinates, scale and rotation in 3D space */
        std::vector<Script*> m_scripts; /**< The scripts attached to the object. */

        static inline uint32_t NEXT_ID { 0 }; /**< The next id of the object. Static field. */
    };
}

#endif /* CRUSTENGINE_OBJECT_H */
