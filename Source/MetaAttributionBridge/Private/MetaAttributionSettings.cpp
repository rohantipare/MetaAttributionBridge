// Copyright Valii Studio 2026. All Rights Reserved.

#include "MetaAttributionSettings.h"

UMetaAttributionSettings::UMetaAttributionSettings()
{
    FacebookAppId = TEXT("");
    FacebookClientToken = TEXT("");
}

FName UMetaAttributionSettings::GetCategoryName() const
{
    return FName("Plugins");
}
