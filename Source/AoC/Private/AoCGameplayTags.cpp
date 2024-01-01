// Copyright by Leon Enders ©, All Rights Reserved.


#include "AoCGameplayTags.h"

#include "GameplayTagsManager.h"


FAoCGameplayTags FAoCGameplayTags::AoCGameplayTags;


void FAoCGameplayTags::InitializeNativeGameplayTags()
{
	//PrimaryAttributeTags
	AoCGameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"), FString("increases attack damage, knockback penetration"));
	AoCGameplayTags.Attributes_Primary_Agility = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Agility"), FString("increases melee crit chance, attack/castspeed, movementspeed"));
	AoCGameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"), FString("increases magic damage mana/resource pool"));
	AoCGameplayTags.Attributes_Primary_Vitality = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vitality"), FString("increases health pool and tenacity"));
	AoCGameplayTags.Attributes_Primary_Willpower = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Willpower"), FString("increases health, mana/resource regeneration"));
	AoCGameplayTags.Attributes_Primary_Dexterity = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Dexterity"), FString("increases air control, knock resistance, magic crit, armor penetration"));
	AoCGameplayTags.Attributes_Primary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Armor"), FString("increases physical damage reduction"));
	AoCGameplayTags.Attributes_Primary_MagicResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.MagicResistance"), FString("increases magic damage reduction"));

	//SecondaryAttributeTags

	AoCGameplayTags.Attributes_Secondary_PhysicalCritChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.PhysicalCritChance"), FString("chance to critically hit an enemy for extra damage with physical damage"));
	AoCGameplayTags.Attributes_Secondary_MagicCritChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MagicCritChance"), FString("chance to critically hit an enemy for extra damage with magic damage"));
	AoCGameplayTags.Attributes_Secondary_CritDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CritDamage"), FString("increases damage done when critical hitting"));
	AoCGameplayTags.Attributes_Secondary_AttackSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.AttackSpeed"), FString("reduces the time between basic attacks"));
	AoCGameplayTags.Attributes_Secondary_CastSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CastSpeed"), FString("reduces the cast time of abilities"));
	AoCGameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"), FString("ignores percentage of armor"));
	AoCGameplayTags.Attributes_Secondary_MagicPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MagicPenetration"), FString("ignores percentage of magic resist"));
	AoCGameplayTags.Attributes_Secondary_PhysicalDamageReduction = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.PhysicalDamageReduction"), FString("percentage of damage reduction when receiving physical damage"));
	AoCGameplayTags.Attributes_Secondary_MagicDamageReduction = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MagicDamageReduction"), FString("percentage of damage reduction when receiving magic damage"));
	AoCGameplayTags.Attributes_Secondary_CooldownReduction = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CooldownReduction"), FString("decreases the cooldown time for abilities"));
	AoCGameplayTags.Attributes_Secondary_MovementSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MovementSpeed"), FString("increases the movementspeed"));
	AoCGameplayTags.Attributes_Secondary_AirControl = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.AirControl"), FString("increases the control over movement while being in air"));
	AoCGameplayTags.Attributes_Secondary_KnockbackResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.KnockbackResistance"), FString("reduces the effect of knockbacks"));
	AoCGameplayTags.Attributes_Secondary_KnockbackPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.KnockbackPenetration"), FString("increases the effect of knockbacks"));
	AoCGameplayTags.Attributes_Secondary_Tenacity = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Tenacity"), FString("reduces the time of crowd control effects"));
	AoCGameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"), FString("automatically regenerate health every second"));
	AoCGameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"), FString("automatically regenerate mana every second"));
	AoCGameplayTags.Attributes_Secondary_HealthMax = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthMax"), FString("the maximum amount of health"));
	AoCGameplayTags.Attributes_Secondary_ManaMax = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaMax"), FString("the maximum amount of mana"));
	AoCGameplayTags.Attributes_Secondary_EnergyMax = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.EnergyMax"), FString("the maximum amount of energy"));
	AoCGameplayTags.Attributes_Secondary_RageMax = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.RageMax"), FString("the maximum amount of rage"));
	


}
