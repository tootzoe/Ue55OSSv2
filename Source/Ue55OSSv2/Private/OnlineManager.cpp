// Fill out your copyright notice in the Description page of Project Settings.


#include "OnlineManager.h"

#include "OnlineSubsystemUtils.h"
#include "Interfaces/OnlineSessionDelegates.h"

#include "Engine/LocalPlayer.h"




#define SETTING_MAPNAME "TootOnlineDemo"
#define SEARCH_PRESENCE "PRESENCESEARCH"



UOnlineManager::UOnlineManager()
{
   _createSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &UOnlineManager::onCreateSessionDone);
   _destorySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject(this, &UOnlineManager::onDestorySessionDone);
   _startSessionCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject(this, &UOnlineManager::onStartSessionDone);
   _endSessionCompleteDelegate = FOnEndSessionCompleteDelegate::CreateUObject(this, &UOnlineManager::onEndSessionDone);
   _findSessionCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &UOnlineManager::onFindSessionDone);
   _joinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(this, &UOnlineManager::onJoinSessionDone);

}

void UOnlineManager::CreateOnlineSeesion( int32 publicConnCount, bool isLanMatch)
{
    const IOnlineSessionPtr ssessionItf = Online::GetSessionInterface(GetWorld());
    if(!ssessionItf.IsValid()){
        _onCreateSessionDoneEvt.Broadcast(false);
        return;
    }

    _currSessionSettings = MakeShareable(new FOnlineSessionSettings());
    _currSessionSettings->NumPrivateConnections = 0 ;
    _currSessionSettings->NumPublicConnections = 0 ;
    _currSessionSettings->bAllowInvites = true ;
    _currSessionSettings->bAllowJoinInProgress = true ;
    _currSessionSettings->bAllowJoinViaPresence = true ;
    _currSessionSettings->bAllowJoinViaPresenceFriendsOnly = true ;
    _currSessionSettings->bIsDedicated = false ;
    _currSessionSettings->bUsesPresence = true ;
    _currSessionSettings->bIsLANMatch = isLanMatch;
    _currSessionSettings->bShouldAdvertise = true;
    //
    _currSessionSettings  ->Set(FName(SETTING_MAPNAME)  , FString("DemoMainLevel"), EOnlineDataAdvertisementType::ViaOnlineService);

    _createSessionRslHandle = ssessionItf->AddOnCreateSessionCompleteDelegate_Handle(_createSessionCompleteDelegate);


    const ULocalPlayer* localPlayer = GetWorld()->GetFirstLocalPlayerFromController();

    if(!ssessionItf->CreateSession(*localPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *_currSessionSettings)){
        ssessionItf->ClearOnCreateSessionCompleteDelegate_Handle(_createSessionRslHandle);
        _onCreateSessionDoneEvt.Broadcast(false);
    }

}

void UOnlineManager::DestoryOnlineSeesion()
{
    const IOnlineSessionPtr tmpSessionPtr = Online::GetSessionInterface(GetWorld());

    if(!tmpSessionPtr.IsValid()){
        _onDestorySessionDoneEvt.Broadcast(false);
        return;
    }

    _destorySessionRslHandle = tmpSessionPtr->AddOnDestroySessionCompleteDelegate_Handle(_destorySessionCompleteDelegate);

    if(!tmpSessionPtr->DestroySession(NAME_GameSession)){
        tmpSessionPtr->ClearOnDestroySessionCompleteDelegate_Handle(_destorySessionRslHandle);

        _onDestorySessionDoneEvt.Broadcast(false);
    }
}

void UOnlineManager::StartOnlineSeesion()
{
    const IOnlineSessionPtr tmpSeesion = Online::GetSessionInterface(GetWorld());
    if(!tmpSeesion.IsValid()){

        _onStartSessionDoneEvt.Broadcast(false);
        return;
    }

    _startSessionRslHandle = tmpSeesion->AddOnStartSessionCompleteDelegate_Handle(_startSessionCompleteDelegate);


    if(!tmpSeesion->StartSession(NAME_GameSession)){
        tmpSeesion->ClearOnStartSessionCompleteDelegate_Handle(_startSessionRslHandle);
        _onStartSessionDoneEvt.Broadcast(false);
    }
}

void UOnlineManager::EndOnlineSeesion()
{
    const IOnlineSessionPtr tmpSeesion = Online::GetSessionInterface(GetWorld());
    if(!tmpSeesion.IsValid()){

        _onEndSessionDoneEvt.Broadcast(false);
        return;
    }

    _endSessionRslHandle = tmpSeesion->AddOnEndSessionCompleteDelegate_Handle(_endSessionCompleteDelegate);

    if(!tmpSeesion->EndSession(NAME_GameSession)){
        tmpSeesion->ClearOnEndSessionCompleteDelegate_Handle(_endSessionRslHandle);
        _onEndSessionDoneEvt.Broadcast(false);
    }
}

