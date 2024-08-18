// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AoCAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AoCGameplayTags.h"
#include "GameplayEffectExtension.h"
#include "Ability System/AoCAbilitySystemLibrary.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "Player/AoCPlayerController.h"

UAoCAttributeSet::UAoCAttributeSet()
{
	const FAoCGameplayTags& GameplayTags = FAoCGameplayTags::Get();

	// Primary Attributes
	TagsToAttribute.Add(GameplayTags.Attributes_Primary_Might, GetMightAttribute);
	TagsToAttribute.Add(GameplayTags.Attributes_Primary_Agility, GetAgilityAttribute);
	TagsToAttribute.Add(GameplayTags.Attributes_Primary_Intelligence, GetIntelligenceAttribute);
	TagsToAttribute.Add(GameplayTags.Attributes_Primary_Vitality, GetVitalityAttribute);
	TagsToAttribute.Add(GameplayTags.Attributes_Primary_Balance, GetBalanceAttribute);
	TagsToAttribute.Add(GameplayTags.Attributes_Primary_Dexterity, GetDexterityAttribute);


	// Secondary Attributes
	TagsToAttribute.Add(GameplayTags.Attributes_Secondary_CritChance, GetCritChanceAttribute);
	TagsToAttribute.Add(GameplayTags.Attributes_Secondary_Power, GetPowerAttribute);
	TagsToAttribute.Add(GameplayTags.Attributes_Secondary_CritDamage, GetCritDamageAttribute);
	TagsToAttribute.Add(GameplayTags.Attributes_Secondary_AttackSpeed, GetAttackSpeedAttribute);
	TagsToAttribute.Add(GameplayTags.Attributes_Secondary_CastSpeed, GetCastSpeedAttribute);
	TagsToAttribute.Add(GameplayTags.Attributes_Secondary_Penetration, GetPenetrationAttribute);
	TagsToAttribute.Add(GameplayTags.Attributes_Secondary_HealingPower, GetHealingPowerAttribute);
	TagsToAttribute.Add(GameplayTags.Attributes_Secondary_Defense, GetDefenseAttribute);
	TagsToAttribute.Add(GameplayTags.Attributes_Secondary_DamageReduction, GetDamageReductionAttribute);
	TagsToAttribute.Add(GameplayTags.Attributes_Secondary_CooldownReduction, GetCooldownReductionAttribute);
	TagsToAttribute.Add(GameplayTags.Attributes_Secondary_MovementSpeed, GetMovementSpeedAttribute);
	TagsToAttribute.Add(GameplayTags.Attributes_Secondary_AirControl, GetAirControlAttribute);
	TagsToAttribute.Add(GameplayTags.Attributes_Secondary_Tenacity, GetTenacityAttribute);
	TagsToAttribute.Add(GameplayTags.Attributes_Secondary_HealthRegeneration, GetHealthRegenerationAttribute);
	TagsToAttribute.Add(GameplayTags.Attributes_Secondary_ManaRegeneration, GetManaRegenerationAttribute);
	TagsToAttribute.Add(GameplayTags.Attributes_Secondary_Vampirism, GetManaRegenerationAttribute);
	TagsToAttribute.Add(GameplayTags.Attributes_Secondary_MaxHealth, GetMaxHealthAttribute);
	TagsToAttribute.Add(GameplayTags.Attributes_Secondary_MaxMana, GetMaxManaAttribute);
	TagsToAttribute.Add(GameplayTags.Attributes_Secondary_MaxEnergy, GetMaxEnergyAttribute);
	TagsToAttribute.Add(GameplayTags.Attributes_Secondary_MaxRage, GetMaxRageAttribute);

	
	
}

void UAoCAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Primary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, Might, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, Agility, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, Vitality, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, Balance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, Dexterity, COND_None, REPNOTIFY_Always);

	// Secondary Attributes
	
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, CritChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, Power, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, CritDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, AttackSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, CastSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, Penetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, HealingPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, Defense, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, DamageReduction, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, CooldownReduction, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, MovementSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, AirControl, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, Tenacity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, Vampirism, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);

	// Vital Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, Energy, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, Rage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, MaxRage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, MaxEnergy, COND_None, REPNOTIFY_Always);
}

void UAoCAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if(Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f , GetMaxHealth());
	}
	if(Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f , GetMaxMana());
	}
	
	
}

void UAoCAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetupEffectProperties(Data, Props);
	
	if(Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
		
	}

	if(Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
	
	if(Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float InDamage = GetIncomingDamage();
		SetIncomingDamage(0.f);
		if(InDamage > 0.f )
		{
			const float NewHealth = GetHealth() - InDamage;
			SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));
			
			const bool bIsCriticalHit = UAoCAbilitySystemLibrary::GetIsCriticalHit(Data.EffectSpec.GetEffectContext());
			SetFloatingText(Props,InDamage,bIsCriticalHit);


			const bool bIsFatal = NewHealth<=0.f;
			if(bIsFatal)
			{
				
				OnAvatarDeathDelegate.Broadcast(Props.SourceCharacter);
			}
			else
			{
				
				const FGameplayTagContainer GameplayTagContainer= FGameplayTagContainer(FAoCGameplayTags::Get().Effects_HitReact);
				Props.TargetASC->TryActivateAbilitiesByTag(GameplayTagContainer);
				
			}
		}
	}
	if(Data.EvaluatedData.Attribute == GetIncomingXPAttribute())
	{
		const float XP = GetIncomingXP();
		SetIncomingXP(0.f);
		OnXPReceivedDelegate.Broadcast(XP);
	}
	
}
void UAoCAttributeSet::SetFloatingText(const FEffectProperties& Props, const float Damage, const bool IsCriticalHit)
{

	if(Props.SourceCharacter != Props.TargetCharacter)
	{
		if(AAoCPlayerController* APC = Cast<AAoCPlayerController>(Props.SourceCharacter->Controller))
		{
			APC->ShowDamageText(Damage, Props.TargetCharacter, IsCriticalHit);
		}
		if(AAoCPlayerController* APC = Cast<AAoCPlayerController>(Props.TargetCharacter->Controller))
		{
			APC->ShowDamageText(Damage, Props.TargetCharacter, IsCriticalHit);
		}
	}
}

