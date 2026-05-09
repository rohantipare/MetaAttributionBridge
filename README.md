# Meta Attribution Bridge Plugin

> [!WARNING]
> **Platform Support**: This plugin is specifically designed and supported only for the **Android** platform.

## Overview

The **Meta Attribution Bridge** is a lightweight, zero-code plugin that integrates the official Meta (Facebook) SDK into Unreal Engine 5. 

If you are running user acquisition or ad campaigns on Facebook, Instagram, or the Meta Audience Network, you need a way to track **Cost Per Install (CPI)** and measure **Return on Ad Spend (ROAS)**. This plugin acts as the bridge between your Unreal Engine game and the Meta Ads ecosystem.

### Key Intentions & Features:
- **Install Tracking (CPI):** Automatically notifies Meta the moment a user installs and opens your game from an ad, allowing your campaigns to accurately report app installs.
- **App Event Optimization (AEO):** Seamlessly log custom in-game events (like `MatchStarted`, `TutorialCompleted`, or `PurchaseMade`). You can use these events in the Meta Ads Manager to optimize your ad campaigns to target high-value players.
- **Zero-Code Setup:** No complicated C++ or blueprinting is required for basic install tracking. Just drop in your App ID in the Project Settings, and the plugin automatically handles the Android JNI initialization, background threading, and lifecycle hooks for you.

## Setup

1. Enable the plugin in your project (Edit -> Plugins -> Meta Attribution Bridge).
2. Go to **Edit -> Project Settings**.
3. Scroll down to **Plugins** and select **Meta Attribution Bridge**.
4. Enter your **Facebook App ID** and **Facebook Client Token** in the provided fields.

These settings will be dynamically injected into the Android manifest and string resources during the build process.

## Usage

### C++
You can access the subsystem anywhere in your game to log events:

```cpp
#include "MetaAttributionSubsystem.h"

// ...

if (UMetaAttributionSubsystem* MetaAttribution = GetWorld()->GetGameInstance()->GetSubsystem<UMetaAttributionSubsystem>())
{
    MetaAttribution->LogFacebookEvent("MyCustomEvent");
}
```

### Blueprints
The subsystem is fully exposed to Blueprints. You can find the following nodes under the **Analytics | Meta** category:
- `Log Facebook Event`

*(Note: The Facebook SDK automatically initializes itself when the game starts, so you do not need to call any initialization nodes manually).*

## Packaging
The plugin uses Unreal Plugin Language (UPL) to automatically:
- Download the required Facebook core Android libraries via gradle.
- Inject the necessary permissions (`AD_ID`).
- Add the `meta-data` tags with your App ID and Client Token to the `AndroidManifest.xml`.

## How to Verify (Debugging)

To confirm that the Meta SDK is successfully initializing and sending events on Android, you can filter your device's **Logcat** output for the plugin's dedicated log category: `LogMetaAttribution`.

You should see logs similar to this when the game boots:
```text
D/UE5: [YYYY.MM.DD-HH.MM.SS:MS][  0]LogMetaAttribution: MetaAttributionSubsystem Initialized
D/UE5: [YYYY.MM.DD-HH.MM.SS:MS][  0]LogMetaAttribution: Initializing Facebook SDK...
D/UE5: [YYYY.MM.DD-HH.MM.SS:MS][  0]LogMetaAttribution: Facebook SDK activateApp called successfully.
```

And when a custom event is logged:
```text
D/UE5: [YYYY.MM.DD-HH.MM.SS:MS][123]LogMetaAttribution: Attempting to log Facebook Event: MatchStarted
D/UE5: [YYYY.MM.DD-HH.MM.SS:MS][123]LogMetaAttribution: Successfully logged Facebook Event: MatchStarted
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details. This makes it completely free to use in both personal and commercial projects.

## Support

If you encounter any issues, bugs, or have feature requests, please open an issue on the [GitHub Repository](https://github.com/rohantipare/MetaAttributionBridge/issues).
