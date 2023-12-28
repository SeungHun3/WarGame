// Fill out your copyright notice in the Description page of Project Settings.


#include "GI_WarGame.h"

void UGI_WarGame::SetStartPosition(FVector _Loc)
{
	StartLoc = _Loc;
	StartControl();
}

FVector UGI_WarGame::getStartPosition()
{
	return StartLoc;
}


