// Fill out your copyright notice in the Description page of Project Settings.


#include "RemoveUnusedUtility.h"
#include "EditorUtilityLibrary.h"
#include "C:/Program Files/Epic Games/UE_5.0/Engine/Plugins/Editor/EditorScriptingUtilities/Source/EditorScriptingUtilities/Public/EditorAssetLibrary.h"

void URemoveUnusedUtility::RemoveUnusedAssets(bool bDeleteImmediately)
{

	TArray<UObject*> SelectedObjects = UEditorUtilityLibrary::GetSelectedAssets();
	TArray<UObject*> UnusedObjects = TArray<UObject*>();
	
	for (UObject* SelectedObject : SelectedObjects)
	{
		if (ensure(SelectedObject))
		{
			// �I�����ꂽ�A�Z�b�g���Q�Ƃ���Ă��Ȃ��ꍇ
			if (UEditorAssetLibrary::FindPackageReferencersForAsset(SelectedObject->GetPathName(), true).Num() <= 0)
			{
				// ���g�p�̃A�Z�b�g�Ƃ��Ēǉ�
				UnusedObjects.Add(SelectedObject);
			}
		}
	}

	uint32	Counter = 0;

	for (UObject* SelectedObject : SelectedObjects)
	{
		if (bDeleteImmediately)
		{
			// �����ɍ폜����ꍇ
			if (UEditorAssetLibrary::DeleteLoadedAsset(SelectedObject))
			{
				++Counter;
			}
			else
			{
				PrintToScreen("Error deleting " + SelectedObject->GetPathName(), FColor::Red);
			}
		}
		else
		{
			// �����ɍ폜���Ȃ��ꍇ
			// �S�~���Ɉړ����邽�߂̐V�����p�X���쐬
			FString NewPath = FPaths::Combine(TEXT("/Game"), TEXT("Trash"), SelectedObject->GetName());
			if (UEditorAssetLibrary::RenameLoadedAsset(SelectedObject, NewPath))
			{
				++Counter;
			}
			else
			{
				PrintToScreen("Error moving " + SelectedObject->GetPathName(), FColor::Red);
			}
		}
	}

	GiveFeedback(bDeleteImmediately ? "Deleted" : "Moved to bin:", Counter);
}

void URemoveUnusedUtility::PrintToScreen(FString Message, FColor Color)
{
	if (ensure(GEngine))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.5f, Color, Message);
	}
}

void URemoveUnusedUtility::GiveFeedback(FString Method, uint32 Counter)
{
	FString Message = FString("No matching files found");
	FColor Color = Counter > 0 ? FColor::Green : FColor::Red;
	if (Counter > 0)
	{
		Message = Method.AppendChar(' ');
		Message.AppendInt(Counter);
		Message.Append(Counter == 1 ? TEXT(" file") : TEXT(" files"));
	}
	PrintToScreen(Message, Color);
}
