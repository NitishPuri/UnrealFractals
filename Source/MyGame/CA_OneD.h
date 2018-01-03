// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RuntimeMeshComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

#include "Components/TextRenderComponent.h"
#include "CA_OneD.generated.h"

UCLASS()
class MYGAME_API ACA_OneD : public AActor
{
    GENERATED_BODY()
    
public:    
    // Sets default values for this actor's properties
    ACA_OneD();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Parameters")
    FVector2D Size = FVector2D(10.0, 20.0);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Parameters")
    int Offset = 150;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Parameters")
    UStaticMesh* Base_StaticMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Parameters")
    UMaterialInterface* Base_Material;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Parameters")
    TArray<int> Ruleset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Parameters")
    TArray<int> Initial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Parameters")
    int AnimationDelay = 30;

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

    void NextGeneration();
    void GenerateMesh();

    void SetupMesh();

    int rules(int a, int b, int c);
    
    UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
    UHierarchicalInstancedStaticMeshComponent* HISMActor;

    UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
    UHierarchicalInstancedStaticMeshComponent* HISMActorD;

    UPROPERTY(Transient)
    TArray< int > Cells;

    TArray< UTextRenderComponent* > DebugText;

    int Generation = 0;

    int Counter = 0;

};
