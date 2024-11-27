// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Overlay.h"
#include "Components/ProgressBar.h"
#include "Components/Slider.h"
#include "RobotHunter/Game/CustomGameStateBase.h"
#include "RobotHunter/UI/Menu/BaseMenu.h"
#include "RobotHunter/UI/Menu/Game/Inventory/InventorySettings.h"
#include "RobotHunter/UI/Template/Prefab/ButtonPrefab/ButtonPrefab.h"
#include "RobotHunter/UI/Template/Prefab/TextPrefab/TextPrefab.h"
#include "InventoryMenu.generated.h"

class UDataInventoryPlayer;

UENUM()
enum EInventoryType
{
	Transfer,
	Destroy
};

/**
 * 
 */
UCLASS()
class ROBOTHUNTER_API UInventoryMenu final : public UBaseMenu
{
	GENERATED_BODY()

	UPROPERTY()
	TEnumAsByte<EInventoryType> inventoryType;

	UPROPERTY(EditAnywhere, Category = "Custom")
	TObjectPtr<UInventorySettings> settings;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UButtonPrefab> transferSide;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UButtonPrefab> destroySide;

#pragma region firstPlayer
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UTextPrefab> firstPlayerName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UDataInventoryPlayer> firstPlayerData;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UProgressBar> oldWeightFirstPlayer;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UProgressBar> newWeightFirstPlayer;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<USlider> sliderWeightFirstPlayer;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<USlider> sliderPadding;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UButtonPrefab> BtnAction;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UOverlay> overlayFirstEgg;
#pragma endregion firstPlayer

#pragma region secondPlayer
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UTextPrefab> secondPlayerName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UDataInventoryPlayer> secondPlayerData;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UProgressBar> oldWeightSecondPlayer;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UProgressBar> newWeightSecondPlayer;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	TObjectPtr<UOverlay> overlaySecondEgg;
#pragma endregion firstPlayer

	UPROPERTY()
	TObjectPtr<ACustomGameStateBase> customGameState;

	UPROPERTY()
	bool isInRange = false;


private:
#pragma region transfert Side
	UFUNCTION()
	void SetNewWeight();
	UFUNCTION()
	void SetTransferSide();
	UFUNCTION()
	void ChangeValueNewWeight(float newValue);
	UFUNCTION()
	void TransferFromInventory();
#pragma endregion transfert Side

#pragma region destroy Side
	UFUNCTION()
	void DestroyFromInventory();
	UFUNCTION()
	void SetDestroySide();
#pragma endregion destroy Side

	UFUNCTION()
	void SyncSliderPaddingWithWeight(float newValue);
	UFUNCTION()
	void SyncWeightWithPadding(float newValue);
	UFUNCTION()
	void InitializePlayers();

	FORCEINLINE bool HasSecondPlayer() const { return customGameState->GetPlayers().Num() == 2; }

	[[deprecated]]
	virtual void Init() override;
	virtual void RegisterEvents() override;
	virtual void Refresh() override;
	virtual void InitWithDelay() override;
	
	void UpdateOldPercent() const;
	void SetPlayerName(const TObjectPtr<AMainCharacter>& _player, const TObjectPtr<UTextPrefab>& _text) const;
	void SetInformationFromPlayer(const TObjectPtr<AMainCharacter>& _player,
	                              const TObjectPtr<UDataInventoryPlayer>& _dip,
	                              const TObjectPtr<USlider>& _slider,
	                              const TObjectPtr<UProgressBar>& _currentWeight,
	                              const TObjectPtr<UProgressBar>& _oldProgressBar,
	                              const TObjectPtr<UOverlay>& _overlayEgg) const;
};
