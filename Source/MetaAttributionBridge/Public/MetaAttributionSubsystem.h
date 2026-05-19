// Copyright Valii Studio 2026. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MetaAttributionSubsystem.generated.h"

/**
 * Subsystem for handling Meta (Facebook) SDK events in the game.
 */
UCLASS()
class METAATTRIBUTIONBRIDGE_API UMetaAttributionSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    // UGameInstanceSubsystem interface
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    /**
     * Initialize Facebook SDK for CPI Tracking
     */
    UFUNCTION(BlueprintCallable, Category = "Analytics|Meta")
    void InitializeFacebookSDK();

    /**
     * Log Custom Facebook Event (for AEO)
     */
    UFUNCTION(BlueprintCallable, Category = "Analytics|Meta")
    void LogFacebookEvent(FString EventName);
};
