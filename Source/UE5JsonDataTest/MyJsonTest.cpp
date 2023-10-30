//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "MyJsonTest.h"
//#include "Misc/FileHelper.h"    // 언리얼 엔진에서 파일 및 디렉토리 관련 작업을 수행하기 위한 함수와 클래스를 포함하는 헤더파일
//#include "Serialization/JsonReader.h"   // 언리얼 엔진에서 JSON파일을 읽어오기 위한 JSON Reader 클래스와 관련된 기능을포함하는 헤더파일
//#include "Serialization/JsonSerializer.h"   // 언리얼 엔진에서 JSON 파일을 직렬화 및 역직렬화 하는데 사용되는 함수와 클래스를 포함하는 헤더파일
//
//
//UMyJsonTest::UMyJsonTest()
//{
//}
//
//bool UMyJsonTest::ReadJsonFile(FMyJaonData& OutData)
//{
//    FString JsonString; // JSON 파일의 내용을 저장할 FString 변수를 선언.
//    if (FFileHelper::LoadFileToString(JsonString, *(FPaths::ProjectContentDir() / TEXT("Data/JsonData.json"))))  // 해당 경로에서 JSON 파일을 읽어와 FString에 저장
//    {
//        TSharedPtr<FJsonObject> JsonObject; // JSON 데이터를 파싱하기 위한 TSharedPtr로 선언된 스마트 포인터인 JsonObject를 정의.
//                                            // TSharedPtr는 Unreal Engine의 스마트 포인터로, 메모리 관리를 보다 안전하게 처리할 수 있도록 도와준다.
//
//        TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);
//            // JSON 데이터를 읽기 위한 JsonReader를 생성.
//            // TJsonReaderFactory<TCHAR>::Create 함수를 사용하여 JSON 문자열 JsonString에 대한 리더(Reader)를 생성.
//            // TCHAR는 Unreal Engine에서 문자열 처리를 위한 매크로로, 플랫폼 간 호환성을 제공.
//
//        if (FJsonSerializer::Deserialize(JsonReader, JsonObject))   //  JSON 데이터를 JsonObject에 파싱. 이 함수를 통해 JSON 데이터의 내용이 JsonObject로 파싱되고, 필요한 정보에 접근할 수 있음.
//        {                                                           // 파싱: 주어진 데이터를 분석하고, 원하는 형식으로 추출하는 과정.
//            OutData.Name = JsonObject->GetStringField("name");
//            OutData.Age = JsonObject->GetIntegerField("age");
//            OutData.Height = JsonObject->GetNumberField("height");  // JsonObject에서 필드 이름을 사용하여 JSON 데이터를 파싱한 결과를 OutData 구조체에 저장.
//
//            FString PlayerName;
//            int32 PlayerAge;
//            float PlayerHeight;
//
//            // 데이터 로드
//            JsonObject->TryGetStringField("Player1.name", PlayerName);
//            JsonObject->TryGetNumberField("Player1.age", PlayerAge);
//            JsonObject->TryGetNumberField("Player1.height", PlayerHeight);
//
//            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Player: %s, Age: %d, Height: %f"), *PlayerName, PlayerAge, PlayerHeight));
//
//            // 데이터 수정
//            JsonObject->SetStringField("Player2.name", "Alice");
//            JsonObject->SetNumberField("Player2.age", 25);
//            JsonObject->SetNumberField("Player2.Height", 166.0f);
//
//            // JSON 문자열로 직렬화
//            TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonString);
//            FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
//
//
//            return true;    // 파싱 성공
//        }
//    }
//    return false;   // 파싱 실패
//}
