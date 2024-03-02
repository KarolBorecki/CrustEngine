#include "rendering/Library2DWrapper.h"

namespace Crust {
    Crust::Status Crust::Library2DWrapper::init() {
        return OK;
    }

    Crust::Status Library2DWrapper::createWindow(uint16_t p_width, uint16_t p_height) {
        m_width = p_width;
        m_height = p_height;
    }

    bool Library2DWrapper::shouldClose() {
        return WindowShouldClose();
    }

    void Library2DWrapper::onDrawStart() {
        BeginDrawing();
    }

    void Library2DWrapper::onDrawEnd() {
        EndDrawing();
    }

    void Library2DWrapper::quit() {
        ;;
    }

    void Library2DWrapper::resize(uint16_t p_width, uint16_t p_height) {
        m_width = p_width;
        m_height = p_height;
    }

    Crust::Status Library2DWrapper::setWindowCaption(const char* p_caption) {
        SetWindowTitle(p_caption);
        return OK;
    }

    void Library2DWrapper::drawTriangle(float p_x1, float p_y1, float p_x2, float p_y2, float p_x3,float p_y3, uint8_t p_shade) {
        DrawTriangle(
        {p_x1, p_y1},
        {p_x2, p_y2},
        {p_x3, p_y3},
        BLUE
        );
    }
}