#include "Components/BunnyHopComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Sound/SoundBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputActionValue.h"
#include "Characters/Player/BHopPlayer.h"



UBunnyHopComponent::UBunnyHopComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UBunnyHopComponent::BeginPlay()
{
	Super::BeginPlay();

	MyCharacter = Cast<ABHopPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	InitializeVariables();
}

void UBunnyHopComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	DeltaSeconds = DeltaTime;
	if (MyCharacter && MyCharacter->GetCharacterMovement())
	{
		OldVelocity = FVector(MyCharacter->GetCharacterMovement()->Velocity.X, MyCharacter->GetCharacterMovement()->Velocity.Y, 0.0f);
		Speed = FVector(MyCharacter->GetCharacterMovement()->Velocity.X, MyCharacter->GetCharacterMovement()->Velocity.Y, 0.0f).Size();
		FVector FullVelocity = MyCharacter->GetCharacterMovement()->UpdatedPrimitive->GetPhysicsLinearVelocity();
		ZVelocity = FullVelocity.Z;
		bIsInAir = MyCharacter->GetCharacterMovement()->IsFalling();

		UE_LOG(LogTemp, Warning, TEXT("Speed: %.2f | MaxWalkSpeed: %.2f | InAir: %s | GroundFriction: %.2f"),
			Speed,
			MyCharacter->GetCharacterMovement()->MaxWalkSpeed,
			bIsInAir ? TEXT("True") : TEXT("False"),
			MyCharacter->GetCharacterMovement()->GroundFriction);

		if (bIsInAir)
		{
			if (MyCharacter->GetCharacterMovement()->GroundFriction > 0.0f)
			{
				RemoveFriction();
				UE_LOG(LogTemp, Error, TEXT("Friction removed in air"));
			}
		}
	}
}

void UBunnyHopComponent::CustomJump()
{

	if (MyCharacter && MyCharacter->GetCharacterMovement())
	{
		MyCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
		FVector SavedJumpVelocityVector = FVector(0.0f, 0.0f, SavedJumpVelocity);
		MyCharacter->GetCharacterMovement()->AddImpulse(SavedJumpVelocityVector, true);
	}

}

void UBunnyHopComponent::InitializeVariables()
{
	if (MyCharacter && MyCharacter->GetCharacterMovement())
	{
		DefaultMaxWalkSpeed = MyCharacter->GetCharacterMovement()->MaxWalkSpeed;
		SavedJumpVelocity = MyCharacter->GetCharacterMovement()->JumpZVelocity;
		DefaultBraking = MyCharacter->GetCharacterMovement()->BrakingDecelerationWalking;
		DefaultFriction = MyCharacter->GetCharacterMovement()->GroundFriction;
		if (bCustomAirAccelEnabled)
		{
			MyCharacter->GetCharacterMovement()->AirControl = 0.0f;
		}


	}
}

void UBunnyHopComponent::RemoveFriction()
{
	if (MyCharacter && MyCharacter->GetCharacterMovement())
	{
		MyCharacter->GetCharacterMovement()->GroundFriction = 0.0f;
		MyCharacter->GetCharacterMovement()->BrakingDecelerationWalking = 0.0f;

	}

}

void UBunnyHopComponent::ResetFriction()
{
	if (MyCharacter && MyCharacter->GetCharacterMovement())
	{
		MyCharacter->GetCharacterMovement()->MaxWalkSpeed = DefaultMaxWalkSpeed;
		MyCharacter->GetCharacterMovement()->BrakingDecelerationWalking = DefaultBraking;
		MyCharacter->GetCharacterMovement()->GroundFriction = DefaultFriction;

	}
}

