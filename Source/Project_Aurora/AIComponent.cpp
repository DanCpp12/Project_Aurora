#include "AIComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"

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
}

void UAIComponent::base_EnemyMovment()
{
	
}

void UAIComponent::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Begin Overlap: %s"), *OtherActor->GetName());

	for (int i = 0; i < 10; ++i)
	{
		if (Targets[i] == nullptr)
		{
			Targets[i] = OtherActor;
			return;
		}
	}
}

void UAIComponent::HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Log, TEXT("End Overlap: %s"), *OtherActor->GetName());
	for (int i = 0; i < 10; i++)
	{
		if (OtherActor == Targets[i])
		{
			Targets[i] = nullptr;
		}
	}
}

