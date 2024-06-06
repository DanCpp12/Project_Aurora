// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_AuroraCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "HealthComponent.h"
#include "AttributesComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
AProject_AuroraCharacter::AProject_AuroraCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//Setup Health & Attributes Components
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("Health");
	AttributesComponent = CreateDefaultSubobject<UAttributesComponent>("Attributes");

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AProject_AuroraCharacter::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp,
		Log, 
		TEXT("Attributes: Strength - %f, Dexterity - %f, Vitality - %f, Energy - %f"),
		Strength, Dexterity, Vitality, Energy);
}

void AProject_AuroraCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}



void AProject_AuroraCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			SubSystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	// Set up action bindings
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AProject_AuroraCharacter::MoveInput);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}
void AProject_AuroraCharacter::MoveInput(const FInputActionValue& Value)
{
	const FVector2D MoveVector = Value.Get<FVector2D>();
	const FRotator MoveRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0);
	if (MoveVector.X > 0.05f || MoveVector.X < -0.05f) {
		const FVector DirectionVector = MoveRotation.RotateVector(FVector::RightVector);
		AddMovementInput(DirectionVector, MoveVector.X);
	}
	if (MoveVector.Y > 0.05f || MoveVector.Y < -0.05f) {
		const FVector DirectionVector = MoveRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(DirectionVector, MoveVector.Y);
	}
}
