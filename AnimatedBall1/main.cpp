// ���������� ��������� ������ QGuiApplication �� ������ QtGui.
#include <QtGui/QGuiApplication>
#include <QtGui\qwindow.h>
#include "RasterWindow.h"

// ��������� ������� main, ����������� ��������� ��������� ������ � ���������� argc � argv
int main(int argc, char *argv[])
{
	// ��������� ���������� app ���� QGuiApplication.
	// �������� � ���� ��� ����� ������, ��� ��� ��� ������������� Q*Application
	//  ������ ���������������� ��������� ���������� Qt
	QGuiApplication app(argc, argv);

	// ��������� ���������� window ���� QWindow.
	// ��� ���������� ������������ ���� ������������ �������.
	RasterWindow window;

	window.setAnimating(true);

	// ���������� ����� ����: ����� �������� �����, ����� ������� ���� �������
	window.show();

	// ��������� ���� �������: ����� exec ����������� ������ �� ����������
	//  ������ ����������, � ���������� � main ��� �������� (��������� � ������ ������).
	return app.exec();
}
