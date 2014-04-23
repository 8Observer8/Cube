#include <QtGui>
#include "scene3d.h"
#include <cmath>
#include <ctime>

GLfloat VertexArray[8][3];
GLfloat ColorArray[8][3];
GLubyte IndexArray[12][3];

Scene3D::Scene3D(QWidget *parent) :
    QGLWidget(parent)
{
    xRot=-90; yRot=0; zRot=0; zTra=0; nSca=1;
}

void Scene3D::initializeGL()
{
    qglClearColor(Qt::white);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    glEnable(GL_CULL_FACE);

    getVertexArray();
    getColorArray();
    getIndexArray();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
}

void Scene3D::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat ratio=(GLfloat)nHeight/(GLfloat)nWidth;

    if (nWidth>=nHeight)
        glOrtho(-1.0/ratio, 1.0/ratio, -1.0, 1.0, -10.0, 1.0);
    else
        glOrtho(-1.0, 1.0, -1.0*ratio, 1.0*ratio, -10.0, 1.0);

    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}

void Scene3D::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScalef(nSca, nSca, nSca);
    glTranslatef(0.0f, zTra, 0.0f);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(zRot, 0.0f, 0.0f, 1.0f);

    drawAxis();
    drawFigure();
}

void Scene3D::mousePressEvent(QMouseEvent* pe)
{
    ptrMousePosition = pe->pos();
}

void Scene3D::mouseMoveEvent(QMouseEvent* pe)
{
    xRot += 180/nSca*(GLfloat)(pe->y()-ptrMousePosition.y())/height();
    zRot += 180/nSca*(GLfloat)(pe->x()-ptrMousePosition.x())/width();

    ptrMousePosition = pe->pos();

    updateGL();
}

void Scene3D::wheelEvent(QWheelEvent* pe)
{
    if ((pe->delta())>0) scale_plus(); else if ((pe->delta())<0) scale_minus();

    updateGL();
}

void Scene3D::keyPressEvent(QKeyEvent* pe)
{
    switch (pe->key())
    {
    case Qt::Key_Plus:
        scale_plus();
        break;

    case Qt::Key_Equal:
        scale_plus();
        break;

    case Qt::Key_Minus:
        scale_minus();
        break;

    case Qt::Key_Up:
        rotate_up();
        break;

    case Qt::Key_Down:
        rotate_down();
        break;

    case Qt::Key_Left:
        rotate_left();
        break;

    case Qt::Key_Right:
        rotate_right();
        break;

    case Qt::Key_Z:
        translate_down();
        break;

    case Qt::Key_X:
        translate_up();
        break;

    case Qt::Key_Space:
        defaultScene();
        break;

    case Qt::Key_Escape:
        this->close();
        break;
    }

    updateGL();
}

void Scene3D::scale_plus()
{
    nSca = nSca*1.1;
}

void Scene3D::scale_minus()
{
    nSca = nSca/1.1;
}

void Scene3D::rotate_up()
{
    xRot += 1.0;
}

void Scene3D::rotate_down()
{
    xRot -= 1.0;
}

void Scene3D::rotate_left()
{
    zRot += 1.0;
}

void Scene3D::rotate_right()
{
    zRot -= 1.0;
}

void Scene3D::translate_down()
{
    zTra -= 0.05;
}

void Scene3D::translate_up()
{
    zTra += 0.05;
}

void Scene3D::defaultScene()
{
    xRot=-90; yRot=0; zRot=0; zTra=0; nSca=1;
}

void Scene3D::drawAxis()
{
    glLineWidth(3.0f);

    glColor4f(1.00f, 0.00f, 0.00f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f( 10.0f,  0.0f,  0.0f);
    glVertex3f(-1.0f,  0.0f,  0.0f);
    glEnd();

    QColor halfGreen(0, 128, 0, 255);
    qglColor(halfGreen);
    glBegin(GL_LINES);
    glVertex3f( 0.0f,  10.0f,  0.0f);
    glVertex3f( 0.0f, -1.0f,  0.0f);

    glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
    glVertex3f( 0.0f,  0.0f,  10.0f);
    glVertex3f( 0.0f,  0.0f, -1.0f);
    glEnd();
}

void Scene3D::drawFigure()
{
    glVertexPointer(3, GL_FLOAT, 0, VertexArray);
    glColorPointer(3, GL_FLOAT, 0, ColorArray);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, IndexArray);
}

