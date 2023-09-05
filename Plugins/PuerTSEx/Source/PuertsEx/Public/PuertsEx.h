// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "JsEnv.h"

DECLARE_LOG_CATEGORY_EXTERN(LogPuertsEx, Verbose, All);

class IPuertsExModule : public IModuleInterface
{
	static FORCEINLINE IPuertsExModule& Get()
	{
		return FModuleManager::LoadModuleChecked<IPuertsExModule>("PuertsEx");
	}
	/** 是否激活Module */
	virtual bool IsActive() = 0;

	/** 设置Module激活状态 */
	virtual void SetActive(bool bActive) = 0;

	/** 热更时重新Reload，预留接口 */
	virtual void HotReload() = 0;

	/** C++获取JsEnv虚拟机，预留接口，待以后研究能否直接在C++执行Mixin操作 */
	virtual TSharedPtr<puerts::FJsEnv> GetJsEvn(UObject* Object = nullptr) = 0;

	/** C++设置JsEnv虚拟机，预留接口 */
	virtual void SetJsEvn(TSharedPtr<puerts::FJsEnv> InJsEnv) = 0;
};

class FPuertsExModule : public IPuertsExModule,
						public FUObjectArray::FUObjectCreateListener,
						public FUObjectArray::FUObjectDeleteListener
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** 重载的Interface方法 */
	virtual bool IsActive() override;
	virtual void SetActive(bool bInActive) override;
	virtual void HotReload() override;
	virtual TSharedPtr<puerts::FJsEnv> GetJsEvn(UObject* Object /* = nullptr */) override;
	virtual void SetJsEvn(TSharedPtr<puerts::FJsEnv> InJsEnv) override;

	/** 注册设置方法 */
	void RegisterSettings();
	/** 取消注册设置方法 */
	void UnregisterSettings();
	/** 注册监听引擎部分Delegate */
	void RegisterDelegates();
	/** 取消注册监听引擎部分Delegate */
	void UnregisterDelegates();
#if WITH_EDITOR	
	/** 监听Project Settings修改回调 */
	bool HandleSettingsSaved();
#endif
	
	/** 监听创建UObject */
	virtual void NotifyUObjectCreated(const class UObjectBase* InObject, int32 Index) override;
	/** 监听销毁UObject */
	virtual void NotifyUObjectDeleted(const class UObjectBase* InObject, int32 Index) override;
	/** 监听销毁UObjectArray */
	virtual void OnUObjectArrayShutdown() override;
	/** 非Game线程Class的Mixin，转移到Game线程 */
	void OnAsyncLoadingFlushUpdate();

#pragma region 监听常用事件
	void OnWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources);
	void OnPostWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources);
	void OnPreWorldInitialization(UWorld* World, const UWorld::InitializationValues);
	void OnPostWorldInitialization(UWorld* World, const UWorld::InitializationValues);
	void OnPostEngineInit();
	void OnPreExit();
	void OnCrash();
	void PreLoadMap(const FString& MapName);
	void PostLoadMapWithWorld(UWorld* World);
	void OnPostGarbageCollect();

#if WITH_EDITOR
	void PreBeginPIE(bool bIsSimulating);
	void BeginPIE(bool bIsSimulating);
	void PostPIEStarted(bool bIsSimulating);
	void PrePIEEnded(bool bIsSimulating);
	void EndPIE(bool bIsSimulating);
	void OnEndPlayMap();
#endif
#pragma endregion 监听常用事件

private:
	/** Mixin功能开关 */
	bool bIsAutoMixin = false;
	/** Mixin激活状态开关 */
	bool bIsActive = false;
	TArray<UObject*> Candidates;  //非Game线程先缓存Object实例对象
	FCriticalSection CandidatesLock;
	FDelegateHandle OnAsyncLoadingFlushUpdateDelegateHandle;

	FDelegateHandle WorldCleanupHandle;
	FDelegateHandle PostWorldCleanupHandle;
	FDelegateHandle PreWorldInitializationHandle;
	FDelegateHandle PostWorldInitializationHandle;
	FDelegateHandle PostEngineInitHandle;
	FDelegateHandle PreExitHandle;
	FDelegateHandle HandleSystemErrorHandle;
	FDelegateHandle HandleSystemEnsureHandle;
	FDelegateHandle PreLoadMapHandle;
	FDelegateHandle PostLoadMapWithWorldHandle;
#if WITH_EDITOR
	FDelegateHandle PreBeginPIEHandle;
	FDelegateHandle BeginPIEHandle;
	FDelegateHandle PostPIEStartedHandle;
	FDelegateHandle PrePIEEndedHandle;
	FDelegateHandle EndPIEHandle;
#endif	
};
