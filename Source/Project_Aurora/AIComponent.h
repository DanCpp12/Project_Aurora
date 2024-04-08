#pragma once
#include "components/ActorComponent.h"
#include "AIComponent.generated.h"

class USphereComponent;

UCLASS(meta = (BlueprintSpawnableComponent))
class UAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAIComponent();
	void BeginPlay() override;

	void base_EnemyMovment();

	UFUNCTION()
	void HandleBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	UFUNCTION()
	void HandleEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

private:
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* Sphere = nullptr;

	UPROPERTY(VisibleAnywhere)
	AActor* Targets[10] = { nullptr };

};