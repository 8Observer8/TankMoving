#ifndef SQUARE_H
#define SQUARE_H

#include <vector>
#include <GL/gl.h>

class Square
{
public:
    enum Direction { Up, Left, Down, Right };
    Square();
    void draw( unsigned int textureID ) const;
    void move( Direction dir, int step );
    void init();

    std::vector<int> vertices;
    std::vector<unsigned int> indices;
    //std::vector<float> colors;
    std::vector<float> textures;
    const size_t size;
};

#endif // SQUARE_H
