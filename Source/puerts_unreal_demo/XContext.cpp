// Fill out your copyright notice in the Description page of Project Settings.


#include "XContext.h"

bool UXContext::HasMixin(const UClass* ParentClass)
{
	if (TSObjInMixiningMap.Contains(ParentClass))
	{
		UE_LOG(LogTemp, Log, TEXT("[HasMixin] HasMixin = true, %p"), ParentClass);
		return true;
	}
	if (TSObjMixinMap.Contains(ParentClass))
	{
		UE_LOG(LogTemp, Log, TEXT("[HasMixin] HasMixin = true, %p"), ParentClass);
		return true;
	}
	return false;
}

UClass* UXContext::Mixin(const UClass* ParentClass, const FName& TSModuleName, bool ObjectTakeByNative, bool Inherit, bool NoMixinedWarning, bool ReMixed)
{
	if (CallMixinFromCPP.IsBound()) 
	{
		TSObjInMixiningMap.Add(ParentClass, true);
		UClass* MixRet = CallMixinFromCPP.Execute(ParentClass, TSModuleName, false, false, false, ReMixed);
		if (MixRet)
		{
			UE_LOG(LogTemp, Log, TEXT("[Mixin] ClassName = %s, ClassPtr = %p"), *(TSModuleName.ToString()), ParentClass);
			TSObjInMixiningMap.Remove(ParentClass);
			if (!TSObjMixinMap.Contains(ParentClass))
			{
				TSObjMixinMap.Add(ParentClass, TSModuleName);
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("[Mixin] Repeat Mixin TSModuleName = %s"), *(TSModuleName.ToString()));
			}
			return MixRet;
		}
	}
	return nullptr;
}

bool UXContext::UnMixinClass(const UClass* TSClass)
{
	if (TSObjMixinMap.Contains(TSClass))
	{
		if (CallUnMixinFromCPP.IsBound())
		{
			FName TSClassName = TSObjMixinMap[TSClass];
			CallUnMixinFromCPP.Execute(TSClassName);
			TSObjInMixiningMap.Remove(TSClass);
			UE_LOG(LogTemp, Log, TEXT("[UnMixin] UnMixin ClassName = %s, ClassPtr = %p"), *(TSClassName.ToString()), TSClass);
			return true;
		}
	}
	return false;
}

bool UXContext::UnMixinAllClass()
{
	return true;
}
