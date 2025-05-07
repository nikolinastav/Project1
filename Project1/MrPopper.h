#include "GameObject.h"
#include "timer.h"

// Einai h kalsh gia ton paikti
class MrPopper : public GameObject {
private:
    bool trapped;
    float speed = 2.5f;

public:
    MrPopper(GameState *gs, const std::string &name = "", int x = 0, int y = 0, int w = 0, int h = 0)
        : GameObject(gs, name, x, y, w, h) {
        trapped=false;

        m_brush.texture = "assets\\mrpopper1.png";
    }

    void update(float ms) override {
        
        // An den einai mesa stin fouska tote kineitai monos tou
        if (!trapped) {
            if (graphics::getKeyState(graphics::SCANCODE_LEFT)) {
                m_pos_x -= speed * timer;
                m_brush.texture = "assets\\mrpopper2.png";
            }
            if (graphics::getKeyState(graphics::SCANCODE_RIGHT)) {
                m_pos_x += speed * timer;
                m_brush.texture = "assets\\mrpopper1.png";
            }
            if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {
                trapped = false;
            }
            
            // An einai ston aera peftei pros ta katw
            if (m_pos_y < CanvasHeight-m_height/2.0f) {
                m_pos_y += speed * timer;
            }
            // An ftasei sto katw meros tou parathirou tote kanei reset
            if (m_pos_y > CanvasHeight-m_height/2.0f) {
                m_pos_y = CanvasHeight - m_height / 2.0f;
            }
        }
        else {
            // An einai mesa stin fouska tote kineitai mazi me tin fouska
            m_pos_y -= speed * timer;

            // An ftasei sto panw meros tou parathirou tote eleutherwnetai
            if (m_pos_y < 0) {
				trapped = false;
			}
        }
    }

    // setter
    void setTrapped(bool t) {
        trapped = t;
    }

    // getter
    bool isTrapped() {
        return trapped;
    }
};
