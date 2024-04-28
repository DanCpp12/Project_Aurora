#pragma once
#include "components/ActorComponent.h"
#include "AIComponent.generated.h"

class USphereComponent;

UENUM(BlueprintType)
enum class MovmentStates
{
	Null,
	Idle,
	Attack
};

UENUM(BlueprintType)
enum class CombatStates
{
	Null,
	Attack,
	Block
};

UCLASS(meta = (BlueprintSpawnableComponent))
class UAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAIComponent();
	void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	FVector base_EnemyMovmentAI();

	UFUNCTION(BlueprintCallable)
	bool base_EnemyCombatAI();

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

	UPROPERTY(BlueprintReadWrite)
	bool NewTarget = true;
	

private:
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* Sphere = nullptr;

	UPROPERTY(Editanywhere)
	int MovmentRange = 300;

	UPROPERTY(EditDefaultsOnly/*, VisibleAnywhere*/)
	int MovmentRadiusFromSpawnPoint = 1000;

	UPROPERTY(Editanywhere/*, VisibleAnywhere*/)
	float MovmentTimer;

	UPROPERTY(VisibleAnywhere)
	AActor* Targets[10] = { nullptr };
	UPROPERTY(VisibleAnywhere)
	FVector target;

	UPROPERTY(VisibleAnywhere)
	MovmentStates MovmentState;

	UPROPERTY(VisibleAnywhere)
	CombatStates CombatState;

	FVector SpawnPoint;
	float MTimer = 0;
	void Base_EnemyMovmentState();
	void Base_EnemyCombatState();
};