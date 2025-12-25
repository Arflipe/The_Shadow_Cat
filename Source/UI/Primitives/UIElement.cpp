#include "UIElement.h"
#include "../../Game.h"
#include "../../Renderer/Renderer.h"

UIElement::UIElement(const Vector2 &offset, const float scale, const float angle, int drawOrder)
        :mOffset(offset)
        ,mAbsolutePos(offset)
        ,mScale(scale)
        ,mAngle(angle)
        ,mIsVisible(true)
        ,mDrawOrder(drawOrder)
        ,mParent(nullptr)
{
}

UIElement::UIElement(UIElement& parent, const Vector2 &offset, const float scale, const float angle)
    :mParent(&parent)
    ,mOffset(offset)
    ,mScale(scale)
    ,mAngle(angle)
    ,mIsVisible(true)
{
    parent.AddChild(this);
    mDrawOrder = parent.GetDrawOrder() + 1;
}

UIElement::~UIElement()
{
    while (!mChildren.empty())
        delete mChildren.back();
    
    Game::Instance().GetRenderer()->RemoveUIElement(this);
    if (mParent) mParent->RemoveChild(this);
}

void UIElement::DrawTree(class Shader* shader)
{
    ResolvePosition();
    Draw(shader);
    for (auto child : mChildren)
        if (child->IsVisible())
            child->DrawTree(shader);
}

void UIElement::AddChild(UIElement* child)
{
    mChildren.push_back(child);
}

void UIElement::RemoveChild(UIElement* child)
{
    auto it = std::find(mChildren.begin(), mChildren.end(), child);
    if (it != mChildren.end()) mChildren.erase(it);
}

void UIElement::ResolvePosition()
{
    if (!mParent) return;
    mAbsolutePos = mParent->GetAbsolutePos() + mOffset * mParent->GetScale();
}