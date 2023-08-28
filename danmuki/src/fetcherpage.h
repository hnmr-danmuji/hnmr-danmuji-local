#ifndef FETCHERPAGE_H
#define FETCHERPAGE_H

#include <QWebEnginePage>

class FetcherPage : public QWebEnginePage
{
	Q_OBJECT
public:
	explicit FetcherPage(QObject* parent = nullptr);

signals:
	void danmuAppears(const QString& context);

protected:
	void javaScriptConsoleMessage(QWebEnginePage::JavaScriptConsoleMessageLevel level, const QString& message, int lineNumber, const QString& sourceID) override;
};

#endif // FETCHERPAGE_H