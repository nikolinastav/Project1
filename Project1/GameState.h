#pragma once

#include <vector>
#include "GameObject.h"
#include "configuration.h"
#include "MrPopper.h"
#include "Bubble.h"
#include "Star.h"
#include "EnemyBird.h"

using namespace std;

class GameState
{
private:

	MrPopper *player;
	Bubble *trappedBubble;					// H fouska pou exei piasei ton paikti
	int score;
	graphics::Brush br;
	bool isRunning, isMenuOn;								// An to paixnidi trexei
	vector<class GameObject*> gameElements;		// Ola ta antikeimena tou paixnidiou

public:

	GameState(){


		// Vazei 5 fouskes
		for(int i = 0; i < 5; i++) {
			gameElements.push_back(new Bubble(this, "Bubble"));
		}

		// Vazei ton paikti
		player = new MrPopper(this, "MrPopper", CanvasWidth / 2, CanvasHeight - 100, 50, 50);
		gameElements.push_back(player);

		// Vazei 3 asteria
		gameElements.push_back(new Star(this, "Star", CanvasWidth / 2 + 300, 200));
		gameElements.push_back(new Star(this, "Star", CanvasWidth / 2, 200));
		gameElements.push_back(new Star(this, "Star", CanvasWidth / 2 - 300, 200));

		// Vazei 3 poulia gyrw apo ta asteria
		gameElements.push_back(new EnemyBird(this, "EnemyBird", CanvasWidth / 2 + 300, 200, 30, 30));
		gameElements.push_back(new EnemyBird(this, "EnemyBird", CanvasWidth / 2, 200, 30, 30));
		gameElements.push_back(new EnemyBird(this, "EnemyBird", CanvasWidth / 2 - 300, 200, 30, 30));



		// Dinei to xrwma gia ta grammata
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.0f;
		br.fill_color[2] = 0.0f;
		br.fill_opacity = 1.0f;
	}

	// Arxikopoihsh olwn twn antikeimenwn tou paixnidiou
	void init() {

		isRunning = true;
		isMenuOn = false;
		score = 0;

		for(int i = 0; i < gameElements.size(); i++)
			gameElements[i]->init();
	}

	// Apeikonisi olwn twn antikeimenwn tou paixnidiou
	void draw() {

		// Draw background
		graphics::Brush br2;
		br2.texture = "assets\\background.png";
		graphics::drawRect(CanvasWidth / 2, CanvasHeight / 2, CanvasWidth, CanvasHeight, br2);


		for(int i = 0; i < gameElements.size(); i++)
			gameElements[i]->draw();
	

		// An den trexei to paixnidi, tote emfanizetai to mhnyma "Game Over"
		if(!isRunning) {
			
			graphics::drawText(400, 300, 50, "Game Over", br);
			return;
		}

		// An to menu einai on, tote emfanizetai to menu
		if(isMenuOn) {
			graphics::drawText(300, 100, 25, "Menu", br);
			graphics::drawText(300, 150, 25, "Press B to go back", br);
			graphics::drawText(300, 200, 25, "Use arrows to move left or right", br);
			graphics::drawText(300, 250, 25, "Press space to pop the bubble", br);
		}

		// Emfanizei to score kai to menu
		graphics::drawText(50, 30, 30, "Score: " + to_string(score), br);
		graphics::drawText(CanvasWidth-200, 30, 20, "Press H for help ", br);
	}

	// Enimerwsi olwn twn antikeimenwn tou paixnidiou
	void update(float ms){

		// An den trexei to paixnidi, den ginetai update
		if(!isRunning)
			return;

		for(int i = 0; i < gameElements.size(); i++)
			gameElements[i]->update(ms);
	
		// An patise to koumpi "H" h to "B" tote emfanizetai/exafanizetai to menu
		if(graphics::getKeyState(graphics::SCANCODE_H)) {

			isMenuOn = true;
		}
		else if(graphics::getKeyState(graphics::SCANCODE_B)) {

			isMenuOn = false;
		}

		// Elegxei an o paikths exei piastei se fouska
		// Simeiwnei tin fouska kai allazei to trapped
		for(int i = 0; i < gameElements.size(); i++) {
			if(gameElements[i]->getName() == "Bubble") {
				if(player->intersect(*(gameElements[i]))) {

					trappedBubble = (Bubble*)gameElements[i];

					// Vazei ton paikti panw sthn fouska
					player->m_pos_x = trappedBubble->m_pos_x;
					player->m_pos_y = trappedBubble->m_pos_y;

					player->setTrapped(true);
					
					break;
				}
			}
		}

		// An o paikths akoumpisei se asteri tote auksanei to score
		// Skaei h fouska kai allazei to trapped
		for(int i = 0; i < gameElements.size(); i++) {
			if(gameElements[i]->getName() == "Star" && gameElements[i]->isActive()) {
				if(player->intersect(*(gameElements[i]))) {
					score++;
					gameElements[i]->setActive(false);
					trappedBubble->setPopped(true);
					player->setTrapped(false);
					graphics::playSound("assets\\collide.wav", 0.5f, false);

					break;
				}
			}
		}

		// An o paikths akoumpisei se poulaki tote xana ginontai active ola ta asteria
		// Kai midenizei to score
		for(int i = 0; i < gameElements.size(); i++) {
			if(gameElements[i]->getName() == "EnemyBird" && gameElements[i]->isActive()) {
				if(player->intersect(*(gameElements[i]))) {
					
					for(int j = 0; j < gameElements.size(); j++) {
						if(gameElements[j]->getName() == "Star") {
							gameElements[j]->setActive(true);
						}
					}
					score = 0;

					break;
				}
			}
		}

		// An o paikths exei piastei se fouska kai patisei to space
		if(graphics::getKeyState(graphics::SCANCODE_SPACE) && player->isTrapped()) {
			
			trappedBubble->setPopped(true);
			trappedBubble->setActive(false);
			player->setTrapped(false);
		}

		// An piasei ola ta asteria tote to paixnidi stamataei
		if(score == 3) {
			isRunning = false;
		}
	}

	// Diagrafi olwn twn antikeimenwn tou paixnidiou
	~GameState() {
		for(int i = 0; i < gameElements.size(); i++)
			delete gameElements[i];
	}
};

