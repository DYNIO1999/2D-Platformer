#include "Texture.h"
#include <glad/glad.h>

#include "core/Logger.h"
#include "core/Assert.h"
namespace LightInDarkness
{

    Texture::Texture(const std::string &_path)
    :m_path(_path)
    {
        stbi_set_flip_vertically_on_load(1);
        unsigned char* data = stbi_load(m_path.c_str(), &m_width,&m_height, &m_channels,0);

        if(!data){
            APP_ERROR("Texture loading failed! Path:{}", m_path);
            APP_ASSERT_NO_INFO(false);
        }else{
            if(m_channels==4){
                m_texutreFormat = GL_RGBA8;
                m_dataFormat = GL_RGBA;
            }else if(m_channels==3){
                m_texutreFormat = GL_RGB8;
                m_dataFormat = GL_RGB;
            }
            APP_INFO("Texture loading succeded! Path:{}", m_path);
            glCreateTextures(GL_TEXTURE_2D, 1, &m_textureID);

            glTextureParameteri(m_textureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTextureParameteri(m_textureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTextureParameteri(m_textureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTextureParameteri(m_textureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

            glTextureStorage2D(m_textureID, 1, m_texutreFormat, m_width, m_height);
            glTextureSubImage2D(m_textureID, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
    }
    Texture::~Texture(){

    }

    std::shared_ptr<Texture> Texture::Create(const std::string &_path)
    {
        std::shared_ptr<Texture> result = std::make_shared<Texture>(_path);
        return result;
    }
    void Texture::Bind(uint _slot)
    {
        m_slot = _slot;
        glBindTextureUnit(m_slot, m_textureID);
    }
}  
