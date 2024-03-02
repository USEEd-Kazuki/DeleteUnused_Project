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
	* �g�p����Ă��Ȃ��A�Z�b�g���폜
	* @param bDeleteImmediately - �����ɍ폜���邩�ǂ����̃t���O
	*/
	UFUNCTION(CallInEditor)
	void RemoveUnusedAssets(bool bDeleteImmediately);

private:
	/**
	* �X�N���[���ւ̃��b�Z�[�W�\��
	* @param Message - ���b�Z�[�W
	* @param Color - ���b�Z�[�W�Ɏg�p����F
	**/
	void PrintToScreen(FString Message, FColor Color);

	/**
	* ���[�U�[�ւ̃t�B�[�h�o�b�N
	* @param Method - �g�p���ꂽ���\�b�h
	* @param Counter - �ϊ����ꂽ�A�Z�b�g��
	**/
	void GiveFeedback(FString Method, uint32 Counter);
	
};
