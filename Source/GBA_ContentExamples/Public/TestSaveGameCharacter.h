// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TestSaveGameCharacter.generated.h"

UCLASS()
class GBA_CONTENTEXAMPLES_API ATestSaveGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestSaveGameCharacter();

	virtual void Serialize(FArchive& Ar) override;
};
