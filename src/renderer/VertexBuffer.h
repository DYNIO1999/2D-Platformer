#ifndef _SRC_RENDERER_VERTEX_BUFFER_H_
#define _SRC_RENDERER_VERTEX_BUFFER_H_
#include <memory>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace DEngine{
class VertexBuffer
{
public:
    VertexBuffer(void* _data, unsigned int _sizeInBytes);
    VertexBuffer(unsigned int _sizeInBytes);
    ~VertexBuffer();

    void SetSubData(void *_data, unsigned int _sizeInBytes);

    unsigned int GetID() const {return m_bufferID;}

    static std::shared_ptr<VertexBuffer> Create(void* _data, unsigned int _sizeInBytes){
        std::shared_ptr<VertexBuffer> result = std::make_shared<VertexBuffer>(_data, _sizeInBytes);
        return result;
    }
    static std::shared_ptr<VertexBuffer> Create(unsigned int _sizeInBytes)
    {
        std::shared_ptr<VertexBuffer> result = std::make_shared<VertexBuffer>(_sizeInBytes);
        return result;
    }



private:
    unsigned int m_bufferID; 
};
}
#endif