void UBunnyHopComponent::MovementModeChanged(TEnumAsByte<EMovementMode> PrevMovementMode, TEnumAsByte<EMovementMode> NewMovementMode, uint8 PrevCustomMode, uint8 NewCustomMode)
{
	if (!MyCharacter || !GetWorld() || !MyCharacter->GetCharacterMovement())
	{
		return;
	}

	// Movement mode 1 = Walking
	if (NewMovementMode == MOVE_Walking)
	{
		FVector ActorLocation = MyCharacter->GetActorLocation();

		// Sound effects for landing
		if (ImpactGroundLargeThreshold * DefaultMaxWalkSpeed * -1.0f > ZVelocity)
		{
			if (LargeImpactSound)
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), LargeImpactSound, ActorLocation);
			}
		}
		else
		{
			if (NormalLandingSound)
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), NormalLandingSound, ActorLocation);
			}
		}

		// BLUEPRINT LOGIC: Pogo jumping kontrolü
		if (bPogoJumpingOn)
		{
			if (bJumpInputDown)
			{
				float CurrentTime = GetWorld()->GetTimeSeconds();
				if (JumpCooldown < CurrentTime)
				{
					bool bShouldJump = false;

					if (MyCharacter->GetCharacterMovement()->IsCrouching())
					{
						if (bCrouchJumpOn)
						{
							bShouldJump = true;
						}
					}
					else
					{
						bShouldJump = true;
					}

					if (bShouldJump)
					{
						// HEMEN jump yap, delay yok!
						CustomJump();
						if (SuccessfulJumpSound)
						{
							UGameplayStatics::PlaySoundAtLocation(GetWorld(), SuccessfulJumpSound, ActorLocation);
						}
						JumpCooldown = CurrentTime + 0.1f;

						RampCheck(bOnSlideableRamp, GroundAngleDotProduct);
						TrimpApplication(GroundAngleDotProduct);

						if (BunnyHopCapOn)
						{
							BunnyHopCapApplication();
						}

						// Jump sonrasý hemen çýk, friction reset etme!
						return;
					}
				}
			}
		}

		// Sadece jump yapmadýysa friction reset et - ama çok kýsa delay ile
		GetWorld()->GetTimerManager().ClearTimer(ResetFrictionTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(
			ResetFrictionTimerHandle,
			this,
			&UBunnyHopComponent::ResetFriction,
			0.016f, // 1 frame delay (60 FPS'te)
			false
		);
	}
}

void UBunnyHopComponent::OnJumpTriggered()
{
	bJumpInputDown = true;
	if (MyCharacter->GetCharacterMovement()->IsWalking())
	{
		if (JumpCooldown < GetWorld()->GetTimeSeconds())
		{
			if (MyCharacter->GetCharacterMovement()->IsCrouching())
			{
				if (bCrouchJumpOn)
				{
					CustomJump();
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), SuccessfulJumpSound, MyCharacter->GetActorLocation());
					JumpCooldown = GetWorld()->GetTimeSeconds() + 0.1f;
					RampCheck(bOnSlideableRamp, GroundAngleDotProduct);
					TrimpApplication(GroundAngleDotProduct);
					if (BunnyHopCapOn)
					{
						BunnyHopCapApplication();
					}

				}
			}
			else
			{
				CustomJump();
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), SuccessfulJumpSound, MyCharacter->GetActorLocation());
				JumpCooldown = GetWorld()->GetTimeSeconds() + 0.1f;
				RampCheck(bOnSlideableRamp, GroundAngleDotProduct);
				TrimpApplication(GroundAngleDotProduct);
				if (BunnyHopCapOn)
				{
					BunnyHopCapApplication();
				}
			}
		}
	}


}

void UBunnyHopComponent::OnJumpCompleted()
{
	bJumpInputDown = false;
	if (MyCharacter)
	{
		MyCharacter->StopJumping();
	}

}

void UBunnyHopComponent::RampCheck(bool& OnSlideableRamp, float& GroundDotProduct)
{
	if (!MyCharacter)
	{
		return;
	}

	FVector Start = MyCharacter->GetActorLocation();
	FVector UpVector = MyCharacter->GetActorUpVector();
	FVector End = Start - (UpVector * 1000.0f);

	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = false;
	FHitResult HitResult;
	QueryParams.AddIgnoredActor(MyCharacter);
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,                           // Hit Result
		Start,                           // Start
		End,                             // End  
		ECollisionChannel::ECC_Visibility, // Trace Channel (Visibility)
		QueryParams                      // Query Params
	);

	if (bHit)
	{
		// Tolerance ile normalize et (Blueprint'teki gibi)
		float Tolerance = 0.0001f;

		// Impact Normal'ý tolerance ile normalize et
		FVector ImpactNormal = HitResult.Normal;
		ImpactNormal.Normalize(Tolerance);

		FVector NormalizedOldVelocity = OldVelocity.GetSafeNormal(Tolerance);

		GroundDotProduct = FVector::DotProduct(ImpactNormal, NormalizedOldVelocity);

		// ACos ile açýyý hesapla (radyan cinsinden)
		float AngleRadians = FMath::Acos(FMath::Clamp(GroundDotProduct, -1.0f, 1.0f));

		// Radyan'ý dereceye çevir
		float AngleDegrees = FMath::RadiansToDegrees(AngleRadians);

		// Açý 90 dereceden büyükse (yani yokuþ yukarý)
		if (AngleDegrees > 90.0f)
		{
			OnSlideableRamp = true;
		}
		else
		{
			OnSlideableRamp = false;
		}

	}
	else
	{
		OnSlideableRamp = false;
		GroundDotProduct = 1.0f;
	}

}

