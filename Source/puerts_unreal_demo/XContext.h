// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Map.h"
#include "XContext.generated.h"

DECLARE_DYNAMIC_DELEGATE_RetVal_SixParams(UClass*, FDoMixinDelegate,const UClass*, ParentClass, const FName&, TSModuleName, bool, ObjectTakeByNative, bool, Inherit, bool, NoMixinedWarning, bool, ReMixed);
DECLARE_DYNAMIC_DELEGATE_OneParam(FDoUnMixinDelegate, const FName&, TSModuleName);
UCLASS()
class PUERTS_UNREAL_DEMO_API UXContext : public UObject
{
	GENERATED_BODY()
public:
	bool HasMixin(const UClass* ParentClass);
	UClass* Mixin(const UClass* ParentClass, const FName& TSModuleName, bool ObjectTakeByNative, bool Inherit, bool NoMixinedWarning, bool ReMixed);
	bool UnMixinClass(const UClass* ParentClass);
	bool UnMixinAllClass();
public:
	UPROPERTY(EditAnywhere, Category = MixinGoToTS, meta = (IsBindableEvent = "True"))
	FDoMixinDelegate CallMixinFromCPP;
	UPROPERTY(EditAnywhere, Category = MixinGoToTS, meta = (IsBindableEvent = "True"))
	FDoUnMixinDelegate CallUnMixinFromCPP;
private:
	TMap<const UClass*, FName> TSObjMixinMap;
	TMap<const UClass*, bool> TSObjInMixiningMap;
};
