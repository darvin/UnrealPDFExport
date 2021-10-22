// Copyright Epic Games, Inc. All Rights Reserved.

#include "PDFExport.h"
#include "PDFExportStyle.h"
#include "PDFExportCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName PDFExportTabName("PDFExport");

#define LOCTEXT_NAMESPACE "FPDFExportModule"

void FPDFExportModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FPDFExportStyle::Initialize();
	FPDFExportStyle::ReloadTextures();

	FPDFExportCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FPDFExportCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FPDFExportModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FPDFExportModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(PDFExportTabName, FOnSpawnTab::CreateRaw(this, &FPDFExportModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FPDFExportTabTitle", "PDFExport"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FPDFExportModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FPDFExportStyle::Shutdown();

	FPDFExportCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(PDFExportTabName);
}

TSharedRef<SDockTab> FPDFExportModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FPDFExportModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("PDFExport.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FPDFExportModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(PDFExportTabName);
}

void FPDFExportModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FPDFExportCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FPDFExportCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPDFExportModule, PDFExport)