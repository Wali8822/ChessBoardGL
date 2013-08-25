#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QToolBar>
#include <QCheckBox>

class GLWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void    initToolbar();

protected slots:
    void    add();
    void    start();
    void    stop();
    void    reset();
    void    onGLWidgetReset();

    void    gridChanged(bool bValue);
    void    cubeChanged(bool bValue);
    void    NumberChanged(bool bValue);

    void	subWindowActivated(QMdiSubWindow * pSubWnd);

    void    onAnimateFinish(GLWidget * );

private:
    QMdiArea    *   m_pMdiArea;
    QToolBar    *   m_pToolbar;

    QCheckBox   *   m_pIsShowGrid;
    QCheckBox   *   m_pIsShowCube;
    QCheckBox   *   m_pIsShowNumber;

    QAction     *   m_pStartAction;
    QAction     *   m_pStopAction;

    int             m_Index;
};

#endif // MAINWINDOW_H
