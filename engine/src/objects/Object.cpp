#include "objects/Object.h"

#include "objects/Transform.h"

namespace Crust {
    Object::Object() {
        m_id = NEXT_ID++;
    }

    uint32_t Object::getId() const {
        return m_id;
    }

    bool Object::isActive() const {
        return m_active;
    }

    void Object::setActive(bool p_active) {
        m_active = p_active;
    }

    Transform& Object::getTransform() {
        return m_transform;
    }

    std::vector<Script*> Object::getScripts() const {
        return m_scripts;
    }

    Status Object::attachScript(Script& p_script) {
        m_scripts.push_back(&p_script);
        p_script.attachTo(this);
        return OK;
    }
}
