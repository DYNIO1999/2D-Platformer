#ifndef _SRC_RENDERER_INDEX_BUFFER_H_
#define _SRC_RENDERER_INDEX_BUFFER_H_

#include <memory>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace DEngine{
class IndexBuffer
{
public:
    IndexBuffer(unsigned int *_data, unsigned int _sizeInBytes);
    ~IndexBuffer();

    unsigned int GetID() const { return m_indexBufferID;}

    static std::shared_ptr<IndexBuffer> Create(unsigned int *_data, unsigned int _sizeInBytes){
        std::shared_ptr<IndexBuffer> result = std::make_shared<IndexBuffer>(_data,_sizeInBytes);
        return result;
    }
private:
    unsigned int m_indexBufferID;
};
}
#endif
