#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "MainWindow.h"

class GraphicalAssetsApplication : public JUCEApplication
{
public:
    
    GraphicalAssetsApplication() = default;
    
    const String getApplicationName() override;
    const String getApplicationVersion() override;
    bool moreThanOneInstanceAllowed() override;
    
    void initialise (const String& commandLine) override;
    void shutdown() override;
    void systemRequestedQuit() override;
    void anotherInstanceStarted (const String&) override {}

private:
    
    ScopedPointer<MainWindow> mainWindow;
};
