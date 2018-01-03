// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RuntimeMeshComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "GridActor.generated.h"

UCLASS()
class MYGAME_API AGridActor : public AActor
{
    GENERATED_BODY()
    
public:    
    // Sets default values for this actor's properties
    AGridActor();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Parameters")
    FVector Size = FVector(10.0f, 10.0f, 10.0f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Parameters")
    int Offset = 150;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Parameters")
    UStaticMesh* Base_StaticMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Parameters")
    UMaterialInterface* Base_Material;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    virtual void PostLoad() override;
    virtual void PostActorCreated() override;

public:    
    // Called every frame
    virtual void Tick(float DeltaTime) override;

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif // WITH_EDITOR


private:

    void GenerateMesh();

    void SetupMesh();
    
    UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
    UHierarchicalInstancedStaticMeshComponent* HISMActor;

};
