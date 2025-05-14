// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <ModPuzFram/Public/MPFDebugDrawTestActor.h>
#include "Debug/DebugDrawComponent.h"
#include "MPFDebugDrawComponent.generated.h"

class MODULARPUZZLEFRAMEWORKEDITOR_API FMPFDebugSceneProxy final : public FDebugRenderSceneProxy
{
public:
	FMPFDebugSceneProxy(const UPrimitiveComponent* InComponent);

protected:
	virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;


	/*
	// These functions are only necessary if you want to add your own member variables to your SceneProxy struct that are dynamically allocated
	virtual uint32 GetMemoryFootprint(void) const override { return sizeof(*this) + GetAllocatedSizeInternal(); }
	uint32 GetAllocatedSizeInternal(void) const
	{
		// For example, if you add your own Arcs array containing the arcs you want to draw then you'd add something like this
		return FDebugRenderSceneProxy::GetAllocatedSize() + Arcs.GetAllocatedSize()
	}
	*/
};
/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MODULARPUZZLEFRAMEWORKEDITOR_API UMPFDebugDrawComponent : public UDebugDrawComponent
{
	GENERATED_BODY()
	
public:
	UMPFDebugDrawComponent();

	virtual FDebugRenderSceneProxy* CreateDebugSceneProxy() override;

	void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction);

	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;

	virtual bool ShouldRecreateProxyOnUpdateTransform() const override { return true; }
};
