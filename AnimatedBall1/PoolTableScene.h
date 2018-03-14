#pragma once

#include <QtGui/QPainter>
#include "Vector2f.h"
#include "RectF.h"
//  ласс PoolTableScene реализует сцену биль€рдного стола, с шариками и стенками.
class PoolTableScene
{
public:
	explicit PoolTableScene(const RectF& bounds);
	void update(float deltaSeconds);
	void redraw(QPainter& painter);

private:

	Vector2f m_ballPosition;
	//Vector2f m_ballSpeed;
	const Vector2f m_ballSize;
	const RectF m_bounds;

	float m_time = 0;

	float m_ballPositionX = 50;
	float m_ballPositionY = 50;
	bool m_positivX = true;
	bool m_positivY = true;
};
