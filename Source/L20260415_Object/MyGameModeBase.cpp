// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPawn.h"
#include "MyPlayerController.h"

//CDO 기본값 초기화 용이지
AMyGameModeBase::AMyGameModeBase()
{
	DefaultPawnClass = AMyPawn::StaticClass(); //mean AMyPawn의 이름
	//C++에서는 클래스 이름 가르치는 방법이 없어서 CDO의 포인터를 가르침

	PlayerControllerClass = AMyPlayerController::StaticClass();

}
