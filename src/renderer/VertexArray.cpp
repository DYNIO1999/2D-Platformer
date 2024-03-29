#include "VertexArray.h"

namespace DEngine
{
    VertexArray::VertexArray():m_attribCounter(0)
    {
        glCreateVertexArrays(1, &m_vertexArrayID);
    }
    VertexArray::~VertexArray(){
        glDeleteVertexArrays(1, &m_vertexArrayID);
    }
    void VertexArray::Bind(){
        glBindVertexArray(m_vertexArrayID);
    }
}
