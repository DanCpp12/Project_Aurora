// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	CurrentHealth = MaxHealth;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{

	Super::BeginPlay();
	//Check to make sure health and armor work correctly
	UE_LOG(LogTemp, Log, TEXT("Health: %f/%f"), CurrentHealth, MaxHealth);
	UE_LOG(LogTemp, Log, TEXT("Armor: %f"), Armor);
	TakeDamage(20.f);
	
}

void UHealthComponent::TakeDamage(float Damage)
{

	//Make it so you can't completely ignore damage
	if (Armor >= Damage) {
		CurrentHealth -= 1.f;
	}
	else {
		CurrentHealth -= Damage - Armor;
	}
	UE_LOG(LogTemp, Log, TEXT("Damage: %f"), Damage);
	UE_LOG(LogTemp, Log, TEXT("Health: %f/%f"), CurrentHealth, MaxHealth);
}

