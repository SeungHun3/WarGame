// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "IXRTrackingSystem.h"
#include "IHeadMountedDisplay.h"
#include "HeadMountedDisplayFunctionLibrary.h"


// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//CheckSensorData(); 
	//indexSensorData(0);
	//BP_NearPlane();
	//C_Origin_Z();
	//BP_Right();
	//BP_Origin_Z();
	//C_Right_Bottom();
	//BP_FarPlane_Origin_XY();
	//BP_Bottom_FarPlane_Origin_X();
	//C_BP_Right_Bottom();
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}










void CountSensor()
{
	// ���� Ȯ���ϱ�
	int Any = GEngine->XRSystem->CountTrackedDevices(EXRTrackedDeviceType::Any); // 7
	int Controllercnt = GEngine->XRSystem->CountTrackedDevices(EXRTrackedDeviceType::Controller); // 6
	int headmount = GEngine->XRSystem->CountTrackedDevices(EXRTrackedDeviceType::HeadMountedDisplay); // 1
	int invalid = GEngine->XRSystem->CountTrackedDevices(EXRTrackedDeviceType::Invalid);
	int Other = GEngine->XRSystem->CountTrackedDevices(EXRTrackedDeviceType::Other);
	int Tracker = GEngine->XRSystem->CountTrackedDevices(EXRTrackedDeviceType::Tracker);
	int TrackingReference = GEngine->XRSystem->CountTrackedDevices(EXRTrackedDeviceType::TrackingReference); // ���� �ִ� ������ �����͸� ��.

	UE_LOG(LogTemp, Log, TEXT("// All Tracking Devices Count : Any %d, controller %d, headmount %d, invalid %d, Other %d, Tracker %d, TrackingReference %d")
		, Any, Controllercnt, headmount, invalid, Other, Tracker, TrackingReference);
}

