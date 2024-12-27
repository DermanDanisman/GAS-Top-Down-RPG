// Copyright Heathrow

using UnrealBuildTool;
using System.Collections.Generic;

public class GAS_TopDownRPGEditorTarget : TargetRules
{
	public GAS_TopDownRPGEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "GAS_TopDownRPG" } );
	}
}
