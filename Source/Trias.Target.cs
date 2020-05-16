// Dactyl Games, all rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TriasTarget : TargetRules
{
	public TriasTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Trias" } );
	}
}
