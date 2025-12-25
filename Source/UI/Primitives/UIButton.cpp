#include "UIButton.h"
#include "../../Renderer/Texture.h"
#include "UIElement.h"

UIButton::UIButton(UIElement& parent, const std::string& text, std::function<void()> onClick, class Font* font,
                   const Vector2 &offset, float scale, float angle, int pointSize, const unsigned wrapLength)
        :UIText(parent, text, font, offset, scale, angle, pointSize, wrapLength)
        ,mOnClick(onClick)
        ,mHighlighted(false)
{
    mNormalColor = mTextColor;
}

UIButton::~UIButton()
{

}


void UIButton::OnClick()
{
    // Call attached handler, if it exists
    if (mOnClick) {
        mOnClick();
    }
}

void UIButton::Draw(class Shader* shader)
{
    if(mHighlighted) {
        SetTextColor(mTextHighlightColor);
    }
    else {
        SetTextColor(mNormalColor);
    }

    UIText::Draw(shader);
}