void UAoCAttributeSet::SetupEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props)
{

	//Source = causer of the effect (Instigator), Target = Target of the effect (owner of this AS)
	
	Props.GameplayEffectContextHandle = Data.EffectSpec.GetContext();

	Props.SourceASC = Props.GameplayEffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if(IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if(Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if(const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if(Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}
	
	

	if(Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);

		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
	
	Props.TargetASC = Data.Target.AbilityActorInfo.Get()->AbilitySystemComponent.Get();
	Props.TargetAvatarActor = Data.Target.GetAvatarActor();
	if(Props.TargetAvatarActor != nullptr)
	{
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);

		if(Props.TargetCharacter != nullptr)
		{
			Props.TargetController = Props.TargetCharacter->GetController();
		}
	}
	
}



void UAoCAttributeSet::OnRep_Might(const FGameplayAttributeData& OldMight) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, Might, OldMight);
}

void UAoCAttributeSet::OnRep_Agility(const FGameplayAttributeData& OldAgility) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, Agility, OldAgility);
}

void UAoCAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, Intelligence, OldIntelligence);
}

void UAoCAttributeSet::OnRep_Vitality(const FGameplayAttributeData& OldVitality) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, Vitality, OldVitality);
}

void UAoCAttributeSet::OnRep_Balance(const FGameplayAttributeData& OldBalance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, Balance, OldBalance);
}

void UAoCAttributeSet::OnRep_Dexterity(const FGameplayAttributeData& OldDexterity) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, Dexterity, OldDexterity);
}

void UAoCAttributeSet::OnRep_CritChance(const FGameplayAttributeData& OldCritChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, CritChance, OldCritChance);
}

void UAoCAttributeSet::OnRep_Power(const FGameplayAttributeData& OldPower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, Power, OldPower);
}

void UAoCAttributeSet::OnRep_CritDamage(const FGameplayAttributeData& OldCritDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, CritDamage, OldCritDamage);
}

void UAoCAttributeSet::OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, AttackSpeed, OldAttackSpeed);
}

void UAoCAttributeSet::OnRep_CastSpeed(const FGameplayAttributeData& OldCastSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, CastSpeed, OldCastSpeed);
}

void UAoCAttributeSet::OnRep_Penetration(const FGameplayAttributeData& OldPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, Penetration, OldPenetration);
}

void UAoCAttributeSet::OnRep_HealingPower(const FGameplayAttributeData& OldHealingPower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, HealingPower, OldHealingPower);
}

void UAoCAttributeSet::OnRep_Defense(const FGameplayAttributeData& OldDefense) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, Defense, OldDefense);
}

void UAoCAttributeSet::OnRep_DamageReduction(const FGameplayAttributeData& OldDamageReduction) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, DamageReduction, OldDamageReduction);
}

void UAoCAttributeSet::OnRep_CooldownReduction(const FGameplayAttributeData& OldCooldownReduction) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, CooldownReduction, OldCooldownReduction);
}

void UAoCAttributeSet::OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, MovementSpeed, OldMovementSpeed);
}

void UAoCAttributeSet::OnRep_AirControl(const FGameplayAttributeData& OldAirControl) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, AirControl, OldAirControl);
}


void UAoCAttributeSet::OnRep_Tenacity(const FGameplayAttributeData& OldTenacity) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, Tenacity, OldTenacity);
}

void UAoCAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, HealthRegeneration, OldHealthRegeneration);
}

void UAoCAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, ManaRegeneration, OldManaRegeneration);
}

void UAoCAttributeSet::OnRep_Vampirism(const FGameplayAttributeData& OldVampirism) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, Vampirism, OldVampirism);
}

void UAoCAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, MaxHealth, OldMaxHealth);
}

void UAoCAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, MaxMana, OldMaxMana);
}

void UAoCAttributeSet::OnRep_MaxEnergy(const FGameplayAttributeData& OldMaxEnergy) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, MaxEnergy, OldMaxEnergy);
}

void UAoCAttributeSet::OnRep_MaxRage(const FGameplayAttributeData& OldMaxRage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, MaxRage, OldMaxRage);
}


// Vital

void UAoCAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, Health, OldHealth);
	
}

void UAoCAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, Mana, OldMana);
}

void UAoCAttributeSet::OnRep_Energy(const FGameplayAttributeData& OldEnergy) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, Energy, OldEnergy);
}

void UAoCAttributeSet::OnRep_Rage(const FGameplayAttributeData& OldRage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, Rage, OldRage);
}






