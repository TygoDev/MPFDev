// Fill out your copyright notice in the Description page of Project Settings.


#include "CreateBlueprint.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "KismetCompilerModule.h"
#include "Kismet2/KismetEditorUtilities.h"

UBlueprint* UCreateBlueprint::CreateBlueprint(FString BlueprintPath, TSubclassOf<UObject> ParentClass, bool& bOutSuccess, FString& OutInfoMessage) {
	
	if (StaticLoadObject(UObject::StaticClass(), nullptr, *BlueprintPath) != nullptr) {
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Create Blueprint Failed - An asset already exists at that location. '%s'"), *BlueprintPath);
		return nullptr;
	}

	if (!FKismetEditorUtilities::CanCreateBlueprintOfClass(ParentClass)) {
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Create Blueprint Failed - Parent class is not blueprintable. '%s'"), *BlueprintPath);
		return nullptr;
	}

	UPackage* Package = CreatePackage(*BlueprintPath);
	if (Package == nullptr) {
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Create Blueprint Failed - Failed to create the asset package. Make sure the path is valid. '%s'"), *BlueprintPath);
		return nullptr;
	}

	UClass* BpClass = nullptr;
	UClass* BpGenClass = nullptr;
	FModuleManager::LoadModuleChecked<IKismetCompilerInterface>("KismetCompiler").GetBlueprintTypesForClass(ParentClass, BpClass, BpGenClass);

	UBlueprint* Blueprint = FKismetEditorUtilities::CreateBlueprint(ParentClass, Package, *FPaths::GetBaseFilename(BlueprintPath), BPTYPE_Normal, BpClass, BpGenClass);

	FAssetRegistryModule::AssetCreated(Blueprint);
	Blueprint->MarkPackageDirty();

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Create Blueprint Succeeded - '%s'"), *BlueprintPath);
	return Blueprint;
}

