#include "PoolTableScene.h"
#include <QtGui>

namespace
{
	// —корость, пикселей в секунду
	constexpr float BALL_SPEED_X = 400;
	constexpr float BALL_SPEED_Y = 250;

	constexpr float BALL_SIZE = 40;
}

PoolTableScene::PoolTableScene(const RectF &bounds)
	: m_bounds(bounds)
	, m_ballSpeed(BALL_SPEED_X, BALL_SPEED_Y)
	, m_ballSize(BALL_SIZE, BALL_SIZE)
{
}


void PoolTableScene::update(float deltaSeconds)
{
	//m_ballPositionX += BALL_SPEED_X * deltaSeconds;
	//m_ballPositionY += BALL_SPEED_Y * deltaSeconds;
	// ћетод УPoolTableScene::updateФ станет сложнее:
	// после пересчЄта координат, хранимых в m_ballPosition, 
	// мы должны проверить два случа€

	if (m_positivX)
	{
		m_ballPosition.x += BALL_SPEED_X * deltaSeconds;
	}
	else
	{
		m_ballPosition.x -= BALL_SPEED_X * deltaSeconds;
	}
	if (m_positivY)
	{
		m_ballPosition.y += BALL_SPEED_Y * deltaSeconds;
	}
	else
	{
		m_ballPosition.y -= BALL_SPEED_Y * deltaSeconds;
	}

	
	
	if (m_ballPosition.x < m_bounds.leftEdge())
	{
		m_positivX = true;
	}
	
	if (m_ballPosition.x > m_bounds.rightEdge() - m_ballSize.x)
	{
		m_positivX = false;
	}
	
	if (m_ballPosition.y > m_bounds.bottomEdge() - m_ballSize.y)
	{
		m_positivY = false;
	}
	if (m_ballPosition.y < m_bounds.topEdge())
	{
		m_positivY = true;
			
	}
	


}

void PoolTableScene::redraw(QPainter& painter)
{
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setBrush(QBrush(QColor(0xFA, 0xFE, 0x78)));
	painter.drawEllipse(QRectF(m_ballPosition.x, m_ballPosition.y, BALL_SIZE, BALL_SIZE));
}
