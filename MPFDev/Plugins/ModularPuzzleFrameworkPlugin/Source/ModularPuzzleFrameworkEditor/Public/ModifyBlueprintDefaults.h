// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorAssetLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "ModifyBlueprintDefaults.generated.h"

/**
 * 
 */
UCLASS()
class MODULARPUZZLEFRAMEWORKEDITOR_API UModifyBlueprintDefaults : public UBlueprintGeneratedClass
{
	GENERATED_BODY()
	
	public:
	UFUNCTION(BlueprintCallable, Category = "Editor|Blueprint Modification")
	static void ModifyBlueprintEnum(UBlueprint* Blueprint, FName EnumPropertyName, uint8 NewEnumValue);
};
