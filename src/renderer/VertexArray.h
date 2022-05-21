#ifndef _SRC_RENDERER_VERTEX_ARRAY_H_
#define _SRC_RENDERER_VERTEX_ARRAY_H_

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

namespace LightInDarkness{
class VertexArray
{
public:
    VertexArray();
    ~VertexArray();


    // THINK HOW TO DO IT!!!


    template <typename T>
    void AddBuffer(const T& _buffer);
    template <>
    void AddBuffer<VertexBuffer>(const VertexBuffer&_buffer){
        //STRIDE AND STUFF THINK !!!
        glEnableVertexArrayAttrib(m_vertexArrayID, m_attribCounter);
        glVertexArrayAttribFormat(m_vertexArrayID, m_attribCounter, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(m_vertexArrayID, 0, 0);
        glVertexArrayVertexBuffer(m_vertexArrayID, 0, _buffer.GetID(), 0, 3 * sizeof(float));
    }
    template <>
    void AddBuffer<IndexBuffer>(const IndexBuffer &_buffer)
    {
        glVertexArrayElementBuffer(m_vertexArrayID, _buffer.GetID());
    }

    void Bind();
    unsigned int GetID() const { return m_vertexArrayID;}
private:
    unsigned int m_vertexArrayID;
    unsigned int m_attribCounter;

};
}
#endif
