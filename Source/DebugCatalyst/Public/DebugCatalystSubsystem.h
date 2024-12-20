// © 2024 Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HAL/IConsoleManager.h"
#include "DebugCatalystSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnProfileUpdateDelegate, FName, Profile, bool, bValue);

/**
 * 
 */
UCLASS()
class DEBUGCATALYST_API UDebugCatalystSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UPROPERTY(BlueprintAssignable, Category = "Debug Catalyst")
	FOnProfileUpdateDelegate OnProfileUpdated;

	UFUNCTION(BlueprintCallable, Category = "DebugCatalyst")
	bool GetProfileValue(FName Profile);

	void OnProfileCommand(const TArray<FString>& Args, UWorld* World);

private:

	UPROPERTY()
	TMap<FName, bool> Profiles;

	IConsoleCommand* Command;
};
