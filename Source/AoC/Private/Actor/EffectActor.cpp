// Created by Leon Enders


#include "Actor/EffectActor.h"

#include "AbilitySystemInterface.h"
#include "Ability System/AoCAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
AEffectActor::AEffectActor()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(Mesh);
	
}


void AEffectActor::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AEffectActor::EndOverlap);

	
}

void AEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{


	//TODO: Remove the const hack
	if(IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UAoCAttributeSet* AoCAttributeSet = Cast<UAoCAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAoCAttributeSet::StaticClass()));

		UAoCAttributeSet* MutableAoCAttributeSet = const_cast<UAoCAttributeSet*>(AoCAttributeSet);

		MutableAoCAttributeSet->SetHealth(AoCAttributeSet->GetHealth() + 25.f);
		Destroy();

	}
}

void AEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}



