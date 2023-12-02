// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DPlayerCharacterInputConfig.generated.h"

class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class SECRETSANTA_API UDPlayerCharacterInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* PlayerCharacterIMC;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* MoveHorizontalIA;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* JumpIA;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* SprintIA;
};
