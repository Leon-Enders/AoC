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
	FGameplayTag Attributes_Primary_Might;
	FGameplayTag Attributes_Primary_Agility;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Vitality;
	FGameplayTag Attributes_Primary_Balance;
	FGameplayTag Attributes_Primary_Dexterity;

	
	//SecondaryAttributeTags
	FGameplayTag Attributes_Secondary_CritChance;
	FGameplayTag Attributes_Secondary_Power;
	FGameplayTag Attributes_Secondary_CritDamage;
	FGameplayTag Attributes_Secondary_AttackSpeed;
	FGameplayTag Attributes_Secondary_CastSpeed;
	FGameplayTag Attributes_Secondary_Penetration;
	FGameplayTag Attributes_Secondary_HealingPower;
	FGameplayTag Attributes_Secondary_Defense;
	FGameplayTag Attributes_Secondary_DamageReduction;
	FGameplayTag Attributes_Secondary_CooldownReduction;
	FGameplayTag Attributes_Secondary_MovementSpeed;
	FGameplayTag Attributes_Secondary_AirControl;
	FGameplayTag Attributes_Secondary_Tenacity;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_Vampirism;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;
	FGameplayTag Attributes_Secondary_MaxEnergy;
	FGameplayTag Attributes_Secondary_MaxRage;


	/*
	 * Meta Attributes Tags
	*/
	FGameplayTag Attributes_Meta_XP;
	/*
	 * Meta Attributes Tags End
	 */

	
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

	FGameplayTag InputTag_Confirm;
	FGameplayTag InputTag_Cancel;
	
	// Damage
	FGameplayTag Damage;
	FGameplayTag Damage_Magic;
	FGameplayTag Damage_Physical;


	// Resistances
	//TODO: Rename all Resistance attributes to Attributes_Resistances_.. and place here
	
	// Effects
	FGameplayTag Effects_HitReact;


	// Animation Tags
	FGameplayTag Animations_Forward;
	FGameplayTag Animations_Backward;
	FGameplayTag Animations_Left;
	FGameplayTag Animations_Right;
	FGameplayTag Animations_Idle;


	/*
	 * Champion
	 */
	
	// Fire Monk
	// AbilityTags
	FGameplayTag Abilities_FireMonk_BasicAttack;
	FGameplayTag Abilities_FireMonk_BasicAttack1;
	FGameplayTag Abilities_FireMonk_BasicAttack2;
	FGameplayTag Abilities_FireMonk_BasicAttack3;
	FGameplayTag Abilities_FireMonk_FlamingArts;
	FGameplayTag Abilities_FireMonk_LaunchExplosion;
	FGameplayTag Abilities_FireMonk_FlameBoost;
	FGameplayTag Abilities_FireMonk_FlamingTerror;
	FGameplayTag Abilities_FireMonk_BlazingPunch;
	FGameplayTag Abilities_FireMonk_FlyingKick;
	FGameplayTag Abilities_FireMonk_RisingKickOfTheFlame;
	FGameplayTag Abilities_FireMonk_FlamingBarrier;
	FGameplayTag Abilities_FireMonk_FireUp;
	FGameplayTag Abilities_FireMonk_ExplosiveKneeKick;
	
	// CooldownTags
	FGameplayTag Cooldown_FireMonk_BasicAttack;
	FGameplayTag Cooldown_FireMonk_FlamingArts;
	FGameplayTag Cooldown_FireMonk_LaunchExplosion;
	FGameplayTag Cooldown_FireMonk_FlameBoost;
	FGameplayTag Cooldown_FireMonk_FlamingTerror;
	FGameplayTag Cooldown_FireMonk_BlazingPunch;
	FGameplayTag Cooldown_FireMonk_FlyingKick;
	FGameplayTag Cooldown_FireMonk_RisingKickOfTheFlame;
	FGameplayTag Cooldown_FireMonk_FlamingBarrier;
	FGameplayTag Cooldown_FireMonk_FireUp;
	FGameplayTag Cooldown_FireMonk_ExplosiveKneeKick;
	
	// DreamWeaver
	// AbilityTags
	FGameplayTag Abilities_DreamWeaver_BasicAttack;
	FGameplayTag Abilities_DreamWeaver_DreamEssence;
	FGameplayTag Abilities_DreamWeaver_IllusionaryMist;
	FGameplayTag Abilities_DreamWeaver_IllusiveEvasion;
	FGameplayTag Abilities_DreamWeaver_NightmarePortal;
	FGameplayTag Abilities_DreamWeaver_HealFountain;
	FGameplayTag Abilities_DreamWeaver_DreamBreath;
	FGameplayTag Abilities_DreamWeaver_DreamSeeds;

	// CooldownTags
	FGameplayTag Cooldown_DreamWeaver_BasicAttack;
	FGameplayTag Cooldown_DreamWeaver_DreamEssence;
	FGameplayTag Cooldown_DreamWeaver_IllusionaryMist;
	FGameplayTag Cooldown_DreamWeaver_IllusiveEvasion;
	FGameplayTag Cooldown_DreamWeaver_NightmarePortal;
	FGameplayTag Cooldown_DreamWeaver_HealFountain;
	FGameplayTag Cooldown_DreamWeaver_DreamBreath;
	FGameplayTag Cooldown_DreamWeaver_DreamSeeds;

	// DemonWarrior
	// AbilityTags
	FGameplayTag Abilities_DemonWarrior_BasicAttack;
	FGameplayTag Abilities_DemonWarrior_DemonicSpikes;
	FGameplayTag Abilities_DemonWarrior_CatchUp;
	FGameplayTag Abilities_DemonWarrior_DecayToBlood;
	FGameplayTag Abilities_DemonWarrior_DemonicChain;
	FGameplayTag Abilities_DemonWarrior_DemonicSmash;
	FGameplayTag Abilities_DemonWarrior_DrinkTheirBlood;
	FGameplayTag Abilities_DemonWarrior_BloodTrail;
	
	//CooldownTags
	FGameplayTag Cooldown_DemonWarrior_BasicAttack;
	FGameplayTag Cooldown_DemonWarrior_DemonicSpikes;
	FGameplayTag Cooldown_DemonWarrior_CatchUp;
	FGameplayTag Cooldown_DemonWarrior_DecayToBlood;
	FGameplayTag Cooldown_DemonWarrior_DemonicChain;
	FGameplayTag Cooldown_DemonWarrior_DemonicSmash;
	FGameplayTag Cooldown_DemonWarrior_DrinkTheirBlood;
	FGameplayTag Cooldown_DemonWarrior_BloodTrail;
	
	// ThunderKnight
	// AbilityTags
	FGameplayTag Abilities_ThunderKnight_BasicAttack;
	FGameplayTag Abilities_ThunderKnight_ElectricEvasion;
	FGameplayTag Abilities_ThunderKnight_Electrify;
	FGameplayTag Abilities_ThunderKnight_HomingLightning;
	FGameplayTag Abilities_ThunderKnight_LightningCrash;
	FGameplayTag Abilities_ThunderKnight_LightningDash;
	FGameplayTag Abilities_ThunderKnight_ThunderSpear;
	FGameplayTag Abilities_ThunderKnight_ElectricDance;
	
	//CooldownTags
	FGameplayTag Cooldown_ThunderKnight_BasicAttack;
	FGameplayTag Cooldown_ThunderKnight_ElectricEvasion;
	FGameplayTag Cooldown_ThunderKnight_Electrify;
	FGameplayTag Cooldown_ThunderKnight_HomingLightning;
	FGameplayTag Cooldown_ThunderKnight_LightningCrash;
	FGameplayTag Cooldown_ThunderKnight_LightningDash;
	FGameplayTag Cooldown_ThunderKnight_ThunderSpear;
	FGameplayTag Cooldown_ThunderKnight_ElectricDance;
	
	// FrostMage
	// AbilityTags
	FGameplayTag Abilities_FrostMage_BasicAttack;
	FGameplayTag Abilities_FrostMage_FrostNova;
	FGameplayTag Abilities_FrostMage_FrostVolley;
	FGameplayTag Abilities_FrostMage_IceFlurry;
	FGameplayTag Abilities_FrostMage_FrozenOrb;
	FGameplayTag Abilities_FrostMage_IceBlock;
	FGameplayTag Abilities_FrostMage_GlacialSpike;
	FGameplayTag Abilities_FrostMage_FrozenAir;
	FGameplayTag Abilities_FrostMage_IcyVeins;
	
	//CooldownTags
	FGameplayTag Cooldown_FrostMage_BasicAttack;
	FGameplayTag Cooldown_FrostMage_FrostNova;
	FGameplayTag Cooldown_FrostMage_FrostVolley;
	FGameplayTag Cooldown_FrostMage_IceFlurry;
	FGameplayTag Cooldown_FrostMage_FrozenOrb;
	FGameplayTag Cooldown_FrostMage_IceBlock;
	FGameplayTag Cooldown_FrostMage_GlacialSpike;
	FGameplayTag Cooldown_FrostMage_FrozenAir;
	FGameplayTag Cooldown_FrostMage_IcyVeins;
	
	// MagicArcher
	// AbilityTags
	FGameplayTag Abilities_MagicArcher_BasicAttack;
	FGameplayTag Abilities_MagicArcher_Aim;
	FGameplayTag Abilities_MagicArcher_ElementalShot;
	FGameplayTag Abilities_MagicArcher_ScatterShot;
	FGameplayTag Abilities_MagicArcher_ElementalInfusion;
	FGameplayTag Abilities_MagicArcher_RapidFire;
	FGameplayTag Abilities_MagicArcher_MagicTurret;
	FGameplayTag Abilities_MagicArcher_TrapShot;
	FGameplayTag Abilities_MagicArcher_RainOfArrows;
	FGameplayTag Abilities_MagicArcher_EnchantedArrow;
	
	//CooldownTags
	FGameplayTag Cooldown_MagicArcher_BasicAttack;
	FGameplayTag Cooldown_MagicArcher_Aim;
	FGameplayTag Cooldown_MagicArcher_ElementalShot;
	FGameplayTag Cooldown_MagicArcher_ScatterShot;
	FGameplayTag Cooldown_MagicArcher_ElementalInfusion;
	FGameplayTag Cooldown_MagicArcher_RapidFire;
	FGameplayTag Cooldown_MagicArcher_MagicTurret;
	FGameplayTag Cooldown_MagicArcher_TrapShot;
	FGameplayTag Cooldown_MagicArcher_RainOfArrows;
	FGameplayTag Cooldown_MagicArcher_EnchantedArrow;
	
	// TheLastOne
	// AbilityTags
	FGameplayTag Abilities_TheLastOne_BasicAttack;
	FGameplayTag Abilities_TheLastOne_Bash;
	FGameplayTag Abilities_TheLastOne_Glare;
	FGameplayTag Abilities_TheLastOne_Guard;
	FGameplayTag Abilities_TheLastOne_Engage;
	FGameplayTag Abilities_TheLastOne_Dissension;
	FGameplayTag Abilities_TheLastOne_EmptyBook;
	
	//CooldownTags
	FGameplayTag Cooldown_TheLastOne_BasicAttack;
	FGameplayTag Cooldown_TheLastOne_Bash;
	FGameplayTag Cooldown_TheLastOne_Glare;
	FGameplayTag Cooldown_TheLastOne_Guard;
	FGameplayTag Cooldown_TheLastOne_Engage;
	FGameplayTag Cooldown_TheLastOne_Dissension;
	FGameplayTag Cooldown_TheLastOne_EmptyBook;


	
	// Melee Combo Tags
	FGameplayTag Melee_ComboA1;
	FGameplayTag Melee_ComboA2;
	FGameplayTag Melee_ComboA3;
	FGameplayTag Melee_ComboA4;
	
	FGameplayTag Melee_ComboB1;
	FGameplayTag Melee_ComboB2;
	FGameplayTag Melee_ComboB3;
	FGameplayTag Melee_ComboB4;

	FGameplayTag Melee_ComboC1;
	FGameplayTag Melee_ComboC2;
	FGameplayTag Melee_ComboC3;
	FGameplayTag Melee_ComboC4;
	/*
	 * Champion end
	*/

	
	/*
	 * AI Enemy
	 */
	FGameplayTag Abilities_Enemy_Attack_Melee;
	
	/*
	 * AI Enemy end
	 */
	
	
	/*
	 * Event Tags
	 */ 
	//TODO: Rename tags to only Montage...
	// Player
	FGameplayTag Event_Montage_SaveAttack;
	FGameplayTag Event_Montage_ResetCombo;
	FGameplayTag Event_Montage_NextCombo;
	
	// AI
	FGameplayTag Event_Montage_Enemy_Attack_Weapon;
	FGameplayTag Event_Montage_Enemy_Attack_RightHand;
	FGameplayTag Event_Montage_Enemy_Attack_LeftHand;
	/*
	 * Event Tags end
	 */
	
	
private:
	static FAoCGameplayTags AoCGameplayTags;
};
