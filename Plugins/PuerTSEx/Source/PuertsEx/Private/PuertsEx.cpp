// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuerTSEx.h"
#include "PuertsExSetting.h"
#include "ISettingsModule.h"
#include "Modules/ModuleManager.h"
#include "GameDelegates.h"
#include "ISettingsSection.h"
#if WITH_EDITOR
#include "Editor.h"
#endif 
#include "PuertsMixinInterface.h"
#include "PuertsMixinTool.h"
#include "Logging/LogMacros.h"


#define LOCTEXT_NAMESPACE "FPuertsExModule"

DEFINE_LOG_CATEGORY(LogPuertsEx);

constexpr EInternalObjectFlags AsyncObjectFlags = EInternalObjectFlags::AsyncLoading | EInternalObjectFlags::Async;

void FPuertsExModule::StartupModule()
{
	RegisterSettings();
#if WITH_EDITOR
	if (!IsRunningGame())
	{
		RegisterDelegates();
	}
	if (IsRunningGame() || IsRunningDedicatedServer())
#endif
		SetActive(true);
}

void FPuertsExModule::ShutdownModule()
{
	UnregisterSettings();
	UnregisterDelegates();
	SetActive(false);
}


bool FPuertsExModule::IsActive()
{
	return bIsActive;
}

void FPuertsExModule::SetActive(bool bInActive)
{
	if (bIsActive == bInActive)
	{
		return;
	}
	if (bInActive)
	{
		GUObjectArray.AddUObjectCreateListener(this);
		GUObjectArray.AddUObjectDeleteListener(this);
		OnAsyncLoadingFlushUpdateDelegateHandle = FCoreDelegates::OnAsyncLoadingFlushUpdate.AddRaw(this, &FPuertsExModule::OnAsyncLoadingFlushUpdate);
	}
	else
	{
		GUObjectArray.RemoveUObjectCreateListener(this);
		GUObjectArray.RemoveUObjectDeleteListener(this);
	}
	bIsActive = bInActive;
	UE_LOG(LogPuertsEx,Log,TEXT("[Puerts] Active = "),bInActive ? TEXT("true") : TEXT("false"));
}

void FPuertsExModule::HotReload()
{

}

TSharedPtr<puerts::FJsEnv> FPuertsExModule::GetJsEvn(UObject* Object /* = nullptr */)
{
	return nullptr;
}


void FPuertsExModule::SetJsEvn(TSharedPtr<puerts::FJsEnv> InJsEnv)
{

}

void FPuertsExModule::RegisterSettings()
{
#if WITH_EDITOR
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		auto SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "PuertsEx",
			LOCTEXT("TileSetEditorSettingsName", "PuertsEx Settings"),
			LOCTEXT("TileSetEditorSettingsDescription", "Configure the setting of PuertsEx plugin."),
			GetMutableDefault<UPuertsExSetting>());

		SettingsSection->OnModified().BindRaw(this, &FPuertsExModule::HandleSettingsSaved);
	}
#endif
}


void FPuertsExModule::UnregisterSettings()
{
#if WITH_EDITOR
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "PuertsEx");
	}
#endif
}


