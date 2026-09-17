// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Sci_Fi_Shooter : ModuleRules
{
	public Sci_Fi_Shooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"Niagara"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Sci_Fi_Shooter",
			"Sci_Fi_Shooter/Variant_Platforming",
			"Sci_Fi_Shooter/Variant_Platforming/Animation",
			"Sci_Fi_Shooter/Variant_Combat",
			"Sci_Fi_Shooter/Variant_Combat/AI",
			"Sci_Fi_Shooter/Variant_Combat/Animation",
			"Sci_Fi_Shooter/Variant_Combat/Gameplay",
			"Sci_Fi_Shooter/Variant_Combat/Interfaces",
			"Sci_Fi_Shooter/Variant_Combat/UI",
			"Sci_Fi_Shooter/Variant_SideScrolling",
			"Sci_Fi_Shooter/Variant_SideScrolling/AI",
			"Sci_Fi_Shooter/Variant_SideScrolling/Gameplay",
			"Sci_Fi_Shooter/Variant_SideScrolling/Interfaces",
			"Sci_Fi_Shooter/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
