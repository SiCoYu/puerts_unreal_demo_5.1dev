// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UObjectBase.h"
#include "GameFramework/Actor.h"
#include "AutoBindInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAutoBindInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class JSENV_API IAutoBindInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	FString GetModuleName() const;
	virtual void NotifyUObjectCreated(const UObjectBase* ObjectBase, int32 Index) = 0;
	virtual void NotifyUObjectDeleted(const UObjectBase* ObjectBase, int32 Index) = 0;
};
