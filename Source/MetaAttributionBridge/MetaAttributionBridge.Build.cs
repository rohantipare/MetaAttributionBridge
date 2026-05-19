// Copyright Valii Studio 2026. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class MetaAttributionBridge : ModuleRules
{
	public MetaAttributionBridge(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
		);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
		);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
		);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "DeveloperSettings"
				// ... add private dependencies that you statically link with here ...	
			}
		);

        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PrivateDependencyModuleNames.AddRange(new string[] {
                "Launch",
                "ApplicationCore"
            });

            string uplPath = Path.Combine(ModuleDirectory, "..", "ThirdParty", "MetaSDK", "MetaAttributionBridge_UPL.xml");
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", uplPath);
        }
    }
}
