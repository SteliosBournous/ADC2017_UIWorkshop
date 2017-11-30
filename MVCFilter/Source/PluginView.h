#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "FilmStripDial.h"

/**
 * This is the view. It holds some basic Components
 * and does some basic layout functions, but handles little else
 */
class PluginView  : public AudioProcessorEditor
                  , private Timer
{
public:

    PluginView (PluginProcessor&);
    ~PluginView();

    void paint (Graphics&) override;
    void resized() override;
    
    FilmStripDial cutoff;
    FilmStripDial resonance;
    FilmStripDial drive;
    
    ComboBox filterMode;
    ComboBox distortionMode;
    
    ImageButton distortionIsPreFilter;

private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginView)

    void timerCallback() override;

    /**
     * Some utility functions for constructing our UI
     */
    void addControls();
    void initialiseDials();
    void initialiseButtons();
    void initialiseLabels();
    
    Component* getComponentUnderTheMouse() const;
    
    Label cutoffLabel;
    Label resonanceLabel;
    Label driveLabel;
    Label distortionPreFilterLabel;
    Label infoLabel;
    
    /**
     * Copy of the processor - we need to store this for later when we bind and unbind ourselves
     */
    PluginProcessor& processor;
    SharedResourcePointer<TooltipWindow> tooltip;
};
