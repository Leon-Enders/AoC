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

// Called every frame
void AAoCCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAoCCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

