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

	//movment restricktions
	FVector SpawnPoint;
	float MTimer = 0;
	UPROPERTY(Editanywhere, Category = "Movment Settings")
	int MovmentRange = 300;
	UPROPERTY(Editanywhere, Category = "Movment Settings")
	int MovmentRadiusFromSpawnPoint = 1000;
	UPROPERTY(Editanywhere, Category = "Movment Settings")
	float MovmentTimer = 1;


	//stuck
	UPROPERTY(Editanywhere, Category = "Stuck Settings")
	int Tolerance = 4;
	UPROPERTY(Editanywhere, Category = "Stuck Settings")
	float Delay = 1;
	float DelayTimer = 0;
	FVector OldPosition;
	bool IsStuck();


	//AI
	UPROPERTY(VisibleAnywhere, Category = "AI Debug")
	AActor* Targets[10] = { nullptr };
	UPROPERTY(VisibleAnywhere, Category = "AI Debug")
	FVector target;
	UPROPERTY(VisibleAnywhere, Category = "AI Debug")
	MovmentStates MovmentState;
	UPROPERTY(VisibleAnywhere, Category = "AI Debug")
	CombatStates CombatState;
	void Base_EnemyMovmentState();
	void Base_EnemyCombatState();
};