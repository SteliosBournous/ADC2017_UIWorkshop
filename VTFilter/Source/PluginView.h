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

    Array<ScopedPointer<AudioProcessorValueTreeState::SliderAttachment>> sliders;
    Array<ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment>> combos;
    Array<ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment>> buttons;
    
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginView)

    void timerCallback() override;

    void addControls();
    void initialiseButtons();
    void initialiseLabels();
    
    Component* getComponentUnderTheMouse() const;
    String getParameterKeyForComponentUnderTheMouse() const;

    Label cutoffLabel;
    Label resonanceLabel;
    Label driveLabel;
    Label distortionPreFilterLabel;
    Label infoLabel;
    
    PluginProcessor& processor;
    SharedResourcePointer<TooltipWindow> tooltip;
};
