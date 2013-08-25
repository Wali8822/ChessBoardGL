#include "glwidget.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QtOpenGL>
#include <QtGui>

static const GLfloat    CUBE_SIZE = 0.15f;
static const GLfloat    START_X = 0.0f;
static const GLfloat    START_Z = 0.0f;

static const GLfloat    ANIMATE_STEP = 0.2f;

GLWidget::GLWidget(int size, int x, int y,QWidget *parent) :
    QGLWidget(parent),
    m_AnimateTimer(),
    m_bIsDrawNumber(false),
    m_bIsDrawGrid(true),
    m_bIsDrawCube(true),
    m_Board(size,x,y),
    m_Colors(),
    m_XRot(0),
    m_YRot(0),
    m_ZRot(0),
    m_EyePos(2.0f),
    m_CubeYScale(1.0f),
    m_MaxTileDraw(0)
{
    QGLFormat f = format();

    f.setDoubleBuffer(true);
    setFormat(f);

    setMinimumSize(200,300);

    for(int i=0;i<m_Board.getMaxColorCount();++i)
    {
        m_Colors.push_back(QColor(qrand()%255,qrand()%255,qrand()%255));
    }

    m_AnimateTimer.setInterval(50);
    QObject::connect(&m_AnimateTimer,SIGNAL(timeout()),this,SLOT(onAnimate()));

    m_MaxTileDraw =  m_Board.getMaxColorCount();
    m_EyePos = sqrt((double)m_Board.size()) * 0.5f;

    grabKeyboard();
}

void GLWidget::setIsDrawNumber(bool isDrawNumber)
{
    m_bIsDrawNumber = isDrawNumber;

    updateGL();
}

void GLWidget::setIsDrawGrid(bool isDrawGrid)
{
    m_bIsDrawGrid = isDrawGrid;

    updateGL();
}

void GLWidget::setIsDrawCube(bool isDrawCube)
{
    m_bIsDrawCube = isDrawCube;

    updateGL();
}

bool GLWidget::IsDrawNumber() const
{
    return m_bIsDrawNumber;
}

bool GLWidget::IsDrawGrid() const
{
    return m_bIsDrawGrid;
}

bool GLWidget::IsDrawCube() const
{
    return m_bIsDrawCube;
}

bool GLWidget::isAniminating() const
{
    return m_AnimateTimer.isActive();
}

void GLWidget::startAnimate()
{
    if(m_MaxTileDraw == m_Board.getMaxColorCount())
    {
        m_MaxTileDraw = -1;
        m_CubeYScale = 0.0f;
    }

    m_AnimateTimer.start();
}

void GLWidget::stopAnimate()
{
    m_AnimateTimer.stop();
}

void GLWidget::resetAnimate()
{
    m_MaxTileDraw = m_Board.getMaxColorCount();
    m_CubeYScale = 1.0f;
    m_AnimateTimer.stop();

    updateGL();

    emit reset_signal();
}

void GLWidget::initializeGL()
{
    glClearColor(0.5f,0.5f,0.5f,1.0f);

    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0f);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
//    glEnable(GL_MULTISAMPLE);

    static GLfloat light_position[4] = { 5.0, 5.0, 7.0, 1.0 };
    static GLfloat mat_specular[] = {1.0,1.0,1.0,1.0};
    static GLfloat mat_shininess[]={50.0};
    static GLfloat white_light [] = {1.0,1.0,1.0,1.0};
    static GLfloat lmodel_ambient[] = {0.1,0.1,0.1,1.0};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,white_light);
    glLightfv(GL_LIGHT0,GL_SPECULAR,white_light);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lmodel_ambient);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(60.0f,1.0f,0.1f,200.0f);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    GLfloat centerX = m_Board.size() / 2 * CUBE_SIZE;
    GLfloat centerY = 0.0f;
    GLfloat centerZ = m_Board.size() / 2 * CUBE_SIZE;

    gluLookAt(m_EyePos,m_EyePos,m_EyePos,
              centerX,centerY,centerZ,
              0.0f,1.0f,0.0f);
}

