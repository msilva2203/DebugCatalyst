// © 2024 Marco Silva


#include "DebugCatalystSubsystem.h"

void UDebugCatalystSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	Command = IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("catalyst.debug.profile"),
		TEXT("Toggle the debug profile on or off"),
		FConsoleCommandWithWorldAndArgsDelegate::CreateUObject(this, &UDebugCatalystSubsystem::OnProfileCommand),
		ECVF_Cheat
	);
}

void UDebugCatalystSubsystem::Deinitialize()
{
	Super::Deinitialize();
	
	IConsoleManager::Get().UnregisterConsoleObject(Command);
}

void UDebugCatalystSubsystem::OnProfileCommand(const TArray<FString>& Args, UWorld* World)
{
	if (Args.Num() < 2) return;
	FName Profile = FName(Args[0]);
	bool bNewValue = Args[1].ToBool();
	bool* bCurrent = Profiles.Find(Profile);

	if (bCurrent == nullptr || bNewValue != *bCurrent)
	{
		Profiles.Add(Profile, bNewValue);
		OnProfileUpdated.Broadcast(Profile, bNewValue);
	}
	
}
