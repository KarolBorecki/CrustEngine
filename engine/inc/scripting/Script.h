#ifndef CRUSTENGINE_SCRIPT_H
#define CRUSTENGINE_SCRIPT_H

#include "objects/Object.h"

#include "logging/Logger.h"

namespace Crust {
    class Object;
}

namespace Crust {
    class Script {
    public:
        virtual void reload() {};

        virtual void start() {};

        virtual void update(float p_delta_time) {};

        void attachTo(Object* p_object) { m_object = p_object; }

    protected:
        Object* m_object { nullptr };
    };
}

#endif /* CRUSTENGINE_SCRIPT_H */