void UOnlineManager::FindOnlineSeesion(int32 MaxLimit, bool IsLANQuery)
{
    const IOnlineSessionPtr tmpSeesion = Online::GetSessionInterface(GetWorld());
    if(!tmpSeesion.IsValid()){

        _onFindSessionDoneEvt.Broadcast(TArray<FOnlineSessionSearchResult>(), false);
        return;
    }

    _findSessionRslHandle = tmpSeesion->AddOnFindSessionsCompleteDelegate_Handle(_findSessionCompleteDelegate);
    _currSearchedSession = MakeShareable(new FOnlineSessionSearch());
    _currSearchedSession->MaxSearchResults = MaxLimit;
    _currSearchedSession->bIsLanQuery = IsLANQuery;
    //
    _currSearchedSession->QuerySettings.Set(FName(TEXT(SEARCH_PRESENCE)) , true , EOnlineComparisonOp::Equals  );

    const ULocalPlayer* localPlayer = GetWorld()->GetFirstLocalPlayerFromController();

    if(!tmpSeesion->FindSessions (*localPlayer->GetPreferredUniqueNetId(), _currSearchedSession.ToSharedRef())){
        tmpSeesion->ClearOnFindSessionsCompleteDelegate_Handle(_findSessionRslHandle);
         _onFindSessionDoneEvt.Broadcast(TArray<FOnlineSessionSearchResult>(), false);
    }
}

void UOnlineManager::JoinOnlineSeesion(const FOnlineSessionSearchResult &SessionResult)
{
    const IOnlineSessionPtr tmpSeesion = Online::GetSessionInterface(GetWorld());
     if(!tmpSeesion.IsValid()){

         _onJoinSessionDoneEvt .Broadcast( EOnJoinSessionCompleteResult::UnknownError);
         return;
     }

     _joinSessionRslHandle = tmpSeesion->AddOnJoinSessionCompleteDelegate_Handle(_joinSessionCompleteDelegate);

     const ULocalPlayer* localPlayer = GetWorld()->GetFirstLocalPlayerFromController();

     if(!tmpSeesion->JoinSession (*localPlayer->GetPreferredUniqueNetId(), NAME_GameSession, SessionResult )){
         tmpSeesion->ClearOnJoinSessionCompleteDelegate_Handle(_joinSessionRslHandle);
           _onJoinSessionDoneEvt .Broadcast( EOnJoinSessionCompleteResult::UnknownError);
     }
}


void UOnlineManager::onCreateSessionDone(FName sessionName, bool isSuccessful)
{
    const IOnlineSessionPtr tmpSeesion = Online::GetSessionInterface(GetWorld());
    if(tmpSeesion){
        tmpSeesion->ClearOnCreateSessionCompleteDelegate_Handle(_createSessionRslHandle);
    }

    _onCreateSessionDoneEvt.Broadcast(isSuccessful);

}

void UOnlineManager::onDestorySessionDone(FName sessionName, bool isSuccessful)
{

    const IOnlineSessionPtr tmpSeesion = Online::GetSessionInterface(GetWorld());
    if(tmpSeesion){
        tmpSeesion->ClearOnDestroySessionCompleteDelegate_Handle(_destorySessionRslHandle);
    }

    _onDestorySessionDoneEvt.Broadcast(isSuccessful);
}

void UOnlineManager::onStartSessionDone(FName sessionName, bool isSuccessful)
{
    const IOnlineSessionPtr tmpSeesion = Online::GetSessionInterface(GetWorld());
    if(tmpSeesion){
        tmpSeesion->ClearOnStartSessionCompleteDelegate_Handle(_startSessionRslHandle);
    }

    _onStartSessionDoneEvt.Broadcast(isSuccessful);
}

void UOnlineManager::onEndSessionDone(FName sessionName, bool isSuccessful)
{
    const IOnlineSessionPtr tmpSeesion = Online::GetSessionInterface(GetWorld());
    if(tmpSeesion){
        tmpSeesion->ClearOnEndSessionCompleteDelegate_Handle(_endSessionRslHandle);

    }

    _onEndSessionDoneEvt.Broadcast(isSuccessful);
}

void UOnlineManager::onFindSessionDone(bool isSuccessful)
{
    const IOnlineSessionPtr tmpSeesion = Online::GetSessionInterface(GetWorld());
    if(tmpSeesion.IsValid()){
         tmpSeesion->ClearOnFindSessionsCompleteDelegate_Handle(_findSessionRslHandle);
    }

    if(_currSearchedSession->SearchResults.Num() <= 0 ){
          _onFindSessionDoneEvt.Broadcast(TArray<FOnlineSessionSearchResult>(), isSuccessful);
          return;
    }

      _onFindSessionDoneEvt.Broadcast(_currSearchedSession->SearchResults, isSuccessful);

}

void UOnlineManager::onJoinSessionDone(FName sessionName, EOnJoinSessionCompleteResult::Type rsl)
{
    const IOnlineSessionPtr tmpSeesion = Online::GetSessionInterface(GetWorld());
    if(tmpSeesion){
        tmpSeesion->ClearOnJoinSessionCompleteDelegate_Handle(_joinSessionRslHandle);
    }

    _onJoinSessionDoneEvt.Broadcast(rsl);
}

bool UOnlineManager::tryTravleToCurrSession()
{
    const IOnlineSessionPtr tmpSeesion = Online::GetSessionInterface(GetWorld());
    if(!tmpSeesion.IsValid()){
       return false;
    }

    FString connStr;
    if(!tmpSeesion->GetResolvedConnectString(NAME_GameSession,  connStr)){
        return false;
    }

    APlayerController* playerCtrllor = GetWorld()->GetFirstPlayerController();
    playerCtrllor->ClientTravel(connStr , TRAVEL_Absolute);

    return true;

}










