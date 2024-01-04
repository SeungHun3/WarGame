// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class WARGAME_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// 트래킹 센서 테스트

	//TSharedPtr<IXRTrackingSystem, ESPMode::ThreadSafe> HMD;
	void CheckSensorData();

	void BP_NearPlane();
	void BP_Bottom_FarPlane_Origin_X();
	void BP_Right();
	void BP_Origin_Z();
	void BP_FarPlane_Origin_XY();

	void C_BP_Right_Bottom();


	void C_Origin_Z();
	void C_Right_Bottom();

	UFUNCTION(BlueprintCallable)
	void indexSensorData(int index, bool AllCheck = false);
};
