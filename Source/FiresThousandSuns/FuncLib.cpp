
#include "FuncLib.h"
#include "GenericPlatform/GenericPlatformMisc.h"
//#include "Lumin/LuminPlatformApplicationMisc.h"
#include "FiresThousandSunsGameInstance.h"

constexpr float D_LEN = 5.0f;

UFiresThousandSunsGameInstance* UFuncLib::Fires_GI = nullptr;


bool	UFuncLib::CheckObject(UObject* obj, FString ErrorMsg) {
	if (!obj) {
		if (GEngine) {
			D_(GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, ErrorMsg));
			LOG(ErrorMsg);
			if (UFuncLib::Fires_GI) { UFuncLib::Fires_GI->AddDebugMessage(ErrorMsg); }
		}
		return false;
	}
	return true;
}

void	UFuncLib::PrintStats(const FPlayerStatistics& Stats) {
	if (GEngine) {
		D_(GEngine->AddOnScreenDebugMessage(-1, D_LEN, FColor::Cyan, FString::Printf(TEXT("Fortify Stacks          : %lf"), Stats.FortifyEffect)));
		D_(GEngine->AddOnScreenDebugMessage(-1, D_LEN, FColor::Cyan, FString::Printf(TEXT("Spell Supression Effect : %lf"), Stats.SpellSuppressionEffect)));
		D_(GEngine->AddOnScreenDebugMessage(-1, D_LEN, FColor::Cyan, FString::Printf(TEXT("Spell Supression Chance : %lf"), Stats.SpellSuppressionChance)));
		D_(GEngine->AddOnScreenDebugMessage(-1, D_LEN, FColor::Cyan, FString::Printf(TEXT("Fire Resistance         : %lf"), Stats.FireResistance)));
		D_(GEngine->AddOnScreenDebugMessage(-1, D_LEN, FColor::Cyan, FString::Printf(TEXT("Life Regeneration       : %lf"), Stats.LifeRegeneration)));
		D_(GEngine->AddOnScreenDebugMessage(-1, D_LEN, FColor::Cyan, FString::Printf(TEXT("Life                    : %lf"), Stats.Life)));
		D_(GEngine->AddOnScreenDebugMessage(-1, D_LEN, FColor::Cyan, FString::Printf(TEXT("Movement Speed          : %lf"), Stats.MovementSpeed)));
	}
}

void	UFuncLib::CopyToClipboard(FString Input) {
	// FGenericPlatformMisc FPlatformApplicationMisc
	FGenericPlatformMisc::ClipboardCopy(*Input);
}

FString	UFuncLib::GetFromClipboard() {
	FString res;
	FGenericPlatformMisc::ClipboardPaste(res);
	return res;
}

void UFuncLib::SaveThumbnail(FString ObjectPath, FString OutputPath) {}
/*
#include "AssetRegistry/AssetRegistryModule.h"
#include "ObjectTools.h"
#include "IImageWrapperModule.h"
#include "Misc/FileHelper.h"
#include "UObject/SoftObjectPath.h"

void UFuncLib::SaveThumbnail(FString ObjectPath, FString OutputPath)
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	FSoftObjectPath sop;
	sop.SetPath(*ObjectPath);
	sop.ToFName();
	FAssetData AssetData = AssetRegistryModule.Get().GetAssetByObjectPath(sop.ToFName());
	UObject* MyObject = AssetData.GetAsset();
	if (UFuncLib::CheckObject(MyObject, "fuck1"))
	{
		FObjectThumbnail* ObjectThumbnail = ThumbnailTools::GenerateThumbnailForObjectToSaveToDisk(MyObject);
		if (ObjectThumbnail)
		{
			IImageWrapperModule& ImageWrapperModule = FModuleManager::Get().LoadModuleChecked<IImageWrapperModule>(TEXT("ImageWrapper"));
			TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);
			ImageWrapper->SetRaw(
				ObjectThumbnail->GetUncompressedImageData().GetData(),
				ObjectThumbnail->GetUncompressedImageData().Num(),
				ObjectThumbnail->GetImageWidth(),
				ObjectThumbnail->GetImageHeight(),
				ERGBFormat::BGRA, 8);
			if (ImageWrapper)
			{
				const TArray64<uint8>& CompressedByteArray = ImageWrapper->GetCompressed();
				if (FFileHelper::SaveArrayToFile(CompressedByteArray, *OutputPath)) {

				} else { UFuncLib::CheckObject(nullptr, "fuck4"); }
			} else { UFuncLib::CheckObject(nullptr, "fuck3"); }
		} else { UFuncLib::CheckObject(nullptr, "fuck2"); }
	}
}
*/

