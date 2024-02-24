// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecCalcTest.generated.h"

/**
 * 
 */
UCLASS()
class GBA_CONTENTEXAMPLES_API UExecCalcTest : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UExecCalcTest();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
	
	static FGameplayAttribute GetAttributeProperty(const UClass* InClass, const FName& InPropertyName)
	{
		return FindFProperty<FProperty>(InClass, InPropertyName);
	}
	
	static FGameplayAttribute GetAttributeProperty(const FString& InPackageName, const FName& InPropertyName)
	{
		const TSubclassOf<UAttributeSet> AttributeSetClass = StaticLoadClass(UAttributeSet::StaticClass(), nullptr, *InPackageName);
		if (!AttributeSetClass)
		{
			UE_LOG(LogTemp, Warning, TEXT("UExecCalcTest::GetAttributeProperty - Unable to get class from PackageName: %s"), *InPackageName)
			FGameplayAttribute Dummy;
			return Dummy;
		}
		
		return FindFProperty<FProperty>(AttributeSetClass, InPropertyName);
	}

private:
	static void DebugGameplayEffectAttributeCaptureDefinition(const FGameplayEffectAttributeCaptureDefinition& InDefinition);

	static double GetDistanceToTarget(const FGameplayEffectCustomExecutionParameters& InExecutionParams);
};
