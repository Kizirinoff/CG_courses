#include "PoolTableScene.h"

namespace
{
	// —корость, пикселей в секунду
	constexpr float BALL_SPEED_X = 200;
	constexpr float BALL_SPEED_Y = 200;

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
	m_ballPositionX += BALL_SPEED_X * deltaSeconds;
	m_ballPositionY += BALL_SPEED_Y * deltaSeconds;

	
	if (m_ballPosition.x < m_bounds.leftEdge())
	{
		m_ballPosition.x = m_bounds.leftEdge();
		m_ballSpeed.x = -m_ballSpeed.x;
	}
	else if (m_ballPosition.x > m_bounds.rightEdge() - m_ballSize.x)
	{
		m_ballPosition.x = m_bounds.rightEdge() - m_ballSize.x;
		m_ballSpeed.x = -m_ballSpeed.x;
	}
	
	if (m_ballPosition.y < m_bounds.bottomEdge())
	{
		m_ballPosition.y = m_bounds.bottomEdge();
		m_ballSpeed.y = -m_ballSpeed.y;
	}
	else if (m_ballPosition.y > m_bounds.topEdge() - m_ballSize.y)
	{
		m_ballPosition.y = m_bounds.topEdge() + m_ballSize.y;
		m_ballSpeed.y = -m_ballSpeed.y;
	}
	

}

void PoolTableScene::redraw(QPainter& painter)
{
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setBrush(QBrush(QColor(0xFA, 0xFE, 0x78)));
	painter.drawEllipse(QRectF(m_ballPositionX, m_ballPositionY, BALL_SIZE, BALL_SIZE));
}
