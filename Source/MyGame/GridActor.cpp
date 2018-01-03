// Fill out your copyright notice in the Description page of Project Settings.

#include "GridActor.h"


// Sets default values
AGridActor::AGridActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

    HISMActor = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HISMActor"));
    HISMActor->SetupAttachment(RootComponent);
    //Size = { 3, 3, 3 };

    //Base_StaticMesh = 

}

// Called when the game starts or when spawned
void AGridActor::BeginPlay()
{
	Super::BeginPlay();
    GenerateMesh();
}

void AGridActor::PostActorCreated()
{
    Super::PostActorCreated();
    GenerateMesh();
}

void AGridActor::PostLoad()
{
    Super::PostLoad();
    GenerateMesh();
}

// Called every frame
void AGridActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGridActor::SetupMesh()
{
    HISMActor->SetRelativeLocation(FVector(0, 0, 0));
    HISMActor->SetStaticMesh(Base_StaticMesh);
    HISMActor->SetMaterial(0, Base_Material);
}

void AGridActor::GenerateMesh()
{

    HISMActor->ClearInstances();
    FTransform Params;
    for (int32 i = 0; i < Size.X; ++i)
    {
        for (int32 j = 0; j < Size.Y; ++j)
        {
            for (int32 k = 0; k < Size.Z; ++k) 
            {
                Params.SetTranslation(FVector( i*Offset, j*Offset, k*Offset));
                HISMActor->AddInstance(Params);
            }
        }
    }
}

#if WITH_EDITOR
void AGridActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    FName MemberPropertyChanged = (PropertyChangedEvent.MemberProperty ? PropertyChangedEvent.MemberProperty->GetFName() : NAME_None);

    if ((MemberPropertyChanged == GET_MEMBER_NAME_CHECKED(AGridActor, Size)) || 
        (MemberPropertyChanged == GET_MEMBER_NAME_CHECKED(AGridActor, Offset)))
    {
        GenerateMesh();
    }
    else if ((MemberPropertyChanged == GET_MEMBER_NAME_CHECKED(AGridActor, Base_StaticMesh)) ||
             (MemberPropertyChanged == GET_MEMBER_NAME_CHECKED(AGridActor, Base_Material)))
    {
        SetupMesh();
    }
    //else if ((MemberPropertyChanged == GET_MEMBER_NAME_CHECKED(AHeightFieldAnimatedActor, Material)))
    //{
    //    MeshComponent->SetMaterial(0, Material);
    //}
}
#endif // WITH_EDITOR

