// Fill out your copyright notice in the Description page of Project Settings.


#include "MPFDebugDrawComponent.h"

namespace MPF {
	namespace Editor {

		// Editor show flag used to turn on and off encounter visualization components
		TCustomShowFlag<> ShowMPFDebug(TEXT("MPFDebug"), true /*DefaultEnabled*/, SFG_Developer, FText::FromString("MPF Debug"));

	}
} // MPF::Editor

FMPFDebugSceneProxy::FMPFDebugSceneProxy(const UPrimitiveComponent* InComponent)
	: FDebugRenderSceneProxy(InComponent)
{
	// When drawing a shape should we draw it as a solid mesh or a wireframe or both
	// Solid mesh can be much more expensive if drawing lots of shapes
	// We can also override the draw type for each individual shape
	DrawType = EDrawType::WireMesh;
	// Draw alpha is more or less useless and doesn't do at all what you'd expect it to do
	// It only applies to the SolidMesh draw type
	// The equation for the final alpha of a shape is (Color.A * DrawAlpha) % 255
	// As you can see DrawAlpha is multiplied by the shape's color (assigned when creating the shape) and then is shoved into a uint8 (which is where the % 255 comes from)
	// This is almost never what you'd actually want when adjusting alpha and I strongly suggest leaving this value at 1 and just adjusting alpha in the shape's color itself
	DrawAlpha = 1;

	//Set the show flag for this scene proxy to be the one we've created
	ViewFlagName = TEXT("MPFDebug");
	ViewFlagIndex = static_cast<uint32>(FEngineShowFlags::FindIndexByName(*ViewFlagName));
}

FPrimitiveViewRelevance FMPFDebugSceneProxy::GetViewRelevance(const FSceneView* View) const
{
	FPrimitiveViewRelevance ViewRelevance;

	ViewRelevance.bDrawRelevance = IsShown(View) && ViewFlagIndex != INDEX_NONE && View->Family->EngineShowFlags.GetSingleFlag(ViewFlagIndex);
	// We need to enable translucency for if we use DrawType SolidMesh
	ViewRelevance.bSeparateTranslucency = ViewRelevance.bNormalTranslucency = IsShown(View);
	ViewRelevance.bDynamicRelevance = true;
	ViewRelevance.bShadowRelevance = IsShadowCast(View);
	return ViewRelevance;
}

UMPFDebugDrawComponent::UMPFDebugDrawComponent() {
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 1.f;
	bTickInEditor = true;

	SetCastShadow(false);
	SetHiddenInGame(true);
	bVisibleInReflectionCaptures = false;
	bVisibleInRayTracing = false;
	bVisibleInRealTimeSkyCaptures = false;
	// Exclude this component from non-editor builds
	bIsEditorOnly = true;

#if WITH_EDITORONLY_DATA
	SetIsVisualizationComponent(true);
#endif;

}

void UMPFDebugDrawComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	MarkRenderStateDirty();
}

FDebugRenderSceneProxy* UMPFDebugDrawComponent::CreateDebugSceneProxy()
{	
	FMPFDebugSceneProxy* Ret = new FMPFDebugSceneProxy(this);

	if (AMPFDebugDrawTestActor* TestActor = Cast<AMPFDebugDrawTestActor>(GetOwner()))
	{
		// Example drawing lines to all the actors we're referencing
		for (const AActor* OtherActor : TestActor->TestChildren)
		{
			if (OtherActor)
			{
				FVector newLocationTestActor = FVector(TestActor->GetActorLocation().X, TestActor->GetActorLocation().Y, TestActor->GetActorLocation().Z + 50);
				FVector newLocationOtherActor = FVector(OtherActor->GetActorLocation().X, OtherActor->GetActorLocation().Y, OtherActor->GetActorLocation().Z + 50);
				Ret->Lines.Emplace(
					newLocationTestActor,
					newLocationOtherActor,
					FColor::Blue,
					4.f
				);
			}
		}
	}

	Ret->Cylinders.Emplace(
		GetComponentLocation(),
		FVector::UpVector,
		12.5f,
		50.f,
		FColor::Blue.WithAlpha(128),
		FDebugRenderSceneProxy::EDrawType::SolidMesh
	);

	/*
	Ret->Spheres.Emplace(
		GetComponentLocation(),
		FVector::UpVector,
		25.f,
		50.f,
		FColor::Red.WithAlpha(128),
		FDebugRenderSceneProxy::EDrawType::SolidMesh
	)
	*/

	// Here's a list of all the types of things you can add to the debug scene proxy
	// Ret->Lines.Emplace(...)
	// Ret->DashedLines.Emplace(...)
	// Ret->ArrowLines.Emplace(...)
	// Ret->Cylinders.Emplace(...)
	// Ret->Stars.Emplace(...)
	// Ret->Boxes.Emplace(...)
	// Ret->Spheres.Emplace(...)
	// Ret->Cones.Emplace(...)
	// Ret->Capsules.Emplace(...)
	// Ret->Texts.Emplace(...)
	// Ret->Meshes.Emplace(...)

	// You can tell the scene proxy to use a different material for any Meshes as long as you set their Color.A to be 255
	// Ret->SolidMeshMaterial = nullptr;

	return Ret;
}

FBoxSphereBounds UMPFDebugDrawComponent::CalcBounds(const FTransform& LocalToWorld) const
{
	FBoxSphereBounds::Builder BoundsBuilder;

	BoundsBuilder += Super::CalcBounds(LocalToWorld);
	// Add initial sphere bounds so if we have no TestChildren our bounds will still be non-zero
	BoundsBuilder += FSphere(GetComponentLocation(), 50.f);
	if (AMPFDebugDrawTestActor* TestActor = Cast<AMPFDebugDrawTestActor>(GetOwner()))
	{
		// Expand our bounds to include all our TestChildren
		for (const AActor* OtherActor : TestActor->TestChildren)
		{
			if (OtherActor)
			{
				BoundsBuilder += OtherActor->GetActorLocation();
			}
		}
	}
	return BoundsBuilder;	
}
