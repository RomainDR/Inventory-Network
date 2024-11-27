// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryMenu.h"

#include "GameFramework/PlayerState.h"
#include "RobotHunter/CCC/Character/MainCharacter.h"
#include "RobotHunter/Game/CustomGameStateBase.h"
#include "../InventorySettings.h"
#include "RobotHunter/UI/Template/Game/Inventory/DataInventoryPlayer.h"

void UInventoryMenu::Init()
{
	Super::Init();

	customGameState = GetWorld()->GetGameState<ACustomGameStateBase>();
	CHECK_NULL_WITH_RETURN(customGameState, "Custom game state is null", return);
}

void UInventoryMenu::SetNewWeight()
{
	if (inventoryType != Transfer)
	{
		return;
	}
	oldWeightFirstPlayer->SetPercent(newWeightFirstPlayer->GetPercent());
}

void UInventoryMenu::SetTransferSide()
{
	inventoryType = Transfer;
	Refresh();
}

void UInventoryMenu::InitializePlayers()
{
	LOG(true, "Player Join refreshing");	

	AMainCharacter* _p = customGameState->GetPlayers()[0];
	CHECK_NULL_WITH_RETURN(_p, "p is null", return);

	APlayerState* _ps = _p->GetPlayerState();
	CHECK_NULL_WITH_RETURN(_ps, "ps is null", return);
	
	SET_TEXT_STR(firstPlayerName->GetText(),_ps->GetPlayerName());
	
	if(HasSecondPlayer())
	{
		_p = customGameState->GetPlayers()[1];
		CHECK_NULL_WITH_RETURN(_p, "p is null", return);

		_ps = _p->GetPlayerState();
		CHECK_NULL_WITH_RETURN(_ps, "ps is null", return);
		SET_TEXT_STR(secondPlayerName->GetText(),_ps->GetPlayerName());
	}
	else	
		SET_TEXT_STR(secondPlayerName->GetText(), settings->GetNoPlayerText());
}

void UInventoryMenu::SetPlayerName(const TObjectPtr<AMainCharacter>& _player,
                                   const TObjectPtr<UTextPrefab>& _text) const
{
	AMainCharacter* _p = _player;
	CHECK_NULL_WITH_RETURN(_p, "First player is null", return);
}

void UInventoryMenu::ChangeValueNewWeight(float newValue)
{
	AMainCharacter* _player = customGameState->GetPlayers()[0];
	CHECK_NULL_WITH_RETURN(_player, "player is null", return);

	UInventoryComponent* _inventory = _player->GetPlayerBag()->GetInventoryComponent();
	CHECK_NULL_WITH_RETURN(_inventory, "Inventory component is null", return);

	const float _currentWeight = _inventory->GetWeightByQuantity(settings->NameOfRessource(),
	                                                             _inventory->GetQuantityByKey(
		                                                             settings->NameOfRessource()));
	const int maxInventory = _inventory->GetMaxWeightBiomass();

	const float maxRatioSlider = _currentWeight / maxInventory;
	float _ratio;


	if (newValue >= _currentWeight)
	{
		sliderWeightFirstPlayer->SetValue(_currentWeight);
		sliderPadding->SetValue(_currentWeight);
		_ratio = maxRatioSlider;
	}
	else
	{
		_ratio = newValue / sliderWeightFirstPlayer->GetMaxValue();
	}

	firstPlayerData->SetNewValue(FMath::RoundToInt((maxRatioSlider - _ratio) * maxInventory));
	newWeightFirstPlayer->SetPercent(_ratio);
	if (inventoryType == Destroy)
	{
		BtnAction->SetIsEnabled(newValue < _currentWeight);
	}
}

void UInventoryMenu::TransferFromInventory()
{
	if (inventoryType != Transfer)
	{
		return;
	}
}

void UInventoryMenu::DestroyFromInventory()
{
	if (inventoryType != Destroy)
	{
		return;
	}

	AMainCharacter* _first = customGameState->GetPlayers()[0];
	CHECK_NULL_WITH_RETURN(_first, "First player is null", return);

	UInventoryComponent* _inventory = _first->GetPlayerBag()->GetInventoryComponent();
	CHECK_NULL_WITH_RETURN(_inventory, "Inventory First player is null", return);

	const float _currentWeight = _inventory->GetWeightByQuantity(settings->NameOfRessource(),
	                                                             _inventory->GetQuantityByKey(
		                                                             settings->NameOfRessource()));
	const int amountToDrop = _currentWeight - sliderWeightFirstPlayer->GetValue();
	_inventory->DropItem(settings->NameOfRessource(), amountToDrop);
}

void UInventoryMenu::SetDestroySide()
{
	inventoryType = Destroy;
	Refresh();
}

void UInventoryMenu::UpdateOldPercent() const
{
	oldWeightFirstPlayer->SetPercent(newWeightFirstPlayer->GetPercent());
}

