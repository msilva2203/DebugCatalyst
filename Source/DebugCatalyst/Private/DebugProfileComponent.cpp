// © 2024 Marco Silva


#include "DebugProfileComponent.h"

// Sets default values for this component's properties
UDebugProfileComponent::UDebugProfileComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UDebugProfileComponent::BeginPlay()
{
	Super::BeginPlay();

	DebugCatalystSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDebugCatalystSubsystem>();
	if (DebugCatalystSubsystem)
	{
		DebugCatalystSubsystem->OnProfileUpdated.AddDynamic(this, &UDebugProfileComponent::OnDebugProfileUpdated);
		bool bValue = DebugCatalystSubsystem->GetProfileValue(DebugProfile);
		OnComponentProfileUpdated.Broadcast(bValue);
	}
}


// Called every frame
void UDebugProfileComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UDebugProfileComponent::OnDebugProfileUpdated(FName Profile, bool bValue)
{
	if (Profile == DebugProfile)
	{
		bDebugProfileValue = bValue;
		OnComponentProfileUpdated.Broadcast(bValue);
	}
}

bool UDebugProfileComponent::IsDebugProfileActive()
{
	return bDebugProfileValue;
}

