using UnrealBuildTool;

public class ModularPuzzleFrameworkEditor : ModuleRules
{
    public ModularPuzzleFrameworkEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "ModPuzFram", "CoreUObject", "Engine", "Slate", "SlateCore", "AssetRegistry", "KismetCompiler", "UnrealEd", "RHI", "EditorScriptingUtilities" });
    }
}