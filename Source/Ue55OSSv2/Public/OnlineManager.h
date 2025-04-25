// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"




#include "OnlineManager.generated.h"

/**
 * 
 */


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCreateSessionDoneSignature, bool, isSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDestorySessionDoneSignature, bool, isSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStartSessionDoneSignature, bool, isSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndSessionDoneSignature, bool, isSuccessful);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFindSessionDoneSignature,   TArray<FOnlineSessionSearchResult> , sessionResults ,  bool , isSuccessful);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFindSessionDoneSignature , const TArray<FOnlineSessionSearchResult>&  sessionResults ,  bool isSuccessful);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnJoinSessionDoneSignature , EOnJoinSessionCompleteResult::Type rsl);


UCLASS(Blueprintable)
class UE55OSSV2_API UOnlineManager : public UObject
{
	GENERATED_BODY()
	
    public:
    explicit UOnlineManager();
	
    // Create
    UFUNCTION(BlueprintCallable, Category = "TOOT"   )
    void CreateOnlineSeesion(  int32 publicConnCount,  bool isLanMatch);
    FOnCreateSessionDoneSignature _onCreateSessionDoneEvt;
    // Destory
    UFUNCTION(BlueprintCallable, Category = "TOOT"   )
    void DestoryOnlineSeesion( );
    FOnDestorySessionDoneSignature _onDestorySessionDoneEvt;
    // Start Session
    UFUNCTION(BlueprintCallable, Category = "TOOT"   )
    void StartOnlineSeesion( );
    FOnStartSessionDoneSignature _onStartSessionDoneEvt;
    // End Session
    UFUNCTION(BlueprintCallable, Category = "TOOT"   )
    void EndOnlineSeesion( );
    FOnEndSessionDoneSignature _onEndSessionDoneEvt;
    // Find Session
    UFUNCTION(BlueprintCallable, Category = "TOOT"   )
    void FindOnlineSeesion( int32 MaxLimit , bool IsLANQuery );
    FOnFindSessionDoneSignature _onFindSessionDoneEvt;
    // Join Session
   // UFUNCTION(BlueprintCallable, Category = "TOOT"   )
    void JoinOnlineSeesion( const FOnlineSessionSearchResult &SessionResult);
    FOnJoinSessionDoneSignature _onJoinSessionDoneEvt;
    //



    protected:
    void onCreateSessionDone(FName sessionName ,  bool isSuccessful);
    void onDestorySessionDone(FName sessionName ,  bool isSuccessful);
    void onStartSessionDone(FName sessionName ,  bool isSuccessful);
    void onEndSessionDone(FName sessionName ,  bool isSuccessful);
    void onFindSessionDone(   bool isSuccessful);
    void onJoinSessionDone( FName sessionName , EOnJoinSessionCompleteResult::Type rsl );
    bool tryTravleToCurrSession();


   private:

    FOnCreateSessionCompleteDelegate _createSessionCompleteDelegate;
    FDelegateHandle _createSessionRslHandle;
    //
    FOnDestroySessionCompleteDelegate _destorySessionCompleteDelegate;
    FDelegateHandle _destorySessionRslHandle;
    //
    FOnStartSessionCompleteDelegate _startSessionCompleteDelegate;
    FDelegateHandle _startSessionRslHandle;
    //
    FOnEndSessionCompleteDelegate _endSessionCompleteDelegate;
    FDelegateHandle _endSessionRslHandle;
    //
    FOnFindSessionsCompleteDelegate _findSessionCompleteDelegate;
    FDelegateHandle _findSessionRslHandle;
    TSharedPtr<FOnlineSessionSearch> _currSearchedSession;
    //
    FOnJoinSessionCompleteDelegate _joinSessionCompleteDelegate;
    FDelegateHandle _joinSessionRslHandle;
    //

    TSharedPtr<FOnlineSessionSettings> _currSessionSettings;

	
};
