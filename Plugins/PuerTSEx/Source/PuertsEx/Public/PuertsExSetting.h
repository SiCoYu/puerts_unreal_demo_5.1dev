// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PuertsExSetting.generated.h"

UCLASS(config = PuertsEx, defaultconfig, meta = (DisplayName = "PuertsEx"))
class PUERTSEX_API UPuertsExSetting : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(config, EditAnywhere, Category = "控制开关", meta = (Tooltip = "控制AutoMixin开关", defaultValue = false))
    bool AutoMixinEnable = false;
	UPROPERTY(config, EditAnywhere, Category = "控制开关", meta = (Tooltip = "控制UnMixin开关", defaultValue = false))
    bool UnMixinEnable = false;
	UPROPERTY(config, EditAnywhere, Category = "控制开关", meta = (Tooltip = "控制日志开关", defaultValue = true))
    bool LogEnable = true;	
};
