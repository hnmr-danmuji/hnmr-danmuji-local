#include <QApplication>
#include <QHttpServer>

#include "danmuji.h"
#include "configwindow.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	//Set up the server.
	Danmuji danmuji;
	//Prepare the main window.
	ConfigWindow w;
	w.setDanmuji(&danmuji);
	w.show();
	//Start the Danmuji.
	danmuji.start();
	return app.exec();
}