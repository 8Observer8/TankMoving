#include "Scene.h"
#include <QDebug>

Scene::Scene( QWidget *parent ) :
    QGLWidget( parent ),
    dir( Right )
{
    this->setFocusPolicy( Qt::StrongFocus );

    connect( &drawingTimer, SIGNAL( timeout() ),
             this, SLOT( updateGL() ) );
    drawingTimer.start( 5 );

//    connect( &animationTimer, SIGNAL( timeout() ),
//             this, SLOT( slotUpdate() ) );
//    animationTimer.start( 50 );
}

void Scene::initializeGL()
{
    // Цвет для очистки буфера изображения - будет просто фон окна
    glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );

    // Устанавливает режим проверки глубины пикселей
    glEnable( GL_DEPTH_TEST );

    // Отключает режим сглаживания цветов
    glShadeModel( GL_FLAT );

    // Устанавливаем режим, когда строятся только внешние поверхности
    glEnable( GL_CULL_FACE );

    glEnable( GL_TEXTURE_2D);

    genTextures();

    // Активизация массива вершин
    glEnableClientState( GL_VERTEX_ARRAY );

    // Активизация массива текстурных координат
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
}

void Scene::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    square.draw( textureID );
}

void Scene::resizeGL( int w, int h )
{
    glViewport( 0, 0, w, h );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    static const int size = 500;

    GLfloat aspectRatio = ( GLfloat )w / ( GLfloat )h;
    if ( w <= h ) {
        glOrtho( -size, size, -size / aspectRatio, size / aspectRatio,
                  1, -1);
    } else {
        glOrtho( -size * aspectRatio, size * aspectRatio, -size, size,
                 1, -1 );
    }

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

void Scene::keyPressEvent( QKeyEvent *event )
{
    static const unsigned int step = 3;
    switch( event->key() ) {
        case Qt::Key_Left:
            dir = Left;
            square.move( square.Left, -step );
            break;
        case Qt::Key_Right:
            dir = Right;
            square.move( square.Right, step );
            break;
        case Qt::Key_Down:
            dir = Down;
            square.move( square.Down, -step );
            break;
        case Qt::Key_Up:
            dir = Up;
            square.move( square.Up, step );
            break;
    }

    slotUpdate();
}

void Scene::genTextures()
{
    genFrames();

    for( size_t i = 0; i < framesToRight.size(); ++i ) {
        textureIdArrayToRight.push_back( bindTexture( framesToRight[i], GL_TEXTURE_2D ) );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    }

    for( size_t i = 0; i < framesToLeft.size(); ++i ) {
        textureIdArrayToLeft.push_back( bindTexture( framesToLeft[i], GL_TEXTURE_2D ) );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    }

    for( size_t i = 0; i < framesToDown.size(); ++i ) {
        textureIdArrayToDown.push_back( bindTexture( framesToDown[i], GL_TEXTURE_2D ) );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    }

    for( size_t i = 0; i < framesToUp.size(); ++i ) {
        textureIdArrayToUp.push_back( bindTexture( framesToUp[i], GL_TEXTURE_2D ) );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    }

    if ( framesToUp.size() == 4 ) {
        textureID = textureIdArrayToUp[0];
    }
}

void Scene::genFrames()
{
    QPixmap pixmap = QPixmap( QString( ":Textures/pla1.bmp" ) );
    const unsigned int step = pixmap.width() / 4;
    QPixmap copyPixmap;
    for ( unsigned int i = 0; i < 4; ++i ) {
        copyPixmap = pixmap.copy( i * step, 0, step, step );
        framesToRight.push_back( copyPixmap );
    }

    for( unsigned int i = 0; i < framesToRight.size(); ++i ) {
        QImage image = framesToRight[i].toImage();
        framesToLeft.push_back( QPixmap::fromImage( image.mirrored( true, false ) ) );
    }

    for( unsigned int i = 0; i < framesToRight.size(); ++i ) {
        QPixmap rotatedPixmap( framesToRight[i] );
        QMatrix rm;
        rm.rotate( 90 );
        framesToDown.push_back( rotatedPixmap.transformed( rm ) );
    }

    for( unsigned int i = 0; i < framesToDown.size(); ++i ) {
        QImage image = framesToDown[i].toImage();
        framesToUp.push_back( QPixmap::fromImage( image.mirrored( false, true ) ) );
    }
}

void Scene::slotUpdate()
{
    static int i = 0;

    if ( i == 4 ) {
        i = 0;
    }

    switch( dir ) {
        case Left:
            textureID = textureIdArrayToLeft[i];
            break;
        case Up:
            textureID = textureIdArrayToUp[i];
            break;
        case Right:
            textureID = textureIdArrayToRight[i];
            break;
        case Down:
            textureID = textureIdArrayToDown[i];
            break;
    }

    ++i;
    updateGL();
}
