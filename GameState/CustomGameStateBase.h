// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CustomGameInstance.h"
#include "CustomGameStateBase.generated.h"

/**
 * 
 */
class AMainCharacter;

UCLASS()
class ROBOTHUNTER_API ACustomGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerJoin);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerQuit);

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<AMainCharacter> playerOwner;

	/* Si c'est le serveur qui pointe la liste, le character [0] = owner et [1] = autre client */
	UPROPERTY(VisibleAnywhere)
		TArray<AMainCharacter*> players;

protected:
	UPROPERTY(EditAnywhere)
		TEnumAsByte<EGameStatus> startStatus = GameNone;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, meta = (AllowPrivateAccess))
	FOnPlayerJoin onPlayerJoin;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable, meta = (AllowPrivateAccess))
	FOnPlayerQuit onPlayerQuit;

	
	//UPROPERTY(EditAnywhere, Category = "Members")
	//	TArray<TEnumAsByte<EMemberType>> unlockedMembers;

public:
	ACustomGameStateBase();

	bool Register(AMainCharacter* _player, const bool _isOwner);
	bool Unregister(AMainCharacter* _player);

	FORCEINLINE AMainCharacter* GetPlayerOwner() const {
		return playerOwner;
	}
	/* Si c'est le serveur qui pointe la liste, le character [0] = owner et [1] = autre client */
	FORCEINLINE TArray<AMainCharacter*> GetPlayers() const {
		return players;
	}
	FORCEINLINE TEnumAsByte<EGameStatus> GetStartStatus() const { return startStatus; }
	FORCEINLINE FOnPlayerJoin& OnPlayerJoin() { return onPlayerJoin; }
	FORCEINLINE FOnPlayerQuit& OnPlayerQuit() { return onPlayerQuit; }

};