void UBunnyHopComponent::TrimpApplication(float GroundDot)
{
	UE_LOG(LogTemp, Error, TEXT("TrimpMultiplyDown C++ value: %.6f"), TrimpMultiplyDown);
	GroundAngleDotProduct = GroundDot;


	if (GroundAngleDotProduct > 0.05f)
	{
		float CombinedValue = GroundAngleDotProduct * (-1.0f / TrimpMultiplyDown) * Speed;
		float min = TrimpVerticalCapDown * SavedJumpVelocity * -1.0f;
		float ClampedValue = FMath::Clamp(CombinedValue, min, 0.0f);
		FVector ImpulseVector = (OldVelocity * GroundAngleDotProduct * TrimpMultiplyDown) + FVector(0.0f, 0.0f, ClampedValue);
		if (MyCharacter && MyCharacter->GetCharacterMovement())
		{
			MyCharacter->GetCharacterMovement()->AddImpulse(ImpulseVector, true);
		}

	}
	else
	{
		if (GroundAngleDotProduct < -0.05f)
		{
			float  Tempfloat = TrimpMultiplyUp * Speed * GroundAngleDotProduct * -1.0f;
			FVector TempVector = FVector(0.0f, 0.0f, Tempfloat);
			FVector ImpulseVector = (OldVelocity * GroundAngleDotProduct * TrimpUpLateralSlow) + TempVector;
			if (MyCharacter && MyCharacter->GetCharacterMovement())
			{
				MyCharacter->GetCharacterMovement()->AddImpulse(ImpulseVector, true);
			}

		}
		else
		{
			return;
		}
	}
}

void UBunnyHopComponent::BunnyHopCapApplication()
{
	BunnyHopSpeedCap = DefaultMaxWalkSpeed * BunnyHopCap;
	if (Speed > BunnyHopSpeedCap)
	{
		FVector NormalizedOldVelocity = OldVelocity.GetSafeNormal(0.0001f);
		FVector NegateVector = NormalizedOldVelocity * -1.0f;

		MyCharacter->GetCharacterMovement()->AddImpulse(NegateVector * ((Speed - BunnyHopSpeedCap) * BunnyHopLoseSpeedAmount), true);
		AppliedCap = ((Speed - BunnyHopSpeedCap) * BunnyHopLoseSpeedAmount) + BunnyHopSpeedCap;
		MyCharacter->GetCharacterMovement()->MaxWalkSpeed = AppliedCap;
	}
	else
	{
		return;
	}
}

void UBunnyHopComponent::OnMoveTriggered(const FInputActionValue& Value)
{
	if (!MyCharacter || !GetWorld())
	{
		return;
	}

	// Input values al
	FVector2D MovementVector = Value.Get<FVector2D>();
	ForwardAxisInput = MovementVector.Y;
	LeftRightAxisInput = MovementVector.X;

	// Forward ve Right vektörleri al
	ForwardVectorInput = MyCharacter->GetActorForwardVector();
	LeftRightVectorInput = MyCharacter->GetActorRightVector();

	// Is in Air branch
	if (bIsInAir)
	{
		// Set: Is Rampsliding = false
		IsRampSliding = false;

		// Custom Air Accel Enabled check
		if (bCustomAirAccelEnabled)
		{
			AirAcceleration(ForwardVectorInput, LeftRightVectorInput, ForwardAxisInput, LeftRightAxisInput);
		}
		else
		{
			// Default movement input
			MyCharacter->AddMovementInput(ForwardVectorInput, ForwardAxisInput);
			MyCharacter->AddMovementInput(LeftRightVectorInput, LeftRightAxisInput);
		}
	}
	else // Not in air (ground)
	{
		// Ramp Slide check
		if (RampSlide())
		{
			// Set: Is Rampsliding = true
			IsRampSliding = true;

			// Remove Friction
			RemoveFriction();

			// Air Acceleration (while ramp sliding)
			AirAcceleration(ForwardVectorInput, LeftRightVectorInput, ForwardAxisInput, LeftRightAxisInput);
		}
		else
		{
			// Is Rampsliding check
			if (IsRampSliding)
			{
				// Add Ramp Momentum
				AddRampMomentum();

				// Set: Is Rampsliding = false
				IsRampSliding = false;

				// Delay before reset friction
				GetWorld()->GetTimerManager().ClearTimer(ResetFrictionTimerHandle);
				GetWorld()->GetTimerManager().SetTimer(
					ResetFrictionTimerHandle,
					this,
					&UBunnyHopComponent::ResetFriction,
					2.0f,
					false
				);
			}

			// Standard movement input
			MyCharacter->AddMovementInput(ForwardVectorInput, ForwardAxisInput);
			MyCharacter->AddMovementInput(LeftRightVectorInput, LeftRightAxisInput);

			// Enable Custom Ground Accel check
			if (bEnableCustomGroundAccel)
			{
				GroundAcceleration(ForwardVectorInput, LeftRightVectorInput, ForwardAxisInput, LeftRightAxisInput);
			}
		}
	}
}

