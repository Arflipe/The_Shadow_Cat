#include "UpgradeHUD.h"
#include "../../Game.h"
#include "../../GameConstants.h"
#include "../../Actors/Characters/ShadowCat.h"
#include <string>

#include "../../LevelManager.h"
#include "../AbilityCard.h"

Event<AbilityCard*> UpgradeHUD::OnCardSelected;

UpgradeHUD::UpgradeHUD(UIElement& parent, const std::string& fontName)
    :UIScreen(parent, fontName)
{
    mBackImage = new UIImage(*this, "../Assets/HUD/Background/UpgradeBackground.png", Vector2::Zero, 1.0f, 0.0f);
    float x = AbilityCard::CARD_INIT_X;
    float y = AbilityCard::CARD_Y;
    for (int i = 0; i < GameConstants::UPGRADE_COUNT; ++i)
    {
        AbilityCard* card = new AbilityCard(*mBackImage, mFont, Vector2(x, y), 1.0f, 0.0f);
        x += AbilityCard::CARD_SPACING;
        mAbilityCards.push_back(card);
    }
}

void UpgradeHUD::RefreshCards()
{
    if (LevelManager::Instance().GetPlayer() == nullptr) return;

    std::vector<UpgradeInfo> upgrades = LevelManager::Instance().GetPlayer()->GetRandomUpgrades();
    // Copy for reference
    mCurrentUpgradeInfo = upgrades;

    // Update cards
    for (size_t i = 0; i < upgrades.size(); ++i)
        mAbilityCards[i]->SetAbility(upgrades[i]);

    mSelectedCardIndex = 0;
    OnCardSelected.Invoke(mAbilityCards[0]);
}

void UpgradeHUD::UpdateSelectedCard(int indexChange)
{
    if (mCurrentUpgradeInfo.empty()) return;

    mSelectedCardIndex += indexChange;
    int upgradeCount = static_cast<int>(mCurrentUpgradeInfo.size());
    if (mSelectedCardIndex < 0) mSelectedCardIndex = upgradeCount - 1;
    if (mSelectedCardIndex >= (int)upgradeCount) mSelectedCardIndex = 0;

    OnCardSelected.Invoke(mAbilityCards[mSelectedCardIndex]);
}

void UpgradeHUD::Update(float deltaTime)
{   
    auto player = LevelManager::Instance().GetPlayer();
    if (player == nullptr) return;
    if (player->GetUpgradePoints() < 1) return;

    // Already paused
    if (Game::Instance().IsPaused()) return;

    RefreshCards();
    
    SetIsVisible(true);
    Game::Instance().SetPaused(true);
}


void UpgradeHUD::OnActiveKeyPress(int key)
{
    if (mAbilityCards.empty())
        return;

    switch (key) {
    case SDLK_a:
    case SDLK_LEFT:
        UpdateSelectedCard(-1);
        break;
    
    case SDLK_d:
    case SDLK_RIGHT:
        UpdateSelectedCard(1);
        break;
    
    case SDLK_e:
    case SDLK_SPACE:
    case SDLK_RETURN:
    case SDLK_KP_ENTER:
        LevelManager::Instance().GetPlayer()->SpendUpgradePoint(mCurrentUpgradeInfo[mSelectedCardIndex]);
        SetIsVisible(false);
        Game::Instance().SetPaused(false);
        break;

    default:
        break;
    }
}