#include "core/Scene.h"

namespace Crust {
    Scene::Scene() : m_name(Crust::DEFAULT_SCENE_NAME) {}

    Scene::Scene(const char *p_name) : m_name(p_name) {}

    Scene::Scene(Camera &p_main_camera) : m_name(Crust::DEFAULT_SCENE_NAME), m_camera(&p_main_camera) {}

    Scene::Scene(const char *p_name, Camera &p_main_camera) : m_name(p_name), m_camera(&p_main_camera) {}

    void Scene::onLoad() {
        m_loaded = true;
        if (!m_started) {
            start();
        } else {
            reload();
        }
    }

    void Scene::onUnLoad() {
        m_loaded = false;
    }

    void Scene::start() {
        if (m_started) {
            return;
        }
        m_started = true;
        for (auto object: m_objects) {
                for (auto script: object->getScripts()) {
                        script->start();
                }

        }
        for (auto script : m_camera->getScripts()) {
            script->start();
        }
    }

    void Scene::update(double p_delta_time) {
        for (auto object: m_objects) {
            for (auto script: object->getScripts()) {
                script->update(p_delta_time);
            }
        }
        for (auto script : m_camera->getScripts()) {
            script->update(p_delta_time);
        }
    }

    void Scene::reload() {
        for (auto object: m_objects) {
            for (auto script: object->getScripts()) {
                script->reload();
            }
        }
        for (auto script: m_camera->getScripts()) {
            script->reload();
        }
    }

    const char *Scene::getName() const {
        return m_name;
    }

    Camera &Scene::getMainCamera() const {
        return *m_camera;
    }

    void Scene::setMainCamera(Camera &p_camera) {
        m_camera = &p_camera;
    }

    bool Scene::isLoaded() const {
        return m_loaded;
    }

    bool Scene::isStarted() const {
        return m_started;
    }

    std::vector<Object *> Scene::getObjects() const {
        return m_objects;
    }

    std::vector<LightSource *> Scene::getLights() const {
        return m_lights;
    }

    std::vector<RenderObject *> Scene::getRenderObjects() const {
        return m_render_objects;
    }

    Status Scene::addObject(Object &p_object) {
        m_objects.push_back(&p_object);

        auto *renderObj = dynamic_cast<RenderObject *>(&p_object);
        if (renderObj != nullptr) {
            m_render_objects.push_back(renderObj);
        }

        auto *lightSource = dynamic_cast<LightSource *>(&p_object);
        if (lightSource != nullptr) {
            m_lights.push_back(lightSource);
        }

        return OK;
    }
}