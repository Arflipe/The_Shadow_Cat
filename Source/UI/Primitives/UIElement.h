#pragma once

#include "../../Math.h"
#include "../../Renderer/Shader.h"
#include <vector>

class UIElement {
public:
    UIElement(const Vector2 &offset = Vector2::Zero, const float scale = 1.0f, const float angle = 0.0f, int drawOrder = 100);
    UIElement(UIElement& parent, const Vector2 &offset = Vector2::Zero, const float scale = 1.0f, const float angle = 0.0f);
    ~UIElement();

    // Getters/setters
    const Vector2& GetOffset() const { return mOffset; }
    void SetOffset(const Vector2 &offset) { mOffset = offset; }

    const Vector2& GetAbsolutePos() const { return mAbsolutePos; }
    void SetAbsolutePos(const Vector2 &absPos) { mAbsolutePos = absPos; }

    float GetScale() const { return mScale; }
    void SetScale(const float scale) { mScale = scale; }

    float GetAngle() const { return mAngle; }
    void SetAngle(const float angle) { mAngle = angle; }

    int GetDrawOrder() const { return mDrawOrder; }
    
    void AddChild(UIElement* child);
    void RemoveChild(UIElement* child);
    
    void DrawTree(class Shader* shader);
    virtual void Draw(class Shader* shader) { };

    virtual void SetIsVisible(bool isVisible) { mIsVisible = isVisible; }
    bool IsVisible() const { return mIsVisible; }
    
protected:
    void ResolvePosition();

    UIElement* mParent = nullptr;
    std::vector<UIElement*> mChildren;

    Vector2 mOffset;
    Vector2 mAbsolutePos = Vector2(0.0f, 0.0f);
    float mScale;
    float mAngle;

    int mDrawOrder;

private:
    bool mIsVisible;
};
