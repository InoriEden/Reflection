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
	TFieldPath<FInt64Property> sss;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool a;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool t;


	


};
