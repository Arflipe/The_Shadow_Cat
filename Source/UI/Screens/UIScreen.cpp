// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "UIScreen.h"
#include "../../UIManager.h"
#include "../../Game.h"
#include "../../Renderer/Renderer.h"

UIScreen::UIScreen(UIElement& parent, const std::string& fontName)
    :UIElement(parent)
    ,mPos(0.f, 0.f)
    ,mSize(0.f, 0.f)
    ,mSelectedButtonIndex(-1)
{
    UIManager::Instance().GetRootUI()->AddScreen(this);
    mFont = Game::Instance().GetRenderer()->GetFont(fontName);
}

UIScreen::~UIScreen()
{
    for (auto t : mTexts) {
        delete t;
    }
    mTexts.clear();

    for (auto b : mButtons) {
        delete b;
    }
    mButtons.clear();

    for (auto img : mImages) {
        delete img;
    }
    mImages.clear();

    for (auto rect : mRects) {
        delete rect;
    }
    mRects.clear();
}

void UIScreen::Update(float deltaTime)
{
    
}

void UIScreen::HandleKeyPress(int key, bool isActive)
{
    OnKeyPress(key);
    if (isActive) OnActiveKeyPress(key);
}

void UIScreen::SetIsVisible(bool isVisible)
{
    UIElement::SetIsVisible(isVisible);
    if (isVisible) UIManager::Instance().PushUI(this);
    else UIManager::Instance().RemoveUI(this);
}

UIText* UIScreen::AddText(const std::string& name, const Vector2& offset, float scale, float angle, const int pointSize, const int unsigned wrapLength, int drawOrder)
{
    UIText* text = new UIText(*this, name, mFont, offset, scale, angle, pointSize, wrapLength);
    mTexts.emplace_back(text);
    
    return text;
}

UIButton* UIScreen::AddButton(const std::string& name, std::function<void()> onClick, const Vector2& offset, float scale, float angle, const int pointSize, const int unsigned wrapLength, int drawOrder)
{
    UIButton* button = new UIButton(*this, name, onClick, mFont, offset, scale, angle, pointSize, wrapLength);
    mButtons.emplace_back(button);

    return button;
}

UIImage* UIScreen::AddImage(const std::string& imagePath, const Vector2& offset, float scale, float angle, int drawOrder)
{
    UIImage* image = new UIImage(*this, imagePath, offset, scale, angle);
    mImages.emplace_back(image);

    return image;
}

UIRect *UIScreen::AddRect(const Vector2 &offset, const Vector2 &size, float scale, float angle, int drawOrder)
{
    UIRect* rect = new UIRect(*this, offset, size, scale, angle);
    mRects.emplace_back(rect);

    return rect;
}