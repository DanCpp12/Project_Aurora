// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributesComponent.generated.h"

UENUM(BlueprintType)
enum class EAttribute {
	STRENGTH = 0,
	DEXTERITY = 1,
	VITALITY = 2,
	ENERGY = 3
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_AURORA_API UAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributesComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float Strength = 0.f; //Affects ability to carry heavy equipment & Melee dmg
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float Dexterity = 0.f; //Affects Ranged accuracy & dodge chance. Improves dmg of dex weapons
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float Vitality = 0.f; //Affects HP & Stamina
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float VitalityAdd = 2.f;//How much Vitality should increase Max Health
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float Energy = 0.f; //Affects Mana & Mana regen. Improves cast rate & spell crit

	UFUNCTION()
	void LevelUp(EAttribute Attribute);

};