// C =
// right bottom FarPlane -2 ~ 2 ������ ��
// left top camera NearPlane ���� ��
// BP = 
// bottom FarPlane 1.�� ��
// top camera NearPlane ���� ��
void AMyPawn::CheckSensorData()
{
	auto HMD = GEngine->XRSystem;
	//CountSensor();

	auto device = HMD->GetHMDDevice();
	// �Ѵ� false
	UE_LOG(LogTemp, Log, TEXT("// HasHiddenAreaMesh : %s"),
		device->HasHiddenAreaMesh() ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));
	UE_LOG(LogTemp, Log, TEXT("// HasVisibleAreaMesh : %s"),
		device->HasVisibleAreaMesh() ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));
	
	UE_LOG(LogTemp, Log, TEXT("// GetHMDName : %s"), *device->GetHMDName().ToString()); //Oculus Quest2
	
	UE_LOG(LogTemp, Log, TEXT("// GetSystemName : %s"),
		*HMD->GetSystemName().ToString()); // openXR // ������ �������Ʈ ������ ���� ����
	
	
	UE_LOG(LogTemp, Log, TEXT("// IsTracking : %s"),
		HMD->IsTracking(0) ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));
	
	// ��ġ Ʈ��ŷ ����? true
	bool DoesSupportPositionalTracking = HMD->DoesSupportPositionalTracking();
	UE_LOG(LogTemp, Log, TEXT("// DoesSupportPositionalTracking : %s"),
		DoesSupportPositionalTracking ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));
	
	
	// HMD�� ��ġ ������ �����ϴ� ��� ���� ���� ������? true
	bool hasVaildTrackingPosition = HMD->HasValidTrackingPosition();
	UE_LOG(LogTemp, Log, TEXT("// HasValidTrackingPosition : %s"),
		hasVaildTrackingPosition ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));
	
	/*
	* ���׷��� �������� ��Ȱ��ȭ�� ��쿡�� ������ �����ϴ� �� ����� �� �ֽ��ϴ�.
	* �⺻ ���������� ������ ������ �� ������ �׻� false�� ��ȯ�մϴ�.
	* �� ����� ���Ӱ� ���� ������ ��ο��� ȣ��˴ϴ�.
	*/
	//false
	UE_LOG(LogTemp, Log, TEXT("// IsHeadTrackingEnforced : %s"), HMD->IsHeadTrackingEnforced() ? 
		UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));
	
	UE_LOG(LogTemp, Log, TEXT("// GetTrackedDevicePropertySerialNumber : %s"),
		*HMD->GetTrackedDevicePropertySerialNumber(0)); // NoSerial
	UE_LOG(LogTemp, Log, TEXT("///////////////////////////////////////////////////////////"));
	
	// ���� �Լ����� �����ϸ� ���� �����Ͱ� ����
	FXRSensorProperties sensorData;
	FQuat TempQuat;
	FVector TempVector;
	bool Active = HMD->GetTrackingSensorProperties(0, TempQuat, TempVector, sensorData);
	// false
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Active : % s"), 
		Active ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));
	
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Vector X: %f  Y: %f, Z: %f  "), TempVector.X, TempVector.Y, TempVector.Z);
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Left: %f"), sensorData.LeftFOV);
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Right: %f"), sensorData.RightFOV);
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Top: %f"), sensorData.TopFOV);
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Bottom: %f"), sensorData.BottomFOV);
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Camera Distance : %f"), sensorData.CameraDistance);
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : FarPlane : %f"), sensorData.FarPlane);
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : NearPlane : %f"), sensorData.NearPlane);

	

	FVector Origin;
	FRotator Orient;
	float Left;
	float Right;
	float Top;
	float Bottom;
	float CameraDistance;
	float NearPlane;
	float FarPlane;
	bool IsActive;
	UHeadMountedDisplayFunctionLibrary::GetTrackingSensorParameters(Origin, Orient, Left, Right, Top, Bottom, CameraDistance, NearPlane, FarPlane, IsActive);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Vector X: %f  Y: %f, Z: %f  "), Origin.X, Origin.Y, Origin.Z);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Left: %f"), Left);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Right: %f"), Right);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Top: %f"), Top);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Bottom: %f"), Bottom);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Camera Distance : %f"), CameraDistance);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : FarPlane : %f"), FarPlane);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : NearPlane : %f"), NearPlane);
	
	
	UE_LOG(LogTemp, Log, TEXT("///////////////////////////////////////////////////////////"));

}
	
// �������Ʈ
//  NearPlane ����, top ������ �׿� ���� 0
void AMyPawn::BP_NearPlane()
{
	FVector Origin;
	FRotator Orient;
	float Left;
	float Right;
	float Top;
	float Bottom;
	float CameraDistance;
	float NearPlane;
	float FarPlane;
	bool IsActive;
	UHeadMountedDisplayFunctionLibrary::GetTrackingSensorParameters(Origin, Orient, Left, Right, Top, Bottom, CameraDistance, NearPlane, FarPlane, IsActive);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Vector X: %f  Y: %f, Z: %f  "), Origin.X, Origin.Y, Origin.Z);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Left: %f"), Left);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Right: %f"), Right);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Top: %f"), Top);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Bottom: %f"), Bottom);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Camera Distance : %f"), CameraDistance);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : FarPlane : %f"), FarPlane);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : NearPlane : %f"), NearPlane);
}


