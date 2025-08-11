#pragma once

#include "CoreMinimal.h"
#include "Characters/BHopBaseCharacter.h"
#include "InputActionValue.h"
#include "GameplayTagContainer.h"
#include "BHopPlayer.generated.h"

class UCameraComponent;
class UDataAsset_InputConfig;
class UBunnyHopComponent;
class UBHopPlayerCombatComponent;

UCLASS()
class BHOPGAME_API ABHopPlayer : public ABHopBaseCharacter
{
GENERATED_BODY()

public:
ABHopPlayer();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    virtual void PossessedBy(AController* NewController) override;
    virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode = 0) override;
    // IPawnCombatInterface
    virtual UPawnCombatComponent* GetPawnCombatComponent() const override;

    // Camera Component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    UCameraComponent* FirstPersonCameraComponent;
       
	// BunnyHop Component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BunnyHop", meta = (AllowPrivateAccess = "true"))
    UBunnyHopComponent* BunnyHopComponent;

	// Combat Component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
    UBHopPlayerCombatComponent* CombatComponent;


private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
    UDataAsset_InputConfig* InputConfigDataAsset;

    // Input Functions
    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void JumpPressed();
    void JumpReleased();
	void AbilityInputPressed(FGameplayTag InInputTag);
    void AbilityInputReleased(FGameplayTag InInputTag);


public:

	FORCEINLINE UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	FORCEINLINE UBHopPlayerCombatComponent* GetCombatComponent() const { return CombatComponent; }
	FORCEINLINE UBunnyHopComponent* GetBunnyHopComponent() const { return BunnyHopComponent; }
};