// Fill out your copyright notice in the Description page of Project Settings.


#include "PuertsMixinTool.h"

UPuertsMixinTool* UPuertsMixinTool::InstancePtr = nullptr;

UPuertsMixinTool::UPuertsMixinTool()
{
	
}

UPuertsMixinTool* UPuertsMixinTool::GetInstance()
{
	if (InstancePtr == nullptr)
	{
		InstancePtr = NewObject<UPuertsMixinTool>((UObject*)GetTransientPackage(), UPuertsMixinTool::StaticClass());
		InstancePtr->SetTSEnable(true);
		UE_LOG(LogTemp, Log, TEXT("[MixinTool] New PuertsMixinTool = %p"),InstancePtr);
	}
	return InstancePtr;
}



bool UPuertsMixinTool::IsValidAndActive()
{
	return InstancePtr != nullptr && InstancePtr->bEnableTS;
}


void UPuertsMixinTool::Dispose()
{
	InstancePtr = nullptr;
}

void UPuertsMixinTool::SetTSEnable(bool bInEnable)
{
	bEnableTS = bInEnable;
	UE_LOG(LogTemp, Log, TEXT("[MixinTool] bEnableTS = %s, Ptr = %p"), bEnableTS ? TEXT("true") : TEXT("false"), InstancePtr);
}

bool UPuertsMixinTool::GetTSEnable()
{
	return bEnableTS;
}

void UPuertsMixinTool::Initialize_Implementation()
{

}

void UPuertsMixinTool::Deinitialize_Implementation()
{

}

bool UPuertsMixinTool::HasMixin_Implementation(const FName& TSModuleName)
{
	return false;
}

void UPuertsMixinTool::Mixin_Implementation(UClass* ParentClass, const FName& TSModuleName, bool bObjectTakeByNative /*= false*/, bool bInherit /*= false*/, bool bNoMixinedWarning /*= false*/, bool bForceMixin /*= false*/)
{

}

bool UPuertsMixinTool::UnMixin_Implementation(const FName& TSClassName)
{
	return true;
}

void UPuertsMixinTool::UnMixinAll_Implementation()
{

}
