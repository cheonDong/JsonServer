// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonDataObj.h"

// Sets default values
AJsonDataObj::AJsonDataObj()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJsonDataObj::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJsonDataObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJsonDataObj::MeshBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

