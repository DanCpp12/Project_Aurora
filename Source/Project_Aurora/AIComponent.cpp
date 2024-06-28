#include "AIComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Math/UnrealMathUtility.h"

UAIComponent::UAIComponent()
{
	//create sphere object
	ViewField = CreateDefaultSubobject<USphereComponent>("ViewField");
	ViewField->SetSphereRadius(300);
	ViewField->bOwnerNoSee = false;
	ViewField->SetHiddenInGame(false);
	ViewField->OnComponentBeginOverlap.AddDynamic(this, &UAIComponent::HandleBeginOverlap);
	ViewField->OnComponentEndOverlap.AddDynamic(this, &UAIComponent::HandleEndOverlap);
}

void UAIComponent::BeginPlay()
{
	Super::BeginPlay();

	//attach sphere to owner
	ViewField->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	GetOwner()->FinishAndRegisterComponent(ViewField);
	ViewField->SetupAttachment(GetOwner()->GetRootComponent());

	SpawnPoint = GetOwner()->GetActorLocation();
}

FVector UAIComponent::PlayMovmentAI()
{
	if (movementAI == MovementAI::Base)
	{
		if ((int)GetOwner()->GetActorLocation().X <= (int)target.X + 60 && (int)GetOwner()->GetActorLocation().Y <= (int)target.Y + 60 &&
			(int)GetOwner()->GetActorLocation().X >= (int)target.X - 60 && (int)GetOwner()->GetActorLocation().Y >= (int)target.Y - 60)
		{
			if (MovmentState == MovmentStates::Idle && !NewTarget)
			{
				MTimer = 0;
			}
			NewTarget = true;
		}
		if (!NewTarget) { NewTarget = IsStuck(); }
		DelayTimer += GetWorld()->DeltaTimeSeconds;

		Base_EnemyMovmentState();

		if (MovmentState == MovmentStates::Attack)
		{
			NewTarget = false;
			AttackMovement();
		}
		else if (MovmentState == MovmentStates::Idle && NewTarget)
		{
			if (MovmentTimer <= MTimer)
			{
				NewTarget = false;
				IdleMovement();
			}
			else
			{
				MTimer += GetWorld()->DeltaTimeSeconds;
			}
		
		}
		return target;
	}
	else if (movementAI == MovementAI::Boss)
	{
		BossMovementStates();
		UE_LOG(LogTemp, Log, TEXT("Movement state = %s"), *UEnum::GetValueAsString(MovmentState));
		return FVector(0,0,0);
	}
	return FVector(0, 0, 0);
}

bool UAIComponent::PlayCombatAI()
{
	if (MovmentState != MovmentStates::Attack)
	{
		CombatState = CombatStates::Null;
		UE_LOG(LogTemp, Log, TEXT("combat state = null"));
		return false;
	}
	else
	{
		Base_EnemyCombatState();
		if (CombatState == CombatStates::Basic_Attack)
		{
			UE_LOG(LogTemp, Log, TEXT("Hit enemy:"));
		}
		else if (CombatState == CombatStates::Block)
		{
			UE_LOG(LogTemp, Log, TEXT("Block enemy:"));
		}
		return true;
	}
}

void UAIComponent::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for (int i = 0; i < 10; ++i)
	{
		if (Targets[i] == nullptr && OtherActor->GetComponentByClass<UAIComponent>() == nullptr)
		{
			Targets[i] = OtherActor;
			return;
		}
	}
}

void UAIComponent::HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	for (int i = 0; i < 10; i++)
	{
		if (OtherActor == Targets[i])
		{
			Targets[i] = nullptr;
		}
	}
}

bool UAIComponent::IsStuck()
{
	if (FMath::IsNearlyEqual(GetOwner()->GetActorLocation().X, OldPosition.X, 4) &&
		FMath::IsNearlyEqual(GetOwner()->GetActorLocation().Y, OldPosition.Y, 4))
	{
		if (Delay <= DelayTimer)
		{
			OldPosition = GetOwner()->GetActorLocation();
			DelayTimer = 0;
		}
		return true;
	}
	else
	{
		if (Delay <= DelayTimer)
		{
			OldPosition = GetOwner()->GetActorLocation();
			DelayTimer = 0;
		}
		return false;
	}
}

void UAIComponent::Base_EnemyMovmentState()
{
	for (int i = 0; i < 10; ++i)
	{
		if (Targets[i] != nullptr)
		{
			MovmentState = MovmentStates::Attack;
			return;
		}
		else
		{
			MovmentState = MovmentStates::Idle;
		}
	}
}

void UAIComponent::Base_EnemyCombatState()
{
	int randstate = FMath::RandRange(1, 2);
	if (randstate == 1)
	{
		CombatState = CombatStates::Basic_Attack;
	}
	else if (randstate == 2)
	{
		CombatState = CombatStates::Block;
	}
}

void UAIComponent::BossMovementStates()
{
	int randstate;
	randstate = FMath::RandRange(1, 2);
	if (MovmentState == MovmentStates::Backup)
	{
		if (randstate == 1)
		{
			MovmentState = MovmentStates::Charge;
		}
		else if (randstate == 2)
		{
			MovmentState = MovmentStates::Attack;
		}
		return;
	}
	else if (randstate == 1)
	{
		MovmentState = MovmentStates::Attack;
	}
	else if (randstate == 2)
	{
		MovmentState = MovmentStates::Backup;
	}
	/*for (int i = 1; i < 10; ++i)
	{
		if (Targets[i] != nullptr)
		{
			randstate = FMath::RandRange(1, 2);
			if (MovmentState == MovmentStates::Backup)
			{
				randstate = FMath::RandRange(1, 3);
				if (randstate == 1)
				{
					MovmentState = MovmentStates::Charge;
				}
				else if (randstate == 2)
				{
					MovmentState = MovmentStates::Backup;
				}
				else if (randstate == 3)
				{
					MovmentState = MovmentStates::Attack;
				}
			}
			else if (randstate == 1)
			{
				MovmentState = MovmentStates::Attack;
			}
		}
	}*/
}

void UAIComponent::AttackMovement()
{
	for (int i = 0; i < 10; ++i)
	{
		if (Targets[i] != nullptr)
		{
			target = Targets[i]->GetActorLocation();
			return;
		}
	}
}

void UAIComponent::IdleMovement()
{
	float angle = FMath::RandRange(-45.f, 45.f);
	angle += GetOwner()->GetActorRotation().Yaw;
	FVector offset = FVector(cosf(angle), sinf(angle), 0) * TravleDistanse;
	if (FVector::DistXY(GetOwner()->GetActorLocation() + offset, SpawnPoint) <= MovmentRadiusFromSpawnPoint)
	{
		target = GetOwner()->GetActorLocation() + offset;
		target.Z = 100.f;
		UE_LOG(LogTemp, Log, TEXT("move to random position: %f, %f, %f"), target.X, target.Y, target.Z);
	}
}
