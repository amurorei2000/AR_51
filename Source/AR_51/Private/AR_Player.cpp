// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_Player.h"
#include "ARBlueprintLibrary.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "EngineMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.h"
#include "Components/TextBlock.h"
#include "GroundDetectionComponent.h"


AAR_Player::AAR_Player()
{
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(rootComp);

	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	cameraComp->SetupAttachment(RootComponent);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	AutoReceiveInput = EAutoReceiveInput::Player0;

	groundComp = CreateDefaultSubobject<UGroundDetectionComponent>(TEXT("Ground Detection"));
}

void AAR_Player::BeginPlay()
{
	Super::BeginPlay();

	UARBlueprintLibrary::SetEnabledXRCamera(true);

	// AR ������ �����Ѵ�.
	UARBlueprintLibrary::StartARSession(arSessions[0]);

	// UI ���� ����Ѵ�.
	if (mainWidget_Source != nullptr)
	{
		mainUI = CreateWidget<UMainWidget>(GetWorld(), mainWidget_Source);

		if (mainUI != nullptr)
		{
			mainUI->AddToViewport();
		}
	}

	FTimerHandle viewHandle;
	GetWorldTimerManager().SetTimer(viewHandle, this, &AAR_Player::GetViewportSize, 0.5f, false);

	playerCon = GetWorld()->GetFirstPlayerController();
}

void AAR_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAR_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAR_Player::GetViewportSize()
{
	/*vSize = GEngine->GameViewport->Viewport->GetSizeXY();
	player->mainUI->logText1->SetText(FText::FromString(FString::Printf(TEXT("%d x %d"), vSize.X, vSize.Y)));*/
}
