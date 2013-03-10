#ifndef Gui_hpp
#define Gui_hpp

#include <QObject>
#include <QtGui>
#include <QtWebKit/QWebView>

#include "NewsView.hpp"

class Gui : public QWidget
{
        Q_OBJECT

public:
        Gui();
        ~Gui();

public slots:
        void setProgressBarValue(int value);
	//void setProgressBarRange(int lowerLimit, int upperLimit);
	//void updateAvailable();
	//void isUpToDate();
	//void finishedUpdating();

signals:
        void runLauncher();
        void runUpdater();
        void progressBarValueSet(int value);
	void progressBarRangeSet(int lowerLimit, int upperLimit);

private:
        void initWindow();
        void initLayout();
        QVBoxLayout *mainLayout;
        QHBoxLayout *newsFeedLayout;
        QHBoxLayout *controlsLayout;
        QProgressBar *progressBar;
        QPushButton *leftArrowButton;
        NewsView *newsFeed;
        QPushButton *rightArrowButton;
        QPushButton *controlButton;
        bool isUpdateMode;
};

#endif /* Gui_hpp */
