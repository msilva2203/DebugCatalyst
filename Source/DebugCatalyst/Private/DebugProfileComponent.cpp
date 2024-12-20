// © 2024 Marco Silva


#include "DebugProfileComponent.h"

UDebugProfileComponent::UDebugProfileComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UDebugProfileComponent::BeginPlay()
{
	Super::BeginPlay();

	DebugCatalystSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDebugCatalystSubsystem>();
	if (DebugCatalystSubsystem)
	{
		DebugCatalystSubsystem->OnProfileUpdated.AddDynamic(this, &UDebugProfileComponent::OnDebugProfileUpdated);
		bDebugProfileValue = DebugCatalystSubsystem->GetProfileValue(DebugProfile);
		OnComponentProfileUpdated.Broadcast(bDebugProfileValue);
	}
	else
	{
		bDebugProfileValue = false;
	}
}

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