// bottom ���� 
// farPlane -2 ~ 2 ������ ��
// top, camera, nearPlane  ����   
void AMyPawn::BP_Bottom_FarPlane_Origin_X()
{
	auto HMD = GEngine->XRSystem;
	auto device = HMD->GetHMDDevice();
	// �Ѵ� false
	UE_LOG(LogTemp, Log, TEXT("// HasHiddenAreaMesh : %s"),
		device->HasHiddenAreaMesh() ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));
	UE_LOG(LogTemp, Log, TEXT("// HasVisibleAreaMesh : %s"),
		device->HasVisibleAreaMesh() ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));

	// ��ġ Ʈ��ŷ ����? true
	bool DoesSupportPositionalTracking = HMD->DoesSupportPositionalTracking();

	// ���� �Լ����� �����ϸ� ���� �����Ͱ� ����
	FXRSensorProperties sensorData;
	FQuat TempQuat;
	FVector TempVector;
	bool Active = HMD->GetTrackingSensorProperties(0, TempQuat, TempVector, sensorData);
	// false
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Active : % s"),
		Active ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));

	FVector Origin;
	FRotator Orient;
	float Left;
	float Right;
	float Top;
	float Bottom;
	float CameraDistance;
	float NearPlane;
	float FarPlane;
	bool IsActive;
	UHeadMountedDisplayFunctionLibrary::GetTrackingSensorParameters(Origin, Orient, Left, Right, Top, Bottom, CameraDistance, NearPlane, FarPlane, IsActive);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Vector X: %f  Y: %f, Z: %f  "), Origin.X, Origin.Y, Origin.Z);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Left: %f"), Left);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Right: %f"), Right);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Top: %f"), Top);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Bottom: %f"), Bottom);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Camera Distance : %f"), CameraDistance);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : FarPlane : %f"), FarPlane);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : NearPlane : %f"), NearPlane);


	UE_LOG(LogTemp, Log, TEXT("///////////////////////////////////////////////////////////"));

}

void AMyPawn::BP_Right()
{
	auto HMD = GEngine->XRSystem;
	auto device = HMD->GetHMDDevice();
	UE_LOG(LogTemp, Log, TEXT("// GetHMDName : %s"), *device->GetHMDName().ToString()); //Oculus Quest2

	UE_LOG(LogTemp, Log, TEXT("// GetSystemName : %s"),
		*HMD->GetSystemName().ToString()); // openXR // ������ �������Ʈ ������ ���� ����


	UE_LOG(LogTemp, Log, TEXT("// IsTracking : %s"),
		HMD->IsTracking(0) ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));


	UE_LOG(LogTemp, Log, TEXT("///////////////////////////////////////////////////////////"));
	FXRSensorProperties sensorData;
	FQuat TempQuat;
	FVector TempVector;
	bool Active = HMD->GetTrackingSensorProperties(0, TempQuat, TempVector, sensorData);
	// false
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Active : % s"),
		Active ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));


	FVector Origin;
	FRotator Orient;
	float Left;
	float Right;
	float Top;
	float Bottom;
	float CameraDistance;
	float NearPlane;
	float FarPlane;
	bool IsActive;
	UHeadMountedDisplayFunctionLibrary::GetTrackingSensorParameters(Origin, Orient, Left, Right, Top, Bottom, CameraDistance, NearPlane, FarPlane, IsActive);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Vector X: %f  Y: %f, Z: %f  "), Origin.X, Origin.Y, Origin.Z);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Left: %f"), Left);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Right: %f"), Right);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Top: %f"), Top);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Bottom: %f"), Bottom);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Camera Distance : %f"), CameraDistance);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : FarPlane : %f"), FarPlane);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : NearPlane : %f"), NearPlane);


	UE_LOG(LogTemp, Log, TEXT("///////////////////////////////////////////////////////////"));


}

