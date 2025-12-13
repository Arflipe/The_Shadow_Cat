#pragma once

#include <string>
#include <SDL_image.h>
#include "UIElement.h"

class UIImage : public UIElement
{
public:
    UIImage(UIElement& parent, const Vector2 &offset, float scale = 1.0f, float angle = 0.0f);
    UIImage(UIElement& parent, const std::string &imagePath, const Vector2 &offset, float scale = 1.0f, float angle = 0.0f);

    ~UIImage();

    void Draw(class Shader* shader) override;

protected:
    class Texture* mTexture;
};
