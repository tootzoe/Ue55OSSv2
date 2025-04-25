// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "OnlineBpBridge.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UE55OSSV2_API UOnlineBpBridge : public UObject
{
	GENERATED_BODY()
	
	
  public:
    explicit UOnlineBpBridge();



UFUNCTION(BlueprintCallable, Category = "TOOT" , meta = (WorldContext="WorldContextObj"))
    void StartOnlineSession(UObject* WorldContextObj);

    //
    UFUNCTION(BlueprintImplementableEvent, Category = "TOOT")
    void OnlineCompleteEvt(bool IsSuccessful);

    //
    //
    UFUNCTION(BlueprintCallable, Category = "TOOT"  )
    void TestGetworldFunc( );


    protected:




    private:

     class  UOnlineManager* _onlineManager;
    // class  UTestGetworld* _testGetWorld;
	
};
