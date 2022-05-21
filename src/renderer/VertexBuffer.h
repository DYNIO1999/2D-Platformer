#ifndef _SRC_RENDERER_VERTEX_BUFFER_H_
#define _SRC_RENDERER_VERTEX_BUFFER_H_

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace LightInDarkness{
class VertexBuffer
{
public:
    VertexBuffer(void* _data, unsigned int _sizeInBytes);
    ~VertexBuffer();
    unsigned int GetID() const {return m_bufferID;}
private:
    unsigned int m_bufferID; 
};
}
#endif