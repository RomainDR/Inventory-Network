// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameStateBase.h"
#include "../CCC/Character/MainCharacter.h"

bool ACustomGameStateBase::Register(AMainCharacter* _player, const bool _isOwner)
{
	if (players.Contains(_player)) return false;
	if (_isOwner)	
		playerOwner = _player;	
	players.Add(_player);
	onPlayerJoin.Broadcast();
	//_player->PlayerInitVoiceChat(); //TODO Fix l'erreur  thib stp (c'est pas moi)
	return true;
}

bool ACustomGameStateBase::Unregister(AMainCharacter* _player)
{
	if (!players.Contains(_player)) return false;
	players.Remove(_player);
	onPlayerQuit.Broadcast();
	return true;
}

ACustomGameStateBase::ACustomGameStateBase()
{
	PrimaryActorTick.bCanEverTick = true;
}
