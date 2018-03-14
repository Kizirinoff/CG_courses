#pragma once

// Подключаем заголовки используемых классов.
#include <QtGui/QWindow>
#include <QtGui/QPainter>
#include <QtGui/QResizeEvent>
#include <QtGui/QExposeEvent>
#include <QtGui/QBackingStore>
#include "PoolTableScene.h"
#include <QtCore/QElapsedTimer>
#include <memory>
// Класс RasterWindow наследует все поля и методы класса QWindow
class RasterWindow : public QWindow
{
	// Макрос Q_OBJECT является меткой для Qt moc - генератора кода в составе Qt SDK
	Q_OBJECT

public: // Начало секции публично доступных полей и методов

	// Добавьте в класс RasterWindow новые
	// публичные методы “isAnimating” и “setAnimating”:
	bool isAnimating() const;
	void setAnimating(bool isAnimating);

	// Затем добавьте булево поле для хранения данных этого свойства
	//bool m_isAnimating = false;
	
		// Конструктор класса: принимает один (опциональный) параметр типа QWindow,
		//  в этом параметре можно передать родительское окно (например, для модального диалога)
	explicit RasterWindow(QWindow *parent = 0);

protected: // Начало секции полей и методов, доступных только в наследниках этого класса

		   // Ниже перегружены полиморфные методы родительского класса QWindow
		   // Библиотека Qt рассылает различные события по этим методам
		   
		  
		   
    //  - метод event вызывается перед обработкой любых событий, включая resizeEvent и exposeEvent
	bool event(QEvent *event) override;
	
	//  - метод exposeEvent вызывается при показе окна
	void exposeEvent(QExposeEvent *event) override;

	//  - метод resizeEvent вызывается при изменении размера окна
	void resizeEvent(QResizeEvent *event) override;

private: // Начало секции полей и методов, доступных только в наследниках этого класса
	
	void renderNow();
	void renderLater();
	void updateScene(); // обновляет состояние сцены
	void renderScene(); // перерисовывает содержимое сцены
	
	
	void render(QPainter *painter);



	// Класс QBackingStore предоставляет окну буфер рисования кадра.
	// Грубо говоря, этот буфер содержит будущие пиксели окна и позволяет
	//  рисовать векторную графику (фигуры, изображения, текст), заполняя
	//  этот буфер пикселей.
	QBackingStore *m_backingStore = nullptr;
	std::unique_ptr<PoolTableScene> m_scene; // объект сцены
	QElapsedTimer m_updateTimer; // таймер обновления сцены
	bool m_isAnimating = false;
};
