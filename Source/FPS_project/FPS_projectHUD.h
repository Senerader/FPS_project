// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FPS_projectHUD.generated.h"

UCLASS()
class AFPS_projectHUD : public AHUD
{
	GENERATED_BODY()

public:
	AFPS_projectHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

