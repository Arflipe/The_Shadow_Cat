// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <list>

#include "../../Math.h"
#include "../Primitives/UIText.h"
#include "../Primitives/UIButton.h"
#include "../Primitives/UIImage.h"
#include "../Primitives/UIRect.h"

class UIScreen : public UIElement
{
public:
    UIScreen(UIElement& parent, const std::string& fontName);
    virtual ~UIScreen();

    // UIScreen subclasses can override these
    virtual void Update(float deltaTime);
    
    void HandleKeyPress(int key, bool isActive = false);

    virtual void OnActiveKeyPress(int key) { }
    virtual void OnKeyPress(int key) { }

    void SetIsVisible(bool isVisible) override;

    // Add a button to this screen
    UIButton* AddButton(const std::string& name, std::function<void()> onClick, const Vector2& offset, float scale = 1.0f, float angle = 0.0f, const int pointSize = 40, const int unsigned wrapLength = 1024, int drawOrder = 100);
    UIText* AddText(const std::string& name, const Vector2& offset, float scale = 1.0f, float angle = 0.0f, const int pointSize = 40, const int unsigned wrapLength = 1024, int drawOrder = 100);
    UIImage* AddImage(const std::string& imagePath, const Vector2& offset, float scale = 1.0f, float angle = 0.0f, int drawOrder = 100);
    UIRect* AddRect(const Vector2 &offset, const Vector2 &size, float scale = 1.0f, float angle = 0.0f, int drawOrder = 100);

protected:
    // Sets the mouse mode to relative or not
    class Font* mFont;

    // Configure positions
    Vector2 mPos;
    Vector2 mSize;

    // List of buttons, texts, and images
    int mSelectedButtonIndex;
    std::vector<UIButton *> mButtons;
    std::vector<UIText *> mTexts;
    std::vector<UIImage *> mImages;
    std::vector<UIRect *> mRects;
};
