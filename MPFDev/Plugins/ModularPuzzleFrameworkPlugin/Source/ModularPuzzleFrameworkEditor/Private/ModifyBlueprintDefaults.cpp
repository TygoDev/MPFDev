#include "ModifyBlueprintDefaults.h"
#include "Engine/BlueprintGeneratedClass.h"

void UModifyBlueprintDefaults::ModifyBlueprintEnum(UBlueprint* Blueprint, FName EnumPropertyName, uint8 NewEnumValue)
{
    if (!Blueprint)
    {
        UE_LOG(LogTemp, Warning, TEXT("ModifyBlueprintEnum: Blueprint is null!"));
        return;
    }

    UClass* BPClass = Blueprint->GeneratedClass;
    if (!BPClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("ModifyBlueprintEnum: Blueprint class is null!"));
        return;
    }

    UObject* DefaultObject = BPClass->GetDefaultObject();
    if (!DefaultObject)
    {
        UE_LOG(LogTemp, Warning, TEXT("ModifyBlueprintEnum: DefaultObject is null!"));
        return;
    }

    // Find the enum property by name
    FProperty* Property = BPClass->FindPropertyByName(EnumPropertyName);
    if (!Property || !Property->IsA<FByteProperty>())  // Enums are stored as bytes
    {
        UE_LOG(LogTemp, Warning, TEXT("ModifyBlueprintEnum: Property not found or not an enum!"));
        return;
    }

    // Set the new enum value
    FByteProperty* EnumProperty = CastField<FByteProperty>(Property);
    EnumProperty->SetPropertyValue_InContainer(DefaultObject, NewEnumValue);

    // Mark package as dirty so changes are saved
    DefaultObject->MarkPackageDirty();
    UE_LOG(LogTemp, Log, TEXT("ModifyBlueprintEnum: Successfully modified enum property!"));

    // Save the asset to keep the changes
    UEditorAssetLibrary::SaveAsset(Blueprint->GetPathName());
}
