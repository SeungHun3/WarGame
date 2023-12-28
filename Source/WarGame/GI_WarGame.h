// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GI_WarGame.generated.h"

/**
 * 
 */
UCLASS()
class WARGAME_API UGI_WarGame : public UGameInstance
{
	GENERATED_BODY()


private:
	FVector StartLoc;

public:
	
	
	UFUNCTION(BlueprintCallable)
	void SetStartPosition(FVector _Loc);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FVector getStartPosition();

	UFUNCTION(BlueprintImplementableEvent)
	void StartControl();


};
