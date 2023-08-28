#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QMainWindow>

class QPlainTextEdit;

class QLineEdit;
class QLabel;
class Danmuji;
class ConfigWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit ConfigWindow(QWidget* parent = 0);

	void setDanmuji(Danmuji* danmuji);

private slots:
	void onPortChanged(int port);

private:
	QWidget* m_container;
	QLineEdit* m_port;

	QPlainTextEdit* m_debug;
};

#endif // CONFIGWINDOW_H