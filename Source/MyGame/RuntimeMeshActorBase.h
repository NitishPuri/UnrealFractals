// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RuntimeMeshComponent.h"
#include "RuntimeMeshActorBase.generated.h"

UCLASS()
class MYGAME_API ARuntimeMeshActorBase : public AActor
{
	GENERATED_BODY()
	
public:	

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
    USceneComponent* RootNode;

    UPROPERTY(EditAnywhere)
    URuntimeMeshComponent* RuntimeMesh;

	// Sets default values for this actor's properties
	ARuntimeMeshActorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
