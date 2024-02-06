// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GBA_ContentExamples : ModuleRules
{
	public GBA_ContentExamples(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks",
			
			"BlueprintAttributes"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			
		});
	}
}
