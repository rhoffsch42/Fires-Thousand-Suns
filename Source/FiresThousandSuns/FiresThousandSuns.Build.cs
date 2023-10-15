// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FiresThousandSuns : ModuleRules
{
	public FiresThousandSuns(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay",
			"NavigationSystem", "AIModule", "Niagara", "EnhancedInput", "Slate", "AudioWidgets", "SlateCore", "CommonUI",
			"ImageWrapper", "AssetRegistry"
        });
        /*PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Niagara"));*/
	}
}
