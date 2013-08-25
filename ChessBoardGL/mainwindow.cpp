#include "mainwindow.h"
#include "glwidget.h"
#include "chessinfodialog.h"

#include <QMdiSubWindow>
#include <QAction>
#include <QCheckBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_pMdiArea(new QMdiArea(this)),
      m_pToolbar(new QToolBar(this)),
      m_pIsShowGrid(NULL),
      m_pIsShowCube(NULL),
      m_pIsShowNumber(NULL),
      m_pStartAction(NULL),
      m_pStopAction(NULL),
      m_Index(0)
{
    m_pMdiArea->setViewMode(QMdiArea::TabbedView);

    initToolbar();
    setGeometry(50,50,800,480);

    setCentralWidget(m_pMdiArea);

    QObject::connect(m_pMdiArea,SIGNAL(subWindowActivated(QMdiSubWindow*)),
                     this,SLOT(subWindowActivated(QMdiSubWindow*)));
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::initToolbar()
{
    addToolBar(Qt::TopToolBarArea, m_pToolbar);

    QAction * pAction =  m_pToolbar->addAction(QIcon("./plus.png"),"Add");
    QObject::connect(pAction,SIGNAL(triggered()),this,SLOT(add()));

    m_pToolbar->addSeparator();

    m_pStartAction = m_pToolbar->addAction(QIcon("./start.png"),"Start");
    QObject::connect(m_pStartAction,SIGNAL(triggered()),this,SLOT(start()));
    m_pStartAction->setEnabled(false);

    m_pStopAction = m_pToolbar->addAction(QIcon("./stop.png"),"Stop");
    QObject::connect(m_pStopAction,SIGNAL(triggered()),this,SLOT(stop()));
    m_pStopAction->setEnabled(false);

    pAction = m_pToolbar->addAction(QIcon("./restart.png"),"Stop");
    QObject::connect(pAction,SIGNAL(triggered()),this,SLOT(reset()));

    m_pToolbar->addSeparator();
    m_pIsShowGrid = new QCheckBox(QObject::tr("Íø¸ñ"));
    m_pToolbar->addWidget(m_pIsShowGrid);
    QObject::connect(m_pIsShowGrid,SIGNAL(clicked(bool)),this,SLOT(gridChanged(bool)));

    m_pIsShowCube = new QCheckBox(QObject::tr("·½¿é"));
    m_pToolbar->addWidget(m_pIsShowCube);
    QObject::connect(m_pIsShowCube,SIGNAL(clicked(bool)),this,SLOT(cubeChanged(bool)));

    m_pIsShowNumber = new QCheckBox(QObject::tr("Êý×Ö"));
    m_pToolbar->addWidget(m_pIsShowNumber);
    QObject::connect(m_pIsShowNumber,SIGNAL(clicked(bool)),this,SLOT(NumberChanged(bool)));
}

void MainWindow::add()
{
    if(m_pMdiArea != NULL)
    {
        ChessInfoDialog dlg;

        if(dlg.exec() == QDialog::Accepted)
        {
            GLWidget * pGLWidget = new GLWidget(dlg.getSize(),dlg.getX(),dlg.getY());

            QMdiSubWindow * pWnd =  m_pMdiArea->addSubWindow(pGLWidget);

            pWnd->setWindowTitle("Board:"+QString::number(++m_Index));
            pWnd->show();

            QObject::connect(pGLWidget,SIGNAL(reset_signal()),
                             this,SLOT(onGLWidgetReset()));
            QObject::connect(pGLWidget,SIGNAL(animateFinish(GLWidget*)),
                             this,SLOT(onAnimateFinish(GLWidget*)));
        }
    }
}

void MainWindow::start()
{
    QMdiSubWindow * pSubWnd = m_pMdiArea->activeSubWindow();

    if(pSubWnd != NULL)
    {
        GLWidget * pWidget = dynamic_cast<GLWidget*>(pSubWnd->widget());

        pWidget->startAnimate();

        m_pStartAction->setEnabled(false);
        m_pStopAction->setEnabled(true);
    }
}

void MainWindow::stop()
{
    QMdiSubWindow * pSubWnd = m_pMdiArea->activeSubWindow();

    if(pSubWnd != NULL)
    {
        GLWidget * pWidget = dynamic_cast<GLWidget*>(pSubWnd->widget());

        pWidget->stopAnimate();

        m_pStartAction->setEnabled(true);
        m_pStopAction->setEnabled(false);
    }
}

void MainWindow::reset()
{
    QMdiSubWindow * pSubWnd = m_pMdiArea->activeSubWindow();

    if(pSubWnd != NULL)
    {
        GLWidget * pWidget = dynamic_cast<GLWidget*>(pSubWnd->widget());

        pWidget->resetAnimate();
    }
}

void MainWindow::onGLWidgetReset()
{
    m_pStartAction->setEnabled(true);
    m_pStopAction->setEnabled(false);
}

void MainWindow::gridChanged(bool bValue)
{
    QMdiSubWindow * pSubWnd = m_pMdiArea->activeSubWindow();

    if(pSubWnd != NULL)
    {
        GLWidget * pWidget = dynamic_cast<GLWidget*>(pSubWnd->widget());

        pWidget->setIsDrawGrid(bValue);
    }
}

void MainWindow::cubeChanged(bool bValue)
{
    QMdiSubWindow * pSubWnd = m_pMdiArea->activeSubWindow();

    if(pSubWnd != NULL)
    {
        GLWidget * pWidget = dynamic_cast<GLWidget*>(pSubWnd->widget());

        pWidget->setIsDrawCube(bValue);
    }
}

void MainWindow::NumberChanged(bool bValue)
{
    QMdiSubWindow * pSubWnd = m_pMdiArea->activeSubWindow();

    if(pSubWnd != NULL)
    {
        GLWidget * pWidget = dynamic_cast<GLWidget*>(pSubWnd->widget());

        pWidget->setIsDrawNumber(bValue);
    }
}

void MainWindow::subWindowActivated(QMdiSubWindow * pSubWnd)
{
    if(pSubWnd != NULL)
    {
        GLWidget * pWidget = dynamic_cast<GLWidget*>(pSubWnd->widget());

        pWidget->grabKeyboard();

        m_pIsShowGrid->setChecked(pWidget->IsDrawGrid());
        m_pIsShowCube->setChecked(pWidget->IsDrawCube());
        m_pIsShowNumber->setChecked(pWidget->IsDrawNumber());

        m_pStartAction->setEnabled(!pWidget->isAniminating());
        m_pStopAction->setEnabled(pWidget->isAniminating());
    }
}

void MainWindow::onAnimateFinish(GLWidget * pOther)
{
    QMdiSubWindow * pSubWnd = m_pMdiArea->activeSubWindow();

    if(pSubWnd != NULL)
    {
        GLWidget * pWidget = dynamic_cast<GLWidget*>(pSubWnd->widget());

        if(pWidget == pOther)
        {
            m_pStartAction->setEnabled(true);
            m_pStopAction->setEnabled(false);
        }
    }
}







