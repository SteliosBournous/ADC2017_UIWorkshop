#include "GraphicalAssetsApplication.h"

const String GraphicalAssetsApplication::getApplicationName()
{
    return ProjectInfo::projectName;
}

const String GraphicalAssetsApplication::getApplicationVersion()
{
    return ProjectInfo::versionString;
}

bool GraphicalAssetsApplication::moreThanOneInstanceAllowed()
{
    return true;
}

void GraphicalAssetsApplication::initialise (const String& commandLine)
{
    mainWindow = new MainWindow (getApplicationName());
}

void GraphicalAssetsApplication::shutdown()
{
    mainWindow = nullptr;
}

void GraphicalAssetsApplication::systemRequestedQuit()
{
    quit();
}
