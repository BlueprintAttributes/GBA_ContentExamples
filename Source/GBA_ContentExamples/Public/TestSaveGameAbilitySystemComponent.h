// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "TestSaveGameAbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GBA_CONTENTEXAMPLES_API UTestSaveGameAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	virtual void Serialize(FArchive& Ar) override;
};
