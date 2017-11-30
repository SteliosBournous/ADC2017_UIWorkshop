#include "MainContentComponent.h"

MainContentComponent::MainContentComponent()
{
    setSize (500, 500);
    addAndMakeVisible (tabbedPanel);
}

void MainContentComponent::resized()
{
    tabbedPanel.setBounds (getLocalBounds());
}
