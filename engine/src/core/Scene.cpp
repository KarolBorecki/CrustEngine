#include "core/Scene.h"

namespace Crust {
    Scene::Scene(std::string p_name, Camera& p_main_camera) : m_name(p_name), m_camera(&p_main_camera) {}

    void Scene::onLoad() {
        m_loaded = true;
    }

    void Scene::onUnLoad() {
        m_loaded = false;
    }

    void Scene::start() {
        m_started = true;
    }

    void Scene::update() {
    }

    void Scene::reload() {
    }

    std::string Scene::getName() const {
        return m_name;
    }

    Camera& Scene::getMainCamera() const {
        return *m_camera;
    }

    void Scene::setMainCamera(Camera& p_camera) {
        m_camera = &p_camera;
    }

    std::vector<Object*> Scene::getObjects() const {
        return m_objects;
    }

    std::vector<LightSource*> Scene::getLights() const {
        return m_lights;
    }

    std::vector<RenderObject*> Scene::getRenderObjects() const {
        return m_render_objects;
    }

    Status Scene::addObject(Object& p_object) {
        return ERROR;
    }
}