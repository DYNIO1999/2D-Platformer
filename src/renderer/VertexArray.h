#ifndef _SRC_RENDERER_VERTEX_ARRAY_H_
#define _SRC_RENDERER_VERTEX_ARRAY_H_

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace LightInDarkness{
class VertexArray
{
public:
    VertexArray();
    ~VertexArray();



    template <typename T>
    void AddBuffer(const T& _buffer);
    template <>
    void AddBuffer<VertexBuffer>(const VertexBuffer&_buffer){

        glEnableVertexArrayAttrib(m_vertexArrayID, 0);
        glVertexArrayAttribFormat(m_vertexArrayID, 0, 3, GL_FLOAT, GL_FALSE, 0);
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

};
}
#endif
