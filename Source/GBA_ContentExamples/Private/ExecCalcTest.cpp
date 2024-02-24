// Fill out your copyright notice in the Description page of Project Settings.


#include "ExecCalcTest.h"

#include "AbilitySystemComponent.h"
#include "NativeGameplayTags.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ExecCalcTest)

UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_GameplayEffect_Calculation_EnableDistanceMitigation, "GameplayEffect.Calculation.EnableDistanceMitigation");

struct FDamageCapturedAttributes
{
	FGameplayEffectAttributeCaptureDefinition AttackPower;
	FGameplayEffectAttributeCaptureDefinition Armor;
	FGameplayEffectAttributeCaptureDefinition Damage;
	
	FDamageCapturedAttributes()
	{
		const FString AttributeSetClassPath = TEXT("/Game/ExampleContent/04_ExecCalc/GBA_ExecClass_Set.GBA_ExecClass_Set_C");

		AttackPower = FGameplayEffectAttributeCaptureDefinition(
			UExecCalcTest::GetAttributeProperty(AttributeSetClassPath, TEXT("AttackPower")),
			EGameplayEffectAttributeCaptureSource::Source,
			false
		);
		
		Armor = FGameplayEffectAttributeCaptureDefinition(
			UExecCalcTest::GetAttributeProperty(AttributeSetClassPath, TEXT("Armor")),
			EGameplayEffectAttributeCaptureSource::Target,
			false
		);
		
		Damage = FGameplayEffectAttributeCaptureDefinition(
			UExecCalcTest::GetAttributeProperty(AttributeSetClassPath, TEXT("Damage")),
			EGameplayEffectAttributeCaptureSource::Source,
			true
		);
	}

	static FDamageCapturedAttributes& Get()
	{
		static FDamageCapturedAttributes CapturedAttributes;
		return CapturedAttributes;
	}
};

UExecCalcTest::UExecCalcTest()
{
	const FDamageCapturedAttributes CapturedAttributes = FDamageCapturedAttributes::Get();
	RelevantAttributesToCapture.Add(CapturedAttributes.AttackPower);
	RelevantAttributesToCapture.Add(CapturedAttributes.Armor);
	RelevantAttributesToCapture.Add(CapturedAttributes.Damage);

	DebugGameplayEffectAttributeCaptureDefinition(CapturedAttributes.AttackPower);
	DebugGameplayEffectAttributeCaptureDefinition(CapturedAttributes.Armor);
	DebugGameplayEffectAttributeCaptureDefinition(CapturedAttributes.Damage);
}

