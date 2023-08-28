#ifndef DANMIJI_H
#define DANMIJI_H

#include <QWebSocket>

#include <QObject>

class QWebEngineView;
class QHttpServer;
class QWebSocketServer;
class Danmuji : public QObject
{
	Q_OBJECT
public:
	explicit Danmuji(QObject* parent = nullptr);
	void start();

signals:
	void portChanged(int port);

private slots:
	void onMessageArrive(const QString& content);
	void onNewPageServer();

private:
	QHttpServer *m_pageServer, *m_fetchServer;
	QWebSocketServer* m_messageServer;
	QWebEngineView* m_fetcher;

	QString m_clientPage, m_clientStyle, m_fetcherPage, m_decodeJs;

	int m_messagePort;
};

#endif // DANMIJI_H