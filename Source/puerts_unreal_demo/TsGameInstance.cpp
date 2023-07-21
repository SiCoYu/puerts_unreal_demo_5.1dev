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
    Arguments.Add(TPair<FString, UObject*>{TEXT("Context"), RuntimeContext });
    GameScript->Start("AutoMixinTest", Arguments);
}


void UTsGameInstance::Shutdown()
{
    Super::Shutdown();
    GameScript.Reset();
}

void UTsGameInstance::MixinBP(AActor* Target)
{
    if (Target)
    {
        RuntimeContext->Mixin(Target->StaticClass(),"", false, false, false, false);
    }    
}

void UTsGameInstance::MixinBPClass(UClass* TargetClass, FString TSName, bool SpawnActorInTS)
{
    if (IsValid(TargetClass) && !RuntimeContext->HasMixin(TSName)) 
    {
        UClass* MixinClass = RuntimeContext->Mixin(TargetClass, TSName, false, false, false, SpawnActorInTS);
        if (IsValid(MixinClass) && !SpawnActorInTS)
        {
            AActor* pActor = GetWorld()->SpawnActor<AActor>(MixinClass);
            UE_LOG(LogTemp, Log, TEXT("[CPP2TS] Spawn Actor From C++ = %s"), *(pActor->GetName()));
        }
    }    
}

void UTsGameInstance::NotifyUObjectCreated(const UObjectBase* InObjectBase, int32 Index)
{   	
    UObject* Object = (UObject*)InObjectBase;
    const UObject* CDO;
	if (Object->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
	{
		CDO = Object;
	}
	else
	{
		const auto Class = Cast<UClass>(Object);
		CDO = Class ? Class->GetDefaultObject() : Object->GetClass()->GetDefaultObject();
	}

	if (CDO->HasAnyFlags(RF_NeedInitialization))
	{
		// CDO还没有初始化完成
		return;
	}
    const AActor* Actor = CastChecked<AActor>(CDO);
    if (Actor)
    {
		FString ModuleName = IAutoBindInterface::Execute_GetModuleName(Actor);

		AActor* ActorCDO = Cast<AActor>(Actor->GetClass()->GetDefaultObject());
		if (ActorCDO)
		{
            UE_LOG(LogTemp, Log, TEXT("Actor CDO = %s"), *(ActorCDO->GetActorLabel()));
		}
		UBlueprintGeneratedClass* ActorBPClass = Cast<UBlueprintGeneratedClass>(Actor->GetClass());
        UE_LOG(LogTemp, Log, TEXT("Actor = %s"), *(ActorBPClass->GetName()));
		MixinBPClass(ActorBPClass, ModuleName, true);
    }
}

void UTsGameInstance::NotifyUObjectDeleted(const UObjectBase* InObjectBase, int32 Index)
{

}
