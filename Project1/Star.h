#include "GameObject.h"
#include "timer.h"

class Star : public GameObject {

private:
    Timer timer;

public:
    Star(GameState *gs, const std::string &name, int x, int y)
        : GameObject(gs, name, x, y, 50, 50) {
        
        m_brush.texture = "assets/star.png";
    }

};

