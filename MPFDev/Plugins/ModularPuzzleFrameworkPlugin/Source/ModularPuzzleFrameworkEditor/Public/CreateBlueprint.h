// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CreateBlueprint.generated.h"

/**
 * 
 */
UCLASS()
class MODULARPUZZLEFRAMEWORKEDITOR_API UCreateBlueprint : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Create Blueprint")
	static UBlueprint* CreateBlueprint(FString BlueprintPath, TSubclassOf<UObject> ParentClass, bool& bOutSucces, FString& OutInfoMessage);
};
