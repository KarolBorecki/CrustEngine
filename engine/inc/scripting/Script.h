#ifndef CRUSTENGINE_SCRIPT_H
#define CRUSTENGINE_SCRIPT_H

#include "objects/Object.h"

namespace Crust {
    class Object;
}

namespace Crust {
    class Script {
    public:
        virtual void reload() {};

        virtual void start() {};

        virtual void update() {};

        void attachTo(Object* p_object) { m_object = p_object; }
    private:
        Object* m_object;
    };
}

#endif /* CRUSTENGINE_SCRIPT_H */
