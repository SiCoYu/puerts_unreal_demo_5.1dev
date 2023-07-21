// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "JsEnv.h"

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AutoBindInterface.h"
#include "TsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUERTS_UNREAL_DEMO_API UTsGameInstance : public UGameInstance, public IAutoBindInterface
{
	GENERATED_BODY()

public:

    virtual void Init() override;

    virtual void OnStart() override;

    virtual void Shutdown() override;
    UFUNCTION(BlueprintCallable)
    void MixinBP(AActor* Target);

	UFUNCTION(BlueprintCallable)
	void MixinBPClass(UClass* TargetClass, FString TSName, bool SpawnActorInTS);

	void NotifyUObjectCreated(const UObjectBase* InObjectBase, int32 Index) override;

	void NotifyUObjectDeleted(const UObjectBase* InObjectBase, int32 Index) override;
private:
    TSharedPtr<puerts::FJsEnv> GameScript;
    class UXContext* RuntimeContext;
};
