// Fill out your copyright notice in the Description page of Project Settings.


#include "OnlineBpBridge.h"


#include "Engine.h"

#include "OnlineManager.h"

 
 


UOnlineBpBridge::UOnlineBpBridge()  
     
{

     // _onlineManager = NewObject<UOnlineManager>( this );
    // _onlineManager->_onCreateSessionDoneEvt.Clear();
    // _onlineManager->_onCreateSessionDoneEvt.AddUniqueDynamic(this, &UOnlineBpBridge::OnlineCompleteEvt);

}

void UOnlineBpBridge::StartOnlineSession(UObject *WorldContextObj)
{
#if 0
    UE_LOG(LogTemp, Warning, TEXT("Start Online session........."));

    if(_onlineManager){

        UE_LOG(LogTemp, Warning, TEXT("_onlineManager ok................"));

    }

   const UWorld* tmpWorld = GEngine->GetWorldFromContextObject(WorldContextObj , EGetWorldErrorMode::ReturnNull );

    if(!tmpWorld){

        UE_LOG(LogTemp, Warning, TEXT("get world Failed................"));

       return;

    }


    _onlineManager->createSeesion(tmpWorld ,5 , true);
#endif
}

void UOnlineBpBridge::TestGetworldFunc()
{
    UE_LOG(LogTemp, Warning, TEXT("TestGetworld()  gooooooooo.........."));

    if(GetWorld()){
         UE_LOG(LogTemp, Warning, TEXT("GetWorld() okkkkkkkkkkkk.........."));
    }

   // if(!_testGetWorld){
  //       _testGetWorld = NewObject<UTestGetworld>(  nullptr    );
  //  }


  //  _testGetWorld->doTestGetworld();


}