// -1< Z < ~1 �� ��
void AMyPawn::BP_Origin_Z() 
{
	auto HMD = GEngine->XRSystem;
	auto device = HMD->GetHMDDevice();
	// �Ѵ� false
	UE_LOG(LogTemp, Log, TEXT("// HasHiddenAreaMesh : %s"),
		device->HasHiddenAreaMesh() ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));
	UE_LOG(LogTemp, Log, TEXT("// HasVisibleAreaMesh : %s"),
		device->HasVisibleAreaMesh() ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));

	UE_LOG(LogTemp, Log, TEXT("// GetHMDName : %s"), *device->GetHMDName().ToString()); //Oculus Quest2

	UE_LOG(LogTemp, Log, TEXT("// GetSystemName : %s"),
		*HMD->GetSystemName().ToString()); // openXR // ������ �������Ʈ ������ ���� ����


	UE_LOG(LogTemp, Log, TEXT("// IsTracking : %s"),
		HMD->IsTracking(0) ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));

	UE_LOG(LogTemp, Log, TEXT("///////////////////////////////////////////////////////////"));

	// ���� �Լ����� �����ϸ� ���� �����Ͱ� ����
	FXRSensorProperties sensorData;
	FQuat TempQuat;
	FVector TempVector;
	bool Active = HMD->GetTrackingSensorProperties(0, TempQuat, TempVector, sensorData);
	// false
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Active : % s"),
		Active ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));

	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Vector X: %f  Y: %f, Z: %f  "), TempVector.X, TempVector.Y, TempVector.Z);
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Left: %f"), sensorData.LeftFOV);
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Right: %f"), sensorData.RightFOV);
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Top: %f"), sensorData.TopFOV);
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Bottom: %f"), sensorData.BottomFOV);
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Camera Distance : %f"), sensorData.CameraDistance);
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : FarPlane : %f"), sensorData.FarPlane);
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : NearPlane : %f"), sensorData.NearPlane);



	FVector Origin;
	FRotator Orient;
	float Left;
	float Right;
	float Top;
	float Bottom;
	float CameraDistance;
	float NearPlane;
	float FarPlane;
	bool IsActive;
	UHeadMountedDisplayFunctionLibrary::GetTrackingSensorParameters(Origin, Orient, Left, Right, Top, Bottom, CameraDistance, NearPlane, FarPlane, IsActive);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Vector X: %f  Y: %f, Z: %f  "), Origin.X, Origin.Y, Origin.Z);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Left: %f"), Left);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Right: %f"), Right);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Top: %f"), Top);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Bottom: %f"), Bottom);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Camera Distance : %f"), CameraDistance);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : FarPlane : %f"), FarPlane);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : NearPlane : %f"), NearPlane);


	UE_LOG(LogTemp, Log, TEXT("///////////////////////////////////////////////////////////"));

}


// FarPlane -4.~ �� ���� , origin x, y �� ���� 
void AMyPawn::BP_FarPlane_Origin_XY()
{
	auto HMD = GEngine->XRSystem;
	UE_LOG(LogTemp, Log, TEXT("// IsTracking : %s"),
		HMD->IsTracking(0) ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));

	// ��ġ Ʈ��ŷ ����? true
	bool DoesSupportPositionalTracking = HMD->DoesSupportPositionalTracking();
	UE_LOG(LogTemp, Log, TEXT("// DoesSupportPositionalTracking : %s"),
		DoesSupportPositionalTracking ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));
	UE_LOG(LogTemp, Log, TEXT("///////////////////////////////////////////////////////////"));

	FVector Origin;
	FRotator Orient;
	float Left;
	float Right;
	float Top;
	float Bottom;
	float CameraDistance;
	float NearPlane;
	float FarPlane;
	bool IsActive;
	UHeadMountedDisplayFunctionLibrary::GetTrackingSensorParameters(Origin, Orient, Left, Right, Top, Bottom, CameraDistance, NearPlane, FarPlane, IsActive);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Vector X: %f  Y: %f, Z: %f  "), Origin.X, Origin.Y, Origin.Z);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Left: %f"), Left);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Right: %f"), Right);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Top: %f"), Top);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Bottom: %f"), Bottom);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Camera Distance : %f"), CameraDistance);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : FarPlane : %f"), FarPlane);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : NearPlane : %f"), NearPlane);


	UE_LOG(LogTemp, Log, TEXT("///////////////////////////////////////////////////////////"));

}


