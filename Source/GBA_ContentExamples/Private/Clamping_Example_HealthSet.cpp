// Fill out your copyright notice in the Description page of Project Settings.

#include "Clamping_Example_HealthSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

void UClamping_Example_HealthSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UClamping_Example_HealthSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UClamping_Example_HealthSet, Endurance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UClamping_Example_HealthSet, MaxEndurance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UClamping_Example_HealthSet, Shield, COND_None, REPNOTIFY_Always);
}

void UClamping_Example_HealthSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UClamping_Example_HealthSet, Health, OldHealth);
}

void UClamping_Example_HealthSet::OnRep_Endurance(const FGBAGameplayClampedAttributeData& OldEndurance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UClamping_Example_HealthSet, Endurance, OldEndurance);
}

void UClamping_Example_HealthSet::OnRep_MaxEndurance(const FGameplayAttributeData& OldMaxEndurance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UClamping_Example_HealthSet, MaxEndurance, OldMaxEndurance);
}

void UClamping_Example_HealthSet::OnRep_Shield(const FGameplayAttributeData& OldShield)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UClamping_Example_HealthSet, Shield, OldShield);
}
