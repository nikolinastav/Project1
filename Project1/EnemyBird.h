#include "GameObject.h"
#include "timer.h"

class EnemyBird : public GameObject {

    int initialX;
    int initialY;
    int direction;

public:
    EnemyBird(GameState *gs, const std::string &name = "", int x = 0, int y = 0, int w = 0, int h = 0)
        : GameObject(gs, name, x, y, w, h) {

        m_brush.texture = "assets\\enemy1.png";

        initialX = x;
        initialY = y;
        direction = 1;

    }

    void update(float ms) override {
        
        // Kinetai deksia gia 200 pixels kai meta aristera gia 200 pixels
        if (m_pos_x - initialX > 200) {
			direction = -1;
		}
        else if (m_pos_x - initialX < -200) {
            direction = 1;
        }

		m_pos_x += direction * 0.1 * ms;

    }
};
