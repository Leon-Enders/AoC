// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Ability System/Data/AoCSocketManagerInfo.h"
#include "Components/ActorComponent.h"
#include "AoCSocketManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AOC_API UAoCSocketManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UAoCSocketManagerComponent();
	void InitializeSocketManagerData(FName CharacterName, USkeletalMeshComponent* Mesh);
	
	FVector GetMainHandSocketLocation(const FGameplayTag& MontageTag)const;
	FVector GetOffHandSocketLocation(const FGameplayTag& MontageTag)const;

	void HandleDeath()const;
protected:
	
	virtual void BeginPlay() override;
	
private:
	
	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> OwnerMesh;

	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> MainHandComponent;
	
	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> OffHandComponent;
	
	FAoCSocketManagerData SocketManagerData;
};
