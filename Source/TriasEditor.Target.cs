// Dactyl Games, all rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TriasEditorTarget : TargetRules
{
	public TriasEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "Trias" } );
	}
}
