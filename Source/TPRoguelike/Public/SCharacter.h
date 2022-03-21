// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USInteractionComponent;
class USAttributeComponent;

UCLASS()
class TPROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USInteractionComponent* InteractionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	USAttributeComponent* AttributeComponent;

	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

protected:
	// Abilities
	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Primary Attack")
	TSubclassOf<AActor> PrimaryAttack_ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Primary Attack")
	UAnimMontage* PrimaryAttackAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Primary Attack")
	FName PrimaryWeaponSocketName;

	FTimerHandle TH_PrimaryAttack; 

	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Q Ability")
	TSubclassOf<AActor> Q_Ability_ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Q Ability")
	UAnimMontage* Q_AbilityAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Q Ability")
	FName Q_AbilityWeaponSocketName;

	FTimerHandle TH_Q_Ability; 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
