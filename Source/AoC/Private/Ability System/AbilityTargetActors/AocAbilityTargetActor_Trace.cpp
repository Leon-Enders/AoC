// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AbilityTargetActors/AocAbilityTargetActor_Trace.h"

#include "Abilities/GameplayAbility.h"
#include "AoC/AoC.h"
#include "Character/AoCChampion.h"

void AAocAbilityTargetActor_Trace::ConfirmTargeting()
{
	check(ShouldProduceTargetData());
	if (SourceActor)
	{
		bDebug = false;
		FGameplayAbilityTargetDataHandle Handle = MakeTargetData(PerformTrace(SourceActor));
		TargetDataReadyDelegate.Broadcast(Handle);
	}
	Super::ConfirmTargeting();
}

FHitResult AAocAbilityTargetActor_Trace::PerformTrace(AActor* InSourceActor)
{
	if (!OwningAbility) // Server and launching client only
		{
			return FHitResult();
		}

	APlayerController* PC = OwningAbility->GetCurrentActorInfo()->PlayerController.Get();
	check(PC);
	FVector ViewStart;
	FRotator ViewRot;
	PC->GetPlayerViewPoint(ViewStart, ViewRot);

	UE_LOG(LogTemp, Warning, TEXT("CameraPoint is: %s"), *ViewStart.ToString());
	
	bool bTraceComplex = false;
	TArray<AActor*> ActorsToIgnore;

	ActorsToIgnore.Add(InSourceActor);

	FCollisionQueryParams Params(SCENE_QUERY_STAT(AGameplayAbilityTargetActor_SingleLineTrace), bTraceComplex);
	Params.bReturnPhysicalMaterial = true;
	Params.AddIgnoredActors(ActorsToIgnore);

	FVector TraceStart = ViewStart;// InSourceActor->GetActorLocation();
	FVector TraceEnd = ViewStart + ViewRot.Euler().ForwardVector * 1000.f;
	
	
	FHitResult ReturnHitResult;
	//Default to end of trace line if we don't hit anything.
	GetWorld()->LineTraceSingleByChannel(ReturnHitResult,TraceStart, TraceEnd, ECC_TargetSystem, Params);	

	//if (!ReturnHitResult.bBlockingHit)
	//{
	//	ReturnHitResult.Location = TraceEnd;
	//}


#if ENABLE_DRAW_DEBUG
	if (bDebug)
	{
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green);
		DrawDebugSphere(GetWorld(), TraceEnd, 100.0f, 16, FColor::Green);
	}
#endif // ENABLE_DRAW_DEBUG
	return ReturnHitResult;
}

void AAocAbilityTargetActor_Trace::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TWeakObjectPtr<AActor> TargetActor = PerformTrace(SourceActor).GetActor();
	
	DrawTargetOutline(ActorToOutline, TargetActor);
	ActorToOutline = TargetActor;
}

void AAocAbilityTargetActor_Trace::DrawTargetOutline(TWeakObjectPtr<AActor> InHitActor,
                                                     TWeakObjectPtr<AActor> InLatestHitActors)
{
	if(InHitActor.IsValid())
	{
		if(InHitActor->IsA(CharacterClassToOutline))
		{
			const AAoCCharacterBase* Character = Cast<AAoCCharacterBase>(InHitActor);
			if(USkeletalMeshComponent* Mesh = Character->GetComponentByClass<USkeletalMeshComponent>())
			{
				Mesh->SetOverlayMaterialMaxDrawDistance(1.f);
			}
		}
	}
	
	if(InLatestHitActors.IsValid())
	{
		if(InLatestHitActors->IsA(CharacterClassToOutline))
		{
			const AAoCCharacterBase* Character = Cast<AAoCCharacterBase>(InLatestHitActors);
			if(USkeletalMeshComponent* Mesh = Character->GetComponentByClass<USkeletalMeshComponent>())
			{
				Mesh->SetOverlayMaterialMaxDrawDistance(0.f);
			}
		}
	}
}
