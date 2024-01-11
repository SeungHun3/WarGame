// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"
#include "CustomTestModule.generated.h"

/**
 *
 */
UCLASS(config = Engine, defaultconfig)
class TESTCUSTOM_API UCustomTestModuleSettings : public UObject
{
	GENERATED_BODY()

public:
	static FORCEINLINE UCustomTestModuleSettings* Get()
	{
		UCustomTestModuleSettings* Settings = GetMutableDefault<UCustomTestModuleSettings>();
		check(Settings);
		return Settings;
	}
};