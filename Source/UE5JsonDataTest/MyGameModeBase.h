// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HTTP.h"
#include "MyGameModeBase.generated.h"

USTRUCT(BlueprintType)
struct FMyJaonData
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JSON")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JSON")
	int32 Age;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JSON")
	float Height;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JSON")
	FVector CharacterLocation;
};
/**
 * 
 */
UCLASS()
class UE5JSONDATATEST_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMyGameModeBase();

    TSharedPtr<IHttpRequest> HTTPRequest;
    class FHttpModule* Http;

    // HTTP 요청 보내기
    void SendHttpRequest();

    // HTTP 요청 처리
    void HandleHttpRequest(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
