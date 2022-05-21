#ifndef _SRC_RENDERER_INDEX_BUFFER_H_
#define _SRC_RENDERER_INDEX_BUFFER_H_

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace LightInDarkness{
class IndexBuffer
{
public:
    IndexBuffer(unsigned int *_data, unsigned int _sizeInBytes);
    ~IndexBuffer();

    unsigned int GetID() const { return m_indexBufferID;}
private:
    unsigned int m_indexBufferID;
};
}
#endif
