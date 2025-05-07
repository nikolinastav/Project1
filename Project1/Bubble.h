#include "GameObject.h"
#include "timer.h"

class Bubble : public GameObject {

private:
    bool popped;
    float speed = 2.5;
    float timeSincePopped;          // Xronos pou perase apo tin stigmi pou eskase

public:
    Bubble(GameState *gs, const std::string &name = "")
    : GameObject(gs, name, 0, CanvasHeight-50, 50, 50) {

        m_brush.fill_opacity = 0.5f;
        popped = false;

        // Dialegei tyxaio xrwma gia tin fouska
        m_brush.fill_color[0] = (float)rand() / (float)RAND_MAX;
        m_brush.fill_color[1] = (float)rand() / (float)RAND_MAX;
        m_brush.fill_color[2] = (float)rand() / (float)RAND_MAX;

        // Dialegei tyxaia thesi gia to x mono
        m_pos_x = (float)(rand() % (CanvasWidth-100) + 100);
    }

 
    void update(float ms) override {
        
        // Paei pros ta panw
        m_pos_y -= speed * timer;

        // KOitazei an exei ftasei sto panw meros tou parathirou
        if (m_pos_y < 0) {
            m_pos_y = CanvasHeight + rand() % 200;
            m_pos_x = (float)(rand() % (CanvasWidth-100) + 100);
            m_active = true;
            popped = true;
            graphics::playSound("assets\\pop.wav", 0.5f, false);
        }

        // An exei skasei to paei xana apo katw meta apo 2 deuterolepta
        if (popped) {
            timeSincePopped += timer;
            if (timeSincePopped > 2000) {
                m_pos_y = CanvasHeight;
                m_pos_x = (float)(rand() % (CanvasWidth-100) + 100);
                popped = false;
                timeSincePopped = 0;
                m_active = true;
            }
        }
    }

    void draw() {

		// To zwgrafizei mono an einai active
		if (m_active) {
			
			graphics::drawDisk(m_pos_x, m_pos_y, m_width / 2.0f, m_brush);
		}
	}

    void setPopped(bool p) {
        popped = p;

        if (popped) {
            m_pos_x = -100;     // To bgazei ektos gia na min kanei epafi me ton player
            graphics::playSound("assets\\pop.wav", 0.5f, false);
		}
    }
};
