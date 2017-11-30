/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "ColourPalette.h"
#include "CommonSizes.h"

#include "GradientComponent.h"
#include "CardComponent.h"

#include "RelativePositionsView.h"
#include "ProportionalSizesView.h"
#include "MainAxisAndCrossAxisView.h"
#include "GridCardsView.h"

class MainView   : public Component
{
public:
    //==============================================================================
    MainView();
    ~MainView();

    void paint (Graphics&) override;
    void resized() override;
    
    GradientComponent background;
    
    RelativePositionsView relativePositionsView;
    ProportionalSizesView proportionalSizesView;
    MainAxisAndCrossAxisView mainAxisAndCrossAxisView;
    
    GridCardsView gridCardsView;
    

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainView)
};
