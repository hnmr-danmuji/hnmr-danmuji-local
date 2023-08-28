#include <QLabel>
#include <QBoxLayout>
#include <QLineEdit>
#include <QFormLayout>
#include <QDesktopServices>
#include <QWebEngineView>

#include <QPlainTextEdit>

#include "danmuji.h"
#include "configwindow.h"

ConfigWindow::ConfigWindow(QWidget* parent) :
	QMainWindow(parent),
	m_container(new QWidget(this)),
	m_port(new QLineEdit(this)),

	m_debug(new QPlainTextEdit(this))
{
	setCentralWidget(m_container);
	//Set the layout.
	QFormLayout* layout = new QFormLayout(m_container);
	m_container->setLayout(layout);
	layout->addRow(tr("Danmuji URL:"), m_port);

	layout->addWidget(m_debug);
	//Configure the display widget.
	//QDesktopServices::openUrl(QUrl(m_port->text()));
}

void ConfigWindow::setDanmuji(Danmuji* danmuji)
{
	connect(danmuji, &Danmuji::portChanged, this, &ConfigWindow::onPortChanged);
}

void ConfigWindow::onPortChanged(int port)
{
	m_port->setText("http://localhost:" + QString::number(port));
}