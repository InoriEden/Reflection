// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UE4CPPGameModeBase.generated.h"


/**
 * 
 */
UCLASS()
class UE4CPP_API AUE4CPPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool b;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TFieldPath<FInt64Property> sss;


	


};
