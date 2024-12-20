// Copyright by Leon Enders ©, All Rights Reserved.


#include "AoCGameplayTags.h"

#include "GameplayTagAssetInterface.h"
#include "GameplayTagsManager.h"


FAoCGameplayTags FAoCGameplayTags::AoCGameplayTags;


void FAoCGameplayTags::InitializeNativeGameplayTags()
{
	//PrimaryAttributeTags
	AoCGameplayTags.Attributes_Primary_Might = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Might"), FString("increases attack damage, knockback penetration"));
	AoCGameplayTags.Attributes_Primary_Agility = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Agility"), FString("increases melee crit chance, attack/castspeed, movementspeed"));
	AoCGameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"), FString("increases magic damage mana/resource pool"));
	AoCGameplayTags.Attributes_Primary_Vitality = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vitality"), FString("increases health pool and tenacity"));
	AoCGameplayTags.Attributes_Primary_Balance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Balance"), FString("increases health, mana/resource regeneration"));
	AoCGameplayTags.Attributes_Primary_Dexterity = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Dexterity"), FString("increases Penetration, Cooldown Reduction and Speed"));

	//SecondaryAttributeTags
	AoCGameplayTags.Attributes_Secondary_CritChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CritChance"), FString("chance to critically hit an enemy for extra damage with physical damage"));
	AoCGameplayTags.Attributes_Secondary_Power = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Power"), FString("chance to critically hit an enemy for extra damage with magic damage"));
	AoCGameplayTags.Attributes_Secondary_CritDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CritDamage"), FString("increases damage done when critical hitting"));
	AoCGameplayTags.Attributes_Secondary_AttackSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.AttackSpeed"), FString("reduces the time between basic attacks"));
	AoCGameplayTags.Attributes_Secondary_CastSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CastSpeed"), FString("reduces the cast time of abilities"));
	AoCGameplayTags.Attributes_Secondary_Penetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Penetration"), FString("ignores percentage of defense"));
	AoCGameplayTags.Attributes_Secondary_HealingPower = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealingPower"), FString("ignores percentage of magic resist"));
	AoCGameplayTags.Attributes_Secondary_Defense = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Defense"), FString("percentage of damage reduction when receiving physical damage"));
	AoCGameplayTags.Attributes_Secondary_DamageReduction = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.DamageReduction"), FString("percentage of damage reduction when receiving magic damage"));
	AoCGameplayTags.Attributes_Secondary_CooldownReduction = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CooldownReduction"), FString("decreases the cooldown time for abilities"));
	AoCGameplayTags.Attributes_Secondary_MovementSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MovementSpeed"), FString("increases the movementspeed"));
	AoCGameplayTags.Attributes_Secondary_AirControl = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.AirControl"), FString("increases the control over movement while being in air"));
	AoCGameplayTags.Attributes_Secondary_Tenacity = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Tenacity"), FString("reduces the time of crowd control effects"));
	AoCGameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"), FString("automatically regenerate health every second"));
	AoCGameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"), FString("automatically regenerate mana every second"));
	AoCGameplayTags.Attributes_Secondary_Vampirism = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Vampirism"), FString("recovers a percentage of damage dealt as hp"));
	AoCGameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"), FString("the maximum amount of health"));
	AoCGameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"), FString("the maximum amount of mana"));
	AoCGameplayTags.Attributes_Secondary_MaxEnergy = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxEnergy"), FString("the maximum amount of energy"));
	AoCGameplayTags.Attributes_Secondary_MaxRage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxRage"), FString("the maximum amount of rage"));

	// Meta Attributes Tags
	AoCGameplayTags.Attributes_Meta_XP = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Meta.XP"), FString("Meta attribute tag for XP"));

	
	
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
	AoCGameplayTags.InputTag_Confirm = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTags.Confirm"), FString("Confirm button input"));
	AoCGameplayTags.InputTag_Cancel = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTags.Cancel"), FString("Cancel button input"));

	
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



	/*
	 * Champion
	 */
	
	// Fire Monk
	// AbilityTags
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

	// CooldownTags
	AoCGameplayTags.Cooldown_FireMonk_BasicAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.FireMonk.BasicAttack"), FString("Tag applied when BasicAttack ability is cooldown"));
	AoCGameplayTags.Cooldown_FireMonk_FlamingArts = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.FireMonk.FlamingArts"), FString("Tag applied when flaming arts ability is cooldown"));
	AoCGameplayTags.Cooldown_FireMonk_LaunchExplosion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.FireMonk.LaunchExplosion"), FString("Tag applied when LaunchExplosion ability is cooldown"));
	AoCGameplayTags.Cooldown_FireMonk_FlameBoost = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.FireMonk.FlameBoost"), FString("Tag applied when FlameBoost ability is cooldown"));
	AoCGameplayTags.Cooldown_FireMonk_FlamingTerror = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.FireMonk.FlamingTerror"), FString("Tag applied when FlamingTerror ability is cooldown"));
	AoCGameplayTags.Cooldown_FireMonk_BlazingPunch = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.FireMonk.BlazingPunch"), FString("Tag applied when BlazingPunch ability is cooldown"));
	AoCGameplayTags.Cooldown_FireMonk_RisingKickOfTheFlame = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.FireMonk.RisingKickOfTheFlame"), FString("Tag applied when RisingKickOfTheFlame ability is cooldown"));
	AoCGameplayTags.Cooldown_FireMonk_FlamingBarrier = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.FireMonk.FlamingBarrier"), FString("Tag applied when FlamingBarrier ability is cooldown"));
	AoCGameplayTags.Cooldown_FireMonk_FireUp = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.FireMonk.FireUp"), FString("Tag applied when FireUp ability is cooldown"));
	AoCGameplayTags.Cooldown_FireMonk_ExplosiveKneeKick = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.FireMonk.ExplosiveKneeKick"), FString("Tag applied when ExplosiveKneeKick ability is cooldown"));

	
	// DreamWeaver
	// AbilityTags
	AoCGameplayTags.Abilities_DreamWeaver_BasicAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.DreamWeaver.BasicAttack"), FString("BasicAttack ability tag"));
	AoCGameplayTags.Abilities_DreamWeaver_DreamSeeds = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.DreamWeaver.DreamSeeds"), FString("DreamSeeds ability tag"));
	AoCGameplayTags.Abilities_DreamWeaver_DreamEssence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.DreamWeaver.DreamEssence"), FString("DreamEssence ability tag"));
	AoCGameplayTags.Abilities_DreamWeaver_IllusionaryMist = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.DreamWeaver.IllusionaryMist"), FString("IllusionaryMist ability tag"));
	AoCGameplayTags.Abilities_DreamWeaver_IllusiveEvasion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.DreamWeaver.IllusiveEvasion"), FString("IllusiveEvasion ability tag"));
	AoCGameplayTags.Abilities_DreamWeaver_NightmarePortal = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.DreamWeaver.NightmarePortal"), FString("NightmarePortal ability tag"));
	AoCGameplayTags.Abilities_DreamWeaver_HealFountain = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.DreamWeaver.HealFountain"), FString("HealFountain ability tag"));
	AoCGameplayTags.Abilities_DreamWeaver_DreamBreath = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.DreamWeaver.DreamBreath"), FString("DreamBreath ability tag"));
	
	// CooldownTags
	AoCGameplayTags.Cooldown_DreamWeaver_BasicAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.DreamWeaver.BasicAttack"), FString("BasicAttack Cooldown tag"));
	AoCGameplayTags.Cooldown_DreamWeaver_DreamSeeds = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.DreamWeaver.DreamSeeds"), FString("DreamSeeds Cooldown tag"));
	AoCGameplayTags.Cooldown_DreamWeaver_DreamEssence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.DreamWeaver.DreamEssence"), FString("DreamEssence Cooldown tag"));
	AoCGameplayTags.Cooldown_DreamWeaver_IllusionaryMist = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.DreamWeaver.IllusionaryMist"), FString("IllusionaryMist Cooldown tag"));
	AoCGameplayTags.Cooldown_DreamWeaver_IllusiveEvasion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.DreamWeaver.IllusiveEvasion"), FString("IllusiveEvasion Cooldown tag"));
	AoCGameplayTags.Cooldown_DreamWeaver_NightmarePortal = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.DreamWeaver.NightmarePortal"), FString("NightmarePortal Cooldown tag"));
	AoCGameplayTags.Cooldown_DreamWeaver_HealFountain = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.DreamWeaver.HealFountain"), FString("HealFountain Cooldown tag"));
	AoCGameplayTags.Cooldown_DreamWeaver_DreamBreath = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.DreamWeaver.DreamBreath"), FString("DreamBreath Cooldown tag"));

	// DemonWarrior
	// AbilityTags
	AoCGameplayTags.Abilities_DemonWarrior_BasicAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.DemonWarrior.BasicAttack"), FString("BasicAttack ability tag"));
	AoCGameplayTags.Abilities_DemonWarrior_BloodTrail = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.DemonWarrior.BloodTrail"), FString("BloodTrail ability tag"));
	AoCGameplayTags.Abilities_DemonWarrior_CatchUp = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.DemonWarrior.CatchUp"), FString("CatchUp ability tag"));
	AoCGameplayTags.Abilities_DemonWarrior_DecayToBlood = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.DemonWarrior.DecayToBlood"), FString("DecayToBlood ability tag"));
	AoCGameplayTags.Abilities_DemonWarrior_DemonicChain = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.DemonWarrior.DemonicChain"), FString("BasicAttack ability tag"));
	AoCGameplayTags.Abilities_DemonWarrior_DemonicSmash = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.DemonWarrior.DemonicSmash"), FString("DemonicChain ability tag"));
	AoCGameplayTags.Abilities_DemonWarrior_DemonicSpikes = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.DemonWarrior.DemonicSpikes"), FString("DemonicSpikes ability tag"));
	AoCGameplayTags.Abilities_DemonWarrior_DrinkTheirBlood = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.DemonWarrior.DrinkTheirBlood"), FString("DrinkTheirBlood ability tag"));
	
	// CooldownTags
	AoCGameplayTags.Cooldown_DemonWarrior_BasicAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.DemonWarrior.BasicAttack"), FString("BasicAttack Cooldown tag"));
	AoCGameplayTags.Cooldown_DemonWarrior_BloodTrail = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.DemonWarrior.BloodTrail"), FString("BloodTrail Cooldown tag"));
	AoCGameplayTags.Cooldown_DemonWarrior_CatchUp = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.DemonWarrior.CatchUp"), FString("CatchUp ability tag"));
	AoCGameplayTags.Cooldown_DemonWarrior_DecayToBlood = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.DemonWarrior.DecayToBlood"), FString("DecayToBlood Cooldown tag"));
	AoCGameplayTags.Cooldown_DemonWarrior_DemonicChain = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.DemonWarrior.DemonicChain"), FString("BasicAttack Cooldown tag"));
	AoCGameplayTags.Cooldown_DemonWarrior_DemonicSmash = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.DemonWarrior.DemonicSmash"), FString("DemonicChain Cooldown tag"));
	AoCGameplayTags.Cooldown_DemonWarrior_DemonicSpikes = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.DemonWarrior.DemonicSpikes"), FString("DemonicSpikes Cooldown tag"));
	AoCGameplayTags.Cooldown_DemonWarrior_DrinkTheirBlood = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.DemonWarrior.DrinkTheirBlood"), FString("DrinkTheirBlood Cooldown tag"));
	
	// ThunderKnight
	// AbilityTags
	AoCGameplayTags.Abilities_ThunderKnight_BasicAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.ThunderKnight.BasicAttack"), FString("BasicAttack ability tag"));
	AoCGameplayTags.Abilities_ThunderKnight_ElectricEvasion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.ThunderKnight.ElectricEvasion"), FString("ElectricEvasion ability tag"));
	AoCGameplayTags.Abilities_ThunderKnight_Electrify = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.ThunderKnight.Electrify"), FString("Electrify ability tag"));
	AoCGameplayTags.Abilities_ThunderKnight_HomingLightning = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.ThunderKnight.HomingLightning"), FString("HomingLightning ability tag"));
	AoCGameplayTags.Abilities_ThunderKnight_LightningCrash = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.ThunderKnight.LightningCrash"), FString("LightningCrash ability tag"));
	AoCGameplayTags.Abilities_ThunderKnight_LightningDash = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.ThunderKnight.LightningDash"), FString("LightningDash ability tag"));
	AoCGameplayTags.Abilities_ThunderKnight_ThunderSpear = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.ThunderKnight.ThunderSpear"), FString("ThunderSpear ability tag"));
	AoCGameplayTags.Abilities_ThunderKnight_ElectricDance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.ThunderKnight.ElectricDance"), FString("ElectricDance ability tag"));
	
	// CooldownTags
	AoCGameplayTags.Cooldown_ThunderKnight_BasicAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.ThunderKnight.BasicAttack"), FString("BasicAttack Cooldown tag"));
	AoCGameplayTags.Cooldown_ThunderKnight_ElectricEvasion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.ThunderKnight.ElectricEvasion"), FString("ElectricEvasion Cooldown tag"));
	AoCGameplayTags.Cooldown_ThunderKnight_Electrify = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.ThunderKnight.Electrify"), FString("Electrify Cooldown tag"));
	AoCGameplayTags.Cooldown_ThunderKnight_HomingLightning = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.ThunderKnight.HomingLightning"), FString("HomingLightning Cooldown tag"));
	AoCGameplayTags.Cooldown_ThunderKnight_LightningCrash = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.ThunderKnight.LightningCrash"), FString("LightningCrash Cooldown tag"));
	AoCGameplayTags.Cooldown_ThunderKnight_LightningDash = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.ThunderKnight.LightningDash"), FString("LightningDash Cooldown tag"));
	AoCGameplayTags.Cooldown_ThunderKnight_ThunderSpear = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.ThunderKnight.ThunderSpear"), FString("ThunderSpear Cooldown tag"));
	AoCGameplayTags.Cooldown_ThunderKnight_ElectricDance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.ThunderKnight.ElectricDance"), FString("ElectricDance Cooldown tag"));
	
	// FrostMage
	// AbilityTags
	AoCGameplayTags.Abilities_FrostMage_BasicAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.FrostMage.BasicAttack"), FString("Tag applied when BasicAttack ability is active"));
	AoCGameplayTags.Abilities_FrostMage_FrostNova = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.FrostMage.FrostNova"), FString("Tag applied when FrostNova ability is active"));
	AoCGameplayTags.Abilities_FrostMage_FrostVolley = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.FrostMage.FrostVolley"), FString("Tag applied when FrostVolley ability is active"));
	AoCGameplayTags.Abilities_FrostMage_IceFlurry = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.FrostMage.IceFlurry"), FString("Tag applied when IceFlurry ability is active"));
	AoCGameplayTags.Abilities_FrostMage_FrozenOrb = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.FrostMage.FrozenOrb"), FString("Tag applied when FrozenOrb ability is active"));
	AoCGameplayTags.Abilities_FrostMage_IceBlock = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.FrostMage.IceBlock"), FString("Tag applied when IceBlock ability is active"));
	AoCGameplayTags.Abilities_FrostMage_GlacialSpike = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.FrostMage.GlacialSpike"), FString("Tag applied when GlacialSpike ability is active"));
	AoCGameplayTags.Abilities_FrostMage_FrozenAir = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.FrostMage.FrozenAir"), FString("Tag applied when FrozenAir ability is active"));
	AoCGameplayTags.Abilities_FrostMage_IcyVeins = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.FrostMage.IcyVeins"), FString("Tag applied when IcyVeins ability is active"));

	// CooldownTags
	AoCGameplayTags.Cooldown_FrostMage_BasicAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.FrostMage.BasicAttack"), FString("Tag applied when BasicAttack ability is on cooldown"));
	AoCGameplayTags.Cooldown_FrostMage_FrostNova = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.FrostMage.FrostNova"), FString("Tag applied when FrostNova ability is on cooldown"));
	AoCGameplayTags.Cooldown_FrostMage_FrostVolley = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.FrostMage.FrostVolley"), FString("Tag applied when FrostVolley ability is on cooldown"));
	AoCGameplayTags.Cooldown_FrostMage_IceFlurry = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.FrostMage.IceFlurry"), FString("Tag applied when IceFlurry ability is on cooldown"));
	AoCGameplayTags.Cooldown_FrostMage_FrozenOrb = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.FrostMage.FrozenOrb"), FString("Tag applied when FrozenOrb ability is on cooldown"));
	AoCGameplayTags.Cooldown_FrostMage_IceBlock = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.FrostMage.IceBlock"), FString("Tag applied when IceBlock ability is on cooldown"));
	AoCGameplayTags.Cooldown_FrostMage_GlacialSpike = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.FrostMage.GlacialSpike"), FString("Tag applied when GlacialSpike ability is on cooldown"));
	AoCGameplayTags.Cooldown_FrostMage_FrozenAir = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.FrostMage.FrozenAir"), FString("Tag applied when FrozenAir ability is on cooldown"));
	AoCGameplayTags.Cooldown_FrostMage_IcyVeins = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.FrostMage.IcyVeins"), FString("Tag applied when IcyVeins ability is on cooldown"));

	// MagicArcher
	// AbilityTags
	AoCGameplayTags.Abilities_MagicArcher_BasicAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.MagicArcher.BasicAttack"), FString("Tag applied when BasicAttack ability is active"));
	AoCGameplayTags.Abilities_MagicArcher_Aim = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.MagicArcher.Aim"), FString("Tag applied when Aim ability is active"));
	AoCGameplayTags.Abilities_MagicArcher_ElementalShot = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.MagicArcher.ElementalShot"), FString("Tag applied when ElementalShot ability is active"));
	AoCGameplayTags.Abilities_MagicArcher_ScatterShot = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.MagicArcher.ScatterShot"), FString("Tag applied when ScatterShot ability is active"));
	AoCGameplayTags.Abilities_MagicArcher_ElementalInfusion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.MagicArcher.ElementalInfusion"), FString("Tag applied when ElementalInfusion ability is active"));
	AoCGameplayTags.Abilities_MagicArcher_RapidFire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.MagicArcher.RapidFire"), FString("Tag applied when RapidFire ability is active"));
	AoCGameplayTags.Abilities_MagicArcher_MagicTurret = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.MagicArcher.MagicTurret"), FString("Tag applied when MagicTurret ability is active"));
	AoCGameplayTags.Abilities_MagicArcher_TrapShot = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.MagicArcher.TrapShot"), FString("Tag applied when TrapShot ability is active"));
	AoCGameplayTags.Abilities_MagicArcher_RainOfArrows = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.MagicArcher.RainOfArrows"), FString("Tag applied when RainOfArrows ability is active"));
	AoCGameplayTags.Abilities_MagicArcher_EnchantedArrow = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.MagicArcher.EnchantedArrow"), FString("Tag applied when EnchantedArrow ability is active"));

	// CooldownTags
	AoCGameplayTags.Cooldown_MagicArcher_BasicAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.MagicArcher.BasicAttack"), FString("Tag applied when BasicAttack ability is on cooldown"));
	AoCGameplayTags.Cooldown_MagicArcher_Aim = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.MagicArcher.Aim"), FString("Tag applied when Aim ability is on cooldown"));
	AoCGameplayTags.Cooldown_MagicArcher_ElementalShot = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.MagicArcher.ElementalShot"), FString("Tag applied when ElementalShot ability is on cooldown"));
	AoCGameplayTags.Cooldown_MagicArcher_ScatterShot = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.MagicArcher.ScatterShot"), FString("Tag applied when ScatterShot ability is on cooldown"));
	AoCGameplayTags.Cooldown_MagicArcher_ElementalInfusion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.MagicArcher.ElementalInfusion"), FString("Tag applied when ElementalInfusion ability is on cooldown"));
	AoCGameplayTags.Cooldown_MagicArcher_RapidFire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.MagicArcher.RapidFire"), FString("Tag applied when RapidFire ability is on cooldown"));
	AoCGameplayTags.Cooldown_MagicArcher_MagicTurret = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.MagicArcher.MagicTurret"), FString("Tag applied when MagicTurret ability is on cooldown"));
	AoCGameplayTags.Cooldown_MagicArcher_TrapShot = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.MagicArcher.TrapShot"), FString("Tag applied when TrapShot ability is on cooldown"));
	AoCGameplayTags.Cooldown_MagicArcher_RainOfArrows = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.MagicArcher.RainOfArrows"), FString("Tag applied when RainOfArrows ability is on cooldown"));
	AoCGameplayTags.Cooldown_MagicArcher_EnchantedArrow = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.MagicArcher.EnchantedArrow"), FString("Tag applied when EnchantedArrow ability is on cooldown"));

	// TheLastOne
	// AbilityTags
	AoCGameplayTags.Abilities_TheLastOne_BasicAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.TheLastOne.BasicAttack"), FString("Tag applied when BasicAttack ability is active"));
	AoCGameplayTags.Abilities_TheLastOne_Bash = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.TheLastOne.Bash"), FString("Tag applied when Bash ability is active"));
	AoCGameplayTags.Abilities_TheLastOne_Engage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.TheLastOne.Engage"), FString("Tag applied when Engage ability is active"));
	AoCGameplayTags.Abilities_TheLastOne_Glare = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.TheLastOne.Glare"), FString("Tag applied when Glare ability is active"));
	AoCGameplayTags.Abilities_TheLastOne_Guard = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.TheLastOne.Guard"), FString("Tag applied when Guard ability is active"));
	AoCGameplayTags.Abilities_TheLastOne_Dissension = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.TheLastOne.Dissension"), FString("Tag applied when Dissension ability is active"));
	AoCGameplayTags.Abilities_TheLastOne_EmptyBook = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.TheLastOne.EmptyBook"), FString("Tag applied when EmptyBook ability is active"));
	
	// CooldownTags
	AoCGameplayTags.Cooldown_TheLastOne_BasicAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.TheLastOne.BasicAttack"), FString("Tag applied when BasicAttack Cooldown is active"));
	AoCGameplayTags.Cooldown_TheLastOne_Bash = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.TheLastOne.Bash"), FString("Tag applied when Bash Cooldown is active"));
	AoCGameplayTags.Cooldown_TheLastOne_Engage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.TheLastOne.Engage"), FString("Tag applied when Engage Cooldown is active"));
	AoCGameplayTags.Cooldown_TheLastOne_Glare = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.TheLastOne.Glare"), FString("Tag applied when Glare Cooldown is active"));
	AoCGameplayTags.Cooldown_TheLastOne_Guard = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.TheLastOne.Guard"), FString("Tag applied when Guard Cooldown is active"));
	AoCGameplayTags.Cooldown_TheLastOne_Dissension = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.TheLastOne.Dissension"), FString("Tag applied when Dissension Cooldown is active"));
	AoCGameplayTags.Cooldown_TheLastOne_EmptyBook = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.TheLastOne.EmptyBook"), FString("Tag applied when EmptyBook Cooldown is active"));
	
	/*
	 * Champion end
	 */
	
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


	/*
	* Champion end
	*/

	/*
	 * AI Enemy
	 */
	
	AoCGameplayTags.Abilities_Enemy_Attack_Melee = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Enemy.Attack.Melee"), FString("Tag to activate enemy melee ability"));

	/*
	 * AI Enemy end
	 */


	
	// Event Tags
	AoCGameplayTags.Event_Montage_SaveAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Montage.SaveAttack"), FString("Tag to buffer next Combo Input in a Montage"));
	AoCGameplayTags.Event_Montage_ResetCombo = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Montage.ResetCombo"), FString("Tag to reset a Combo"));
	AoCGameplayTags.Event_Montage_NextCombo = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Montage.NextCombo"), FString("Tag to grant next Basic Attack Combo"));


	// AI Enemy
	AoCGameplayTags.Event_Montage_Enemy_Attack_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Montage.Enemy.Attack.Weapon"), FString("Event tag for enemy ai Attack with weapon"));
	AoCGameplayTags.Event_Montage_Enemy_Attack_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Montage.Enemy.Attack.RightHand"), FString("Event tag for enemy ai Attack with right hand"));
	AoCGameplayTags.Event_Montage_Enemy_Attack_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Montage.Enemy.Attack.LeftHand"), FString("Event tag for enemy ai Attack with left hand"));
	
}
