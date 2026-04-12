#include "UIImage.h"
#include "../../Renderer/Texture.h"
#include "../../Renderer/Shader.h"
#include "../../Renderer/Renderer.h"
#include "../../Actors/Actor.h"
#include "../../Game.h"
#include "../../GameConstants.h"


UIImage::UIImage(UIElement& parent, const Vector2 &offset, const float scale, const float angle)
        :UIElement(parent, offset, scale, angle)
        ,mTexture(nullptr)
{

}

UIImage::UIImage(UIElement& parent, const std::string &imagePath, const Vector2 &offset, const float scale, const float angle)
        :UIElement(parent, offset, scale, angle)
{
    SetImage(imagePath);
}

UIImage::~UIImage()
{

}

void UIImage::SetImage(const std::string &imagePath)
{
    mTexture = Game::Instance().GetRenderer()->GetTexture(imagePath);
}

void UIImage::Draw(class Shader* shader)
{
    if(!IsVisible())
        return;

    float absWidth = mTexture ? static_cast<float>(mTexture->GetWidth()) : 32.0f;
    float absHeight = mTexture ? static_cast<float>(mTexture->GetHeight()) : 32.0f;

    Matrix4 scaleMat = Matrix4::CreateScale(absWidth * mScale, absHeight * mScale, 1.0f);
    Matrix4 rotMat = Matrix4::CreateRotationZ(mAngle);
    Matrix4 transMat = Matrix4::CreateTranslation(Vector3(mAbsolutePos.x, mAbsolutePos.y, 0.0f));

    // Set world transform
    Matrix4 world = scaleMat * rotMat * transMat;
    shader->SetMatrixUniform("uWorldTransform", world);

    shader->SetVectorUniform("uColor", Color::White);
    shader->SetVectorUniform("uTexRect", Vector4::UnitRect);
    shader->SetVectorUniform("uCameraPos", Vector2::Zero);

    // Set uTextureFactor
    shader->SetFloatUniform("uTextureFactor", mTexture ? 1.0f : 0.0f);

    // Set current texture
    if (mTexture) mTexture->SetActive();

    // Draw quad
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}