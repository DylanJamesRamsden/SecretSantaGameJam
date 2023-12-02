// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DGameplayCharacter.generated.h"

class UDPlayerCharacterInputConfig;
struct FInputActionValue;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SECRETSANTA_API ADGameplayCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADGameplayCharacter();

protected:

	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CameraComp;

	UPROPERTY(EditDefaultsOnly)
	UDPlayerCharacterInputConfig* PlayerCharacterInputConfig;

	UPROPERTY(BlueprintReadOnly)
	bool bIsSprinting;

	UPROPERTY(BlueprintReadOnly)
	bool bIsFacingRight = true;
	bool bIsTurning;
	FRotator TargetTurnRotation;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void MoveHorizontal(const FInputActionValue&  Value);

	UFUNCTION()
	void ToggleSprint(const FInputActionValue&  Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
