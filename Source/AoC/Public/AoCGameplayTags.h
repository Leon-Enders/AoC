// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"



/**
 * GameplayTags Singleton struct, register all GameplayTags here
 */
struct AOC_API FAoCGameplayTags
{
public:
	FORCEINLINE static const FAoCGameplayTags& Get(){return AoCGameplayTags;}
	static void InitializeNativeGameplayTags();


	
	//PrimaryAttributeTags
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Agility;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Vitality;
	FGameplayTag Attributes_Primary_Willpower;
	FGameplayTag Attributes_Primary_Dexterity;
	FGameplayTag Attributes_Primary_Armor;
	FGameplayTag Attributes_Primary_MagicResistance;

	
	//SecondaryAttributeTags
	FGameplayTag Attributes_Secondary_PhysicalCritChance;
	FGameplayTag Attributes_Secondary_MagicCritChance;
	FGameplayTag Attributes_Secondary_CritDamage;
	FGameplayTag Attributes_Secondary_AttackSpeed;
	FGameplayTag Attributes_Secondary_CastSpeed;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_MagicPenetration;
	FGameplayTag Attributes_Secondary_PhysicalDamageReduction;
	FGameplayTag Attributes_Secondary_MagicDamageReduction;
	FGameplayTag Attributes_Secondary_CooldownReduction;
	FGameplayTag Attributes_Secondary_MovementSpeed;
	FGameplayTag Attributes_Secondary_AirControl;
	FGameplayTag Attributes_Secondary_KnockbackResistance;
	FGameplayTag Attributes_Secondary_KnockbackPenetration;
	FGameplayTag Attributes_Secondary_Tenacity;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_Vampirism;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;
	FGameplayTag Attributes_Secondary_MaxEnergy;
	FGameplayTag Attributes_Secondary_MaxRage;


	// InputTags
	FGameplayTag InputTags_LMB;
	FGameplayTag InputTags_RMB;
	FGameplayTag InputTags_1;
	FGameplayTag InputTags_2;
	FGameplayTag InputTags_3;
	FGameplayTag InputTags_4;
	FGameplayTag InputTags_5;
	FGameplayTag InputTags_Q;
	FGameplayTag InputTags_W;
	FGameplayTag InputTags_E;
	FGameplayTag InputTags_R;
	FGameplayTag InputTags_A;


	// Damage
	FGameplayTag Damage;

	// Effects
	FGameplayTag Effects_HitReact;


	//AnimationTags
	FGameplayTag Animation_Forward;
	FGameplayTag Animation_Backward;
	FGameplayTag Animation_Left;
	FGameplayTag Animation_Right;
	FGameplayTag Animation_Idle;
	
	
private:
	static FAoCGameplayTags AoCGameplayTags;
};
