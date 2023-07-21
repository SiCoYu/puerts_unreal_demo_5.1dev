// Fill out your copyright notice in the Description page of Project Settings.


#include "XContext.h"


bool UXContext::HasMixin(const FName& TSModuleName)
{
	if (TSObjInMixiningMap.Contains(TSModuleName))
	{
		return true;
	}
	if (TSObjMixinMap.Contains(TSModuleName))
	{
		UClass* MixinClass = TSObjMixinMap[TSModuleName];
		if (MixinClass)
		{
			return true;
		}
	}
	return false;
}

UClass* UXContext::Mixin(UClass* ParentClass, const FName& TSModuleName, bool ObjectTakeByNative, bool Inherit, bool NoMixinedWarning, bool ReMixed)
{
	if (CallMixinFromCPP.IsBound()) 
	{
		TSObjInMixiningMap.Add(TSModuleName, true);
		UClass* MixRet = CallMixinFromCPP.Execute(ParentClass, TSModuleName, false, false, false, ReMixed);
		if (MixRet)
		{
			TSObjInMixiningMap.Remove(TSModuleName);
			if (!TSObjMixinMap.Contains(TSModuleName))
			{
				TSObjMixinMap.Add(TSModuleName, MixRet);
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("Repeat Mixin TSModuleName = %s"), *(TSModuleName.ToString()));
			}
			return MixRet;
		}
	}
	return nullptr;
}

bool UXContext::UnMixinClass(const FString& ModulePath)
{
	return true;
}

bool UXContext::UnMixinAllClass()
{
	return true;
}
