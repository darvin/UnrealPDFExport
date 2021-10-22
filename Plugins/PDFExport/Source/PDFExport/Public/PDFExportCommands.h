// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "PDFExportStyle.h"

class FPDFExportCommands : public TCommands<FPDFExportCommands>
{
public:

	FPDFExportCommands()
		: TCommands<FPDFExportCommands>(TEXT("PDFExport"), NSLOCTEXT("Contexts", "PDFExport", "PDFExport Plugin"), NAME_None, FPDFExportStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};