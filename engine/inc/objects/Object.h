#ifndef CRUSTENGINE_OBJECT_H
#define CRUSTENGINE_OBJECT_H

#include "Entity.h"
#include "objects/transforms/ObjectTransform.h"

namespace Crust {
    class Script;

    /**
     * @brief The base class for all objects in the engine.
     */
    class Object : public Entity {
    public:

        /**
         * @brief Get the transform of the object.
         *
         * @return The transform of the object.
         */
        virtual inline Transform &transform() override { return m_transform; }

    protected:
        ObjectTransform m_transform; /**< The transform of the object. Represents coordinates, scale and rotation in 3D space */
    };
}

#endif /* CRUSTENGINE_OBJECT_H */
