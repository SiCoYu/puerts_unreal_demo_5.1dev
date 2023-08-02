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

void UTsGameInstance::NotifyUObjectCreated(UObject* InObject, int32 Index)
{  
	const auto Class = InObject->IsA<UClass>() ? static_cast<UClass*>(InObject) : InObject->GetClass();
	if (Class->HasAnyClassFlags(CLASS_NewerVersionExists))
	{
		return;
	}

	static UClass* InterfaceClass = UAutoBindInterface::StaticClass();
	const bool bImplUnluaInterface = Class->ImplementsInterface(InterfaceClass);

	check(Class);

	if (Class->HasAnyFlags(RF_NeedPostLoad | RF_NeedPostLoadSubobjects))
		return;

	if (RuntimeContext->HasMixin(Class))
		return;
	UFunction* Func = Class->FindFunctionByName(FName("GetTSModuleName"));
	if (Func)
	{
		FName TSClassName;
		UObject* DefaultObject = Class->GetDefaultObject();
		DefaultObject->UObject::ProcessEvent(Func, &TSClassName);

		if (!RuntimeContext->HasMixin(Class))
		{
			UClass* MixinClass = RuntimeContext->Mixin(Class, TSClassName, false, false, false, false);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("[Mixin] Repeat Mixin Class = %s, ClassPtr = %p"), *(TSClassName.ToString()), Class);
		}
	}
}

void UTsGameInstance::NotifyUObjectDeleted(UObject* InObject, int32 Index)
{
	UE_LOG(LogTemp, Log, TEXT("[Deleted] InObjectPtr = %p"), InObject);
	const auto Class = InObject->IsA<UClass>() ? static_cast<UClass*>(InObject) : InObject->GetClass();
	if (Class->HasAnyClassFlags(CLASS_NewerVersionExists))
	{
		return;
	}
	check(Class);
	static UClass* InterfaceClass = UAutoBindInterface::StaticClass();
	const bool bImplUnluaInterface = Class->ImplementsInterface(InterfaceClass);
	if (bImplUnluaInterface) 
	{
		RuntimeContext->UnMixinClass(Class);
	}
}
