// Fill out your copyright notice in the Description page of Project Settings.


#include "TestSaveGameAbilitySystemComponent.h"

#include "Utils/GBAUtils.h"


void UTestSaveGameAbilitySystemComponent::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	if (Ar.IsSaveGame())
	{
		FGBAUtils::SerializeAbilitySystemComponentAttributes(this, Ar);
	}
}
