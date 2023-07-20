// Fill out your copyright notice in the Description page of Project Settings.


#include "TsGameInstance.h"
#include "XContext.h"

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
    GameScript->Start("QuickStart", Arguments);
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
    if (IsValid(TargetClass)) 
    {
        UClass* MixinClass = RuntimeContext->Mixin(TargetClass, TSName, false, false, false, SpawnActorInTS);
        if (IsValid(MixinClass) && !SpawnActorInTS)
        {
            AActor* pActor = GetWorld()->SpawnActor<AActor>(MixinClass);
            UE_LOG(LogTemp, Log, TEXT("[CPP2TS] Spawn Actor From C++ = %s"), *(pActor->GetName()));
        }
    }    
}