void GLWidget::paintGL()
{
    makeCurrent();

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    GLfloat centerX = m_Board.size() / 2 * CUBE_SIZE;
    GLfloat centerY = 0.0f;
    GLfloat centerZ = m_Board.size() / 2 * CUBE_SIZE;

    gluLookAt(m_EyePos,m_EyePos,m_EyePos,
              centerX,centerY,centerZ,
              0.0f,1.0f,0.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawBackground();

    glPushMatrix();

    glTranslatef(centerX,centerY,centerZ);
    glRotatef(m_YRot,0.0f,1.0f,0.0f);
    glTranslatef(-centerX,-centerY,-centerZ);

    if(m_bIsDrawCube)
    {
        drawChessBoard();
    }

    if(m_bIsDrawGrid)
    {
        drawBoardGrid();
    }

    if(m_bIsDrawNumber)
    {
        drawNumber();
    }

    glPopMatrix();
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void GLWidget::setColor(const QColor &color)
{
    float faceColor[4];

    faceColor[0] = color.redF();
    faceColor[1] = color.greenF();
    faceColor[2] = color.blueF();
    faceColor[3] = color.alphaF();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, faceColor);
}

void GLWidget::drawBackground()
{
    setColor(QColor(255,0,0));

    glBegin(GL_QUADS);

    glNormal3f(0.0f,-1.0f,0.0f);

    glVertex3f(-8.0f,-0.5f,-8.0f);
    glVertex3f(8.0f, -0.5f,-8.0f);
    glVertex3f(8.0f, -0.5f,8.0f);
    glVertex3f(-8.0f,-0.5f,8.0f);

    glEnd();
}

void GLWidget::drawChessBoard()
{
    for(int x=0;x<m_Board.size();++x)
    {
        for(int y=0;y<m_Board.size();++y)
        {
            int value = m_Board.value(x,y);

            if(value > m_MaxTileDraw)
            {
                continue;
            }

            GLfloat p_x = START_X + CUBE_SIZE * x + x*0.002f/*+ CUBE_SIZE / 2*/;
            GLfloat p_z = START_Z + CUBE_SIZE * y + y*0.002f/*+ CUBE_SIZE / 2*/;

            QColor  color;

            if(x == m_Board.specialX() && y == m_Board.specialY())
            {
                color.setRgb(255,0,0);
            }
            else
            {
                color = m_Colors[value-1];
            }

            setColor(color);

            GLfloat Y = 0.0f;

            if(isAniminating() && value == m_MaxTileDraw)
            {
                Y = CUBE_SIZE * m_CubeYScale;
            }
            else
            {
                Y = CUBE_SIZE;
            }

            glBegin(GL_QUADS);

            glNormal3f(0.0f,    1.0f,   0.0f);
            glVertex3f(p_x,     Y,      p_z);
            glVertex3f(p_x+CUBE_SIZE,   Y,  p_z);
            glVertex3f(p_x+CUBE_SIZE,   Y,  p_z+CUBE_SIZE);
            glVertex3f(p_x, Y,  p_z+CUBE_SIZE);

            glNormal3f(0.0f,0.0f,-1.0f);
            glVertex3f(p_x  ,0.0f,  p_z);
            glVertex3f(p_x+CUBE_SIZE,   0.0f,   p_z);
            glVertex3f(p_x+CUBE_SIZE,   Y,  p_z);
            glVertex3f(p_x,     Y,  p_z);

            glNormal3f(0.0f,0.0f,1.0f);
            glVertex3f(p_x,     0.0f,       p_z + CUBE_SIZE);
            glVertex3f(p_x+CUBE_SIZE,       0.0f,       p_z + CUBE_SIZE);
            glVertex3f(p_x+CUBE_SIZE,       Y,          p_z + CUBE_SIZE);
            glVertex3f(p_x,     Y,      p_z+CUBE_SIZE);

            glNormal3f(1.0f,0.0f,0.0f);
            glVertex3f(p_x + CUBE_SIZE, 0.0f,   p_z);
            glVertex3f(p_x + CUBE_SIZE, 0.0f,   p_z + CUBE_SIZE);
            glVertex3f(p_x + CUBE_SIZE, Y,  p_z+CUBE_SIZE);
            glVertex3f(p_x + CUBE_SIZE, Y,  p_z);

            glNormal3f(-1.0f,0.0f,0.0f);
            glVertex3f(p_x ,    0.0f,   p_z);
            glVertex3f(p_x ,    0.0f,   p_z + CUBE_SIZE);
            glVertex3f(p_x ,    Y,  p_z+CUBE_SIZE);
            glVertex3f(p_x ,    Y,  p_z);

            glEnd();
        }
    }


}

void GLWidget::drawBoardGrid()
{
    setColor(QColor(255,255,255));
    glLineWidth(2.0f);

    glBegin(GL_LINES);
    for(int x=0;x<m_Board.size()+1;++x)
    {
        //xÖá
        glVertex3f(START_X + CUBE_SIZE * x,0.0f,0.0);
        glVertex3f(START_X + CUBE_SIZE * x,0.0f,CUBE_SIZE*m_Board.size());
    }

    for(int z=0;z<m_Board.size()+1;++z)
    {
        //xÖá
        glVertex3f(0.0f,0.0f,START_Z + CUBE_SIZE * z);
        glVertex3f(CUBE_SIZE * m_Board.size(),0.0f,START_Z + CUBE_SIZE * z);
    }

    glEnd();
}

void GLWidget::drawNumber()
{
    for(int x=0;x<m_Board.size();++x)
    {
        for(int y=0;y<m_Board.size();++y)
        {
            int value = m_Board.value(x,y);

            GLfloat p_x = START_X + CUBE_SIZE * x + x*0.005f + CUBE_SIZE / 2;
            GLfloat p_z = START_Z + CUBE_SIZE * y + y*0.005f + CUBE_SIZE / 2;

            if(m_bIsDrawCube)
            {
                renderText(p_x,CUBE_SIZE,p_z,QString::number(value),QFont("Arial",15));
            }
            else
            {
                renderText(p_x,0.0f,p_z,QString::number(value),QFont("Arial",15));
            }
        }
    }
}

void GLWidget::mousePressEvent(QMouseEvent * me)
{
    m_LastPoint = me->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent * me)
{
    int x_len = me->pos().x() - m_LastPoint.x();
//    int y_len = me->pos().y() - m_LastPoint.y();

    if(me->buttons() & Qt::LeftButton)
    {
//        m_XRot += y_len * 0.1f;
        m_YRot += x_len * 0.3f;

        updateGL();
    }

    m_LastPoint = me->pos();
}

void GLWidget::keyPressEvent(QKeyEvent * ke)
{
    if(ke->key() == Qt::Key_Up)
    {
        m_EyePos -= 0.1f;

        updateGL();
    }

    if(ke->key() == Qt::Key_Down)
    {
        m_EyePos += 0.1f;

        updateGL();
    }
}

void GLWidget::onAnimate()
{
    m_CubeYScale += ANIMATE_STEP;

    if(m_CubeYScale >= 1.0f)
    {
        m_CubeYScale = 0.0f;
        ++m_MaxTileDraw ;
        if(m_MaxTileDraw > m_Board.getMaxColorCount())
        {
            m_AnimateTimer.stop();
            m_MaxTileDraw = m_Board.getMaxColorCount();

            emit animateFinish(this);
        }
    }

    updateGL();
}









