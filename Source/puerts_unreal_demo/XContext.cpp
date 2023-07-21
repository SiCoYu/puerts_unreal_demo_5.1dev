// Fill out your copyright notice in the Description page of Project Settings.


#include "XContext.h"


bool UXContext::HasMixin(const FString& ModulePath)
{
	FName TSClassName = FName(*ModulePath);
	if (TSObjInMixiningMap.Contains(TSClassName))
	{
		return true;
	}
	if (TSObjMixinMap.Contains(TSClassName))
	{
		UClass* MixinClass = TSObjMixinMap[TSClassName];
		if (MixinClass)
		{
			return true;
		}
	}
	return false;
}

UClass* UXContext::Mixin(UClass* ParentClass, const FString& ModulePath, bool ObjectTakeByNative, bool Inherit, bool NoMixinedWarning, bool ReMixed)
{
	if (ScriptMixInHandle.IsBound()) 
	{
		FName TSClassName = FName(*ModulePath);
		TSObjInMixiningMap.Add(TSClassName, true);
		UClass* MixRet = ScriptMixInHandle.Execute(ParentClass, ModulePath, false, false, false, ReMixed);
		if (MixRet)
		{
			TSObjInMixiningMap.Remove(TSClassName);
			if (!TSObjMixinMap.Contains(TSClassName))
			{
				TSObjMixinMap.Add(TSClassName, MixRet);
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("Repeat Mixin TSClassName = %s"),*ModulePath);
			}
			return MixRet;
		}
	}
	return nullptr;
}
