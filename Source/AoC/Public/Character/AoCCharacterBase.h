// Created by Leon Enders

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AoCCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class AOC_API AAoCCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAoCCharacterBase();
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:

	UPROPERTY(BlueprintReadOnly, Category="GameplayAbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category="GameplayAbilitySystem")
	TObjectPtr<UAttributeSet> AttributeSet;
};
