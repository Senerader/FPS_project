// Fill out your copyright notice in the Description page of Project Settings.

#include "Mannequin.h"
#include "../Weapons/BallProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Gun.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/AIModule/Classes/Perception/AISense_Hearing.h"

// Sets default values
AMannequin::AMannequin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent	
	FPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));
	FPCamera->SetupAttachment(RootComponent);
	FPCamera->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FPCamera->bUsePawnControlRotation = true;

	// Create an arms mesh responsible for attaching a gun and firing
	FPArms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPArms"));
	FPArms->SetOnlyOwnerSee(true);
	FPArms->SetupAttachment(FPCamera);
	FPArms->bCastDynamicShadow = false;
	FPArms->CastShadow = false;
	FPArms->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	FPArms->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);
}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();
	
	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	if (!ensure(GunBP)) { return; }
	Gun = GetWorld()->SpawnActor<AGun>(GunBP);

	if (IsPlayerControlled())
	{
		Gun->AttachToComponent(FPArms, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}
	else
	{
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}
	//Setting up anim instances for the gun
	Gun->TPAnimInstance = GetMesh()->GetAnimInstance();
	Gun->FPAnimInstance = FPArms->GetAnimInstance();

	if (InputComponent) 
	{
		InputComponent->BindAction(FName("Fire"), IE_Pressed, this, &AMannequin::PullTrigger);
	}
	
}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMannequin::UnPossessed()
{
	Super::UnPossessed();
	if (!Gun) { return; }
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
}

FString AMannequin::InitializeRobotCode()
{
	char InitialArray[10];
	static const char CharArray[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (int32 i = 0; i < 4; ++i) {
		InitialArray[i] = CharArray[FMath::RandRange(0, 25)];
	}
	InitialArray[4] = '-';
	static const char IntArray[] =
		"0123456789";
	for (int32 i = 5; i < 9; ++i) {
		InitialArray[i] = IntArray[FMath::RandRange(0, 9)];
	}
	InitialArray[9] = '\0';
	//Converting constructed array to UE4 format
	return RobotCode = FString(UTF8_TO_TCHAR(InitialArray));
}

void AMannequin::PullTrigger()
{
	if (!Gun) { return; }
	//Firing from gun muzzle
	Gun->OnFire();
	//Reporting noise form firing a Gun
	UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetActorLocation(), 1.f, Cast<AActor>(this));

}

