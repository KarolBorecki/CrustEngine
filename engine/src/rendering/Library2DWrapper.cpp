#include "rendering/Library2DWrapper.h"

namespace Crust {
    Crust::Status Crust::Library2DWrapper::init() {
        return SDL_Init(SDL_INIT_VIDEO) == 0 ? OK : ERROR;
    }

    Crust::Status Library2DWrapper::createWindow(uint16_t p_width, uint16_t p_height) {
        m_width = p_width;
        m_height = p_height;
        m_is_running = SDL_TRUE;
        return SDL_CreateWindowAndRenderer(m_width, m_height, 0, &m_window, &m_renderer) == 0 ? OK : ERROR;
    }

    bool Library2DWrapper::shouldClose() {
        SDL_Event e;
        if (SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                m_is_running = SDL_FALSE;
            }
        }
        return m_is_running == SDL_FALSE;
    }

    void Library2DWrapper::onDrawStart() {
        SDL_RenderClear(m_renderer);
    }

    void Library2DWrapper::onDrawEnd() {
        SDL_RenderPresent(m_renderer);
    }

    void Library2DWrapper::close() {
        if (m_renderer)
            SDL_DestroyRenderer(m_renderer);
        if (m_window)
            SDL_DestroyWindow(m_window);

        SDL_Quit();
    }

    void Library2DWrapper::resize(uint16_t p_width, uint16_t p_height) {
        m_width = p_width;
        m_height = p_height;
    }

    Crust::Status Library2DWrapper::setWindowCaption(const char* p_caption) {
        SDL_SetWindowTitle(m_window, p_caption);
        return OK;
    }

    void Library2DWrapper::drawTriangle(float p_x1, float p_y1, float p_x2, float p_y2, float p_x3,float p_y3, uint8_t p_shade) {
        p_x1 = m_width - p_x1; p_y1 = m_height - p_y1;
        p_x2 = m_width - p_x2; p_y2 = m_height - p_y2;
        p_x3 = m_width - p_x3; p_y3 = m_height - p_y3;
        const std::vector<SDL_Vertex> verts =
                {
                        {
                                SDL_FPoint{p_x1, p_y1},
                                SDL_Color{p_shade, p_shade, p_shade, 255},
                                SDL_FPoint{0},
                        },
                        {
                                SDL_FPoint{p_x2, p_y2},
                                SDL_Color{p_shade, p_shade, p_shade, 255},
                                SDL_FPoint{0},
                        },
                        {
                                SDL_FPoint{p_x3, p_y3},
                                SDL_Color{p_shade, p_shade, p_shade, 255},
                                SDL_FPoint{0},
                        },
                };
        SDL_RenderGeometry(m_renderer, nullptr, verts.data(), verts.size(), nullptr, 0);
    }
}