#include "IndexBuffer.h"

namespace DEngine{
    IndexBuffer::IndexBuffer(unsigned int* _data, unsigned int _sizeInBytes){
        glCreateBuffers(1, &m_indexBufferID);

        glNamedBufferStorage(m_indexBufferID, _sizeInBytes, _data, GL_DYNAMIC_STORAGE_BIT);
    }
    IndexBuffer::~IndexBuffer(){
        glDeleteBuffers(1, &m_indexBufferID);
    }
}