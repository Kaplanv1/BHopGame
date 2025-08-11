// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Tags/BHopGameplayTags.h"

namespace BHopGameplayTags
{
	// Input Tags
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_EquipKatana, "InputTag.EquipKatana");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UnequipKatana, "InputTag.UnequipKatana");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_PrimaryAttack_Katana, "InputTag.PrimaryAttack.Katana");

	// Player Tags
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Katana, "Player.Ability.Equip.Katana");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_Katana, "Player.Ability.Unequip.Katana");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Primary_Attack_Katana, "Player.Ability.Attack.Primary.Katana");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_HitPause, "Player.Ability.HitPause");
		

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Weapon_Attack, "Player.Weapon.Katana");	

	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_Katana, "Player.Event.Equip.Katana");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Unequip_Katana, "Player.Event.Unequip.Katana");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_HitPause, "Player.Event.HitPause");

	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Light, "Player.SetByCaller.AttackType.Light");

	//Enemy Tags
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Weapon, "Enemy.Weapon")

	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee, "Enemy.Ability.Melee");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Ranged, "Enemy.Ability.Ranged");
	
	// Shared Tags
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeHit, "Shared.Event.MeleeHit");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseDamage, "Shared.SetByCaller.BaseDamage");

	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact, "Shared.Ability.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact, "Shared.Event.HitReact");
	


} 