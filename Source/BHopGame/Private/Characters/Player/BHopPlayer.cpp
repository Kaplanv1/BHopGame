#include "Characters/Player/BHopPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputSubsystems.h"
#include "Components/BunnyHopComponent.h"
#include "DataAssets/DataAsset_InputConfig.h"
#include "Components/BHopInputComponent.h"
#include "Gameplay/Tags/BHopGameplayTags.h"
#include "DataAssets/StartUpData/DataAssets_StartUpDataBase.h"
#include "Components/BHopAbilitySystemComponent.h"
#include "Components/BHopPlayerCombatComponent.h"



ABHopPlayer::ABHopPlayer()
{
	// Set size for collision capsule
	GetCapsuleComponent()->SetCapsuleSize(42.f, 96.0f);

	// Use controller rotation for yaw
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Configure character movement - Normal Unreal movement
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;

	// Create BunnyHop Component
	BunnyHopComponent = CreateDefaultSubobject<UBunnyHopComponent>(TEXT("BunnyHopComponent"));
	// Create Combat Component
	CombatComponent = CreateDefaultSubobject<UBHopPlayerCombatComponent>(TEXT("CombatComponent"));


	// Create First Person Camera
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
}

void ABHopPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void ABHopPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset as input config "))

		ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem);

	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	UBHopInputComponent* BHopInputComponent = CastChecked<UBHopInputComponent>(PlayerInputComponent);

	//Binding Input Actions to Functions

	BHopInputComponent->BindNativeInputAction(InputConfigDataAsset, BHopGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
	BHopInputComponent->BindNativeInputAction(InputConfigDataAsset, BHopGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Look);
	BHopInputComponent->BindNativeInputAction(InputConfigDataAsset, BHopGameplayTags::InputTag_Jump, ETriggerEvent::Triggered, this, &ThisClass::JumpPressed);
	BHopInputComponent->BindNativeInputAction(InputConfigDataAsset, BHopGameplayTags::InputTag_Jump, ETriggerEvent::Completed, this, &ThisClass::JumpReleased);

	BHopInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::AbilityInputPressed, &ThisClass::AbilityInputReleased);

}

void ABHopPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAssets_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(BHopAbilitySystemComponent);

		}
	}
}

UPawnCombatComponent* ABHopPlayer::GetPawnCombatComponent() const
{
	return CombatComponent;
}


void ABHopPlayer::Move(const FInputActionValue& Value)
{
	if (BunnyHopComponent)
	{
		BunnyHopComponent->OnMoveTriggered(Value);
	}
}

void ABHopPlayer::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ABHopPlayer::JumpPressed()
{
	if (BunnyHopComponent)
	{
		BunnyHopComponent->OnJumpTriggered();
	}
}

void ABHopPlayer::JumpReleased()
{
	if (BunnyHopComponent)
	{
		BunnyHopComponent->OnJumpCompleted();
	}
}

void ABHopPlayer::AbilityInputPressed(FGameplayTag InInputTag)
{
	BHopAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void ABHopPlayer::AbilityInputReleased(FGameplayTag InInputTag)
{
	BHopAbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}

void ABHopPlayer::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);

	// BunnyHop component'ine bildir
	if (BunnyHopComponent)
	{
		BunnyHopComponent->MovementModeChanged(
			PrevMovementMode,
			GetCharacterMovement()->MovementMode,
			PreviousCustomMode,
			GetCharacterMovement()->CustomMovementMode
		);
	}
}