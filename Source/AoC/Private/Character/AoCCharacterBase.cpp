// Created by Leon Enders


#include "Character/AoCCharacterBase.h"

// Sets default values
AAoCCharacterBase::AAoCCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAoCCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAoCCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


