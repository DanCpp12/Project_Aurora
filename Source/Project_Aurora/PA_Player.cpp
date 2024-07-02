// Fill out your copyright notice in the Description page of Project Settings.


#include "PA_Player.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputAction.h"

// Sets default values
APA_Player::APA_Player()
{
	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera");
	SpringComp = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringComp->SetupAttachment(RootComponent);
	CameraComp->SetupAttachment(SpringComp);

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APA_Player::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController) {
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem) {
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

}

// Called every frame
void APA_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APA_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EInputComp) {
		EInputComp->BindAction(InputToMove, ETriggerEvent::Triggered, this, &APA_Player::HandleMovementInput);
	}
}

void APA_Player::HandleMovementInput(const FInputActionValue& Value)
{
	const FVector2D MoveVector = Value.Get<FVector2D>();
	APlayerCameraManager* CameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	if (CameraManager) {
		const FVector Forward = CameraManager->GetActorForwardVector();
		const FVector Right = CameraManager->GetActorRightVector();
		AddMovementInput(Forward, MoveVector.Y);
		AddMovementInput(Right, MoveVector.X);
	}
}
