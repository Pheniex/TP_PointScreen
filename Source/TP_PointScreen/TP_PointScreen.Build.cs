// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TP_PointScreen : ModuleRules
{
	public TP_PointScreen(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput",
			"UMG",
			"Slate"
		});
	}
}
