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
        if (InputHandler::getLastEvent().type == Event::EVENT_WINDOW_QUIT) {
            m_is_running = SDL_FALSE;
        }

        return m_is_running == SDL_FALSE;
    }

    void Library2DWrapper::onDrawStart(uint8_t p_background_r, uint8_t p_background_g, uint8_t p_background_b) {
        SDL_SetRenderDrawColor(m_renderer, p_background_r, p_background_g, p_background_b, 255); // background color
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

    Crust::Status Library2DWrapper::setWindowCaption(const char *p_caption) {
        SDL_SetWindowTitle(m_window, p_caption);
        return OK;
    }

    void Library2DWrapper::drawTriangle(float p_x1, float p_y1, float p_x2, float p_y2, float p_x3, float p_y3,
                                        uint8_t r_v1, uint8_t g_v1, uint8_t b_v1, uint8_t a_v1,
                                        uint8_t r_v2, uint8_t g_v2, uint8_t b_v2, uint8_t a_v2,
                                        uint8_t r_v3, uint8_t g_v3, uint8_t b_v3, uint8_t a_v3) {
        p_x1 = m_width - p_x1;
        p_y1 = m_height - p_y1;
        p_x2 = m_width - p_x2;
        p_y2 = m_height - p_y2;
        p_x3 = m_width - p_x3;
        p_y3 = m_height - p_y3;

        SDL_Vertex verts[3] =
                {
                        {
                                SDL_FPoint{p_x1, p_y1},
                                SDL_Color{r_v1, g_v1, b_v1, a_v1},
                                SDL_FPoint{0},
                        },
                        {
                                SDL_FPoint{p_x2, p_y2},
                                SDL_Color{r_v2, g_v2, b_v2, a_v2},
                                SDL_FPoint{0},
                        },
                        {
                                SDL_FPoint{p_x3, p_y3},
                                SDL_Color{r_v3, g_v3, b_v3, a_v3},
                                SDL_FPoint{0},
                        },
                };
        SDL_RenderGeometry(m_renderer, nullptr, verts, 3, nullptr, 0);
    }

    void Library2DWrapper::drawHollowTriangle(float p_x1, float p_y1, float p_x2, float p_y2, float p_x3, float p_y3,
                                              uint8_t r_v1, uint8_t g_v1, uint8_t b_v1, uint8_t a_v1,
                                              uint8_t r_v2, uint8_t g_v2, uint8_t b_v2, uint8_t a_v2,
                                              uint8_t r_v3, uint8_t g_v3, uint8_t b_v3, uint8_t a_v3) {
        drawLine(p_x1, p_y1, p_x2, p_y2, r_v1, g_v1, b_v1, a_v1);
        drawLine(p_x2, p_y2, p_x3, p_y3, r_v2, g_v2, b_v2, a_v2);
        drawLine(p_x3, p_y3, p_x1, p_y1, r_v3, g_v3, b_v3, a_v3);
    }

    void Library2DWrapper::drawLine(uint16_t p_x1, uint16_t p_y1, uint16_t p_x2, uint16_t p_y2, uint8_t r, uint8_t g,
                                    uint8_t b, uint8_t a) {
        p_x1 = m_width - p_x1;
        p_y1 = m_height - p_y1;
        p_x2 = m_width - p_x2;
        p_y2 = m_height - p_y2;

        if (p_x1 < 0 || p_x1 > m_width || p_x2 < 0 || p_x2 > m_width || p_y1 < 0 || p_y1 > m_height || p_y2 < 0 ||
            p_y2 > m_height)
            return;

        SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
        SDL_RenderDrawLine(m_renderer, p_x1, p_y1, p_x2, p_y2);
    }
}