void UExecCalcTest::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UE_LOG(LogTemp, Warning, TEXT("UExecCalcTest Execute_Implementation ..."))

	const FDamageCapturedAttributes CapturedAttributes = FDamageCapturedAttributes::Get();
	DebugGameplayEffectAttributeCaptureDefinition(CapturedAttributes.AttackPower);
	DebugGameplayEffectAttributeCaptureDefinition(CapturedAttributes.Armor);
	DebugGameplayEffectAttributeCaptureDefinition(CapturedAttributes.Damage);
	
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	FGameplayEffectContextHandle EffectContext = Spec.GetContext();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float BaseDamage = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CapturedAttributes.Damage, EvaluateParameters, BaseDamage);
	UE_LOG(LogTemp, Display, TEXT("\t UExecCalcTest Execute_Implementation - BaseDamage: %f"), BaseDamage)
	
	float AttackPower = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CapturedAttributes.AttackPower, EvaluateParameters, AttackPower);
	UE_LOG(LogTemp, Display, TEXT("\t UExecCalcTest Execute_Implementation - AttackPower: %f"), AttackPower)
	
	float Armor = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CapturedAttributes.Armor, EvaluateParameters, Armor);
	UE_LOG(LogTemp, Display, TEXT("\t UExecCalcTest Execute_Implementation - Armor: %f"), Armor)
	
	float DamageToApply = FMath::Max(BaseDamage, 0.f);
	
	// Calculate distance to target - Credits to LyraDamageExecution
	// If Effect spec has GameplayEffect.Calculation.EnableDistanceMitigation as part of its Asset Tags
	const bool bEnableDistanceCalculation = SourceTags->HasTagExact(TAG_GameplayEffect_Calculation_EnableDistanceMitigation);
	UE_LOG(LogTemp, Display, TEXT("\t UExecCalcTest Execute_Implementation - bEnableDistanceCalculation: %s"), *LexToString(bEnableDistanceCalculation))
	if (bEnableDistanceCalculation)
	{
		const double Distance = GetDistanceToTarget(ExecutionParams);
		UE_LOG(LogTemp, Display, TEXT("\t UExecCalcTest Execute_Implementation - Distance: %f"), Distance)

		// Distance attenuation calculation basics
		// At 10m, coefficient is set to 1 (no modification of BaseDamage)
		// Higher we see attenuation the greater the distance is
		// Lower damage is increased the closer we are to the target
		constexpr float DistanceThreshold = 10.f;
		const float DistanceAttenuation = DistanceThreshold / (Distance / 100.f);

		DamageToApply = FMath::Max(BaseDamage * DistanceAttenuation, 0.f);
		UE_LOG(LogTemp, Display, TEXT("\t UExecCalcTest Execute_Implementation - Distance: %f, DistanceAttenuation: %f, Damage: %f"), Distance, DistanceAttenuation, DamageToApply)
	}

	// Attack Power scaling
	//
	// Very simple, attribute acts as a percentage multiplier.
	// Value of 100 means no modification, lower acts as mitigation, higher acts as multiplier.
	UE_LOG(LogTemp, Display, TEXT("\t UExecCalcTest Execute_Implementation - before Attack Power scaling DamageToApply: %f, AttackPower: %f"), DamageToApply, AttackPower)
	DamageToApply = DamageToApply * (AttackPower / 100.f);
	UE_LOG(LogTemp, Display, TEXT("\t UExecCalcTest Execute_Implementation - after Attack Power scaling DamageToApply: %f, AttackPower: %f"), DamageToApply, AttackPower)

	// Armor mitigation
	//
	// Inspired by https://www.totalwar.com/blog/ff2-damage-1/ total war armor piercing calculation
	//
	// > Their armour value is 30, which means that they can reduce the Base portion of the attack by a percentage value
	// > between 15% and 30% [...]
	//
	// > For the sake of this test, the Spearmen have rolled a value of 27.4667 against this attack, a respectable
	// result. This reduces the 16.714 Base damage down to 12.123; a measly four points shaved off this heavily
	// piercing attack!
	//
	// In this case, for an armor roll of 27.4667, and a 16.714 Base damage. 16.714 gets reduced by 27.4667%
	// => Final Damage = BaseDamage * (1 - ArmorPercentage)
	// => Final Damage = 16.714 * (1 - 27.4667 / 100) = 12.123215762

	UE_LOG(LogTemp, Display, TEXT("\t UExecCalcTest Execute_Implementation - before Armor mitigation DamageToApply: %f, Armor: %f"), DamageToApply, Armor)
	DamageToApply = DamageToApply * (1 - Armor / 100.f);
	UE_LOG(LogTemp, Display, TEXT("\t UExecCalcTest Execute_Implementation - after Armor mitigation DamageToApply: %f, Armor: %f"), DamageToApply, Armor)
	
	if (DamageToApply > 0.f)
	{
		const FGameplayAttribute Health = GetAttributeProperty(
			TEXT("/Game/ExampleContent/01_BlueprintAttributes_Welcome/GBA_Health_Set.GBA_Health_Set_C"),
			TEXT("Health")
		);
		
		if (Health.IsValid())
		{
			UE_LOG(LogTemp, Display, TEXT("\t UExecCalcTest Execute_Implementation - Output Health modifier with %f"), -DamageToApply)
			OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(Health, EGameplayModOp::Additive, -DamageToApply));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("\t UExecCalcTest Execute_Implementation - Error getting Health Attribute. Cannot output modifier."))
		}
	}
}

void UExecCalcTest::DebugGameplayEffectAttributeCaptureDefinition(const FGameplayEffectAttributeCaptureDefinition& InDefinition)
{
	UE_LOG(
		LogTemp,
		Display,
		TEXT("UExecCalcTest DebugGameplayEffectAttributeCaptureDefinition - %s IsValid: %s"),
		*InDefinition.AttributeToCapture.GetName(),
		*LexToString(InDefinition.AttributeToCapture.IsValid())
	)
}

double UExecCalcTest::GetDistanceToTarget(const FGameplayEffectCustomExecutionParameters& InExecutionParams)
{
	double Distance = WORLD_MAX;
	
	const FGameplayEffectSpec& Spec = InExecutionParams.GetOwningSpec();
	const FGameplayEffectContextHandle EffectContext = Spec.GetContext();
	
	const AActor* EffectCauser = EffectContext.GetEffectCauser();
	const FHitResult* HitActorResult = EffectContext.GetHitResult();

	FVector ImpactLocation = FVector::ZeroVector;

	// Calculation of hit actor, surface, zone, and distance all rely on whether the calculation has a hit result or not.
	// Effects just being added directly w/o having been targeted will always come in without a hit result, which must default
	// to some fallback information.
	if (HitActorResult)
	{
		const FHitResult& CurHitResult = *HitActorResult;
		const AActor* HitActor = CurHitResult.HitObjectHandle.FetchActor();
		if (HitActor)
		{
			ImpactLocation = CurHitResult.ImpactPoint;
		}
	}

	// Handle case of no hit result or hit result not actually returning an actor
	if (ImpactLocation.IsZero())
	{
		const UAbilitySystemComponent* TargetAbilitySystemComponent = InExecutionParams.GetTargetAbilitySystemComponent();
		const AActor* HitActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor_Direct() : nullptr;
		if (HitActor)
		{
			ImpactLocation = HitActor->GetActorLocation();
		}
	}

	if (EffectContext.HasOrigin())
	{
		Distance = FVector::Dist(EffectContext.GetOrigin(), ImpactLocation);
	}
	else if (EffectCauser)
	{
		Distance = FVector::Dist(EffectCauser->GetActorLocation(), ImpactLocation);
	}
	else
	{
		ensureMsgf(false, TEXT("UExecCalcTest Damage Calculation cannot deduce a source location for damage coming from %s; Falling back to WORLD_MAX dist!"), *GetPathNameSafe(Spec.Def));
	}
	
	return Distance;
}

