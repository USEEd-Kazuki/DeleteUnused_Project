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
			// 選択されたアセットが参照されていない場合
			if (UEditorAssetLibrary::FindPackageReferencersForAsset(SelectedObject->GetPathName(), true).Num() <= 0)
			{
				// 未使用のアセットとして追加
				UnusedObjects.Add(SelectedObject);
			}
		}
	}

	uint32	Counter = 0;

	for (UObject* SelectedObject : SelectedObjects)
	{
		if (bDeleteImmediately)
		{
			// 即座に削除する場合
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
			// 即座に削除しない場合
			// ゴミ箱に移動するための新しいパスを作成
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
