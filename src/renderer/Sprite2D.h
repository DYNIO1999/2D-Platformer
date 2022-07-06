#ifndef _SRC_RENDERER_SPRITE2D_H_
#define _SRC_RENDERER_SPRITE2D_H_
#include <glm/glm.hpp>

#include "Texture.h"
namespace LightInDarkness{
class Sprite2D
{
public:
    Sprite2D(std::shared_ptr<Texture> _texture, const glm::vec2 &_spritePosition, const glm::vec2 &_spriteSize);
    
    
    
    static std::shared_ptr<Sprite2D> Create(std::shared_ptr<Texture> _texture, 
    const glm::vec2 &_spritePosition, const glm::vec2& _spriteSize);

    std::shared_ptr<Texture> GetTexture() const {return m_texture;}


private:
    std::shared_ptr<Texture> m_texture;
    glm::vec2 m_textureCords[2];

};
}
#endif