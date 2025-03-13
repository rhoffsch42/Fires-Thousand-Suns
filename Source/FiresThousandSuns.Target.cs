// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class FiresThousandSunsTarget : TargetRules
{
	public FiresThousandSunsTarget(TargetInfo Target) : base(Target)
	{
        Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V3;
		//IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1;
		ExtraModuleNames.Add("FiresThousandSuns");

        // Added lines
        //BuildEnvironment = TargetBuildEnvironment.Unique;
        //bUseLoggingInShipping = true;
        //bOverrideBuildEnvironment = true;
    }
}
