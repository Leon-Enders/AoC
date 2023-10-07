// Created by Leon Enders

using UnrealBuildTool;
using System.Collections.Generic;

public class AoCTarget : TargetRules
{
	public AoCTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "AoC" } );
	}
}
