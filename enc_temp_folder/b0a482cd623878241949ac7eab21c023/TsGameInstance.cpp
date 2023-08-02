// Fill out your copyright notice in the Description page of Project Settings.


#include "TsGameInstance.h"
#include "XContext.h"
#include "Object.h"
#include "GameFramework/Actor.h"

void UTsGameInstance::Init()
{
    Super::Init();
}

void UTsGameInstance::OnStart()
{
    Super::OnStart();
    GameScript = MakeShared<puerts::FJsEnv>();
    //GameScript = MakeShared<puerts::FJsEnv>(std::make_unique<puerts::DefaultJSModuleLoader>(TEXT("JavaScript")), std::make_shared<puerts::FDefaultLogger>(), 8080);
    //GameScript->WaitDebugger();
    TArray<TPair<FString, UObject*>> Arguments;
    Arguments.Add(TPair<FString, UObject*>(TEXT("GameInstance"), this));
    if (!RuntimeContext)
    {
        RuntimeContext = NewObject<UXContext>();
    }    
	UE_LOG(LogTemp, Log, TEXT("TsGameInstance OnStart"));
    Arguments.Add(TPair<FString, UObject*>{TEXT("Context"), RuntimeContext });
    GameScript->Start("AutoMixinTest", Arguments);
}


void UTsGameInstance::Shutdown()
{
    Super::Shutdown();
    GameScript.Reset();
}

void UTsGameInstance::MixinBPClass(const UClass* TargetClass, FName TSName, bool SpawnActorInTS)
{
    if (IsValid(TargetClass) && !RuntimeContext->HasMixin(TargetClass))
    {
        UClass* MixinClass = RuntimeContext->Mixin(TargetClass, TSName, false, false, false, SpawnActorInTS);
    }  
    else
    {
        UE_LOG(LogTemp, Log, TEXT("[CPP2TS] Repeat Mixin TSModuleName = %s"), *(TSName.ToString()));
    }
}

void UTsGameInstance::UnMixinBPClass(const UClass* TargetClass, FName TSName)
{
    if (IsValid(TargetClass) && RuntimeContext->HasMixin(TargetClass))
    {
        RuntimeContext->UnMixinClass(TargetClass);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("[CPP2TS] UnMixin TSModuleName = %s"), *(TSName.ToString()));
    }
}

void UTsGameInstance::NotifyUObjectCreated(const UObjectBase* InObjectBase, int32 Index)
{  
	UObjectBaseUtility* Object = (UObjectBaseUtility*)InObjectBase;
	if (Object)
	{
		static UClass* InterfaceClass = UAutoBindInterface::StaticClass();
		if (!Object->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))// | RF_NeedInitialization))//过滤掉CDO对象和模版对象
		{
			UClass* Class = Object->GetClass();
			if (Class->IsChildOf<UPackage>() || Class->IsChildOf<UClass>())//过滤掉UPackage和UClass
			{
				//UE_LOG(LogTemp, Log, TEXT("%s===return 1"), *(Object->GetName()));
				return;
			}
			if (Class->HasAnyClassFlags(CLASS_NewerVersionExists))//过滤掉废弃蓝图对象
			{
				//UE_LOG(LogTemp, Log, TEXT("%s===return 2"), *(Object->GetName()));
				return;
			}
			if (Class->ImplementsInterface(InterfaceClass))
			{
				UObject* TempObject = (UObject*)InObjectBase;
				UFunction* Func = Class->FindFunctionByName(FName("GetTSModuleName"));
				if (Func)
				{
					bool bIsActor = Class->IsChildOf<AActor>();
					bool bIsUObject = Class->IsChildOf<UObject>();
					if (Func->GetNativeFunc())
					{
						if (IsInGameThread())
						{
							FName TSClassName;
							UObject* DefaultObject = Class->GetDefaultObject();
							DefaultObject->UObject::ProcessEvent(Func, &TSClassName);
							if (TSClassName.ToString().Len() > 0)
							{
								if (!RuntimeContext->HasMixin(Class))
								{
									UClass* MixinClass = RuntimeContext->Mixin(Class, TSClassName, false, false, false, false);
									UE_LOG(LogTemp, Log, TEXT("[Mixin] Class = %s, ClassPtr = %p"), *(TSClassName.ToString()), Class);
								}
								else
								{
									UE_LOG(LogTemp, Log, TEXT("[Mixin] Repeat Mixin Class = %s, ClassPtr = %p"), *(TSClassName.ToString()), Class);
								}
								
							}
						}
					}
				}
			}
		}
	}
}

void UTsGameInstance::NotifyUObjectDeleted(const UObjectBase* InObjectBase, int32 Index)
{
    const UClass* Class = (UClass*)InObjectBase;
	
	if (IsValid(Class))
	{
		RuntimeContext->UnMixinClass(Class);
		UE_LOG(LogTemp, Log, TEXT("[Deleted] ClassName = %s, ClassPtr = %p"), *(Class->GetName()), InObjectBase);
	}
}
