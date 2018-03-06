// Copyright 2018 Meta Creative Media, LLC

#pragma once

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
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
		float Reach = 100.f;

		UPhysicsHandleComponent* PhysicsHandle = nullptr;
		UInputComponent* InputComponent = nullptr;

		// Raycast and Grab what's in reach.
		void Grab();
		void Release();

		// Find attached physics	
		void FindPhysicsHandleComponent();

		// Setup assumed attached input component
		void SetupInputComponent();

		// Return hit for first physics body in reach
		FHitResult GetFirstPhysicsBodyInReach() const;
		
		FVector GetReachLineStart() const;
		FVector GetReachLineEnd() const;
};
