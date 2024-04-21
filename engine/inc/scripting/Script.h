#ifndef CRUSTENGINE_SCRIPT_H
#define CRUSTENGINE_SCRIPT_H

// Including Entity results in circle dependency
#include "logging/Logger.h"

namespace Crust {
    class Entity;
}

namespace Crust {
    class Script {
    public:
        virtual void reload() {};

        virtual void start() {};

        virtual void update(double p_delta_time) {};

        void attachTo(Entity *p_object) { m_object = p_object; }

    protected:
        Entity *m_object{nullptr};
    };
}

#endif /* CRUSTENGINE_SCRIPT_H */
