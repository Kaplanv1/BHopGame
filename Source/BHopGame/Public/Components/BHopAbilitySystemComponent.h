#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BHopTypes/BHopStructTypes.h"
#include "BHopAbilitySystemComponent.generated.h"

UCLASS()
class BHOPGAME_API UBHopAbilitySystemComponent : public UAbilitySystemComponent
{
    GENERATED_BODY()

public:
    UBHopAbilitySystemComponent();

    void OnAbilityInputPressed(const FGameplayTag& InInputTag);
    void OnAbilityInputReleased(const FGameplayTag& InInputTag);


    UFUNCTION(BlueprintCallable, Category = "BHop|AbilitySystem", meta = (ApplyLevel="1"))
    void GrantPlayerWeaponAbilities(const TArray<FBHopPlayerAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel,TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles); 

    UFUNCTION(BlueprintCallable, Category = "BHop|AbilitySystem")
    void RemovePlayerWeaponAbilities(UPARAM(ref)TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove);
    

};