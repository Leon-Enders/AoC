// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Ability System/Data/AoCSocketManagerInfo.h"
#include "Components/ActorComponent.h"
#include "AoCSocketManagerComponent.generated.h"


UCLASS(BlueprintType ,ClassGroup=(AoCComponents), meta=(BlueprintSpawnableComponent) )
class AOC_API UAoCSocketManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UAoCSocketManagerComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void InitializeSocketManagerData(FName CharacterName, USkeletalMeshComponent* Mesh);

	UFUNCTION(BlueprintCallable)
	FVector GetMainHandSocketLocation(const FGameplayTag& MontageTag)const;

	UFUNCTION(BlueprintCallable)
	FVector GetOffHandSocketLocation(const FGameplayTag& MontageTag)const;

	void HandleDeath()const;
protected:
	
	virtual void BeginPlay() override;
	
private:
	
	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> OwnerMesh;

	UPROPERTY(Replicated)
	TObjectPtr<USkeletalMeshComponent> MainHandComponent;
	
	UPROPERTY(Replicated)
	TObjectPtr<USkeletalMeshComponent> OffHandComponent;

	UPROPERTY(Replicated)
	FAoCSocketManagerData SocketManagerData;
};
