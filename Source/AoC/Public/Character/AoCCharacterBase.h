// Created by Leon Enders

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AoCCharacterBase.generated.h"

// Gameplay Ability System
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class AOC_API AAoCCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAoCCharacterBase();
	virtual void Tick(float DeltaTime) override;


	// Gameplay Ability System
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const;
	
protected:
	
	virtual void BeginPlay() override;
	
	// Gameplay Ability System
	UPROPERTY(EditAnywhere, Category="GameplayAbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, Category="GameplayAbilitySystem")
	TObjectPtr<UAttributeSet> AttributeSet;
};
