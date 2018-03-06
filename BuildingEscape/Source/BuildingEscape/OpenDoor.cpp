// Copyright 2018 Meta Creative Media, LLC

#include "BuildingEscape.h"
#include "OpenDoor.h"
#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();	
	Owner = GetOwner();
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate"), *GetOwner()->GetName())
	}
}

void UOpenDoor::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f), ETeleportType::None);
}

void UOpenDoor::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f), ETeleportType::None);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the trigger volume
	//If the ActorThatOpens is in the volume
	if (GetTotalMassOfActorsOnPlate() > 30.f) // TODO make into a parameter
	{
		OpenDoor();
		DoorLastOpenTime = GetWorld()->GetTimeSeconds();
	}

	//Check if it's time to close the door.
	if (GetWorld()->GetTimeSeconds() - DoorLastOpenTime > CloseDoorDelay)
	{
		CloseDoor();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.0f;

	// Find all the overlapping actors
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	// Iterate through them adding their masses
	for (const auto* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		//UE_LOG(LogTemp, Warning, TEXT("%s is on the pressure plate."), *Actor->GetName())
	}

	return TotalMass;
}

