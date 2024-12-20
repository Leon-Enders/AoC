// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AoCComponent.h"
#include "GameplayTagContainer.h"
#include "Data/AoCSocketManagerDataAsset.h"
#include "AoCSocketManagerComponent.generated.h"


class UAoCSocketManagerDataAsset;

UCLASS(BlueprintType, ClassGroup=(AoCComponents), meta=(BlueprintSpawnableComponent) )
class AOC_API UAoCSocketManagerComponent : public UAoCComponent
{
	GENERATED_BODY()

public:	

	UAoCSocketManagerComponent();
	virtual void InitializeAoCComponent() override;

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

	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> MainHandComponent;
	
	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> OffHandComponent;

	UPROPERTY(EditAnywhere, Category="AvatarProperties")
	TObjectPtr<UAoCSocketManagerDataAsset> SocketManagerData;
};
