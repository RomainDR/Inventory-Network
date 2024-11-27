#include "InventorySettings.h"

FString UInventorySettings::GetWeightTextFormated(FString formatMessage) const
{
	FString _weightText = weightText.ToString();
	_weightText = FString::Format(*_weightText, {formatMessage});
	return _weightText;
}

FString UInventorySettings::GetPriceTextFormated(FString formatMessage) const
{
	FString _priceText = priceText.ToString();
	_priceText = FString::Format(*_priceText, {formatMessage});
	return _priceText;
}
