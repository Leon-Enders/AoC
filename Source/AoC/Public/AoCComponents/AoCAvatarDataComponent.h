// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AoCAvatarDataComponent.generated.h"










UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AOC_API UAoCAvatarDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UAoCAvatarDataComponent();

protected:
	
	virtual void BeginPlay() override;

		
};
