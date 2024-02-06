// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "Abilities/GBAAttributeSetBlueprintBase.h"
#include "Clamping_Example_HealthSet.generated.h"

// Attribute accessors macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/** Please add a class description */
UCLASS(BlueprintType)
class GBA_CONTENTEXAMPLES_API UClamping_Example_HealthSet : public UGBAAttributeSetBlueprintBase
{
	GENERATED_BODY()
public:
	/** Please add a variable description dude! */
	UPROPERTY(BlueprintReadOnly, Category = "Default", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health = 0.00f;
	ATTRIBUTE_ACCESSORS(UClamping_Example_HealthSet, Health)

	/** Please add a variable description dude! */
	UPROPERTY(BlueprintReadOnly, Category = "Default", ReplicatedUsing = OnRep_Endurance)
	FGBAGameplayClampedAttributeData Endurance = 100.00f;
	ATTRIBUTE_ACCESSORS(UClamping_Example_HealthSet, Endurance)

	/** Used to limit the maximum amount of Endurance. */
	UPROPERTY(BlueprintReadOnly, Category = "Default", ReplicatedUsing = OnRep_MaxEndurance)
	FGameplayAttributeData MaxEndurance = 100.00f;
	ATTRIBUTE_ACCESSORS(UClamping_Example_HealthSet, MaxEndurance)

	/** Please add a variable description dude! */
	UPROPERTY(BlueprintReadOnly, Category = "Default", ReplicatedUsing = OnRep_Shield)
	FGameplayAttributeData Shield = 0.00f;
	ATTRIBUTE_ACCESSORS(UClamping_Example_HealthSet, Shield)
	
	/** You will need to add DOREPLIFETIME(UClamping_Example_HealthSet, VarName) to GetLifetimeReplicatedProps */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
protected:
	
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	
	UFUNCTION()
	virtual void OnRep_Endurance(const FGBAGameplayClampedAttributeData& OldEndurance);
	
	UFUNCTION()
	virtual void OnRep_MaxEndurance(const FGameplayAttributeData& OldMaxEndurance);
	
	UFUNCTION()
	virtual void OnRep_Shield(const FGameplayAttributeData& OldShield);
};