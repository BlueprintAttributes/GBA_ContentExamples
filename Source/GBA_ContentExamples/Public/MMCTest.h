// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMCTest.generated.h"

/**
 * 
 */
UCLASS()
class GBA_CONTENTEXAMPLES_API UMMCTest : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UMMCTest();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

protected:
	/**
	 * Gets the captured magnitude value for the given Attribute
	 * For this to work correctly, the Attribute needs to be added to the Relevant Attributes to Capture array
	 *
	 * @return The magnitude value if found, zero otherwise
	 */
	UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect", meta=(DisplayName="Get Captured Attribute Magnitude", ScriptName="GetCapturedAttributeMagnitude"))
	float K2_GetGet(const FGameplayEffectSpec& EffectSpec, FGameplayAttribute Attribute, const FGameplayTagContainer& SourceTags, const FGameplayTagContainer& TargetTags) const;

	static FGameplayAttribute GetAttributeProperty(const UClass* InClass, const FName& InPropertyName)
	{
		return FindFProperty<FProperty>(InClass, InPropertyName);
	}

private:
	FGameplayEffectAttributeCaptureDefinition EnduranceDef;
	FGameplayEffectAttributeCaptureDefinition FatigueDef;
};
