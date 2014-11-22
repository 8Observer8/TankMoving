#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <QGLWidget>
#include <QKeyEvent>
#include <QTimer>
#include "Square.h"

enum Direction { Left, Down, Right, Up };

class Scene : public QGLWidget
{
    Q_OBJECT

public:
    Scene( QWidget *parent = 0 );

private slots:
    void slotUpdate();

private:
    void initializeGL();
    void paintGL();
    void resizeGL( int w, int h );

    void keyPressEvent( QKeyEvent *event );
    void genTextures();
    void genFrames();

private:
    Square square;
    unsigned int textureID;
    std::vector<unsigned int> textureIdArrayToRight;
    std::vector<unsigned int> textureIdArrayToLeft;
    std::vector<QPixmap> framesToRight;
    std::vector<QPixmap> framesToLeft;
    std::vector<unsigned int> textureIdArrayToDown;
    std::vector<unsigned int> textureIdArrayToUp;
    std::vector<QPixmap> framesToDown;
    std::vector<QPixmap> framesToUp;
    QTimer drawingTimer;
    QTimer animationTimer;
    Direction dir;
};

#endif // SCENE_H
