#include "fetcherpage.h"

FetcherPage::FetcherPage(QObject* parent) :
	QWebEnginePage(parent)
{
}

void FetcherPage::javaScriptConsoleMessage(QWebEnginePage::JavaScriptConsoleMessageLevel level, const QString& message, int lineNumber, const QString& sourceID)
{
	//Recast the message.
	emit danmuAppears(message);
}
