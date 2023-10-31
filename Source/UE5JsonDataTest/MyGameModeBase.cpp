// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "HTTP.h"
#include "Misc/FileHelper.h"    // �𸮾� �������� ���� �� ���丮 ���� �۾��� �����ϱ� ���� �Լ��� Ŭ������ �����ϴ� �������
#include "Serialization/JsonReader.h"   // �𸮾� �������� JSON������ �о���� ���� JSON Reader Ŭ������ ���õ� ����������ϴ� �������
#include "Serialization/JsonSerializer.h"   // �𸮾� �������� JSON ������ ����ȭ �� ������ȭ �ϴµ� ���Ǵ� �Լ��� Ŭ������ �����ϴ� �������
#include "JsonUtilities.h"
#include "Json.h"

AMyGameModeBase::AMyGameModeBase()
{
	Http = &FHttpModule::Get();
    SendHttpRequest();
   
}

void AMyGameModeBase::SendHttpRequest()
{
    FString EC2IpAddress = "13.209.50.102/phpinfo.php"; // phpinfo.php ������ ec2�� ���� �� ����ٰ� json data�� ������ ����
    int32 Port = 80; // �� ������ ��Ʈ (�Ϲ������� 80)

    FString JsonString; // JSON ������ ������ ������ FString ������ ����.
    FFileHelper::LoadFileToString(JsonString, *(FPaths::ProjectContentDir() / TEXT("Data/JsonData.json")));
    //if (FFileHelper::LoadFileToString(JsonString, *(FPaths::ProjectContentDir() / TEXT("Data/JsonData.json"))))  // �ش� ��ο��� JSON ������ �о�� FString�� ����
    //{
    //    TSharedPtr<FJsonObject> JsonObject; // JSON �����͸� �Ľ��ϱ� ���� TSharedPtr�� ����� ����Ʈ �������� JsonObject�� ����.
    //    // TSharedPtr�� Unreal Engine�� ����Ʈ �����ͷ�, �޸� ������ ���� �����ϰ� ó���� �� �ֵ��� �����ش�.
    //    TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonString);
    //    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
    //}

    // HTTP ��û ����
    HTTPRequest = Http->CreateRequest();
    HTTPRequest->SetVerb("POST"); // POST ������� ��û
    HTTPRequest->SetHeader("Content-Type", "application/json"); // JSON �����͸� ������ ����
    // HTTPRequest->SetURL(FString::Printf(TEXT("http://%s:%d"), *EC2IpAddress, Port));
    HTTPRequest->SetURL(EC2IpAddress);
    HTTPRequest->SetContentAsString(JsonString); // JSON �����͸� ��û ������ ����

    // ��û ������
    HTTPRequest->OnProcessRequestComplete().BindUObject(this, &AMyGameModeBase::HandleHttpRequest);
    HTTPRequest->ProcessRequest();
}

void AMyGameModeBase::HandleHttpRequest(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful && Response.IsValid())
    {
        // HTTP ��û ���� ���� ó��
        FString ResponseData = Response->GetContentAsString();
        FString ResponseURL = Response->GetURL();
        int32 ResponseCode = Response->GetResponseCode();
        UE_LOG(LogTemp, Warning, TEXT("HTTP ResponseURL: %s"), *ResponseURL);
        UE_LOG(LogTemp, Warning, TEXT("HTTP ResponseData: %s"), *ResponseData);
        UE_LOG(LogTemp, Warning, TEXT("HTTP Responsecode: %d"), ResponseCode);

        if (ResponseCode == 200)
        {
            // ���� �����͸� JSON���� �Ľ�
            TSharedPtr<FJsonObject> JsonObject;
            TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(ResponseData);

            if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
            {
                SendHttpGetRequest();
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON response"));
            }
        }
    }
    else
    {
        // HTTP ��û ���� ���� ó��
        UE_LOG(LogTemp, Error, TEXT("HTTP Request failed"));
    }
}

void AMyGameModeBase::SendHttpGetRequest()
{
    FString EC2IpAddress = "13.209.50.102/phpinfo.php";

    TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(EC2IpAddress);
    Request->SetVerb("GET"); // GET ��û�� �����ϴ�.

    Request->OnProcessRequestComplete().BindUObject(this, &AMyGameModeBase::HandleHttpGetRequest);

    Request->ProcessRequest();
}

void AMyGameModeBase::HandleHttpGetRequest(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful && Response.IsValid())
    {
        // HTTP ��û ���� ���� ó��
        FString ResponseData = Response->GetContentAsString();
        FString ResponseURL = Response->GetURL();
        int32 ResponseCode = Response->GetResponseCode();
        UE_LOG(LogTemp, Warning, TEXT("HTTP ResponseURL: %s"), *ResponseURL);
        UE_LOG(LogTemp, Warning, TEXT("HTTP ResponseData: %s"), *ResponseData);
        UE_LOG(LogTemp, Warning, TEXT("HTTP Responsecode: %d"), ResponseCode);

        if (ResponseCode == 200)
        {
            // ���� �����͸� JSON���� �Ľ�
            TSharedPtr<FJsonObject> JsonObject;
            TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(ResponseData);

            if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
            {
                // JSON �����Ͱ� �Ľ̵Ǹ� ���⿡�� ó��
                FString Key1Value;
                int32 Key2Value;

                if (JsonObject->TryGetStringField("name", Key1Value))
                {
                    // key1�� ���� ������
                    UE_LOG(LogTemp, Warning, TEXT("name: %s"), *Key1Value);
                }

                if (JsonObject->TryGetNumberField("age", Key2Value))
                {
                    // key2�� ���� ������
                    UE_LOG(LogTemp, Warning, TEXT("age: %d"), Key2Value);
                }
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON response"));
            }
        }
    }
    else
    {
        // HTTP ��û ���� ���� ó��
        UE_LOG(LogTemp, Error, TEXT("HTTP Request failed"));
    }
}
