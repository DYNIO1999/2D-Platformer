#include "VertexBuffer.h"
#include "../core/Logger.h"
namespace DEngine
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

    void VertexBuffer::SetSubData(void *_data, unsigned int _sizeInBytes)
    {
        glNamedBufferSubData(m_bufferID, 0, _sizeInBytes, reinterpret_cast<float *>(_data));

    }
}