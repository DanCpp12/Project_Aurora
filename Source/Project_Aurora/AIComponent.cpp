#include "AIComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Math/UnrealMathUtility.h"
#include "Logging/StructuredLog.h"

UAIComponent::UAIComponent()
{
	//create sphere object
	ViewField = CreateDefaultSubobject<USphereComponent>("ViewField");
	ViewField->bOwnerNoSee = false;
	ViewField->SetHiddenInGame(false);
	ViewField->OnComponentBeginOverlap.AddDynamic(this, &UAIComponent::HandleBeginOverlap);
	ViewField->OnComponentEndOverlap.AddDynamic(this, &UAIComponent::HandleEndOverlap);
}

void UAIComponent::BeginPlay()
{
	Super::BeginPlay();

	//attach sphere to owner
	ViewField->SetSphereRadius(ViewFieldSize);
	ViewField->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	GetOwner()->FinishAndRegisterComponent(ViewField);
	ViewField->SetupAttachment(GetOwner()->GetRootComponent());

	SpawnPoint = GetOwner()->GetActorLocation();
}

FAIReturn UAIComponent::PlayMovmentAI()
{
	if ((int)GetOwner()->GetActorLocation().X <= (int)target.X + 60 && (int)GetOwner()->GetActorLocation().Y <= (int)target.Y + 60 &&
		(int)GetOwner()->GetActorLocation().X >= (int)target.X - 60 && (int)GetOwner()->GetActorLocation().Y >= (int)target.Y - 60 || AttckTimer >= AttackTime)
	{
		if (MovmentState == MovmentStates::Idle && !NewTarget)
		{
			MTimer = 0;
		}
		if (AttckTimer >= AttackTime)
		{
			AttckTimer = 0;
		}
		bCanCharge = true;
		NewTarget = true;
		bPathFind = true;
	}
	
	if (!NewTarget) { NewTarget = IsStuck(); }
	DelayTimer += GetWorld()->DeltaTimeSeconds;

	if (movementAI == MovementAI::Base)
	{
		if (NewTarget)
		{
			Base_EnemyMovmentState();
		}

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
		else
		{
			return FAIReturn(GetOwner()->GetActorLocation(), bPathFind);
		}
		return FAIReturn(target, bPathFind);
	}
	else if (movementAI == MovementAI::Boss)
	{
		if (NewTarget)
		{
			BossMovementStates();
		}

		if (MovmentState == MovmentStates::Attack)
		{
			NewTarget = false;
			AttackMovement();
			AttckTimer += GetWorld()->DeltaTimeSeconds;
		}
		else if (MovmentState == MovmentStates::Backup)
		{
			NewTarget = false;
			BackupMovement();
		}
		else if (MovmentState == MovmentStates::Charge)
		{
			NewTarget = false;
			bPathFind = false;
			if (bCanCharge)
			{
				ChargeMovement();
				ChargeTimer += GetWorld()->DeltaTimeSeconds;
			}
			/*GetOwner()->AddActorLocalOffset(target, true);
			return;*/
		}
		else
		{
			return FAIReturn(GetOwner()->GetActorLocation(), bPathFind);
		}
		return FAIReturn(target, bPathFind);
	}
	return FAIReturn(GetOwner()->GetActorLocation(), bPathFind);
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
			if (MovmentState == MovmentStates::Attack && AttckTimer >= AttackTime)
			{
				OldPosition = GetOwner()->GetActorLocation();
				DelayTimer = 0;
				return true;
			}
			else if (MovmentState == MovmentStates::Backup || MovmentState == MovmentStates::Idle)
			{
				OldPosition = GetOwner()->GetActorLocation();
				DelayTimer = 0;
				return true;
			}
			else if (MovmentState == MovmentStates::Charge && ChargeTimer >= TimeToCharge)
			{
				OldPosition = GetOwner()->GetActorLocation();
				DelayTimer = 0;
				return true;
			}
			return false;
		}
		return false;
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
	
	for (int i = 0; i < 10; ++i)
	{
		if (Targets[i] != nullptr)
		{
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
			return;
		}
		else
		{
			MovmentState = MovmentStates::Null;
		}
	}
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

void UAIComponent::BackupMovement()
{
	for (int i = 0; i < 10; ++i)
	{
		if (Targets[i] != nullptr)
		{
			FVector Dir = Targets[i]->GetActorLocation() - GetOwner()->GetActorLocation();
			Dir.Normalize();
			target = Dir * -BackupDistance + GetOwner()->GetActorLocation();
			return;
		}
		else
		{
			target = GetOwner()->GetActorLocation();
		}
	}
}

void UAIComponent::ChargeMovement()
{
	if (TimeToCharge <= ChargeTimer)
	{
		ChargeTimer = 0;
		for (int i = 0; i < 10; ++i)
		{
			if (Targets[i] != nullptr)
			{
				FVector Dir = Targets[i]->GetActorLocation() - GetOwner()->GetActorLocation();
				Dir.Normalize();
				target = Dir * ChargeDistance + GetOwner()->GetActorLocation();
				bCanCharge = false;
				return;
			}
			else
			{
				target = GetOwner()->GetActorLocation();
			}
		}
	}
	else
	{
		target = FVector(-10000000000, 0, 0);
	}
}
