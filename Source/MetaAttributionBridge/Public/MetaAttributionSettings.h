#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "MetaAttributionSettings.generated.h"

UCLASS(Config=Engine, defaultconfig, meta=(DisplayName="Meta Attribution Bridge"))
class METAATTRIBUTIONBRIDGE_API UMetaAttributionSettings : public UDeveloperSettings
{
    GENERATED_BODY()

public:
    UMetaAttributionSettings();

    virtual FName GetCategoryName() const override;

    /** The Facebook App ID for this application. */
    UPROPERTY(Config, EditAnywhere, Category = "Facebook Settings")
    FString FacebookAppId;

    /** The Facebook Client Token for this application. */
    UPROPERTY(Config, EditAnywhere, Category = "Facebook Settings")
    FString FacebookClientToken;
};
