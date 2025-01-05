// Copyright Epic Games, Inc. All Rights Reserved.

#include "GASPlugin.h"

#define LOCTEXT_NAMESPACE "FGASPluginModule"

void FGASPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	// Example: Register custom ability or attribute system components if needed
	UE_LOG(LogTemp, Warning, TEXT("GAS Plugin Initialized"));
}

void FGASPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	// Example: Perform cleanup, unregister any systems, etc.
	UE_LOG(LogTemp, Warning, TEXT("GAS Plugin Shutdown"));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGASPluginModule, GASPlugin)