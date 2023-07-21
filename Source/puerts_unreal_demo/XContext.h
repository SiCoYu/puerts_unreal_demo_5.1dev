// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Map.h"
#include "XContext.generated.h"

DECLARE_DYNAMIC_DELEGATE_RetVal_SixParams(UClass*, FScriptMixinDelegate, UClass*, ParentClass, const FString&, ModulePath, bool, ObjectTakeByNative, bool, Inherit, bool, NoMixinedWarning, bool, ReMixed);

UCLASS()
class PUERTS_UNREAL_DEMO_API UXContext : public UObject
{
	GENERATED_BODY()
public:
	bool HasMixin(const FString& ModulePath);
	UClass* Mixin(UClass* ParentClass, const FString& ModulePath, bool ObjectTakeByNative, bool Inherit, bool NoMixinedWarning, bool ReMixed);
	bool UnMixinClass(const FString& ModulePath);
	bool UnMixinAllClass();
public:
	UPROPERTY(EditAnywhere, Category = MixinGoToTS, meta = (IsBindableEvent = "True"))
	FScriptMixinDelegate ScriptMixInHandle;

private:
	TMap<FName, UClass*> TSObjMixinMap;
	TMap<FName, bool> TSObjInMixiningMap;
};
