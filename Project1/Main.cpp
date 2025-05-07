#include "graphics.h"
#include "GameState.h"
#include "configuration.h"
#include <time.h>


void draw()
{
    GameState* gs;
    
    gs = (GameState*)graphics::getUserData();

    gs->draw();
}

void update(float ms)
{
    GameState* gs;
    
    gs = (GameState*)graphics::getUserData();

    gs->update(ms);
}


int main()
{
    srand(time(0));

    // Dimiourgia antikeimenou paixnidiou
    GameState* gs = new GameState();


    // Arxikopoihsh tou paixnidiou
    graphics::createWindow(WindowsWidth, WindowsHeight, "Bubble Popper");
    graphics::setUserData(gs);

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    // Arxikopoihsh tou canva
    graphics::setCanvasSize(CanvasWidth, CanvasHeight);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    graphics::Brush br;
    br.fill_color[0] = 0.6f;
    br.fill_color[1] = 0.8f;
    br.fill_color[2] = 0.95f;
    graphics::setWindowBackground(br);

    graphics::setFont("assets\\bubbles.ttf");

    gs->init();
    graphics::startMessageLoop();

    return 0;
}