void FPuertsExModule::RegisterDelegates()
{
	WorldCleanupHandle = FWorldDelegates::OnWorldCleanup.AddRaw(this, &FPuertsExModule::OnWorldCleanup);
	PostWorldCleanupHandle = FWorldDelegates::OnPostWorldCleanup.AddRaw(this, &FPuertsExModule::OnPostWorldCleanup);
	PreWorldInitializationHandle = FWorldDelegates::OnPreWorldInitialization.AddRaw(this, &FPuertsExModule::OnPreWorldInitialization);
	PostWorldInitializationHandle = FWorldDelegates::OnPostWorldInitialization.AddRaw(this, &FPuertsExModule::OnPostWorldInitialization);
	PostEngineInitHandle = FCoreDelegates::OnPostEngineInit.AddRaw(this, &FPuertsExModule::OnPostEngineInit);
	PreExitHandle = FCoreDelegates::OnPreExit.AddRaw(this, &FPuertsExModule::OnPreExit);
	HandleSystemErrorHandle = FCoreDelegates::OnHandleSystemError.AddRaw(this, &FPuertsExModule::OnCrash);
	HandleSystemEnsureHandle = FCoreDelegates::OnHandleSystemEnsure.AddRaw(this, &FPuertsExModule::OnCrash);

	PreLoadMapHandle = FCoreUObjectDelegates::PreLoadMap.AddRaw(this, &FPuertsExModule::PreLoadMap);
	PostLoadMapWithWorldHandle = FCoreUObjectDelegates::PostLoadMapWithWorld.AddRaw(this, &FPuertsExModule::PostLoadMapWithWorld);
#if WITH_EDITOR
	PreBeginPIEHandle = FEditorDelegates::PreBeginPIE.AddRaw(this, &FPuertsExModule::PreBeginPIE);
	BeginPIEHandle = FEditorDelegates::BeginPIE.AddRaw(this, &FPuertsExModule::BeginPIE);
	PostPIEStartedHandle = FEditorDelegates::PostPIEStarted.AddRaw(this, &FPuertsExModule::PostPIEStarted);
	PrePIEEndedHandle = FEditorDelegates::PrePIEEnded.AddRaw(this, &FPuertsExModule::PrePIEEnded);
	EndPIEHandle = FEditorDelegates::EndPIE.AddRaw(this, &FPuertsExModule::EndPIE);
	FGameDelegates::Get().GetEndPlayMapDelegate().AddRaw(this, &FPuertsExModule::OnEndPlayMap);
#endif
}


void FPuertsExModule::UnregisterDelegates()
{
	FWorldDelegates::OnWorldCleanup.Remove(WorldCleanupHandle); WorldCleanupHandle.Reset();
	FWorldDelegates::OnPostWorldCleanup.Remove(PostWorldCleanupHandle); PostWorldCleanupHandle.Reset();
	FWorldDelegates::OnPreWorldInitialization.Remove(PreWorldInitializationHandle); PreWorldInitializationHandle.Reset();
	FWorldDelegates::OnPostWorldInitialization.Remove(PostWorldInitializationHandle); PostWorldInitializationHandle.Reset();
	FCoreDelegates::OnPostEngineInit.Remove(PostEngineInitHandle); PostEngineInitHandle.Reset();
	FCoreDelegates::OnPreExit.Remove(PreExitHandle); PreExitHandle.Reset();
	FCoreDelegates::OnHandleSystemError.Remove(HandleSystemErrorHandle); HandleSystemErrorHandle.Reset();
	FCoreDelegates::OnHandleSystemEnsure.Remove(HandleSystemEnsureHandle); HandleSystemEnsureHandle.Reset();

	FCoreUObjectDelegates::PreLoadMap.Remove(PreLoadMapHandle); PreLoadMapHandle.Reset();
	FCoreUObjectDelegates::PostLoadMapWithWorld.Remove(PostLoadMapWithWorldHandle); PostLoadMapWithWorldHandle.Reset();
#if WITH_EDITOR
	FEditorDelegates::PreBeginPIE.Remove(PreBeginPIEHandle); PreBeginPIEHandle.Reset();
	FEditorDelegates::BeginPIE.Remove(BeginPIEHandle); BeginPIEHandle.Reset();
	FEditorDelegates::PostPIEStarted.Remove(PostPIEStartedHandle); PostPIEStartedHandle.Reset();
	FEditorDelegates::PrePIEEnded.Remove(PrePIEEndedHandle); PrePIEEndedHandle.Reset();
	FEditorDelegates::EndPIE.Remove(EndPIEHandle); EndPIEHandle.Reset();
#endif
}

#if WITH_EDITOR
bool FPuertsExModule::HandleSettingsSaved()
{
	const UPuertsExSetting& Settings = *GetDefault<UPuertsExSetting>();
	if (Settings.AutoMixinEnable != bIsAutoMixin)
	{
		bIsAutoMixin = Settings.AutoMixinEnable;
	}
	return true;
}
#endif

