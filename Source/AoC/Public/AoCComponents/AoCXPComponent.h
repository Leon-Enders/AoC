// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AoCComponents/AoCComponent.h"
#include "AoCXPComponent.generated.h"

class UAoCXPDataAsset;
/**
 * 
 */
UCLASS()
class AOC_API UAoCXPComponent : public UAoCComponent
{
	GENERATED_BODY()
	
public:
	
	UAoCXPComponent();
	virtual void InitializeAoCComponent() override;

	

	
private:

	UPROPERTY(EditAnywhere, Category="AvatarProperties")
	TObjectPtr<UAoCXPDataAsset> XPData;
};
