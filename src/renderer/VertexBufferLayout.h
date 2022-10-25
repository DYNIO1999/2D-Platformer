#ifndef _SRC_RENDERER_VERTEX_BUFFER_LAYOUT_H_
#define _SRC_RENDERER_VERTEX_BUFFER_LAYOUT_H_

#include <vector>



#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace DEngine{


struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalised;

    static unsigned int GetSizeType(unsigned int _type){
        switch (_type)
        {
        case GL_FLOAT:
            return 4;
        }
        return 0;
    }
};

class VertexBufferLayout
{
public:
    VertexBufferLayout():m_stride(0){

    }
    ~VertexBufferLayout(){
        m_elements.clear();
    }

    template <typename T>
    void Push(unsigned int _count);
    template <>
    void Push<float>(unsigned int _count)
    {
        m_elements.push_back({GL_FLOAT, _count, GL_FALSE});
        m_stride += _count * VertexBufferElement::GetSizeType(GL_FLOAT);
        
    }

    unsigned int GetStride() const { return m_stride;}
    unsigned int GetSize() const 
    { 
        unsigned int size{0};
        for (const auto &item : m_elements)
        {
            size+=item.count;
        }
        return size;
    }
    std::vector<VertexBufferElement>& GetElements(){return m_elements;};

    std::vector<VertexBufferElement>::iterator begin() { return m_elements.begin(); }
    std::vector<VertexBufferElement>::iterator end() { return m_elements.end(); }

    static std::shared_ptr<VertexBufferLayout> Create(){
        std::shared_ptr<VertexBufferLayout> result = std::make_shared<VertexBufferLayout>();
        return result;
    }

private:
    std::vector<VertexBufferElement> m_elements;
    unsigned int m_stride; 
};

}
#endif