void FPuertsExModule::NotifyUObjectCreated(const class UObjectBase* InObject, int32 Index)
{
	UObject* Object = (UObject*)InObject;
	if (Object) 
	{
		const auto TempClass = Object->IsA<UClass>() ? static_cast<UClass*>(Object) : Object->GetClass();
		check(TempClass);
		if (TempClass)
		{
			int32 InternalIndex = TempClass->GetUniqueID();
			int32 ObjLastNonGCIndex = GUObjectArray.GetObjectArrayNumPermanent();
			UE_LOG(LogPuertsEx, Log, TEXT("[Puerts] InternalIndex = %d, ObjLastNonGCIndex = %d"), InternalIndex, ObjLastNonGCIndex);
			if (GUObjectArray.IsDisregardForGC(TempClass))
			{
				UE_LOG(LogTemp, Log, TEXT("[Puerts] Disregard For GC ClassName = %s, ClassPtr = %p"), *TempClass->GetName(), TempClass);
			}
		}
		UE_LOG(LogPuertsEx, Log, TEXT("[Puerts] Create Object = %s, Ptr = %p, ClassName = %s, ClassPtr = %p"), *Object->GetName(), Object, *TempClass->GetName(), TempClass);
	}
	if (!bIsActive) {
		return;
	}
	
	if (Object)
	{
		if (Object->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))//过滤掉CDO对象和模版对象
		{
			return;
		}
		const auto Class = Object->IsA<UClass>() ? static_cast<UClass*>(Object) : Object->GetClass();
		check(Class);
		if (Class->HasAnyClassFlags(CLASS_NewerVersionExists))
		{
			return;
		}
		if (Class->HasAnyFlags(RF_NeedPostLoad | RF_NeedPostLoadSubobjects))
		{
			return;
		}
		static UClass* InterfaceClass = UPuertsMixinInterface::StaticClass();
		if (Class->ImplementsInterface(InterfaceClass))
		{
			UFunction* Func = Class->FindFunctionByName(FName("GetTSClassName"));
			if (Func && Func->GetNativeFunc())
			{
				if (IsInGameThread())
				{
					FName TSClassName;
					UObject* DefaultObject = Class->GetDefaultObject();
					DefaultObject->UObject::ProcessEvent(Func, &TSClassName);
					if (TSClassName.IsValid() && UPuertsMixinTool::IsValidAndActive())
					{
						UPuertsMixinTool::GetInstance()->Mixin(Class, TSClassName);
					}
				}
				else
				{
					FScopeLock Lock(&CandidatesLock);
					Candidates.Add((UObject*)Object);
				}
			}
		}
	}
}


void FPuertsExModule::NotifyUObjectDeleted(const class UObjectBase* InObject, int32 Index)
{
	if (!bIsActive){
		return;
	}
	
	UObject* Object = (UObject*)InObject;
	if (Object)
	{
		if (Object->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject)) //过滤掉CDO对象和模版对象
		{
			return;
		}
		const auto Class = Object->IsA<UClass>() ? static_cast<UClass*>(Object) : Object->GetClass();
		check(Class);
		if (Class->HasAnyClassFlags(CLASS_NewerVersionExists))
		{
			return;
		}
		if (Class->IsChildOf<UPackage>() || Class->IsChildOf<UClass>())
		{
			return;
		}
	}
}


void FPuertsExModule::OnUObjectArrayShutdown()
{
	GUObjectArray.RemoveUObjectCreateListener(this);
	GUObjectArray.RemoveUObjectDeleteListener(this);
	FCoreDelegates::OnAsyncLoadingFlushUpdate.Remove(OnAsyncLoadingFlushUpdateDelegateHandle); OnAsyncLoadingFlushUpdateDelegateHandle.Reset();
}


