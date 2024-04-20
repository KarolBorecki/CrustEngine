#ifndef CRUSTENGINE_ENTITY_H
#define CRUSTENGINE_ENTITY_H

#include <vector>

#include "static/Definitions.h"
#include "objects/transforms/Transform.h"
#include "scripting/Script.h"

namespace Crust {
    /**
     * @brief The base class for all objects in the engine.
     */
    class Entity {
    public:
        /**
         * @brief Construct a new Object object with default transform.
         */
        Entity() { m_id = NEXT_ID++; }

        /**
         * @brief Construct a new Object object with the specified transform.
         *
         * @param p_transform The transform of the object.
         */
        virtual ~Entity() = default;

        /**
         * @brief Get the id of the object.
         *
         * @return The id of the object.
         */
        inline uint32_t getId() const { return m_id; }

        /**
         * @brief Get if the object is active.
         *
         * @return The active state of the object.
         */
        virtual inline bool isActive() const { return m_active; }

        /**
         * @brief Set the active state of the object.
         *
         * @param p_active The active state of the object.
         */
        virtual inline void setActive(bool p_active) { m_active = p_active; }

        /**
         * @brief Get the scripts attached to the object.
         *
         * @return The scripts attached to the object.
         */
        inline std::vector<Script *> getScripts() const { return m_scripts; }

        /**
         * @brief Attach the script to the object.
         *
         * @param p_script The script to attach.
         * @return Status The status of the operation.
         */
        inline Status attachScript(Script &p_script) {
            m_scripts.push_back(&p_script);
            p_script.attachTo(this);
            return OK;
        }

        virtual Transform &transform() = 0;

    protected:
        uint32_t m_id{0}; /**< The id of the object. */
        bool m_active{
                true}; /**< Whether object is active: is rendered, it's scripts are performed etc. If not active it behaves like it not exists. */

    private:
        std::vector<Script *> m_scripts; /**< The scripts attached to the object. */

        static inline uint32_t NEXT_ID{0}; /**< The next id of the object. Static field. */
    };
}

#endif /* CRUSTENGINE_ENTITY_H */
