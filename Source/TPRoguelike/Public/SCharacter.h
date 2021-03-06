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

	void MoveForward(float Value);
	
	void MoveRight(float Value);
	
	void Jump();
	
	void PrimaryAttack();
	UFUNCTION()
	void PrimaryAttack_TimeElapsed();

	void Q_Ability();
	UFUNCTION()
	void Q_Ability_TimeElapsed();
	
	void PrimaryInteract();

	
	////////////////////////////////////////////////////
	/// Abilities
	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Primary Attack")
	TSubclassOf<ASProjectileBase> PrimaryAttack_ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Primary Attack")
	TObjectPtr<UAnimMontage> PrimaryAttackAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Primary Attack")
	FName PrimaryWeaponSocketName;

	FTimerHandle TH_PrimaryAttack; 

	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Q Ability")
	TSubclassOf<ASProjectileBase> Q_Ability_ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Q Ability")
	TObjectPtr<UAnimMontage> Q_AbilityAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Q Ability")
	FName Q_AbilityWeaponSocketName;

	FTimerHandle TH_Q_Ability;


	////////////////////////////////////////////////////
	/// Health + Death
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float DeltaHealth);

	void OnDeath();



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
