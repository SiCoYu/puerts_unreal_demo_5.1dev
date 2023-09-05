// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PuertsMixinInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPuertsMixinInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PUERTSEX_API IPuertsMixinInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent)
	FName GetTSClassName() const;
};
