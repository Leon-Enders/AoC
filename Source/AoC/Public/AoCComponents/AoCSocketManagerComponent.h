// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Ability System/Data/AoCSocketManagerInfo.h"
#include "Components/ActorComponent.h"
#include "Interaction/AoCComponentInterface.h"
#include "AoCSocketManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AOC_API UAoCSocketManagerComponent : public UActorComponent,public IAoCComponentInterface
{
	GENERATED_BODY()

public:	

	UAoCSocketManagerComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void InitializeAoCComponent(FName CharacterName) override;
	FVector GetMainHandSocketLocation(const FGameplayTag& MontageTag)const;
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
