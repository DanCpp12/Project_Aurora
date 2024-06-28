#pragma once
#include "components/ActorComponent.h"
#include "AIComponent.generated.h"

class USphereComponent;

UENUM(BlueprintType)
enum class MovementAI : uint8
{
	Null,
	Base,
	Boss
};

UENUM(BlueprintType)
enum class CombatAI : uint8
{
	Null,
	Base,
	Boss
};

UENUM(BlueprintType)
enum class MovmentStates : uint8
{
	Null,
	Idle,
	Attack,
	Backup,
	Charge
};

UENUM(BlueprintType)
enum class CombatStates : uint8
{
	Null,
	Basic_Attack,
	Block,
	Charge
};

UCLASS(meta = (BlueprintSpawnableComponent))
class UAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAIComponent();
	void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetMovementAI(MovementAI AI) { movementAI = AI; };
	UFUNCTION(BlueprintCallable)
	void SetCombatAI(TEnumAsByte<CombatAI> AI) { combatAI = AI; };

	UFUNCTION(BlueprintCallable)
	FVector PlayMovmentAI();

	UFUNCTION(BlueprintCallable)
	bool PlayCombatAI();

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
	USphereComponent* ViewField = nullptr;

	//movment restricktions
	FVector SpawnPoint;
	float MTimer = 0;
	UPROPERTY(Editanywhere, Category = "Movment Settings")
	int TravleDistanse = 300;
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
	MovementAI movementAI = MovementAI::Null;
	UPROPERTY(VisibleAnywhere, Category = "AI Debug")
	CombatAI combatAI = CombatAI::Null;
	UPROPERTY(VisibleAnywhere, Category = "AI Debug")
	AActor* Targets[10] = { nullptr };
	UPROPERTY(VisibleAnywhere, Category = "AI Debug")
	FVector target;
	UPROPERTY(VisibleAnywhere, Category = "AI Debug")
	MovmentStates MovmentState;
	UPROPERTY(VisibleAnywhere, Category = "AI Debug")
	CombatStates CombatState;
	//states
	void Base_EnemyMovmentState();
	void Base_EnemyCombatState();

	void BossMovementStates();
	void BossCombatStates();



	//movement
	void AttackMovement();
	void IdleMovement();
};