void FPuertsExModule::OnAsyncLoadingFlushUpdate()
{
	TArray<FWeakObjectPtr> CandidatesTemp;
	TArray<int> CandidatesRemovedIndexes;

	TArray<UObject*> LocalCandidates;
	{
		{
			FScopeLock Lock(&CandidatesLock);
			CandidatesTemp.Append(Candidates);
		}

		for (int32 i = CandidatesTemp.Num() - 1; i >= 0; --i)
		{
			FWeakObjectPtr ObjectPtr = CandidatesTemp[i];
			if (!ObjectPtr.IsValid())
			{
				CandidatesRemovedIndexes.Add(i);
				continue;
			}

			UObject* Object = ObjectPtr.Get();
			if (Object->HasAnyFlags(RF_NeedPostLoad) || Object->HasAnyInternalFlags(AsyncObjectFlags) || Object->GetClass()->HasAnyInternalFlags(AsyncObjectFlags))
			{
				continue;
			}
			LocalCandidates.Add(Object);
			CandidatesRemovedIndexes.Add(i);
		}
	}

	{
		FScopeLock Lock(&CandidatesLock);
		for (int32 j = 0; j < CandidatesRemovedIndexes.Num(); ++j)
		{
			Candidates.RemoveAt(CandidatesRemovedIndexes[j]);
		}
	}

	for (int32 i = 0; i < LocalCandidates.Num(); ++i)
	{
		UObject* Object = LocalCandidates[i];
		UClass* Class = Object->GetClass();
		UFunction* Func = Class->FindFunctionByName(FName("GetTSClassName"));
		if (Func)
		{
			FName TSClassName;
			UObject* DefaultObject = Class->GetDefaultObject();
			DefaultObject->UObject::ProcessEvent(Func, &TSClassName);
			if (TSClassName.IsValid() && UPuertsMixinTool::IsValidAndActive())
			{
				UPuertsMixinTool::GetInstance()->Mixin(Class, TSClassName);
			}
		}
	}
}

void FPuertsExModule::OnWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources)
{
	UE_LOG(LogTemp, Log, TEXT("[UEDelegates-Core] OnWorldCleanup"));
}


void FPuertsExModule::OnPostWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources)
{
	UE_LOG(LogTemp, Log, TEXT("[UEDelegates-Core] OnPostWorldCleanup"));
}


void FPuertsExModule::OnPreWorldInitialization(UWorld* World, const UWorld::InitializationValues)
{
	UE_LOG(LogTemp, Log, TEXT("[UEDelegates-Core] OnPreWorldInitialization"));
}


void FPuertsExModule::OnPostWorldInitialization(UWorld* World, const UWorld::InitializationValues)
{
	UE_LOG(LogTemp, Log, TEXT("[UEDelegates-Core] OnPostWorldInitialization"));
}


void FPuertsExModule::OnPostEngineInit()
{
	UE_LOG(LogTemp, Log, TEXT("[UEDelegates-Core] OnPostEngineInit"));
}


void FPuertsExModule::OnPreExit()
{
	UE_LOG(LogTemp, Log, TEXT("[UEDelegates-Core] OnPreExit"));
}

void FPuertsExModule::OnCrash()
{
	UE_LOG(LogTemp, Log, TEXT("[UEDelegates-Core] OnCrash"));
}


void FPuertsExModule::PreLoadMap(const FString& MapName)
{
	UE_LOG(LogTemp, Log, TEXT("[UEDelegates-Core] PreLoadMap"));
}


void FPuertsExModule::PostLoadMapWithWorld(UWorld* World)
{
	UE_LOG(LogTemp, Log, TEXT("[UEDelegates-Core] PostLoadMapWithWorld"));
}


void FPuertsExModule::OnPostGarbageCollect()
{
	UE_LOG(LogTemp, Log, TEXT("[UEDelegates-Core] OnPostGarbageCollect"));
}

#if WITH_EDITOR
void FPuertsExModule::PreBeginPIE(bool bIsSimulating)
{
	UE_LOG(LogTemp, Log, TEXT("[UEDelegates-Editor] PreBeginPIE"));
	SetActive(true);
}


void FPuertsExModule::BeginPIE(bool bIsSimulating)
{
	UE_LOG(LogTemp, Log, TEXT("[UEDelegates-Editor] BeginPIE"));
}


void FPuertsExModule::PostPIEStarted(bool bIsSimulating)
{
	UE_LOG(LogTemp, Log, TEXT("[UEDelegates-Editor] PostPIEStarted"));
}


void FPuertsExModule::PrePIEEnded(bool bIsSimulating)
{
	UE_LOG(LogTemp, Log, TEXT("[UEDelegates-Editor] PrePIEEnded"));
}


void FPuertsExModule::EndPIE(bool bIsSimulating)
{
	UE_LOG(LogTemp, Log, TEXT("[UEDelegates-Editor] EndPIE"));
}


void FPuertsExModule::OnEndPlayMap()
{
	UE_LOG(LogTemp, Log, TEXT("[UEDelegates-Editor] OnEndPlayMap"));
	SetActive(false);
}
#endif

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPuertsExModule, PuertsEx)
