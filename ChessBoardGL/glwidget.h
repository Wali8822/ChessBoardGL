#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glext.h>
#include <qgl.h>
#include <QTimer>


#include "chessboard.h"


class GLWidget : public QGLWidget
{
    Q_OBJECT
public:


public:
    explicit GLWidget(int size,int x,int y,QWidget *parent = 0);
    
    void    setIsDrawNumber(bool isDrawNumber);
    void    setIsDrawGrid(bool isDrawGrid);
    void    setIsDrawCube(bool isDrawCube);

    bool    IsDrawNumber()const;
    bool    IsDrawGrid()const;
    bool    IsDrawCube()const;

    bool    isAniminating()const;

    void    startAnimate();
    void    stopAnimate();
    void    resetAnimate();

protected:
    virtual void    initializeGL();
    virtual void    paintGL();
    virtual void    resizeGL(int w, int h);

    void    setColor(const QColor & color);
    void    drawBackground();
    void    drawChessBoard();
    void    drawBoardGrid();
    void    drawNumber();

    virtual void    mousePressEvent(QMouseEvent *);
    virtual void    mouseMoveEvent(QMouseEvent *);

    virtual void    keyPressEvent(QKeyEvent * ke);

protected slots:
    void    onAnimate();

signals:
    void    animateFinish(GLWidget * pWidget);
    void    reset_signal();

private:
    QTimer      m_AnimateTimer;

    bool        m_bIsDrawNumber;
    bool        m_bIsDrawGrid;
    bool        m_bIsDrawCube;

    ChessBoard  m_Board;

    QList<QColor>   m_Colors;

    QPoint      m_LastPoint;
    GLfloat     m_XRot;
    GLfloat     m_YRot;
    GLfloat     m_ZRot;

    GLfloat     m_EyePos;

    GLfloat     m_CubeYScale;

    int         m_MaxTileDraw;
};

#endif // GLWIDGET_H
