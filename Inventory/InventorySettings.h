#pragma once

#include "CoreMinimal.h"
#include "../../../BaseSettings.h"
#include "RobotHunter/Utils/DebugUtils.h"
#include "InventorySettings.generated.h"

/**
 * 
 */
UCLASS()
class ROBOTHUNTER_API UInventorySettings final : public UBaseSettings
{
	GENERATED_BODY()

	/** The text formated to be show in UI
	 * {0} represent a value to be replace
	 */
	UPROPERTY(EditAnywhere)
	FText weightText = TEXTSTR("{0} Kg");
	/** The text formated to be show in UI
	 * {0} represent a value to be replace
	 */
	UPROPERTY(EditAnywhere)
	FText priceText = TEXTSTR("{0} $");

	//The text showed when player play solo
	UPROPERTY(EditAnywhere)
	FText noPlayer = TEXTSTR("No Player");

	//Detection distance for transfer between players
	UPROPERTY(EditAnywhere, Category = "Transfer", meta = (UIMin = 0, ClampMin = 0))
	float distanceAllowTransfert = 500;

	/** The name of ressource */
	UPROPERTY()
	FText nameOfRessource = TEXTSTR("Biomass");
	/** The name of ressource */
	UPROPERTY()
	FText nameOfEgg = TEXTSTR("Egg");

	/** The text on button if destroy side */
	UPROPERTY(EditAnywhere, Category = "Destroy")
	FText destroyTextBtn = TEXTSTR("Destroy");

	/** The text on button if transfer side */
	UPROPERTY(EditAnywhere, Category = "Transfer")
	FText transferTextBtn = TEXTSTR("Transfer");

public:
	/** Get the text formated with message */
	FString GetWeightTextFormated(FString formatMessage) const;
	/** Get the text formated with message */
	FString GetPriceTextFormated(FString formatMessage) const;

	/**
	 * Get the name of resource
	 * @return FString
	 */
	FORCEINLINE FString NameOfRessource() const
	{
		return nameOfRessource.ToString();
	}

	/**
		 * Get the name of resource
		 * @return FString
		 */
	FORCEINLINE FString NameOfEgg() const
	{
		return nameOfEgg.ToString();
	}

	FORCEINLINE FString GetNoPlayerText() const { return noPlayer.ToString(); }

	FORCEINLINE FString GetDestroyText() const { return destroyTextBtn.ToString(); }
	FORCEINLINE FString GetTransferText() const { return transferTextBtn.ToString(); }
};
