// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TwoBetterThanOne : ModuleRules
{
	public TwoBetterThanOne(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
