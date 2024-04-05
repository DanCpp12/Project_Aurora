// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributesComponent.generated.h"


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
	float Strength = 0.f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float Dexterity = 0.f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float Vitality = 0.f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float Energy = 0.f;
};
