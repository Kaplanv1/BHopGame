#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BunnyHopComponent.generated.h"

class ABHopPlayer;
class USoundBase;
struct FInputActionValue;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BHOPGAME_API UBunnyHopComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UBunnyHopComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// === VELOCITY ===
	UPROPERTY(BlueprintReadOnly, Category = "Velocity")
	FVector OldVelocity;

	UPROPERTY(BlueprintReadOnly, Category = "Velocity")
	float ZVelocity;

	UPROPERTY(BlueprintReadOnly, Category = "Velocity")
	float ProjectedVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Velocity")
	float SavedJumpVelocity = 850.0f;

	// === REALTIME ===
	UPROPERTY(BlueprintReadOnly, Category = "Realtime")
	float Speed;

	UPROPERTY(BlueprintReadOnly, Category = "Realtime")
	float DeltaSeconds;

	UPROPERTY(BlueprintReadOnly, Category = "Realtime")
	bool bIsInAir = false;

	UPROPERTY(BlueprintReadOnly, Category = "Realtime")
	float InputSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Realtime")
	float DefaultMaxWalkSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Realtime")
	bool bSpeedometerON = true;

	UPROPERTY(BlueprintReadOnly, Category = "Realtime")
	float DefaultFriction;

	UPROPERTY(BlueprintReadOnly, Category = "Realtime")
	float DefaultBraking;

	UPROPERTY(BlueprintReadOnly, Category = "Realtime")
	FVector VectorImpulse;

	// === COMPONENT TICK ===
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component Tick")
	bool bStartWithTickEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component Tick")
	float TickInterval = 0.0f;

	// === RAMPSLIDING ===
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rampsliding")
	float ThresholdRampSlide = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rampsliding")
	float RampMomentum = 0.8f;

	UPROPERTY(BlueprintReadOnly, Category = "Rampsliding")
	bool IsRampSliding = false;

	// === ACCELERATION ===
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Acceleration")
	bool bCustomAirAccelEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Acceleration")
	bool bEnableCustomGroundAccel = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Acceleration")
	float AccelerateAir = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Acceleration")
	float AccelerateGround = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Acceleration")
	float MaxAccelSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Acceleration")
	float AccelerationSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Acceleration")
	float CapAccelSpeed = 200.0f;

	// === TRIMPING ===
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trimping")
	float TrimpVerticalCapDown = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trimping")
	float TrimpMultiplyUp = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trimping")
	float TrimpUpLateralSlow = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trimping")
	float TrimpMultiplyDown = 1.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Trimping")
	float GroundAngleDotProduct = 0.0f;

	// === JUMP ===
	UPROPERTY(BlueprintReadOnly, Category = "Jump")
	float JumpCooldown = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump")
	bool bCrouchJumpOn = true;

	UPROPERTY(BlueprintReadOnly, Category = "Jump")
	bool bJumpInputDown = false;

	UPROPERTY(EditDefaultsOnly, Category = "Jump")
	float ImpactGroundLargeThreshold = 2.0f;

	// === AXIS INPUTS ===
	UPROPERTY(BlueprintReadOnly, Category = "Axis Inputs")
	float ForwardAxisInput = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Axis Inputs")
	float LeftRightAxisInput = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Axis Inputs")
	FVector ForwardVectorInput = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(BlueprintReadOnly, Category = "Axis Inputs")
	FVector LeftRightVectorInput = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(BlueprintReadOnly, Category = "Axis Inputs")
	FVector DirectionInput = FVector(0.0f, 0.0f, 0.0f);

	// === BUNNY HOP ===
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bunny Hop")
	bool bPogoJumpingOn = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bunny Hop")
	float BunnyHopSpeedCap = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bunny Hop")
	float BunnyHopCap = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bunny Hop")
	float BunnyHopLoseSpeedAmount = 0.3f;

	UPROPERTY(BlueprintReadOnly, Category = "Bunny Hop")
	float AppliedCap = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bunny Hop")
	bool BunnyHopCapOn = false;

	// === AUDIO ===
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* LargeImpactSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* NormalLandingSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* SuccessfulJumpSound;

	// Functions
	ABHopPlayer* MyCharacter;
	void CustomJump();
	void InitializeVariables();
	void RemoveFriction();
	void ResetFriction();
	void MovementModeChanged(TEnumAsByte<EMovementMode> PrevMovementMode, TEnumAsByte<EMovementMode> NewMovementMode, uint8 PrevCustomMode, uint8 NewCustomMode);

	UFUNCTION()
	void OnJumpTriggered();

	UFUNCTION()
	void OnJumpCompleted();

	void RampCheck(bool& bOnSlideableRamp, float& GroundAngleDotProduct);
	void TrimpApplication(float GroundDot);
	void BunnyHopCapApplication();

	UFUNCTION()
	void OnMoveTriggered(const FInputActionValue& Value);

	bool RampSlide();
	void AirAcceleration(FVector& ForwardVector, FVector& SideVector, float& ForwardAxis, float& SideAxis);
	void AddRampMomentum();
	void GroundAcceleration(FVector& ForwardVector, FVector& SideVector, float& ForwardAxis, float& SideAxis);

	float AirControl;
	bool bOnSlideableRamp = false;
	FTimerHandle ResetFrictionTimerHandle;
	FTimerHandle DelayTimerHandle;
    
};