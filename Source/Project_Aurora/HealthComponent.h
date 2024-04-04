// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class UArmorComponent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_AURORA_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

protected:
	UHealthComponent();
	// Called when the game starts
	virtual void BeginPlay() override;
	void TakeDamage(float Damage);

public:	
	UPROPERTY(BlueprintReadOnly)
	float CurrentHealth = 0.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (UIMin = "1.0", UIMax = "100.0"))
	float MaxHealth = 100.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Armor = 10.f;
};
