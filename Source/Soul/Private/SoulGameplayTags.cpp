// All Rights Reserved.


#include "SoulGameplayTags.h"

namespace SoulGameplayTags
{
	/** Input Tags **/
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Interact, "InputTag.Interact");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_OpenMenu, "InputTag.OpenMenu");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack_Light, "InputTag.Attack.Light");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack_Heavy, "InputTag.Attack.Heavy");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Skill_Q, "InputTag.Skill.Q");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Skill_E, "InputTag.Skill.E");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Skill_Ultimate, "InputTag.Skill.Ultimate");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Blink, "InputTag.Blink");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Dash, "InputTag.Dash");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Rolling, "InputTag.Rolling");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_SwitchTarget, "InputTag.SwitchTarget");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable, "InputTag.Toggleable");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable_TargetLock, "InputTag.Toggleable.TargetLock");

	/** Player Tags**/
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light, "Player.Ability.Attack.Light");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Heavy, "Player.Ability.Attack.Heavy");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Skill_Q, "Player.Ability.Skill.Q");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Skill_E, "Player.Ability.Skill.E");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Skill_Ultimate, "Player.Ability.Skill.Ultimate");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Blink, "Player.Ability.Blink");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Dash, "Player.Ability.Dash");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Rolling, "Player.Ability.Rolling");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_TargetLock, "Player.Ability.TargetLock");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_HitPause, "Player.Ability.HitPause");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Light, "Player.SetByCaller.AttackType.Light");
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Heavy, "Player.SetByCaller.AttackType.Heavy");
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Q, "Player.SetByCaller.AttackType.Q");
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_E, "Player.SetByCaller.AttackType.E");
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Ultimate, "Player.SetByCaller.AttackType.Ultimate");

	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Blink, "Player.Status.Blink");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Dash, "Player.Status.Dash");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Rolling, "Player.Status.Rolling");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Invincible, "Player.Status.Invincible");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_TargetLock, "Player.Status.TargetLock");

	UE_DEFINE_GAMEPLAY_TAG(Player_Event_SwitchTarget_Left, "Player.Event.SwitchTarget.Left");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_SwitchTarget_Right, "Player.Event.SwitchTarget.Right");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_HitPause, "Player.Event.HitPause");



	/** Enemy Tags**/
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee, "Enemy.Ability.Melee");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee_LightAttack, "Enemy.Ability.Melee.Light");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee_Combo, "Enemy.Ability.Melee.Combo");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee_Shield, "Enemy.Ability.Melee.Shield");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee_ShieldCombo, "Enemy.Ability.Melee.ShieldCombo");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee_Swing, "Enemy.Ability.Melee.Swing");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Dash_Jump, "Enemy.Ability.Dash.Jump");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Dash_Swing, "Enemy.Ability.Dash.Swing");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Ranged, "Enemy.Ability.Ranged");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Teleport, "Enemy.Ability.Teleprot");

	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Strafing, "Enemy.Status.Strafing");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Attack, "Enemy.Status.Attack");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_UnderAttack, "Enemy.Status.UnderAttack");


	/** Shared Tags**/
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact, "Shared.Ability.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_StunReact, "Shared.Ability.StunReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Death, "Shared.Ability.Death");

	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeHit, "Shared.Event.MeleeHit");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact, "Shared.Event.HitReact");

	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseDamage, "Shared.SetByCaller.BaseDamage");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_Energy, "Shared.SetByCaller.Energy");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_GuardGauge, "Shared.SetByCaller.GuardGauge");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_Cost_Stamina, "Shared.SetByCaller.Cost.Stamina");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_Cost_Energy, "Shared.SetByCaller.Cost.Energy");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_Steal_Health, "Shared.SetByCaller.Steal.Health");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_Duration_Invincible, "Shared.SetByCaller.Duration.Invincible");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_Duration_Stun, "Shared.SetByCaller.Duration.Stun");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_Duration_CutScene, "Shared.SetByCaller.Duration.CutScene");

	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Dead, "Shared.Status.Dead");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Stun, "Shared.Status.Stun");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_RecoverGuardGauge, "Shared.Status.RecoverGuardGauge");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Front, "Shared.Status.HitReact.Front");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Left, "Shared.Status.HitReact.Left");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Right, "Shared.Status.HitReact.Right");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Back, "Shared.Status.HitReact.Back");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_CutScene, "Shared.Status.CutScene");
}