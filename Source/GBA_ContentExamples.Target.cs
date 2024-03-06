// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GBA_ContentExamplesTarget : TargetRules
{
	public GBA_ContentExamplesTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		// bUseUnityBuild = false;
		// bUsePCHFiles = false;

		ExtraModuleNames.Add("GBA_ContentExamples");
	}
}