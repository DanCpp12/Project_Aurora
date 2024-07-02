// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PA_Player.generated.h"


struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class USpringArmComponent;
class UCameraComponent;


UCLASS()
class PROJECT_AURORA_API APA_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APA_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health = 100.f;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Setup Default Components
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringComp = nullptr;
	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComp = nullptr;

	//Inputs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* InputToMove;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* InputLightAttack;

	UFUNCTION()
	void HandleMovementInput(const FInputActionValue& Value);

};
