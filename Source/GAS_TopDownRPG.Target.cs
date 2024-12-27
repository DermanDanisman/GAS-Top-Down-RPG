// Copyright Heathrow

using UnrealBuildTool;
using System.Collections.Generic;

public class GAS_TopDownRPGTarget : TargetRules
{
	public GAS_TopDownRPGTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "GAS_TopDownRPG" } );
	}
}
