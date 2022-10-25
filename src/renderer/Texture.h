#ifndef _SRC_RENDERER_TEXTURE_H_
#define _SRC_RENDERER_TEXTURE_H_
#include <string>
#include <stb_image.h>
#include <memory>



namespace DEngine
{
    class Texture
    {
    public:
    Texture() =default;
    Texture(const std::string& _path);
    ~Texture();

    static std::shared_ptr<Texture> Create(const std::string &_path);
    
    void Bind(uint _slot);
    
    uint GetSlot() const{ return m_slot;}

    private:
    uint m_slot;
    std::string m_path;
    uint m_textureID;
    int m_width, m_height, m_channels;
    uint m_texutreFormat,  m_dataFormat;
    };    
}  
#endif
