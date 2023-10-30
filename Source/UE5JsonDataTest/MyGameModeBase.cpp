// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "HTTP.h"
#include "Misc/FileHelper.h"    // 언리얼 엔진에서 파일 및 디렉토리 관련 작업을 수행하기 위한 함수와 클래스를 포함하는 헤더파일
#include "Serialization/JsonReader.h"   // 언리얼 엔진에서 JSON파일을 읽어오기 위한 JSON Reader 클래스와 관련된 기능을포함하는 헤더파일
#include "Serialization/JsonSerializer.h"   // 언리얼 엔진에서 JSON 파일을 직렬화 및 역직렬화 하는데 사용되는 함수와 클래스를 포함하는 헤더파일


AMyGameModeBase::AMyGameModeBase()
{
	Http = &FHttpModule::Get();
    SendHttpRequest();
   
}

void AMyGameModeBase::SendHttpRequest()
{
    FString EC2IpAddress = "13.209.50.102";
    int32 Port = 80; // 웹 서버의 포트 (일반적으로 80)

    FString JsonString; // JSON 파일의 내용을 저장할 FString 변수를 선언.
    FFileHelper::LoadFileToString(JsonString, *(FPaths::ProjectContentDir() / TEXT("Data/JsonData.json")));
    //if (FFileHelper::LoadFileToString(JsonString, *(FPaths::ProjectContentDir() / TEXT("Data/JsonData.json"))))  // 해당 경로에서 JSON 파일을 읽어와 FString에 저장
    //{
    //    TSharedPtr<FJsonObject> JsonObject; // JSON 데이터를 파싱하기 위한 TSharedPtr로 선언된 스마트 포인터인 JsonObject를 정의.
    //    // TSharedPtr는 Unreal Engine의 스마트 포인터로, 메모리 관리를 보다 안전하게 처리할 수 있도록 도와준다.
    //    TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonString);
    //    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
    //}

    // HTTP 요청 생성
    HTTPRequest = Http->CreateRequest();
    HTTPRequest->SetVerb("POST"); // POST 방식으로 요청
    HTTPRequest->SetHeader("Content-Type", "application/json"); // JSON 데이터를 전송할 것임
    HTTPRequest->SetURL(FString::Printf(TEXT("http://%s:%d"), *EC2IpAddress, Port));
    HTTPRequest->SetContentAsString(JsonString); // JSON 데이터를 요청 본문에 설정

    // 요청 보내기
    HTTPRequest->OnProcessRequestComplete().BindUObject(this, &AMyGameModeBase::HandleHttpRequest);
    HTTPRequest->ProcessRequest();
}

void AMyGameModeBase::HandleHttpRequest(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful && Response.IsValid())
    {
        // HTTP 요청 성공 시의 처리
        FString ResponseData = Response->GetContentAsString();
        FString ResponseURL = Response->GetURL();
        UE_LOG(LogTemp, Warning, TEXT("HTTP ResponseURL: %s"), *ResponseURL);
        UE_LOG(LogTemp, Warning, TEXT("HTTP ResponseData: %s"), *ResponseData);

        // 응답 데이터를 JSON으로 파싱
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(ResponseData);

        if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
        {
            // JSON 데이터가 파싱되면 여기에서 처리
            FString Key1Value;
            int32 Key2Value;

            if (JsonObject->TryGetStringField("name", Key1Value))
            {
                // key1의 값을 가져옴
                UE_LOG(LogTemp, Warning, TEXT("name: %s"), *Key1Value);
            }

            if (JsonObject->TryGetNumberField("age", Key2Value))
            {
                // key2의 값을 가져옴
                UE_LOG(LogTemp, Warning, TEXT("age: %d"), Key2Value);
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON response"));
        }
    }
    else
    {
        // HTTP 요청 실패 시의 처리
       UE_LOG(LogTemp, Error, TEXT("HTTP Request failed"));
    }
}
