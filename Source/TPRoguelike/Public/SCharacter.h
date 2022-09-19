// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USInteractionComponent;
class USAttributeComponent;
class ASProjectileBase;

UCLASS()
class TPROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<USInteractionComponent> InteractionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USAttributeComponent> AttributeComponent;

	virtual void BeginPlay() override;
	
	virtual void PostInitializeComponents() override;

	////////////////////////////////////////////////////
	/// Movement
	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);

	void Jump();
	
	UFUNCTION()
	void PrimaryInteract();

	
	////////////////////////////////////////////////////
	/// Abilities

	// Primaty Attack
	UFUNCTION()
	void PrimaryAttack();

	UFUNCTION()
	void PrimaryAttack_TimeElapsed();

	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Primary Attack")
	TSubclassOf<ASProjectileBase> PrimaryAttack_ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Primary Attack")
	TObjectPtr<UAnimMontage> PrimaryAttackAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Primary Attack")
	FName PrimaryWeaponSocketName;

	UPROPERTY()
	FTimerHandle PrimaryAttackTimer; 

	// Q Ability
	UFUNCTION()
	void Q_Ability();

	UFUNCTION()
	void Q_Ability_TimeElapsed();

	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Q Ability")
	TSubclassOf<ASProjectileBase> Q_Ability_ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Q Ability")
	TObjectPtr<UAnimMontage> Q_AbilityAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Q Ability")
	FName Q_AbilityWeaponSocketName;

	UPROPERTY()
	FTimerHandle Q_AbilityTimer;

	// E Ability
	UFUNCTION()
	void E_Ability();

	UFUNCTION()
	void E_Ability_TimeElapsed();

	UPROPERTY(EditDefaultsOnly, Category = "Abilities|E Ability")
	TSubclassOf<ASProjectileBase> E_Ability_ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities|E Ability")
	TObjectPtr<UAnimMontage> E_AbilityAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities|E Ability")
	FName E_AbilityWeaponSocketName;

	UPROPERTY()
	FTimerHandle E_AbilityTimer;


	////////////////////////////////////////////////////
	/// Health + Death
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float DeltaHealth);

	UFUNCTION()
	void OnDeath();

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName TimeToHitParamName = "TimeToHit";

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	////////////////////////////////////////////////////
	/// Cheats

	UFUNCTION(Exec)
	void HealSelf(float Amount = 100.f);
};
