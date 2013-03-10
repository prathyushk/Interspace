#include <cstdlib>

#include <QWebView>
#include <QString>
#include <QUrl>

#include "NewsView.hpp"

NewsView::NewsView() :
        newsItemCount(1),
        currentNewsItem(0)
{
        httpRequest = new HttpRequest(QUrl("http://interspacegame.com/newsfeed/itemcount"), false);
        connect(httpRequest, SIGNAL(downloadComplete(QString)), this, SLOT(httpRequestComplete(QString)));
	httpRequest->start();
}

void NewsView::httpRequestComplete(QString data)
{
        httpRequest->deleteLater();
	
        newsItemCount = data.toInt();
        currentNewsItem = 0;
        load(QUrl("http://interspacegame.com/newsfeed/" + QString::number(currentNewsItem) + ".html"));
}

void NewsView::decrementNewsItem()
{
        currentNewsItem = (currentNewsItem + 1) % newsItemCount;
        load(QUrl("http://interspacegame.com/newsfeed/" + QString::number(currentNewsItem) + ".html"));
        emit newsItemDecremented(currentNewsItem, newsItemCount);
}

void NewsView::incrementNewsItem()
{
        currentNewsItem = (currentNewsItem + 1) % newsItemCount;
        load(QUrl("http://interspacegame.com/newsfeed/" + QString::number(currentNewsItem) + ".html"));
        emit newsItemIncremented(currentNewsItem, newsItemCount);
}
