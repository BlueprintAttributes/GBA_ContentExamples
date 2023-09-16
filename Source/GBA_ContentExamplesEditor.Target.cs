// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GBA_ContentExamplesEditorTarget : TargetRules
{
	public GBA_ContentExamplesEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1;

		// bUseUnityBuild = false;
		// bUsePCHFiles = false;

		ExtraModuleNames.Add("GBA_ContentExamples");
	}
}