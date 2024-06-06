// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Project_AuroraCharacter.generated.h"
class UInputMappingContext;
class UInputAction;
class UAttributesComponent;
struct FInputActionValue;
UCLASS(Blueprintable)
class AProject_AuroraCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AProject_AuroraCharacter();
	virtual void BeginPlay() override;
	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	
	//Attributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float Strength = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float Dexterity = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float Vitality = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float Energy = 1.f;
	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UHealthComponent* HealthComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UAttributesComponent* AttributesComponent = nullptr;

	//Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MoveInputAction;

	void MoveInput(const FInputActionValue& Value);

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;
	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
};