void Scene3D::getVertexArray()
{
    GLfloat R = 0.75;
    GLfloat a = (2 * R) / sqrt(3);

    // Top
    VertexArray[0][0]=a/2;
    VertexArray[0][1]=a/2;
    VertexArray[0][2]=a/2;

    VertexArray[1][0]=-a/2;
    VertexArray[1][1]=a/2;
    VertexArray[1][2]=a/2;

    VertexArray[2][0]=-a/2;
    VertexArray[2][1]=-a/2;
    VertexArray[2][2]=a/2;

    VertexArray[3][0]=a/2;
    VertexArray[3][1]=-a/2;
    VertexArray[3][2]=a/2;

    // Bottom
    VertexArray[4][0]=a/2;
    VertexArray[4][1]=a/2;
    VertexArray[4][2]=-a/2;

    VertexArray[5][0]=-a/2;
    VertexArray[5][1]=a/2;
    VertexArray[5][2]=-a/2;

    VertexArray[6][0]=-a/2;
    VertexArray[6][1]=-a/2;
    VertexArray[6][2]=-a/2;

    VertexArray[7][0]=a/2;
    VertexArray[7][1]=-a/2;
    VertexArray[7][2]=-a/2;

//    // Top
//    VertexArray[0][0] = 1.0;
//    VertexArray[0][1] = 1.0;
//    VertexArray[0][2] = -1.0;

//    VertexArray[1][0] = 1.0;
//    VertexArray[1][1] = -1.0;
//    VertexArray[1][2] = -1;

//    VertexArray[2][0] = -1.0;
//    VertexArray[2][1]=-1.0;
//    VertexArray[2][2]=-1.0;

//    VertexArray[3][0]=-1.0;
//    VertexArray[3][1]=1.0;
//    VertexArray[3][2]=-1;

//    // Bottom
//    VertexArray[4][0]=1.0;
//    VertexArray[4][1]=1.0;
//    VertexArray[4][2]=1.0;

//    VertexArray[5][0]=1.0;
//    VertexArray[5][1]=-1.0;
//    VertexArray[5][2]=1.0;

//    VertexArray[6][0]=-1.0;
//    VertexArray[6][1]=-1.0;
//    VertexArray[6][2]=1.0;

//    VertexArray[7][0]=-1.0;
//    VertexArray[7][1]=1.0;
//    VertexArray[7][2]=1.0;
}

void Scene3D::getColorArray() {
    qsrand(time(NULL));
    qrand();
    for (int i=0; i<8; i++)
    {
        ColorArray[i][0]=0.1f*(qrand()%11);
        ColorArray[i][1]=0.1f*(qrand()%11);
        ColorArray[i][2]=0.1f*(qrand()%11);
    }
}

void Scene3D::getIndexArray() {
    // Top
    IndexArray[0][0]=0;
    IndexArray[0][1]=1;
    IndexArray[0][2]=2;

    IndexArray[1][0]=2;
    IndexArray[1][1]=3;
    IndexArray[1][2]=0;

    // Bottom
    IndexArray[2][0]=4;
    IndexArray[2][1]=7;
    IndexArray[2][2]=5;

    IndexArray[3][0]=5;
    IndexArray[3][1]=7;
    IndexArray[3][2]=6;

    // Sides
    IndexArray[4][0]=0;
    IndexArray[4][1]=4;
    IndexArray[4][2]=5;

    IndexArray[5][0]=0;
    IndexArray[5][1]=5;
    IndexArray[5][2]=1;

    IndexArray[6][0]=1;
    IndexArray[6][1]=5;
    IndexArray[6][2]=2;

    IndexArray[7][0]=2;
    IndexArray[7][1]=5;
    IndexArray[7][2]=6;

    IndexArray[8][0]=2;
    IndexArray[8][1]=6;
    IndexArray[8][2]=3;

    IndexArray[9][0]=3;
    IndexArray[9][1]=6;
    IndexArray[9][2]=7;

    IndexArray[10][0]=0;
    IndexArray[10][1]=3;
    IndexArray[10][2]=7;

    IndexArray[11][0]=0;
    IndexArray[11][1]=7;
    IndexArray[11][2]=4;
}
