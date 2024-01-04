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
	// 센서 확인하기
	int Any = GEngine->XRSystem->CountTrackedDevices(EXRTrackedDeviceType::Any); // 7
	int Controllercnt = GEngine->XRSystem->CountTrackedDevices(EXRTrackedDeviceType::Controller); // 6
	int headmount = GEngine->XRSystem->CountTrackedDevices(EXRTrackedDeviceType::HeadMountedDisplay); // 1
	int invalid = GEngine->XRSystem->CountTrackedDevices(EXRTrackedDeviceType::Invalid);
	int Other = GEngine->XRSystem->CountTrackedDevices(EXRTrackedDeviceType::Other);
	int Tracker = GEngine->XRSystem->CountTrackedDevices(EXRTrackedDeviceType::Tracker);
	int TrackingReference = GEngine->XRSystem->CountTrackedDevices(EXRTrackedDeviceType::TrackingReference); // 여기 있는 센서로 데이터를 줌.

	UE_LOG(LogTemp, Log, TEXT("// All Tracking Devices Count : Any %d, controller %d, headmount %d, invalid %d, Other %d, Tracker %d, TrackingReference %d")
		, Any, Controllercnt, headmount, invalid, Other, Tracker, TrackingReference);
}

// C =
// right bottom FarPlane -2 ~ 2 사이의 값
// left top camera NearPlane 더미 값
// BP = 
// bottom FarPlane 1.대 값
// top camera NearPlane 더미 값
void AMyPawn::CheckSensorData()
{
	auto HMD = GEngine->XRSystem;
	//CountSensor();

	auto device = HMD->GetHMDDevice();
	// 둘다 false
	UE_LOG(LogTemp, Log, TEXT("// HasHiddenAreaMesh : %s"),
		device->HasHiddenAreaMesh() ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));
	UE_LOG(LogTemp, Log, TEXT("// HasVisibleAreaMesh : %s"),
		device->HasVisibleAreaMesh() ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));
	
	UE_LOG(LogTemp, Log, TEXT("// GetHMDName : %s"), *device->GetHMDName().ToString()); //Oculus Quest2
	
	UE_LOG(LogTemp, Log, TEXT("// GetSystemName : %s"),
		*HMD->GetSystemName().ToString()); // openXR // 없으면 블루프린트 데이터 전부 막힘
	
	
	UE_LOG(LogTemp, Log, TEXT("// IsTracking : %s"),
		HMD->IsTracking(0) ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));
	
	// 위치 트래킹 지원? true
	bool DoesSupportPositionalTracking = HMD->DoesSupportPositionalTracking();
	UE_LOG(LogTemp, Log, TEXT("// DoesSupportPositionalTracking : %s"),
		DoesSupportPositionalTracking ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));
	
	
	// HMD가 위치 추적을 지원하는 경우 현재 추적 중인지? true
	bool hasVaildTrackingPosition = HMD->HasValidTrackingPosition();
	UE_LOG(LogTemp, Log, TEXT("// HasValidTrackingPosition : %s"),
		hasVaildTrackingPosition ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));
	
	/*
	* 스테레오 렌더링이 비활성화된 경우에도 추적을 강제하는 데 사용할 수 있습니다.
	* 기본 구현에서는 추적을 적용할 수 없으며 항상 false를 반환합니다.
	* 이 방법은 게임과 렌더 스레드 모두에서 호출됩니다.
	*/
	//false
	UE_LOG(LogTemp, Log, TEXT("// IsHeadTrackingEnforced : %s"), HMD->IsHeadTrackingEnforced() ? 
		UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));
	
	UE_LOG(LogTemp, Log, TEXT("// GetTrackedDevicePropertySerialNumber : %s"),
		*HMD->GetTrackedDevicePropertySerialNumber(0)); // NoSerial
	UE_LOG(LogTemp, Log, TEXT("///////////////////////////////////////////////////////////"));
	
	// 위의 함수들을 제거하면 센서 데이터가 없음
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
	
// 블루프린트
//  NearPlane 정상, top 쓰레기 그외 전부 0
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


// bottom 정상 
// farPlane -2 ~ 2 사이의 값
// top, camera, nearPlane  더미   
void AMyPawn::BP_Bottom_FarPlane_Origin_X()
{
	auto HMD = GEngine->XRSystem;
	auto device = HMD->GetHMDDevice();
	// 둘다 false
	UE_LOG(LogTemp, Log, TEXT("// HasHiddenAreaMesh : %s"),
		device->HasHiddenAreaMesh() ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));
	UE_LOG(LogTemp, Log, TEXT("// HasVisibleAreaMesh : %s"),
		device->HasVisibleAreaMesh() ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));

	// 위치 트래킹 지원? true
	bool DoesSupportPositionalTracking = HMD->DoesSupportPositionalTracking();

	// 위의 함수들을 제거하면 센서 데이터가 없음
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
		*HMD->GetSystemName().ToString()); // openXR // 없으면 블루프린트 데이터 전부 막힘


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