// C = 
// Right, Bottom, FarPlane: -2 ~ 2  ���� �� 
// Left Top Camera nearPlane ����
// 
// BP = 
// Right -2 ~ 2 ���̰� 
// Bottom 3.�� ��
void AMyPawn::C_BP_Right_Bottom()
{
	auto HMD = GEngine->XRSystem;
	auto device = HMD->GetHMDDevice();
	// �Ѵ� false
	UE_LOG(LogTemp, Log, TEXT("// HasHiddenAreaMesh : %s"),
		device->HasHiddenAreaMesh() ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));
	UE_LOG(LogTemp, Log, TEXT("// HasVisibleAreaMesh : %s"),
		device->HasVisibleAreaMesh() ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));

	UE_LOG(LogTemp, Log, TEXT("// GetHMDName : %s"), *device->GetHMDName().ToString()); //Oculus Quest2

	UE_LOG(LogTemp, Log, TEXT("// GetSystemName : %s"),
		*HMD->GetSystemName().ToString()); // openXR 


	UE_LOG(LogTemp, Log, TEXT("// IsTracking : %s"),
		HMD->IsTracking(0) ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));

	// ��ġ Ʈ��ŷ ����? true
	bool DoesSupportPositionalTracking = HMD->DoesSupportPositionalTracking();
	UE_LOG(LogTemp, Log, TEXT("// DoesSupportPositionalTracking : %s"),
		DoesSupportPositionalTracking ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));


	// HMD�� ��ġ ������ �����ϴ� ��� ���� ���� ������? true
	bool hasVaildTrackingPosition = HMD->HasValidTrackingPosition();
	UE_LOG(LogTemp, Log, TEXT("// HasValidTrackingPosition : %s"),
		hasVaildTrackingPosition ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));

	/*
	* ���׷��� �������� ��Ȱ��ȭ�� ��쿡�� ������ �����ϴ� �� ����� �� �ֽ��ϴ�.
	* �⺻ ���������� ������ ������ �� ������ �׻� false�� ��ȯ�մϴ�.
	* �� ����� ���Ӱ� ���� ������ ��ο��� ȣ��˴ϴ�.
	*/
	//false
	UE_LOG(LogTemp, Log, TEXT("// IsHeadTrackingEnforced : %s"), HMD->IsHeadTrackingEnforced() ?
		UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));


	UE_LOG(LogTemp, Log, TEXT("///////////////////////////////////////////////////////////"));

	// ���� �Լ����� �����ϸ� ���� �����Ͱ� ����
	FXRSensorProperties sensorData;
	FQuat TempQuat;
	FVector TempVector;
	bool Active = HMD->GetTrackingSensorProperties(0, TempQuat, TempVector, sensorData);
	// false
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Active : % s"),
		Active ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));

	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Vector X: %f  Y: %f, Z: %f  "), TempVector.X, TempVector.Y, TempVector.Z);
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Left: %f"), sensorData.LeftFOV);
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Right: %f"), sensorData.RightFOV);
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Top: %f"), sensorData.TopFOV);
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Bottom: %f"), sensorData.BottomFOV);
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Camera Distance : %f"), sensorData.CameraDistance);
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : FarPlane : %f"), sensorData.FarPlane);
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : NearPlane : %f"), sensorData.NearPlane);



	FVector Origin;
	FRotator Orient;
	float Left;
	float Right;
	float Top;
	float Bottom;
	float CameraDistance;
	float NearPlane;
	float FarPlane;
	bool IsActive;
	UHeadMountedDisplayFunctionLibrary::GetTrackingSensorParameters(Origin, Orient, Left, Right, Top, Bottom, CameraDistance, NearPlane, FarPlane, IsActive);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Vector X: %f  Y: %f, Z: %f  "), Origin.X, Origin.Y, Origin.Z);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Left: %f"), Left);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Right: %f"), Right);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Top: %f"), Top);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Bottom: %f"), Bottom);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : Camera Distance : %f"), CameraDistance);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : FarPlane : %f"), FarPlane);
	UE_LOG(LogTemp, Log, TEXT("//  BP_SensorData : NearPlane : %f"), NearPlane);


	UE_LOG(LogTemp, Log, TEXT("///////////////////////////////////////////////////////////"));


}

