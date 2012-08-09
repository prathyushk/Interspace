#include <cstdlib>

#include <QObject>
#include <QString>
#include <QFile>
#include <QtGui>
#include <QtWebKit/QWebView>
#include <QDebug>

#include "Gui.hpp"

Gui::Gui() {
  isUpdateMode = false;
  newsItem = 0;

  initWindow(); // Set Up Window
  initLayout(); // Set Up Layout
}

void Gui::initWindow() {
  setWindowTitle(tr("Interspace Launcher")); // Set Title
  setObjectName("gui"); // Set Object Name
  resize(QSize(600, 600)); // Set Size

  // Set Position
  QRect frameRect = frameGeometry();
  frameRect.moveCenter(QDesktopWidget().availableGeometry().center());
  move(frameRect.topLeft());

  // Load Stylesheet
  QFile styleSheet("assets/stylesheets/Gui.qss");
  styleSheet.open(QFile::ReadOnly);
  qApp->setStyleSheet(styleSheet.readAll());
  styleSheet.close();
}

void Gui::initLayout() {
  // Initialize Main Layout
  mainLayout = new QVBoxLayout();
  mainLayout->setContentsMargins(QMargins(20, 135, 20, 11));

  newsFeedLayout = new QHBoxLayout(); // Initialize News Feed Layout

  // Initialize Left Arrow Button
  leftArrowButton = new QPushButton();
  leftArrowButton->setObjectName("leftArrowButton");
  leftArrowButton->setFixedSize(QSize(90, 323));
  connect(leftArrowButton, SIGNAL(clicked()), this, SLOT(decrementNewsItem()));
  newsFeedLayout->addWidget(leftArrowButton);

  // Initialize News Feed
  newsFeed = new QWebView();
  newsFeed->setObjectName("newsFeed");
  newsFeed->setFixedSize(QSize(340, 330));
  newsFeed->load(QUrl("http://www.interspacegame.com/newsfeed/0.html"));
  newsFeedLayout->addWidget(newsFeed);

  // Initialize Right Arrow Button
  rightArrowButton = new QPushButton();
  rightArrowButton->setObjectName("rightArrowButton");
  rightArrowButton->setFixedSize(QSize(90, 323));
  connect(rightArrowButton, SIGNAL(clicked()), this, SLOT(incrementNewsItem()));
  newsFeedLayout->addWidget(rightArrowButton);

  mainLayout->addLayout(newsFeedLayout); // Attach News Feed Layout to Main Layout

  // Initialize Controls Layout
  controlsLayout = new QHBoxLayout();

  // Initialize Progress Bar
  progressBar = new QProgressBar();
  progressBar->setObjectName("progressBar");
  progressBar->setFixedSize(QSize(348, 66));
  connect(this, SIGNAL(progressBarValueSet(int)), progressBar, SLOT(setValue(int)));
  controlsLayout->addWidget(progressBar);

  // Initialize Control Button
  controlButton = new QPushButton();
  controlButton->setObjectName("controlButton");
  controlButton->setFixedSize(QSize(183, 83));
  connect(controlButton, SIGNAL(clicked()), this, SIGNAL(runLauncher()));
  controlsLayout->addWidget(controlButton);

  mainLayout->addLayout(controlsLayout); // Attach Controls Layout to Main Layout

  setLayout(mainLayout); // Set Main Layout
}

void Gui::updateMode() {
} 

void Gui::setProgressBarValue(int value) {
  emit progressBarValueSet(value);
}

void Gui::decrementNewsItem() {
  newsItem--;
  newsFeed->load(QUrl("http://www.interspacegame.com/newsfeed/" + QString::number(newsItem) + ".html"));
}

void Gui::incrementNewsItem() {
  newsItem++;
  newsFeed->load(QUrl("http://www.interspacegame.com/newsfeed/" + QString::number(newsItem) + ".html"));
}

Gui::~Gui() {
  // Delete Widgets
  if (progressBar)
    delete progressBar;
  if (leftArrowButton)
    delete leftArrowButton;
  if (newsFeed)
    delete newsFeed;
  if (rightArrowButton)
    delete rightArrowButton;
  if (controlButton)
    delete controlButton;

  // Delete Layouts
  if (newsFeedLayout)
    delete newsFeedLayout;
  if (controlsLayout)
    delete controlsLayout;
  if (mainLayout)
    delete mainLayout;
}