// -1< Z < ~1 의 값
void AMyPawn::BP_Origin_Z() 
{
	auto HMD = GEngine->XRSystem;
	auto device = HMD->GetHMDDevice();
	// 둘다 false
	UE_LOG(LogTemp, Log, TEXT("// HasHiddenAreaMesh : %s"),
		device->HasHiddenAreaMesh() ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));
	UE_LOG(LogTemp, Log, TEXT("// HasVisibleAreaMesh : %s"),
		device->HasVisibleAreaMesh() ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));

	UE_LOG(LogTemp, Log, TEXT("// GetHMDName : %s"), *device->GetHMDName().ToString()); //Oculus Quest2

	UE_LOG(LogTemp, Log, TEXT("// GetSystemName : %s"),
		*HMD->GetSystemName().ToString()); // openXR // 없으면 블루프린트 데이터 전부 막힘


	UE_LOG(LogTemp, Log, TEXT("// IsTracking : %s"),
		HMD->IsTracking(0) ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));

	UE_LOG(LogTemp, Log, TEXT("///////////////////////////////////////////////////////////"));

	// 위의 함수들을 제거하면 센서 데이터가 없음
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


// FarPlane -4.~ 값 나옴 , origin x, y 값 존재 
void AMyPawn::BP_FarPlane_Origin_XY()
{
	auto HMD = GEngine->XRSystem;
	UE_LOG(LogTemp, Log, TEXT("// IsTracking : %s"),
		HMD->IsTracking(0) ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));

	// 위치 트래킹 지원? true
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
// Right, Bottom, FarPlane: -2 ~ 2  사이 값 
// Left Top Camera nearPlane 더미
// 
// BP = 
// Right -2 ~ 2 사이값 
// Bottom 3.대 값
void AMyPawn::C_BP_Right_Bottom()
{
	auto HMD = GEngine->XRSystem;
	auto device = HMD->GetHMDDevice();
	// 둘다 false
	UE_LOG(LogTemp, Log, TEXT("// HasHiddenAreaMesh : %s"),
		device->HasHiddenAreaMesh() ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));
	UE_LOG(LogTemp, Log, TEXT("// HasVisibleAreaMesh : %s"),
		device->HasVisibleAreaMesh() ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));

	UE_LOG(LogTemp, Log, TEXT("// GetHMDName : %s"), *device->GetHMDName().ToString()); //Oculus Quest2

	UE_LOG(LogTemp, Log, TEXT("// GetSystemName : %s"),
		*HMD->GetSystemName().ToString()); // openXR 


	UE_LOG(LogTemp, Log, TEXT("// IsTracking : %s"),
		HMD->IsTracking(0) ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));

	// 위치 트래킹 지원? true
	bool DoesSupportPositionalTracking = HMD->DoesSupportPositionalTracking();
	UE_LOG(LogTemp, Log, TEXT("// DoesSupportPositionalTracking : %s"),
		DoesSupportPositionalTracking ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));


	// HMD가 위치 추적을 지원하는 경우 현재 추적 중인지? true
	bool hasVaildTrackingPosition = HMD->HasValidTrackingPosition();
	UE_LOG(LogTemp, Log, TEXT("// HasValidTrackingPosition : %s"),
		hasVaildTrackingPosition ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));

	/*
	* 스테레오 렌더링이 비활성화된 경우에도 추적을 강제하는 데 사용할 수 있습니다.
	* 기본 구현에서는 추적을 적용할 수 없으며 항상 false를 반환합니다.
	* 이 방법은 게임과 렌더 스레드 모두에서 호출됩니다.
	*/
	//false
	UE_LOG(LogTemp, Log, TEXT("// IsHeadTrackingEnforced : %s"), HMD->IsHeadTrackingEnforced() ?
		UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));


	UE_LOG(LogTemp, Log, TEXT("///////////////////////////////////////////////////////////"));

	// 위의 함수들을 제거하면 센서 데이터가 없음
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

void AMyPawn::C_Origin_Z() // 월드좌표 y 
{
	auto HMD = GEngine->XRSystem;
	auto device = HMD->GetHMDDevice();
	// 둘다 false
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


//Right, Bottom 정상 // top, Left 더미값, Vector x: 1 , y: 0, z:1
void AMyPawn::C_Right_Bottom()
{
	auto HMD = GEngine->XRSystem;
	auto device = HMD->GetHMDDevice();
	// 둘다 false
	UE_LOG(LogTemp, Log, TEXT("// HasHiddenAreaMesh : %s"),
		device->HasHiddenAreaMesh() ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));
	UE_LOG(LogTemp, Log, TEXT("// HasVisibleAreaMesh : %s"),
		device->HasVisibleAreaMesh() ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));

	// vector 값 유무 x: 1 , y: 0, z:1
	// 
	//UE_LOG(LogTemp, Log, TEXT("// GetSystemName : %s"),
	//	*HMD->GetSystemName().ToString()); // openXR 

	UE_LOG(LogTemp, Log, TEXT("// IsTracking : %s"),
		HMD->IsTracking(0) ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));

	// 위치 트래킹 지원? true
	bool DoesSupportPositionalTracking = HMD->DoesSupportPositionalTracking();
	UE_LOG(LogTemp, Log, TEXT("// DoesSupportPositionalTracking : %s"),
		DoesSupportPositionalTracking ? UTF8_TO_TCHAR("True") : UTF8_TO_TCHAR("False"));
	UE_LOG(LogTemp, Log, TEXT("///////////////////////////////////////////////////////////"));

	// 위의 함수들을 제거하면 센서 데이터가 없음
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


