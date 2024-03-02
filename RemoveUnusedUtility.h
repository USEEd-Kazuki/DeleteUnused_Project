// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetActionUtility.h"
#include "RemoveUnusedUtility.generated.h"

/**
 * 
 */
UCLASS()
class PREFIXPROJECT_API URemoveUnusedUtility : public UAssetActionUtility
{
	GENERATED_BODY()

public:
	/**
	* 使用されていないアセットを削除
	* @param bDeleteImmediately - 即座に削除するかどうかのフラグ
	*/
	UFUNCTION(CallInEditor)
	void RemoveUnusedAssets(bool bDeleteImmediately);

private:
	/**
	* スクリーンへのメッセージ表示
	* @param Message - メッセージ
	* @param Color - メッセージに使用する色
	**/
	void PrintToScreen(FString Message, FColor Color);

	/**
	* ユーザーへのフィードバック
	* @param Method - 使用されたメソッド
	* @param Counter - 変換されたアセット数
	**/
	void GiveFeedback(FString Method, uint32 Counter);
	
};
