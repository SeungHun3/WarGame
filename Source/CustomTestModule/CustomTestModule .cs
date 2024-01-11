//using System.IO;
//using System.Reflection;
using UnrealBuildTool;

public class CustomTestModule : ModuleRules
{
	public CustomTestModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicIncludePaths.AddRange(
			new string[]
			{
				Path.Combine(ModuleDirectory, "Public")
			}
		);


		PrivateIncludePaths.AddRange(
			new string[]
			{
				Path.Combine(ModuleDirectory, "Private")
			}
		);


		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core"
			}
		);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine"
			}
		);

		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{

			}
		);
	}
}