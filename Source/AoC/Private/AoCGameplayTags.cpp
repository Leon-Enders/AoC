// Copyright by Leon Enders ©, All Rights Reserved.


#include "AoCGameplayTags.h"

#include "GameplayTagAssetInterface.h"
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
	AoCGameplayTags.Attributes_Secondary_Vampirism = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Vampirism"), FString("recovers a percentage of damage dealt as hp"));
	AoCGameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"), FString("the maximum amount of health"));
	AoCGameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"), FString("the maximum amount of mana"));
	AoCGameplayTags.Attributes_Secondary_MaxEnergy = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxEnergy"), FString("the maximum amount of energy"));
	AoCGameplayTags.Attributes_Secondary_MaxRage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxRage"), FString("the maximum amount of rage"));
	
	// Input Tags
	AoCGameplayTags.InputTags_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTags.LMB"), FString("Left mouse button input"));
	AoCGameplayTags.InputTags_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTags.RMB"), FString("Right mouse button input"));
	AoCGameplayTags.InputTags_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTags.1"), FString("1 button input"));
	AoCGameplayTags.InputTags_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTags.2"), FString("1 button input"));
	AoCGameplayTags.InputTags_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTags.3"), FString("3 button input"));
	AoCGameplayTags.InputTags_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTags.4"), FString("4 button input"));
	AoCGameplayTags.InputTags_5 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTags.5"), FString("5 button input"));
	AoCGameplayTags.InputTags_Q = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTags.Q"), FString("Q button input"));
	AoCGameplayTags.InputTags_W= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTags.W"), FString("W button input"));
	AoCGameplayTags.InputTags_E = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTags.E"), FString("E button input"));
	AoCGameplayTags.InputTags_R = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTags.R"), FString("R button input"));
	AoCGameplayTags.InputTags_A = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTags.A"), FString("A button input"));
	
	// Damage Tags
	AoCGameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"), FString("Damage Tag"));
	AoCGameplayTags.Damage_Magic = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Magic"), FString("Magic Damage Tag"));
	AoCGameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Physical"), FString("Physical Damage Tag"));
	


	
	// Effect Tags
	AoCGameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.HitReact"), FString("Tag applied to play HitReaction"));


	// Animation Tags
	AoCGameplayTags.Animations_Forward = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Animations.Forward"), FString("Tag applied to play forward montage section"));
	AoCGameplayTags.Animations_Backward = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Animations.Backward"), FString("Tag applied to play backward montage section"));
	AoCGameplayTags.Animations_Left = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Animations.Left"), FString("Tag applied to play left montage section"));
	AoCGameplayTags.Animations_Right = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Animations.Right"), FString("Tag applied to play right montage section"));
	AoCGameplayTags.Animations_Idle = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Animations.Idle"), FString("Tag applied to play idle montage section"));

	// Ability Tags Fire Monk
	AoCGameplayTags.Abilities_FireMonk_BasicAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.FireMonk.BasicAttack"), FString("Tag applied when BasicAttack ability is active"));
	AoCGameplayTags.Abilities_FireMonk_BasicAttack1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.FireMonk.BasicAttack1"), FString("Tag applied when BasicAttack1 ability is ready"));
	AoCGameplayTags.Abilities_FireMonk_BasicAttack2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.FireMonk.BasicAttack2"), FString("Tag applied when BasicAttack2 ability is ready"));
	AoCGameplayTags.Abilities_FireMonk_BasicAttack3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.FireMonk.BasicAttack3"), FString("Tag applied when BasicAttack3 ability is ready"));
	AoCGameplayTags.Abilities_FireMonk_FlamingArts = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.FireMonk.FlamingArts"), FString("Tag applied when flaming arts ability is active"));
	AoCGameplayTags.Abilities_FireMonk_LaunchExplosion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.FireMonk.LaunchExplosion"), FString("Tag applied when LaunchExplosion ability is active"));
	AoCGameplayTags.Abilities_FireMonk_FlameBoost = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.FireMonk.FlameBoost"), FString("Tag applied when FlameBoost ability is active"));
	AoCGameplayTags.Abilities_FireMonk_FlamingTerror = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.FireMonk.FlamingTerror"), FString("Tag applied when FlamingTerror ability is active"));
	AoCGameplayTags.Abilities_FireMonk_BlazingPunch = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.FireMonk.BlazingPunch"), FString("Tag applied when BlazingPunch ability is active"));
	AoCGameplayTags.Abilities_FireMonk_RisingKickOfTheFlame = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.FireMonk.RisingKickOfTheFlame"), FString("Tag applied when RisingKickOfTheFlame ability is active"));
	AoCGameplayTags.Abilities_FireMonk_FlamingBarrier = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.FireMonk.FlamingBarrier"), FString("Tag applied when FlamingBarrier ability is active"));
	AoCGameplayTags.Abilities_FireMonk_FireUp = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.FireMonk.FireUp"), FString("Tag applied when FireUp ability is active"));
	AoCGameplayTags.Abilities_FireMonk_ExplosiveKneeKick = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.FireMonk.ExplosiveKneeKick"), FString("Tag applied when ExplosiveKneeKick ability is active"));


	// Melee Combo Tags

	AoCGameplayTags.Melee_ComboA1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Melee.ComboA1"), FString("Tag to use melee comboA1"));
	AoCGameplayTags.Melee_ComboA2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Melee.ComboA2"), FString("Tag to use melee comboA2"));
	AoCGameplayTags.Melee_ComboA3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Melee.ComboA3"), FString("Tag to use melee comboA3"));
	AoCGameplayTags.Melee_ComboA4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Melee.ComboA4"), FString("Tag to use melee comboA4"));

	AoCGameplayTags.Melee_ComboB1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Melee.ComboB1"), FString("Tag to use melee comboB1"));
	AoCGameplayTags.Melee_ComboB2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Melee.ComboB2"), FString("Tag to use melee comboB2"));
	AoCGameplayTags.Melee_ComboB3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Melee.ComboB3"), FString("Tag to use melee comboB3"));
	AoCGameplayTags.Melee_ComboB4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Melee.ComboB4"), FString("Tag to use melee comboB4"));

	AoCGameplayTags.Melee_ComboC1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Melee.ComboC1"), FString("Tag to use melee comboC1"));
	AoCGameplayTags.Melee_ComboC2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Melee.ComboC2"), FString("Tag to use melee comboC2"));
	AoCGameplayTags.Melee_ComboC3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Melee.ComboC3"), FString("Tag to use melee comboC3"));
	AoCGameplayTags.Melee_ComboC4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Melee.ComboC4"), FString("Tag to use melee comboC4"));

	// Event Tags

	AoCGameplayTags.Event_Montage_SaveAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Montage.SaveAttack"), FString("Tag to buffer next Combo Input in a Montage"));
	AoCGameplayTags.Event_Montage_ResetCombo = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Montage.ResetCombo"), FString("Tag to reset a Combo"));
	AoCGameplayTags.Event_Montage_NextCombo = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Montage.NextCombo"), FString("Tag to grant next Basic Attack Combo"));

}
