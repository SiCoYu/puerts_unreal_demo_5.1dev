// Fill out your copyright notice in the Description page of Project Settings.


#include "XContext.h"

UClass* UXContext::Mixin(UClass* ParentClass, const FString& ModulePath, bool ObjectTakeByNative, bool Inherit, bool NoMixinedWarning, bool ReMixed)
{
	if (ScriptMixInHandle.IsBound()) 
	{
		UClass* MixRet = ScriptMixInHandle.Execute(ParentClass, ModulePath, false, false, false, ReMixed);
		if (MixRet)
		{
			FName TSClassName = FName(*ModulePath);
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
