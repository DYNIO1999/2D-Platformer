#ifndef _SRC_RENDERER_VERTEX_BUFFER_LAYOUT_H_
#define _SRC_RENDERER_VERTEX_BUFFER_LAYOUT_H_

#include <vector>



#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace LightInDarkness{


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

private:
    std::vector<VertexBufferElement> m_elements;
    unsigned int m_stride; 
};

}
#endif