// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Project_AuroraCharacter.generated.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float Strength = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float Dexterity = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float Vitality = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float Energy = 1.f;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;
	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere)
	class UHealthComponent* HealthComponent = nullptr;
	UPROPERTY(VisibleAnywhere)
	class UAttributesComponent* AttributesComponent = nullptr;

};

