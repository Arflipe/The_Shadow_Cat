#pragma once


#include "UIElement.h"
#include "../../Math.h"

class UIRect : public UIElement
{
public:
    UIRect(UIElement& parent, const Vector2 &offset, const Vector2 &size, float scale = 1.0f, float angle = 0.0f);
    ~UIRect();

    void Draw(class Shader* shader) override;
    void SetColor(const Vector4 &color) { mColor = color; }

protected:
    Vector2 mSize;
    Vector4 mColor;
};

