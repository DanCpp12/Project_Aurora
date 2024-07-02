// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Project_Aurora : ModuleRules
{
	public Project_Aurora(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput", "GameplayAbilities" });
		PrivateDependencyModuleNames.AddRange(new string[] { "GameplayTags", "GameplayTasks"});
    }
}