void UInventoryMenu::RegisterEvents()
{
	Super::RegisterEvents();
/*
	ACustomGameStateBase* _gs = Cast<ACustomGameStateBase>(GetWorld()->GetGameState());
	CHECK_NULL_WITH_RETURN(_gs, "GameState is null", return);

	BIND_WIDGET(sliderPadding, OnValueChanged, UInventoryMenu, SyncWeightWithPadding);
	BIND_WIDGET(sliderWeightFirstPlayer, OnValueChanged, UInventoryMenu, SyncWeightWithPadding);
	BIND_WIDGET(sliderWeightFirstPlayer, OnValueChanged, UInventoryMenu, ChangeValueNewWeight);
	BIND_WIDGET(sliderPadding, OnValueChanged, UInventoryMenu, ChangeValueNewWeight);
	BIND_ACTION(BtnAction, OnClick, UInventoryMenu, TransferFromInventory);
	BIND_ACTION(BtnAction, OnClick, UInventoryMenu, DestroyFromInventory);
	BIND_ACTION(transferSide, OnClick, UInventoryMenu, SetTransferSide);
	BIND_ACTION(destroySide, OnClick, UInventoryMenu, SetDestroySide);*/
}

void UInventoryMenu::SyncSliderPaddingWithWeight(float newValue)
{
	sliderWeightFirstPlayer->SetValue(newValue);
}

void UInventoryMenu::SyncWeightWithPadding(float newValue)
{
	sliderPadding->SetValue(newValue);
}

void UInventoryMenu::Refresh()
{
	Super::Refresh();
	InitializePlayers();
	
	AMainCharacter* _first = customGameState->GetPlayers()[0];
	CHECK_NULL_WITH_RETURN(_first, "First player is null", return);

	SetInformationFromPlayer(_first, firstPlayerData, sliderWeightFirstPlayer, newWeightFirstPlayer, oldWeightFirstPlayer,
							  overlayFirstEgg);

	
	if(HasSecondPlayer())
	{
		const AMainCharacter* _second = customGameState->GetPlayers()[1];
		CHECK_NULL_WITH_RETURN(_second, "Second player is null", return);
		
		const float distance = (_first->GetActorLocation() - _second->GetActorLocation()).Length();
		LOG(true, "Length: " + FString::SanitizeFloat(distance));

		//TODO InventoryMenu: activer le transit
	}
	SetInformationFromPlayer(HasSecondPlayer() ?  customGameState->GetPlayers()[1] : nullptr, secondPlayerData, nullptr, oldWeightSecondPlayer, newWeightSecondPlayer,
							  overlaySecondEgg);

	BtnAction->SetIsEnabled(inventoryType == Transfer && isInRange && HasSecondPlayer());
	SET_TEXT_STR(BtnAction->GetText()->GetText(), inventoryType == Transfer ? settings->GetTransferText() : settings->GetDestroyText());

}

void UInventoryMenu::InitWithDelay()
{
	Super::InitWithDelay();
	//TODO remove
	//InitializePlayers();
}

void UInventoryMenu::SetInformationFromPlayer(const TObjectPtr<AMainCharacter>& _player,
                                              const TObjectPtr<UDataInventoryPlayer>& _dip,
                                              const TObjectPtr<USlider>& _slider,
                                              const TObjectPtr<UProgressBar>& _currentWeight,
                                              const TObjectPtr<UProgressBar>& _oldProgressBar,
                                              const TObjectPtr<UOverlay>& _overlayEgg) const
{
	if (_player)
	{
		const ABagActor* _bag = _player->GetPlayerBag();
		CHECK_NULL_WITH_RETURN(_bag, "Bag component is null", return);

		UInventoryComponent* _inventory = _bag->GetInventoryComponent();
		CHECK_NULL_WITH_RETURN(_inventory, "Inventory component is null", return);

		_dip->RefreshInventory(_inventory, settings);

		const float _weight = _inventory->GetWeightByQuantity(settings->NameOfRessource(),
		                                                      _inventory->GetQuantityByKey(
			                                                      settings->NameOfRessource()));
		const float _maxWeight = _inventory->GetMaxWeightBiomass();
		if (_slider)
		{
			_slider->SetMaxValue(_maxWeight);
			_slider->SetValue(_weight);
			sliderPadding->SetMaxValue(_maxWeight);
			sliderPadding->SetValue(_weight);
		}

		const float _ratio = _weight / _maxWeight;
		_currentWeight->SetPercent(_ratio);
		_oldProgressBar->SetPercent(_ratio);

		_overlayEgg->SetVisibility(_inventory->GetHasEgg() ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
	else
	{
		if (_slider)
		{
			_slider->SetMaxValue(0);
			_slider->SetValue(0);
		}
		_currentWeight->SetIsEnabled(false);
		_oldProgressBar->SetIsEnabled(false);
		_currentWeight->SetPercent(0);
		_oldProgressBar->SetPercent(0);
		_overlayEgg->SetVisibility(ESlateVisibility::Hidden);
		_dip->RefreshInventory(nullptr, settings);
	}
}
