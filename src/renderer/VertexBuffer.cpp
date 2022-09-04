#include "VertexBuffer.h"

namespace LightInDarkness
{
    VertexBuffer::VertexBuffer(void *_data, unsigned int _sizeInBytes)
    {
        glCreateBuffers(1, &m_bufferID);
        glNamedBufferStorage(m_bufferID, _sizeInBytes, reinterpret_cast<float *>(_data), GL_DYNAMIC_STORAGE_BIT);
    }

    VertexBuffer::VertexBuffer(unsigned int _sizeInBytes){
        glCreateBuffers(1, &m_bufferID);
        glNamedBufferStorage(m_bufferID, _sizeInBytes, nullptr, GL_DYNAMIC_STORAGE_BIT);
    } 

    VertexBuffer::~VertexBuffer(){
        glDeleteBuffers(1, &m_bufferID);
    }
}