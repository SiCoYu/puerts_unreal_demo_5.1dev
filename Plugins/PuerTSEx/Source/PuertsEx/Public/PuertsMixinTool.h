// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PuertsMixinTool.generated.h"

UCLASS(Blueprintable, DisplayName = PuertsMixinTool)
class PUERTSEX_API UPuertsMixinTool : public UObject
{
	GENERATED_BODY()
public:
	UPuertsMixinTool();

	/** 单例创建 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static UPuertsMixinTool* GetInstance();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool IsValidAndActive();
	UFUNCTION(BlueprintCallable)
	static void Dispose();

	/** 启动/关闭MixinTool */
	UFUNCTION(BlueprintCallable)
	void SetTSEnable(bool bInEnable);
	/** 获取MixinTool启动状态 */
	UFUNCTION(BlueprintCallable)
	bool GetTSEnable();

	/** TS重载此方法，初始化MixinTool */
	UFUNCTION(BlueprintNativeEvent)
	void Initialize();
	/** TS重载此方法，释放MixinTool */
	UFUNCTION(BlueprintNativeEvent)
	void Deinitialize();
	/** TS重载此方法，是否已经Mixin */
	UFUNCTION(BlueprintNativeEvent)
	bool HasMixin(const FName& TSModuleName);
	/** TS重载此方法，执行Mixin */
	UFUNCTION(BlueprintNativeEvent)
	void Mixin(UClass* ParentClass, const FName& TSModuleName, bool bObjectTakeByNative = false, bool bInherit = false, bool bNoMixinedWarning = false, bool bForceMixin = false);
	/** TS重载此方法，执行UnMixin */
	UFUNCTION(BlueprintNativeEvent)
	bool UnMixin(const FName& TSClassName);
	/** TS重载此方法，执行UnMixinAll */
	UFUNCTION(BlueprintNativeEvent)
	void UnMixinAll();

private:
	/** MixinTool状态，防止在TS虚拟机没启动时调用Mixin方法导致的崩溃 */
	bool bEnableTS = false;
	/** MixinTool单例指针 */
	static UPuertsMixinTool* InstancePtr;
};
