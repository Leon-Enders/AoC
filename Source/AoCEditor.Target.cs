// Created by Leon Enders

using UnrealBuildTool;
using System.Collections.Generic;

public class AoCEditorTarget : TargetRules
{
	public AoCEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "AoC" } );
	}
}
