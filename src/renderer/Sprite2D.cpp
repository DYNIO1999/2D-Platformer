#include "Sprite2D.h"

namespace LightInDarkness
{
    std::shared_ptr<Sprite2D> Sprite2D::Create(std::shared_ptr<Texture> _texture, 
    const glm::vec2 &_spritePosition, const glm::vec2 &_spriteSize){
        std::shared_ptr<Sprite2D> result = std::make_shared<Sprite2D>(_texture,_spritePosition, _spriteSize);
        return result;
    }
    Sprite2D::Sprite2D(std::shared_ptr<Texture> _texture, const glm::vec2 &_spritePosition, const glm::vec2 &_spriteSize){
        
    }
}