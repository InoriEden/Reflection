// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class REFLECTION_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	

	UFUNCTION()
	AMyActor* Eee(int i,int m, TArray<AMyActor*>&aactor);

	UFUNCTION()
	void abc(int k);
	template<typename... TReturns, typename... TArgs>
	void InvokeFunctione(UClass* objClass, UObject* obj, UFunction* fun,TTuple<TReturns...>& outParams, TArgs&&... args);
	
	;
};
