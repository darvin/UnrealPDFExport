// Copyright Epic Games, Inc. All Rights Reserved.

#include "PDFExportCommands.h"

#define LOCTEXT_NAMESPACE "FPDFExportModule"

void FPDFExportCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "PDFExport", "Bring up PDFExport window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
