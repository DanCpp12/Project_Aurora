// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributesComponent.h"

// Sets default values for this component's properties
UAttributesComponent::UAttributesComponent()
{
	Strength = 1.f;
	Dexterity = 1.f;
	Vitality = 1.f;
	Energy = 1.f;
}

void UAttributesComponent::BeginPlay() {

	Super::BeginPlay();
}

void UAttributesComponent::LevelUp(EAttribute Attribute)
{
	if (Attribute == EAttribute::STRENGTH) {
		Strength++;
	}
	else if (Attribute == EAttribute::DEXTERITY) {
		Dexterity++;
	}
	else if (Attribute == EAttribute::VITALITY) {
		Vitality++;
	}
	else if (Attribute == EAttribute::ENERGY) {
		Energy++;
	}
	else {
		UE_LOG(LogTemp,Error, TEXT("Invalid Attribute Type"))
	}
}



