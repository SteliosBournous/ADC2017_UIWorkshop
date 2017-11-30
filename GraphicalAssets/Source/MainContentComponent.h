#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "TabbedPanel.h"

class MainContentComponent : public Component
{
public:
    
    MainContentComponent();
    ~MainContentComponent() = default;

    void resized() override;

private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
    
    TabbedPanel tabbedPanel;
};
