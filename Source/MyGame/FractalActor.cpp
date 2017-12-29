// Fill out your copyright notice in the Description page of Project Settings.

#include "FractalActor.h"

#include "RuntimeMeshLibrary.h"


// Sets default values
AFractalActor::AFractalActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    _mesh = CreateDefaultSubobject<URuntimeMeshComponent>(TEXT("Generated Mesh"));
    RootComponent = _mesh;

    // multithreaded physics cooking
    _mesh->bUseAsyncCooking = true;

}

// Called when the game starts or when spawned
void AFractalActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFractalActor::PostActorCreated()
{
    Super::PostActorCreated();

    CreateTriangle();
}

void AFractalActor::PostLoad()
{
    Super::PostLoad();

    CreateTriangle();
}

void AFractalActor::OnConstruction(const FTransform& Transform)
{
    TArray<FVector> Vertices;
    TArray<FVector> Normals;
    TArray<FRuntimeMeshTangent> Tangents;
    TArray<FVector2D> TextureCoordinates;
    TArray<int32> Triangles;

    URuntimeMeshLibrary::CreateBoxMesh(FVector(100, 100, 100), Vertices, Triangles, Normals, TextureCoordinates, Tangents);



    // Create the mesh section specifying collision
    _mesh->CreateMeshSection(0, Vertices, Triangles, Normals, TextureCoordinates, TArray<FColor>(), Tangents, true, EUpdateFrequency::Infrequent);
}

void AFractalActor::CreateTriangle() 
{

    UE_LOG(LogTemp, Warning, TEXT("CreateTriangle()"));

    //TArray<FVector> vertices;
    //vertices.Add(FVector(0, 0, 0));
    //vertices.Add(FVector(0, 100, 0));
    //vertices.Add(FVector(0, 0, 100));

    //TArray<int32> triangles;
    //triangles.Add(0);
    //triangles.Add(1);
    //triangles.Add(2);

    //TArray<FVector> normals;
    //normals.Add(FVector(1, 0, 0));
    //normals.Add(FVector(1, 0, 0));
    //normals.Add(FVector(1, 0, 0));

    //TArray<FVector2D> UV0;
    //UV0.Add(FVector2D(0, 0));
    //UV0.Add(FVector2D(10, 0));
    //UV0.Add(FVector2D(0, 10));

    //TArray<FProcMeshTangent> tangents;
    //tangents.Add(FProcMeshTangent(0, 1, 0));
    //tangents.Add(FProcMeshTangent(0, 1, 0));
    //tangents.Add(FProcMeshTangent(0, 1, 0));

    //TArray<FLinearColor> vertexColors;
    //vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
    //vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));
    //vertexColors.Add(FLinearColor(0.75, 0.75, 0.75, 1.0));

    //_mesh->CreateMeshSection_LinearColor(0, vertices, triangles, normals,
    //    UV0, vertexColors, tangents, true);

    //// enable collision data
    //_mesh->ContainsPhysicsTriMeshData(true);

}

// Called every frame
void AFractalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

