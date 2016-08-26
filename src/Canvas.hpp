#ifndef CANVAS_HPP
#define CANVAS_HPP


#include <GL/glew.h>

#undef near
#undef far


#define QUAD(xPos, yPos, xSize, ySize) xPos, yPos, 0.0f,\
                                       xPos+xSize, yPos, 0.0f,\
                                       xPos, yPos+ySize, 0.0f,\
                                       xPos, yPos+ySize, 0.0f,\
                                       xPos+xSize, yPos, 0.0f,\
                                       xPos+xSize, yPos+ySize, 0.0f


class Shader;
class Texture;

class Canvas {
public:
    Canvas(void);

    void draw(Shader& shader/*, Texture& tex1, Texture& tex2*/) const;

private:
    GLuint _vertexArrayId;

};


#endif // CANVAS_HPP
