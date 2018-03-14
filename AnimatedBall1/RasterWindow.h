#pragma once

// ���������� ��������� ������������ �������.
#include <QtGui/QWindow>
#include <QtGui/QPainter>
#include <QtGui/QResizeEvent>
#include <QtGui/QExposeEvent>
#include <QtGui/QBackingStore>
#include "PoolTableScene.h"
#include <QtCore/QElapsedTimer>
#include <memory>
// ����� RasterWindow ��������� ��� ���� � ������ ������ QWindow
class RasterWindow : public QWindow
{
	// ������ Q_OBJECT �������� ������ ��� Qt moc - ���������� ���� � ������� Qt SDK
	Q_OBJECT

public: // ������ ������ �������� ��������� ����� � �������

	// �������� � ����� RasterWindow �����
	// ��������� ������ �isAnimating� � �setAnimating�:
	bool isAnimating() const;
	void setAnimating(bool isAnimating);

	// ����� �������� ������ ���� ��� �������� ������ ����� ��������
	//bool m_isAnimating = false;
	
		// ����������� ������: ��������� ���� (������������) �������� ���� QWindow,
		//  � ���� ��������� ����� �������� ������������ ���� (��������, ��� ���������� �������)
	explicit RasterWindow(QWindow *parent = 0);

protected: // ������ ������ ����� � �������, ��������� ������ � ����������� ����� ������

		   // ���� ����������� ����������� ������ ������������� ������ QWindow
		   // ���������� Qt ��������� ��������� ������� �� ���� �������
		   
		  
		   
    //  - ����� event ���������� ����� ���������� ����� �������, ������� resizeEvent � exposeEvent
	bool event(QEvent *event) override;
	
	//  - ����� exposeEvent ���������� ��� ������ ����
	void exposeEvent(QExposeEvent *event) override;

	//  - ����� resizeEvent ���������� ��� ��������� ������� ����
	void resizeEvent(QResizeEvent *event) override;

private: // ������ ������ ����� � �������, ��������� ������ � ����������� ����� ������
	
	void renderNow();
	void renderLater();
	void updateScene(); // ��������� ��������� �����
	void renderScene(); // �������������� ���������� �����
	
	
	void render(QPainter *painter);



	// ����� QBackingStore ������������� ���� ����� ��������� �����.
	// ����� ������, ���� ����� �������� ������� ������� ���� � ���������
	//  �������� ��������� ������� (������, �����������, �����), ��������
	//  ���� ����� ��������.
	QBackingStore *m_backingStore = nullptr;
	std::unique_ptr<PoolTableScene> m_scene; // ������ �����
	QElapsedTimer m_updateTimer; // ������ ���������� �����
	bool m_isAnimating = false;
};