void AMyPawn::C_Origin_Z() // ������ǥ y 
{
	auto HMD = GEngine->XRSystem;
	auto device = HMD->GetHMDDevice();
	// �Ѵ� false
	UE_LOG(LogTemp, Log, TEXT("// HasHiddenAreaMesh : %s"),
		device->HasHiddenAreaMesh() ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));
	UE_LOG(LogTemp, Log, TEXT("// HasVisibleAreaMesh : %s"),
		device->HasVisibleAreaMesh() ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));

	UE_LOG(LogTemp, Log, TEXT("// GetHMDName : %s"), *device->GetHMDName().ToString()); //Oculus Quest2


	FXRSensorProperties sensorData;
	FQuat TempQuat;
	FVector TempVector;
	bool Active = HMD->GetTrackingSensorProperties(0, TempQuat, TempVector, sensorData);
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Active : % s"),
		Active ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));

	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Vector X: %f  Y: %f, Z: %f  "), TempVector.X, TempVector.Y, TempVector.Z);

	FVector Origin;
	FRotator Orient;
	float Left;
	float Right;
	float Top;
	float Bottom;
	float CameraDistance;
	float NearPlane;
	float FarPlane;
	bool IsActive;
	UHeadMountedDisplayFunctionLibrary::GetTrackingSensorParameters(Origin, Orient, Left, Right, Top, Bottom, CameraDistance, NearPlane, FarPlane, IsActive);
	UE_LOG(LogTemp, Log, TEXT("///////////////////////////////////////////////////////////"));
}


//Right, Bottom ���� // top, Left ���̰�, Vector x: 1 , y: 0, z:1
void AMyPawn::C_Right_Bottom()
{
	auto HMD = GEngine->XRSystem;
	auto device = HMD->GetHMDDevice();
	// �Ѵ� false
	UE_LOG(LogTemp, Log, TEXT("// HasHiddenAreaMesh : %s"),
		device->HasHiddenAreaMesh() ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));
	UE_LOG(LogTemp, Log, TEXT("// HasVisibleAreaMesh : %s"),
		device->HasVisibleAreaMesh() ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));

	// vector �� ���� x: 1 , y: 0, z:1
	// 
	//UE_LOG(LogTemp, Log, TEXT("// GetSystemName : %s"),
	//	*HMD->GetSystemName().ToString()); // openXR 

	UE_LOG(LogTemp, Log, TEXT("// IsTracking : %s"),
		HMD->IsTracking(0) ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));

	// ��ġ Ʈ��ŷ ����? true
	bool DoesSupportPositionalTracking = HMD->DoesSupportPositionalTracking();
	UE_LOG(LogTemp, Log, TEXT("// DoesSupportPositionalTracking : %s"),
		DoesSupportPositionalTracking ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));
	UE_LOG(LogTemp, Log, TEXT("///////////////////////////////////////////////////////////"));

	// ���� �Լ����� �����ϸ� ���� �����Ͱ� ����
	FXRSensorProperties sensorData;
	FQuat TempQuat;
	FVector TempVector;
	bool Active = HMD->GetTrackingSensorProperties(0, TempQuat, TempVector, sensorData);
	// false
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Active : % s"),
		Active ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));

	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Vector X: %f  Y: %f, Z: %f  "), TempVector.X, TempVector.Y, TempVector.Z);
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Left: %f"), sensorData.LeftFOV);
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Right: %f"), sensorData.RightFOV);
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Top: %f"), sensorData.TopFOV);
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Bottom: %f"), sensorData.BottomFOV);
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : Camera Distance : %f"), sensorData.CameraDistance);
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : FarPlane : %f"), sensorData.FarPlane);
	UE_LOG(LogTemp, Log, TEXT("//  SensorData : NearPlane : %f"), sensorData.NearPlane);


	UE_LOG(LogTemp, Log, TEXT("///////////////////////////////////////////////////////////"));
}

void AMyPawn::indexSensorData(int index, bool AllCheck)
{
	UE_LOG(LogTemp, Log, TEXT("// indexSensorData"));
}


