#include "rendering/Library2DWrapper.h"
#include "static/Definitions.h"

namespace Crust {
    Crust::Status Crust::Library2DWrapper::init() {
        return OK;
    }

    Crust::Status Library2DWrapper::createWindow(uint16_t p_width, uint16_t p_height) {
        return ERROR;
    }

    Crust::Status Library2DWrapper::setWindowCaption(std::string p_caption) {
        return ERROR;
    }

    void Library2DWrapper::onDrawStart() {

    }

    void Library2DWrapper::onDrawEnd() {

    }

    bool Library2DWrapper::shouldClose() {
        return false;
    }

    void Library2DWrapper::quit() {

    }

    void Library2DWrapper::drawTriangle(float p_x1, float p_y1, float p_x2, float p_y2, float p_x3,float p_y3, uint8_t p_shade) {

    }
}