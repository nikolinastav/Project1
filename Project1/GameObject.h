#pragma once
#include <graphics.h>
#include "GameState.h"
#include "configuration.h"
#include <string>
#include <iostream>
#include "box.h"
#include "timer.h"

using namespace std;

class GameObject : public Box
{
	static int m_next_id;

protected:
	class GameState *m_state;
	std::string m_name;
	int m_id = 0;
	bool m_active = true;
	graphics::Brush m_brush;
	Timer timer;

public:
	GameObject(GameState *gs, const std::string &name = "", int x = 0, int y = 0, int w = 0, int h = 0)
	:Box(x, y, w, h), m_state(gs), m_name(name)
	{
		//m_id = m_next_id++;
		m_brush.outline_opacity = 0.0f;
		m_brush.fill_opacity = 1.0f;
	}

	virtual void update(float dt) {}
	virtual void init() { timer.start(); }
	virtual ~GameObject() {}

	bool isActive() { return m_active; }
	void setActive(bool a) { m_active = a; }

	virtual void draw() {

		// To zwgrafizei mono an einai active
		if (m_active) {
			
			graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_brush);
		}
	}

	string getName() { return m_name; }
};