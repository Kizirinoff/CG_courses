#include "RasterWindow.h"

bool RasterWindow::isAnimating() const
{
	return m_isAnimating;
}

void RasterWindow::setAnimating(bool isAnimating)
{
	m_isAnimating = isAnimating;
	if (isAnimating)
	{
		renderLater();
	}
}

// � ������������ �������� � ������������ ������ ����� ������ QBackingStore.
// � ����������� C++ �� ������� ������������ "new", �� ���� �� ��������� � Qt,
//  "new" - ��� �����, �.�. Qt ���������� ������ �������� ���������� �������
//  parent-child.
// ������ ������� �� �������� "this" � ����������� QBackingStore.
// ������ ������ RasterWindow ���������� ��������� ������� ������ QBackingStore.
// ����� ����� ������ ���������� RasterWindow, Qt ������ � ��� �������� �������.

constexpr unsigned WINDOW_WIDTH = 600;
constexpr unsigned WINDOW_HEIGHT = 600;
// ����� �� ������� ��� ������������ ������: ����������� � ����� renderNow.
// � ������������ �� ����� ��������� ����� ������ �����, �������� ��� ���������� 
// parent-child � ������� ���� ���� �������� ��������� this:
RasterWindow::RasterWindow(QWindow *parent)
	: QWindow(parent)
	, m_backingStore(new QBackingStore(this))
	, m_scene(std::make_unique<PoolTableScene>(RectF{ 0, 0, float(WINDOW_WIDTH), float(WINDOW_HEIGHT) }))
{
	setMinimumSize(QSize(WINDOW_WIDTH, WINDOW_HEIGHT));
	m_updateTimer.start();
}
	// ������ ����� event: ���� ����� ���������� ��� 
	// ������ ������� ����, ������� ��� ��� ��������� ������� 
	// ����������� ���������
bool RasterWindow::event(QEvent *event)
{
	if (event->type() == QEvent::UpdateRequest) {
		renderNow();
		return true;
	}
	return QWindow::event(event);
}
	// ������ ����� exposeEvent: ���� ����� ������ QWindow 
	// ���������� Qt �������� ��� ����������� ������ ����.
void RasterWindow::exposeEvent(QExposeEvent *)
{
	if (isExposed())
	{
		renderNow();
	}
}
	// ������ ����� resizeEvent : ���� ����� ������ QWindow
	// ���������� Qt �������� ��� ��������� ������� ����.
void RasterWindow::resizeEvent(QResizeEvent *resizeEvent)
{
	// �������� ������ ������ �����, ����� �� �������� � �������� ����
	m_backingStore->resize(resizeEvent->size());
	if (isExposed())
	{
		renderNow();
	}
}
	// ����� �renderLater� ����� ��������� � �������
	// ������� Qt ������� ���������� ������ (UpdateRequest),
	// ��� ����� �������� ����������� ����� � ��������� �������.
void RasterWindow::renderLater()
{
	requestUpdate();
}
void RasterWindow::updateScene()
{
	const float elapsedSeconds = float(m_updateTimer.elapsed()) / 1000.f;

	// ������� ���������� � ������, ���� ������ �� ����� ������ ��������� �����.
	if (elapsedSeconds > 0)
	{
		m_updateTimer.restart();
		m_scene->update(elapsedSeconds);
	}
}

void RasterWindow::renderScene()
{
	QRect rect(0, 0, width(), height());
	m_backingStore->beginPaint(rect);

	QPaintDevice *device = m_backingStore->paintDevice();
	QPainter painter(device);

	painter.fillRect(0, 0, width(), height(), Qt::white);
	m_scene->redraw(painter);
	painter.end();

	m_backingStore->endPaint();
	m_backingStore->flush(rect);
}


	// ������ ��������� ����� ������� ����� ������ � renderNow. 
	// ����� ����� ��������� ��������� �� ������ �����, �������
	// �����, � ����� ������� ����� �������� �� �����.
void RasterWindow::renderNow()
	{
		if (!isExposed())
		{
			return;
		}

		updateScene();
		renderScene();

		if (m_isAnimating)
		{
			renderLater();
		}
	}

/*
	QRect rect(0, 0, width(), height());
	m_backingStore->beginPaint(rect);

	QPaintDevice *device = m_backingStore->paintDevice();
	QPainter painter(device);

	painter.fillRect(0, 0, width(), height(), Qt::white);
	render(&painter);
	painter.end();

	m_backingStore->endPaint();
	m_backingStore->flush(rect);
	// ��������� � ������ �RasterWindow::renderNow()� �
	// �������� � ����� ������ ������������ �����������:
	if (m_isAnimating)
	{
		renderLater();
	}

	// ������� ����� ���� ����� �render�, � ������� �� 
	// ��������� ��������� ����� ��������� � �������� ������.
*/
void RasterWindow::render(QPainter *painter)
{
	// ������������� ����� ���������� ������������� ����� (anti-aliasing mode)
	painter->setRenderHint(QPainter::Antialiasing);

	// ������������� ����� ������ ����� (���� ����� � RGB)
	painter->setBrush(QBrush(QColor(0xFA, 0xFE, 0x78)));

	// ������ ������ �� �� ���� � �������� 5 ��������
	painter->drawEllipse(QRect(5, 5, width() - 10, height() - 10));
}








