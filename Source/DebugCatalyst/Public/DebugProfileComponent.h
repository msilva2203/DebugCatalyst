// © 2024 Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DebugCatalystSubsystem.h"
#include "DebugProfileComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnComponentProfileUpdateDelegate, bool, bValue);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEBUGCATALYST_API UDebugProfileComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDebugProfileComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void OnDebugProfileUpdated(FName Profile, bool bValue);

	UFUNCTION(BlueprintPure, CAtegory = "Debug Catalyst")
	bool IsDebugProfileActive();

	UPROPERTY(BlueprintAssignable, Category = "Debug Catalyst")
	FOnComponentProfileUpdateDelegate OnComponentProfileUpdated;

public:

	UPROPERTY(EditDefaultsOnly, Category = "Debug Catalyst")
	FName DebugProfile;

	UPROPERTY(BlueprintReadOnly, Category = "DebugCatalyst")
	UDebugCatalystSubsystem* DebugCatalystSubsystem;

private:

	UPROPERTY()
	bool bDebugProfileValue;

};
