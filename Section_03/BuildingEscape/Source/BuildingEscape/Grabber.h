// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:

	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	void BeginPlay() override;

	// Called every frame
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	// find attached physics handle component.
	void FindPhysicsHandleComponent();

	// setup attached input component
	void SetupInputComponent();

	// the reach distance of the player, used to raycast.
	float Reach = 150.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	// ray-cast and grab what's in reach.
	void Grab();

	// release the grabbed physics handle.
	void Release();

	// return hit for first physics body in reach.
	FHitResult GetFirstPhysicsBodyInReach() const;

	// returns current start of reach line.
	FVector GetReachLineStart() const;

	// return current end of reach line.
	FVector GetReachLineEnd() const;
};
