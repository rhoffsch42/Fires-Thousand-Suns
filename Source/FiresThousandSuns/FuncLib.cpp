
#include "FuncLib.h"
//#include "GenericPlatform/GenericPlatformMisc.h"
#include "GenericPlatform/GenericPlatformApplicationMisc.h"
//#include "Lumin/LuminPlatformApplicationMisc.h"
#include "FiresThousandSunsGameInstance.h"
#include "Misc/FileHelper.h"

UFiresThousandSunsGameInstance* UFuncLib::Fires_GI = nullptr;
FString UFuncLib::LogFile = FString(PATH_LOGFILE_RUNTIMEERRORS);

bool	UFuncLib::CheckObject(UObject* obj, FString ErrorMsg) {
	if (!obj) {
		if (GEngine) {
			D_(GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, ErrorMsg));
		}
		LOG(ErrorMsg);
		if (UFuncLib::Fires_GI) { UFuncLib::Fires_GI->AddDebugMessage(ErrorMsg); }
		if (!FFileHelper::SaveStringToFile(
			ErrorMsg.Append("\n"), *UFuncLib::LogFile,
			FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append))
		{
			if (UFuncLib::Fires_GI) { UFuncLib::Fires_GI->AddDebugMessage(FString("Failed to write to ").Append(UFuncLib::LogFile)); }
			if (GEngine) {
				D_(GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString("Failed to write to ").Append(UFuncLib::LogFile)));
			}
		}
		return false;
	}
	return true;
}

void	UFuncLib::CopyToClipboard(FString Input) {
	// FGenericPlatformMisc FPlatformApplicationMisc
	//FGenericPlatformMisc::ClipboardCopy(*Input);
	//FPlatformApplicationMisc::ClipboardCopy(*Input);
	FGenericPlatformApplicationMisc::ClipboardCopy(*Input);
}

FString	UFuncLib::GetFromClipboard() {
	FString res;
	//FGenericPlatformMisc::ClipboardPaste(res);
	FGenericPlatformApplicationMisc::ClipboardPaste(res);
	return res;
}

FString	UFuncLib::GetLogFilePath() { return UFuncLib::LogFile; }

FString	UFuncLib::GetDirPaths() {
	return FString("AutomationDir ").Append(FPaths::AutomationDir())
		.Append("\nAutomationLogDir ").Append(FPaths::AutomationLogDir())
		.Append("\nAutomationReportsDir ").Append(FPaths::AutomationReportsDir())
		.Append("\nAutomationTransientDir ").Append(FPaths::AutomationTransientDir())
		.Append("\nBugItDir ").Append(FPaths::BugItDir())
		.Append("\nCloudDir ").Append(FPaths::CloudDir())
		.Append("\nDiffDir ").Append(FPaths::DiffDir())
		.Append("\nEngineConfigDir ").Append(FPaths::EngineConfigDir())
		.Append("\nEngineContentDir ").Append(FPaths::EngineContentDir())
		.Append("\nEngineDefaultLayoutDir ").Append(FPaths::EngineDefaultLayoutDir())
		.Append("\nEngineDir ").Append(FPaths::EngineDir())
		.Append("\nEngineEditorSettingsDir ").Append(FPaths::EngineEditorSettingsDir())
		.Append("\nEngineIntermediateDir ").Append(FPaths::EngineIntermediateDir())
		.Append("\nEnginePlatformExtensionsDir ").Append(FPaths::EnginePlatformExtensionsDir())
		.Append("\nEngineProjectLayoutDir ").Append(FPaths::EngineProjectLayoutDir())
		.Append("\nEngineSavedDir ").Append(FPaths::EngineSavedDir())
		.Append("\nEngineSourceDir ").Append(FPaths::EngineSourceDir())
		.Append("\nEngineUserDir ").Append(FPaths::EngineUserDir())
		.Append("\nEngineUserLayoutDir ").Append(FPaths::EngineUserLayoutDir())
		.Append("\nEngineVersionAgnosticUserDir ").Append(FPaths::EngineVersionAgnosticUserDir())
		.Append("\nEnterpriseDir ").Append(FPaths::EnterpriseDir())
		.Append("\nEnterpriseFeaturePackDir ").Append(FPaths::EnterpriseFeaturePackDir())
		.Append("\nEnterprisePluginsDir ").Append(FPaths::EnterprisePluginsDir())
		.Append("\nFeaturePackDir ").Append(FPaths::FeaturePackDir())
		.Append("\nGameAgnosticSavedDir ").Append(FPaths::GameAgnosticSavedDir())
		.Append("\nGameDevelopersDir ").Append(FPaths::GameDevelopersDir())
		.Append("\nGameSourceDir ").Append(FPaths::GameSourceDir())
		.Append("\nGameUserDeveloperDir ").Append(FPaths::GameUserDeveloperDir())
		.Append("\nGameUserDeveloperFolderName ").Append(FPaths::GameUserDeveloperFolderName())
		.Append("\nGeneratedConfigDir ").Append(FPaths::GeneratedConfigDir())
		.Append("\nGetPlatformLocalizationFolderName ").Append(FPaths::GetPlatformLocalizationFolderName())
		.Append("\nGetProjectFilePath ").Append(FPaths::GetProjectFilePath())
		.Append("\nGetRelativePathToRoot ").Append(FPaths::GetRelativePathToRoot())
		.Append("\nLaunchDir ").Append(FPaths::LaunchDir())
		.Append("\nProfilingDir ").Append(FPaths::ProfilingDir())
		.Append("\nProjectConfigDir ").Append(FPaths::ProjectConfigDir())
		.Append("\nProjectContentDir ").Append(FPaths::ProjectContentDir())
		.Append("\nProjectDir ").Append(FPaths::ProjectDir())
		.Append("\nProjectIntermediateDir ").Append(FPaths::ProjectIntermediateDir())
		.Append("\nProjectLogDir ").Append(FPaths::ProjectLogDir())
		.Append("\nProjectModsDir ").Append(FPaths::ProjectModsDir())
		.Append("\nProjectPersistentDownloadDir ").Append(FPaths::ProjectPersistentDownloadDir())
		.Append("\nProjectPlatformExtensionsDir ").Append(FPaths::ProjectPlatformExtensionsDir())
		.Append("\nProjectPluginsDir ").Append(FPaths::ProjectPluginsDir())
		.Append("\nProjectSavedDir ").Append(FPaths::ProjectSavedDir())
		.Append("\nProjectUserDir ").Append(FPaths::ProjectUserDir())
		.Append("\nRootDir ").Append(FPaths::RootDir())
		.Append("\nSandboxesDir ").Append(FPaths::SandboxesDir())
		.Append("\nScreenShotDir ").Append(FPaths::ScreenShotDir())
		.Append("\nShaderWorkingDir ").Append(FPaths::ShaderWorkingDir())
		.Append("\nSourceConfigDir ").Append(FPaths::SourceConfigDir())
		.Append("\nVideoCaptureDir ").Append(FPaths::VideoCaptureDir())
	;
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

