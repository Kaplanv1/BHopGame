#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpec.h"
#include "BHopAbilityTypes.generated.h"

/**
 * Ability Slot Types
 */
UENUM(BlueprintType)
enum class EBHopAbilitySlot : uint8
{
    None = 0            UMETA(DisplayName = "None"),
    Primary = 1         UMETA(DisplayName = "Primary (Left Click)"),
    Secondary = 2       UMETA(DisplayName = "Secondary (Right Click)"),
    Movement = 3        UMETA(DisplayName = "Movement (Shift)"),
    Utility = 4         UMETA(DisplayName = "Utility (Q)"),
    Ultimate = 5        UMETA(DisplayName = "Ultimate (E)"),
    Passive1 = 6        UMETA(DisplayName = "Passive 1"),
    Passive2 = 7        UMETA(DisplayName = "Passive 2"),
    Passive3 = 8        UMETA(DisplayName = "Passive 3")
};

/**
 * Ability Info Structure
 */
USTRUCT(BlueprintType)
struct FBHopAbilityInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<class UGameplayAbility> AbilityClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EBHopAbilitySlot Slot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Level = 1;

    UPROPERTY(BlueprintReadOnly)
    FGameplayAbilitySpecHandle Handle;

    FBHopAbilityInfo()
    {
        AbilityClass = nullptr;
        Slot = EBHopAbilitySlot::None;
        Level = 1;
    }
};

/**
 * Weapon Ability Set
 */
USTRUCT(BlueprintType)
struct FBHopWeaponAbilitySet
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName WeaponName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FBHopAbilityInfo> Abilities;

    FBHopWeaponAbilitySet()
    {
        WeaponName = NAME_None;
    }
};
