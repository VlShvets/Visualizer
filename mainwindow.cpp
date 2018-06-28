#include "MainWindow.h"

MainWindow::MainWindow()
{
#ifdef Q_OS_WIN         /// Widnows
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("cp-1251"));
#elif defined Q_OS_UNIX /// Linux
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
#endif

    aboutEtalon = new AboutEtalon;
    QDockWidget *dAboutEtalon = new QDockWidget;
    dAboutEtalon->setWidget(aboutEtalon);
    dAboutEtalon->setMaximumHeight(400);
    dAboutEtalon->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dAboutEtalon->setFeatures(QDockWidget::AllDockWidgetFeatures);
    addDockWidget(Qt::LeftDockWidgetArea, dAboutEtalon);
    dAboutEtalon->setVisible(false);

    aboutTrack = new AboutTrack;
    QDockWidget *dAboutTrack = new QDockWidget;
    dAboutTrack->setWidget(aboutTrack);
    dAboutTrack->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dAboutTrack->setFeatures(QDockWidget::AllDockWidgetFeatures);
    addDockWidget(Qt::LeftDockWidgetArea, dAboutTrack);
    dAboutTrack->setVisible(false);

    graphHeight = new GraphHeight;
    QDockWidget *dGraphHeight = new QDockWidget;
    dGraphHeight->setWidget(graphHeight);
    dGraphHeight->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dGraphHeight->setFeatures(QDockWidget::AllDockWidgetFeatures);
    dGraphHeight->setMinimumWidth(300);
    addDockWidget(Qt::RightDockWidgetArea, dGraphHeight);
    dGraphHeight->setVisible(false);

    painter = new Painter(dAboutEtalon, dAboutTrack, dGraphHeight);
    this->setCentralWidget(painter);

    tool = new Tool(painter);
    QDockWidget *dTool = new QDockWidget;
    dTool->setWidget(tool);
    dTool->setAllowedAreas(Qt::AllDockWidgetAreas);
    dTool->setFeatures(QDockWidget::DockWidgetMovable);
    dTool->setMaximumHeight(100);
    addDockWidget(Qt::TopDockWidgetArea, dTool);
}

MainWindow::~MainWindow()
{
    delete aboutEtalon;
    delete aboutTrack;
    delete graphHeight;
    delete painter;
    delete tool;
}

void MainWindow::customEvent(QEvent *_event)
{
    if((int)_event->type() == TPubEtalonEvent::TPubEtalonType)
        painter->setEtalons(((TPubEtalonEvent*)(_event))->getTPubEtalon(), ((TPubEtalonEvent*)(_event))->getTime());

    if((int)_event->type() == TGenTrcEvent::TGenTrcType)
        painter->setTracks(((TGenTrcEvent*)(_event))->getTGenTrc());

    QWidget::customEvent(_event);
}
