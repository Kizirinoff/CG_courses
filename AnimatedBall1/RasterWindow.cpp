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

// В конструкторе создадим в динамической памяти новый объект QBackingStore.
// В современном C++ не принято использовать "new", но пока вы работаете с Qt,
//  "new" - это норма, т.к. Qt использует особый механизм управления памятью
//  parent-child.
// Именно поэтому мы передали "this" в конструктор QBackingStore.
// Объект класса RasterWindow становится родителем объекта класса QBackingStore.
// Когда будет вызван деструктор RasterWindow, Qt удалит и все дочерние объекты.

constexpr unsigned WINDOW_WIDTH = 600;
constexpr unsigned WINDOW_HEIGHT = 600;
// Также мы изменим два существующих метода: конструктор и метод renderNow.
// В конструкторе мы будем создавать новый объект сцены, связывая его отношением 
// parent-child с классом окна путём передачи указателя this:
RasterWindow::RasterWindow(QWindow *parent)
	: QWindow(parent)
	, m_backingStore(new QBackingStore(this))
	, m_scene(std::make_unique<PoolTableScene>(RectF{ 0, 0, float(WINDOW_WIDTH), float(WINDOW_HEIGHT) }))
{
	setMinimumSize(QSize(WINDOW_WIDTH, WINDOW_HEIGHT));
	m_updateTimer.start();
}
	// Опишем метод event: этот метод вызывается при 
	// каждом событии окна, поэтому при его написании следует 
	// действовать аккуратно
bool RasterWindow::event(QEvent *event)
{
	if (event->type() == QEvent::UpdateRequest) {
		renderNow();
		return true;
	}
	return QWindow::event(event);
}
	// Опишем метод exposeEvent: этот метод класса QWindow 
	// библиотека Qt вызывает при фактическом показе окна.
void RasterWindow::exposeEvent(QExposeEvent *)
{
	if (isExposed())
	{
		renderNow();
	}
}
	// Опишем метод resizeEvent : этот метод класса QWindow
	// библиотека Qt вызывает при изменении размера окна.
void RasterWindow::resizeEvent(QResizeEvent *resizeEvent)
{
	// Изменяем размер буфера кадра, чтобы он совпадал с размером окна
	m_backingStore->resize(resizeEvent->size());
	if (isExposed())
	{
		renderNow();
	}
}
	// Метод “renderLater” будет добавлять в очередь
	// событий Qt событие обновления экрана (UpdateRequest),
	// тем самым форсируя перерисовку кадра в ближайшем будущем.
void RasterWindow::renderLater()
{
	requestUpdate();
}
void RasterWindow::updateScene()
{
	const float elapsedSeconds = float(m_updateTimer.elapsed()) / 1000.f;

	// Пропуск обновления в случае, если таймер не успел засечь прошедшее время.
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


	// Теперь реализуем самый сложный метод класса — renderNow. 
	// Метод будет запускать рисование на буфере кадра, очищать
	// буфер, а потом готовый буфер выводить на экран.
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
	// Перейдите к методу “RasterWindow::renderNow()” и
	// добавьте в конец метода планирование перерисовки:
	if (m_isAnimating)
	{
		renderLater();
	}

	// Остался всего один метод “render”, в котором мы 
	// установим параметры кисти рисования и нарисуем эллипс.
*/
void RasterWindow::render(QPainter *painter)
{
	// Устанавливаем режим устранения ступенчатости фигур (anti-aliasing mode)
	painter->setRenderHint(QPainter::Antialiasing);

	// Устанавливаем кисть жёлтого цвета (цвет задан в RGB)
	painter->setBrush(QBrush(QColor(0xFA, 0xFE, 0x78)));

	// Рисуем эллипс на всё окно с отступом 5 пикселей
	painter->drawEllipse(QRect(5, 5, width() - 10, height() - 10));
}








