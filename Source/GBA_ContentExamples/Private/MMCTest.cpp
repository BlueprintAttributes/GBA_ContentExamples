// Fill out your copyright notice in the Description page of Project Settings.


#include "MMCTest.h"

#include "Clamping_Example_HealthSet.h"

UMMCTest::UMMCTest()
{
	const FString AttributeSetClassPath = TEXT("/Game/ExampleContent/03_MMC/GBA_MMC_Attributes.GBA_MMC_Attributes_C");
	const TSubclassOf<UAttributeSet> AttributeSetClass = StaticLoadClass(UAttributeSet::StaticClass(), nullptr, *AttributeSetClassPath);
	
	EnduranceDef = FGameplayEffectAttributeCaptureDefinition();
	EnduranceDef.AttributeToCapture = UClamping_Example_HealthSet::GetEnduranceAttribute();
	
	FatigueDef = FGameplayEffectAttributeCaptureDefinition();
	FatigueDef.AttributeToCapture = GetAttributeProperty(AttributeSetClass, TEXT("Fatigue"));
	
	RelevantAttributesToCapture.Add(EnduranceDef);
	RelevantAttributesToCapture.Add(FatigueDef);
}

float UMMCTest::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	const FString AttributeSetClassPath = TEXT("/Game/ExampleContent/03_MMC/GBA_MMC_Attributes.GBA_MMC_Attributes_C");
	const TSubclassOf<UAttributeSet> AttributeSetClass = StaticLoadClass(UAttributeSet::StaticClass(), nullptr, *AttributeSetClassPath);
	const FGameplayAttribute Attribute = GetAttributeProperty(AttributeSetClass, TEXT("Fatigue"));
	const float Fatigue = K2_GetGet(Spec, Attribute, *SourceTags, *TargetTags);
	
	float Endurance = 0.f;
	GetCapturedAttributeMagnitude(EnduranceDef, Spec, EvaluationParameters, Endurance);
	Endurance = FMath::Max<float>(Endurance, 0.0f);

	// float MaxMana = 0.f;
	// GetCapturedAttributeMagnitude(MaxManaDef, Spec, EvaluationParameters, MaxMana);
	// MaxMana = FMath::Max<float>(MaxMana, 1.0f);

	UE_LOG(LogTemp, Warning, TEXT("UMMCTest - Fatigue: %f, Endurance: %f"), Fatigue, Endurance);

	return 0.f;
}

float UMMCTest::K2_GetGet(const FGameplayEffectSpec& EffectSpec, FGameplayAttribute Attribute, const FGameplayTagContainer& SourceTags, const FGameplayTagContainer& TargetTags) const
{
	float Magnitude = 0.f;

	// look for the attribute in the capture list
	for (const FGameplayEffectAttributeCaptureDefinition& CurrentCapture : RelevantAttributesToCapture)
	{
		if (CurrentCapture.AttributeToCapture == Attribute)
		{
			// configure the aggregator evaluation parameters
			// TODO: apply filters?
			FAggregatorEvaluateParameters EvaluationParameters;

			EvaluationParameters.SourceTags = &SourceTags;
			EvaluationParameters.TargetTags = &TargetTags;

			// get the attribute magnitude
			GetCapturedAttributeMagnitude(CurrentCapture, EffectSpec, EvaluationParameters, Magnitude);

			// capture found. Stop the search
			break;
		}
	}

	return Magnitude;
}