bool UBunnyHopComponent::RampSlide()
{
	RampCheck(bOnSlideableRamp, GroundAngleDotProduct);
	if (Speed > (DefaultMaxWalkSpeed * ThresholdRampSlide) && bOnSlideableRamp)
	{
		return true;
	}
	else
	{
		return false;
	}


}

void UBunnyHopComponent::AirAcceleration(FVector& ForwardVector, FVector& SideVector, float& ForwardAxis, float& SideAxis)
{
	DirectionInput = (ForwardVector * ForwardAxis) + (SideVector * SideAxis);
	DirectionInput.Normalize(0.0001f);

	ProjectedVelocity = FVector::DotProduct(OldVelocity, DirectionInput);
	InputSpeed = (DirectionInput * DefaultMaxWalkSpeed).Size();
	CapAccelSpeed = 75.0f;
	float ClampedTempValue = FMath::Clamp(InputSpeed, 0.0f, CapAccelSpeed);
	MaxAccelSpeed = ClampedTempValue - ProjectedVelocity;

	if (MaxAccelSpeed <= 0.0f)
	{
		return;
	}
	else
	{
		AccelerationSpeed = FMath::Clamp(DeltaSeconds * InputSpeed * AccelerateAir, 0.0f, MaxAccelSpeed);
		VectorImpulse = DirectionInput * AccelerationSpeed;

		if (MyCharacter && MyCharacter->GetCharacterMovement())
		{
			FVector NewVelocity = OldVelocity + VectorImpulse;
			float NewSpeed = NewVelocity.Size();
			MyCharacter->GetCharacterMovement()->MaxWalkSpeed = FMath::Clamp(NewSpeed, DefaultMaxWalkSpeed, 10000.0f);
			MyCharacter->GetCharacterMovement()->AddImpulse(VectorImpulse, true);
		}

	}

}

void UBunnyHopComponent::AddRampMomentum()
{
	if (MyCharacter && MyCharacter->GetCharacterMovement())
	{
		MyCharacter->GetCharacterMovement()->AddImpulse(FVector(0.0f, 0.0f, ZVelocity * RampMomentum), true);
	}
}

void UBunnyHopComponent::GroundAcceleration(FVector& ForwardVector, FVector& SideVector, float& ForwardAxis, float& SideAxis)
{
	DirectionInput = (ForwardVector * ForwardAxis) + (SideVector * SideAxis);
	DirectionInput.Normalize(0.0001f);

	if (Speed >= (DefaultMaxWalkSpeed * 0.9f))
	{
		ProjectedVelocity = FVector::DotProduct(OldVelocity, DirectionInput);

		// BLUEPRINT'TEKÝ GÝBÝ: (DirectionInput * DefaultMaxWalkSpeed).Size()
		InputSpeed = (DirectionInput * DefaultMaxWalkSpeed).Size();

		MaxAccelSpeed = InputSpeed - ProjectedVelocity;

		if (MaxAccelSpeed <= 0.0f)
		{
			MyCharacter->GetCharacterMovement()->MaxWalkSpeed = DefaultMaxWalkSpeed;
		}
		else
		{
			AccelerationSpeed = FMath::Clamp(DeltaSeconds * InputSpeed * AccelerateGround, 0.0f, MaxAccelSpeed);
			VectorImpulse = DirectionInput * AccelerationSpeed;

			// Blueprint'teki gibi: OldVelocity + VectorImpulse'un boyutunu al
			FVector NewVelocity = OldVelocity + VectorImpulse;
			float NewSpeed = NewVelocity.Size();

			// DefaultMaxWalkSpeed ile 10000 arasýnda clamp et
			MyCharacter->GetCharacterMovement()->MaxWalkSpeed = FMath::Clamp(NewSpeed, DefaultMaxWalkSpeed, 10000.0f);
			MyCharacter->GetCharacterMovement()->AddImpulse(VectorImpulse, true);
		}
	}
	else
	{
		MyCharacter->GetCharacterMovement()->MaxWalkSpeed = DefaultMaxWalkSpeed;
	}
}