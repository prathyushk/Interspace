#ifndef Gui_hpp
#define Gui_hpp

#include <QObject>
#include <QtGui>
#include <QtWebKit/QWebView>

class Gui : public QWidget {
Q_OBJECT

public:
  Gui();
  ~Gui();

public slots:
  void updateMode();
  void setProgressBarValue(int);

private slots:
  void decrementNewsItem();
  void incrementNewsItem();

signals:
  void runLauncher();
  void runUpdater();
  void progressBarValueSet(int);

private:
  void initWindow();
  void initLayout();
  QVBoxLayout *mainLayout;
  QHBoxLayout *newsFeedLayout;
  QHBoxLayout *controlsLayout;
  QProgressBar *progressBar;
  QPushButton *leftArrowButton;
  QWebView *newsFeed;
  QPushButton *rightArrowButton;
  QPushButton *controlButton;
  bool isUpdateMode;
  int newsItem;
};

#endif /* Gui_hpp */
