#include "AIComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Math/UnrealMathUtility.h"

UAIComponent::UAIComponent()
{
	//create sphere object
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetSphereRadius(300);
	Sphere->bOwnerNoSee = false;
	Sphere->SetHiddenInGame(false);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &UAIComponent::HandleBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &UAIComponent::HandleEndOverlap);
}

void UAIComponent::BeginPlay()
{
	Super::BeginPlay();

	//attach sphere to owner
	Sphere->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	GetOwner()->FinishAndRegisterComponent(Sphere);
	Sphere->SetupAttachment(GetOwner()->GetRootComponent());

	SpawnPoint = GetOwner()->GetActorLocation();
}

FVector UAIComponent::base_EnemyMovmentAI()
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
	Base_EnemyMovmentState();

	if (MovmentState == MovmentStates::Attack)
	{
		NewTarget = false;
		//UE_LOG(LogTemp, Log, TEXT("Attack actor att location: %f, %f, %f"), target.X, target.Y, target.Z);
	}
	else if (MovmentState == MovmentStates::Idle && NewTarget)
	{
		if (MovmentTimer <= MTimer)
		{
			NewTarget = false;
			float angle = FMath::RandRange(-45.f, 45.f);
			angle += GetOwner()->GetActorRotation().Yaw;
			FVector offset = FVector(cosf(angle), sinf(angle), 0) * MovmentRange;
			if (FVector::DistXY(GetOwner()->GetActorLocation() + offset, SpawnPoint) <= MovmentRadiusFromSpawnPoint)
			{
				target = GetOwner()->GetActorLocation() + offset;
				target.Z = 100.f;
				UE_LOG(LogTemp, Log, TEXT("move to random position: %f, %f, %f"), target.X, target.Y, target.Z);
			}
		}
		else
		{
			MTimer += GetWorld()->DeltaTimeSeconds;
		}
		
	}
	return target;
}

bool UAIComponent::base_EnemyCombatAI()
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
		if (CombatState == CombatStates::Attack)
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
		if (Targets[i] == nullptr)
		{
			Targets[i] = OtherActor;
			return;
		}
	}
	base_EnemyMovmentAI();
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
	base_EnemyMovmentAI();
}

void UAIComponent::Base_EnemyMovmentState()
{
	for (int i = 1; i < 10; ++i)
	{
		if (Targets[i] != nullptr)
		{
			MovmentState = MovmentStates::Attack;
			target = Targets[i]->GetActorLocation();
			break;
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
		CombatState = CombatStates::Attack;
	}
	else if (randstate == 2)
	{
		CombatState = CombatStates::Block;
	}
}
