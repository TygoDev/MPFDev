// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MPFDebugDrawTestActor.generated.h"

UCLASS(Abstract)
class MODPUZFRAM_API AMPFDebugDrawTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMPFDebugDrawTestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<AActor>> TestChildren;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> MyRootComponent;

};
