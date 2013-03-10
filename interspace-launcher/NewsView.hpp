#ifndef NewsView_hpp
#define NewsView_hpp

#include <QWebView>
#include <QString>

#include "HttpRequest.hpp"

class NewsView : public QWebView
{
        Q_OBJECT

public:
        NewsView();

public slots:
        void decrementNewsItem();
        void incrementNewsItem();

private slots:
        void httpRequestComplete(QString data);

signals:
        void newsItemDecremented(int currentNewsItem, int newsItemCount);
        void newsItemIncremented(int currentNewsItem, int newsItemCount);

private:
        HttpRequest *httpRequest;
        int newsItemCount;
        int currentNewsItem;
};

#endif /* NewsView_hpp */
