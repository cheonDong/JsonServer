//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "MyJsonTest.h"
//#include "Misc/FileHelper.h"    // �𸮾� �������� ���� �� ���丮 ���� �۾��� �����ϱ� ���� �Լ��� Ŭ������ �����ϴ� �������
//#include "Serialization/JsonReader.h"   // �𸮾� �������� JSON������ �о���� ���� JSON Reader Ŭ������ ���õ� ����������ϴ� �������
//#include "Serialization/JsonSerializer.h"   // �𸮾� �������� JSON ������ ����ȭ �� ������ȭ �ϴµ� ���Ǵ� �Լ��� Ŭ������ �����ϴ� �������
//
//
//UMyJsonTest::UMyJsonTest()
//{
//}
//
//bool UMyJsonTest::ReadJsonFile(FMyJaonData& OutData)
//{
//    FString JsonString; // JSON ������ ������ ������ FString ������ ����.
//    if (FFileHelper::LoadFileToString(JsonString, *(FPaths::ProjectContentDir() / TEXT("Data/JsonData.json"))))  // �ش� ��ο��� JSON ������ �о�� FString�� ����
//    {
//        TSharedPtr<FJsonObject> JsonObject; // JSON �����͸� �Ľ��ϱ� ���� TSharedPtr�� ����� ����Ʈ �������� JsonObject�� ����.
//                                            // TSharedPtr�� Unreal Engine�� ����Ʈ �����ͷ�, �޸� ������ ���� �����ϰ� ó���� �� �ֵ��� �����ش�.
//
//        TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);
//            // JSON �����͸� �б� ���� JsonReader�� ����.
//            // TJsonReaderFactory<TCHAR>::Create �Լ��� ����Ͽ� JSON ���ڿ� JsonString�� ���� ����(Reader)�� ����.
//            // TCHAR�� Unreal Engine���� ���ڿ� ó���� ���� ��ũ�η�, �÷��� �� ȣȯ���� ����.
//
//        if (FJsonSerializer::Deserialize(JsonReader, JsonObject))   //  JSON �����͸� JsonObject�� �Ľ�. �� �Լ��� ���� JSON �������� ������ JsonObject�� �Ľ̵ǰ�, �ʿ��� ������ ������ �� ����.
//        {                                                           // �Ľ�: �־��� �����͸� �м��ϰ�, ���ϴ� �������� �����ϴ� ����.
//            OutData.Name = JsonObject->GetStringField("name");
//            OutData.Age = JsonObject->GetIntegerField("age");
//            OutData.Height = JsonObject->GetNumberField("height");  // JsonObject���� �ʵ� �̸��� ����Ͽ� JSON �����͸� �Ľ��� ����� OutData ����ü�� ����.
//
//            FString PlayerName;
//            int32 PlayerAge;
//            float PlayerHeight;
//
//            // ������ �ε�
//            JsonObject->TryGetStringField("Player1.name", PlayerName);
//            JsonObject->TryGetNumberField("Player1.age", PlayerAge);
//            JsonObject->TryGetNumberField("Player1.height", PlayerHeight);
//
//            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Player: %s, Age: %d, Height: %f"), *PlayerName, PlayerAge, PlayerHeight));
//
//            // ������ ����
//            JsonObject->SetStringField("Player2.name", "Alice");
//            JsonObject->SetNumberField("Player2.age", 25);
//            JsonObject->SetNumberField("Player2.Height", 166.0f);
//
//            // JSON ���ڿ��� ����ȭ
//            TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonString);
//            FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
//
//
//            return true;    // �Ľ� ����
//        }
//    }
//    return false;   // �Ľ� ����
//}
