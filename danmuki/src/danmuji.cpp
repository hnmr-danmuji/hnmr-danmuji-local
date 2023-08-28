#include <QApplication>
#include <QDir>
#include <QFile>
#include <QJsonObject>
#include <QHttpServer>
#include <QWebEngineView>
#include <QWebSocketServer>

#include <QMessageBox>

#include "fetcherpage.h"

#include "danmuji.h"

QString loadTextFile(const QString& path)
{
	QString fileContent;
	QFile targetFile(path);
	if (targetFile.open(QIODevice::ReadOnly)) {
		fileContent = QString::fromUtf8(targetFile.readAll());
		targetFile.close();
	}
	return fileContent;
}

Danmuji::Danmuji(QObject* parent) :
	QObject(parent),
	m_pageServer(new QHttpServer(this)),
	m_fetchServer(new QHttpServer(this)),
	m_messageServer(new QWebSocketServer("BLive Chat Fetcher", QWebSocketServer::NonSecureMode, this)),
	m_fetcher(new QWebEngineView(QApplication::activeWindow())),
	m_messagePort(-1)
{
	//Load the data from the resource file.
	QDir appDir(QApplication::applicationDirPath());
	QDir assertDir(appDir.filePath("asserts"));
	//Load the content of the page.
	m_clientPage = loadTextFile(assertDir.filePath("bilibili-client.html"));
	m_clientStyle = loadTextFile(assertDir.filePath("bilibili-client.css"));
	m_fetcherPage = loadTextFile(assertDir.filePath("bilibili-fetch.html"));
	m_decodeJs = loadTextFile(assertDir.filePath("decode.js"));
	//Configure the page server.
	m_pageServer->route("/", [&]() {
		return m_clientPage;
		});
	m_pageServer->route("/bilibili-client.css", [&]() {
		return m_clientStyle;
		});
	m_pageServer->route("/config.js", [&]() {
		return "let socketPort = " + QString::number(m_messagePort);
		});
	//Configure the page server.
	m_fetchServer->route("/", [&]() {
		return m_fetcherPage;
		});
	m_fetchServer->route("/decode.js", [&]() {
		return m_decodeJs;
		});
	//Configure the fetcher page.
	FetcherPage* fetcherPage = new FetcherPage(this);
	m_fetcher->setPage(fetcherPage);
	//Link the page.
	connect(fetcherPage, &FetcherPage::danmuAppears, this, &Danmuji::onMessageArrive);
	//Configure the socket server.
	connect(m_messageServer, &QWebSocketServer::newConnection, this, &Danmuji::onNewPageServer);
}

void Danmuji::start()
{
	//Start the page server.
	const auto clientPort = m_pageServer->listen(QHostAddress::Any);
	emit portChanged(clientPort);
	//Start the message pushing server.
	m_messageServer->listen();
	m_messagePort = m_messageServer->serverPort();
	//Start the danmu fetching server.
	const auto fetcherPort = m_fetchServer->listen(QHostAddress::Any);
	m_fetcher->setUrl(QUrl("http://localhost:"+QString::number(fetcherPort)));
}

void Danmuji::onNewPageServer()
{
	if (m_messageServer->hasPendingConnections())
	{
		//Extract the socket.
		QWebSocket *socket = m_messageServer->nextPendingConnection();
		//Link the socket signals.

	}
}

void Danmuji::onMessageArrive(const QString& message)
{
	//Send to translate queue.
	;
	//Send to client to display the content.
	m_messageServer;
}