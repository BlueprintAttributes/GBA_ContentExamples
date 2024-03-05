// Fill out your copyright notice in the Description page of Project Settings.


#include "TestSaveGameCharacter.h"


// Sets default values
ATestSaveGameCharacter::ATestSaveGameCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATestSaveGameCharacter::Serialize(FArchive& Ar)
{
	if (Ar.IsSaveGame())
	{
		UE_LOG(LogTemp, Display, TEXT("Saving Gaming"))
	}
	
	Super::Serialize(Ar);
}

