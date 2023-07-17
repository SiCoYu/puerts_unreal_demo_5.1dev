// Fill out your copyright notice in the Description page of Project Settings.


#include "XContext.h"

UClass* UXContext::Mixin()
{
	if (ScriptMixInHandle.IsBound()) {
		UClass* MixRet = ScriptMixInHandle.Execute(nullptr, "", false, false, false, true);
	}
	return nullptr;
}
