#pragma once

#include <string>
#include <vector>

#include "UIScreen.h"
#include "../../Actors/Characters/ShadowCat.h"
#include "../../Event.h"

class AbilityCard;

class UpgradeHUD : public UIScreen
{
public:
    UpgradeHUD(UIElement& parent, const std::string& fontName);

    static Event<AbilityCard*> OnCardSelected;

    void Update(float deltaTime) override;
    void OnActiveKeyPress(int key) override;

private:
    void RefreshCards();
    void UpdateSelectedCard(int indexChange);

    UIImage* mBackImage = nullptr;
    std::vector<UpgradeInfo> mCurrentUpgradeInfo;
    std::vector<AbilityCard*> mAbilityCards;
    int mSelectedCardIndex;
};
