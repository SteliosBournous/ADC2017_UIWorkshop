#include "PluginProcessor.h"
#include "PluginView.h"

PluginView::PluginView (PluginProcessor& p)
          : AudioProcessorEditor (&p)
          , cutoff (ImageCache::getFromMemory (BinaryData::DialLarge_png, BinaryData::DialLarge_pngSize),
                    ImageCache::getFromMemory (BinaryData::DialLargeSurround_png, BinaryData::DialLargeSurround_pngSize))
          , resonance (ImageCache::getFromMemory (BinaryData::DialSmall_png, BinaryData::DialSmall_pngSize),
                       ImageCache::getFromMemory (BinaryData::DialSmallSurround_png, BinaryData::DialSmallSurround_pngSize))
          , drive (ImageCache::getFromMemory (BinaryData::DialLarge_png, BinaryData::DialLarge_pngSize),
                   ImageCache::getFromMemory (BinaryData::DialLargeSurround_png, BinaryData::DialLargeSurround_pngSize))
          , cutoffLabel ("", "Cutoff")
          , resonanceLabel ("", "Resonance")
          , driveLabel ("", "Drive")
          , distortionPreFilterLabel ("", "Distortion is pre filter")
          , processor (p)
{
    addControls();
    initialiseDials();
    initialiseButtons();
    initialiseLabels();

    setSize (456, 266);
    
    /**
     * This call will connect the controller and the parameters to register for change notifications
     */
    processor.getController().bindEditor (*this);

    startTimer (25);
}

PluginView::~PluginView()
{
    /**
     * And we need to remember to unbind those parameters once we are shutting down
     */
    processor.getController().unbindEditor (*this);
}

void PluginView::addControls()
{
    addAndMakeVisible (cutoff);
    addAndMakeVisible (resonance);
    addAndMakeVisible (drive);
    addAndMakeVisible (filterMode);
    addAndMakeVisible (distortionMode);
    addAndMakeVisible (distortionIsPreFilter);
    addAndMakeVisible (cutoffLabel);
    addAndMakeVisible (resonanceLabel);
    addAndMakeVisible (driveLabel);
    addAndMakeVisible (distortionPreFilterLabel);
    addAndMakeVisible (infoLabel);
}

void PluginView::initialiseDials()
{
    cutoff.setRange (   0.0f, 1.0f, 0.0f);
    resonance.setRange (0.0f, 1.0f, 0.0f);
    drive.setRange (    0.0f, 1.0f, 0.0f);
}

void PluginView::initialiseButtons()
{
    distortionIsPreFilter.setImages (true, false, true,
                                     ImageCache::getFromMemory (BinaryData::RadioButtonOff_png, BinaryData::RadioButtonOff_pngSize), 1.0f, Colours::transparentBlack,
                                     ImageCache::getFromMemory (BinaryData::RadioButtonOff_png, BinaryData::RadioButtonOff_pngSize), 1.0f, Colours::transparentBlack,
                                     ImageCache::getFromMemory (BinaryData::RadioButtonOn_png,  BinaryData::RadioButtonOn_pngSize),  1.0f, Colours::transparentBlack);
    distortionIsPreFilter.setClickingTogglesState (true);
}

void PluginView::initialiseLabels()
{
    cutoffLabel.setJustificationType (Justification::centred);
    resonanceLabel.setJustificationType (Justification::centred);
    driveLabel.setJustificationType (Justification::centred);
    distortionPreFilterLabel.setJustificationType (Justification::centredLeft);
    infoLabel.setJustificationType (Justification::centred);

    cutoffLabel.setColour (Label::ColourIds::textColourId, Colours::darkgrey);
    resonanceLabel.setColour (Label::ColourIds::textColourId, Colours::darkgrey);
    driveLabel.setColour (Label::ColourIds::textColourId, Colours::darkgrey);
    distortionPreFilterLabel.setColour (Label::ColourIds::textColourId, Colours::darkgrey);

    infoLabel.setColour (Label::ColourIds::backgroundColourId, findColour (ComboBox::backgroundColourId));
    infoLabel.setColour (Label::ColourIds::outlineColourId, findColour (ComboBox::outlineColourId));
    infoLabel.setColour (Label::ColourIds::textColourId, Colours::lightgrey);
}

void PluginView::paint (Graphics& g)
{
    g.fillAll (Colours::lightgrey.brighter());
}

void PluginView::resized()
{
    drive.setBounds (20, 20, 126, 126);
    cutoff.setBounds (drive.getRight() + 32, 20, 126, 126);
    resonance.setBounds (cutoff.getRight() + 32, 47, 72, 72);

    filterMode.setBounds (cutoff.getX(), cutoff.getBottom() + 20, cutoff.getWidth(), 20);
    distortionMode.setBounds (drive.getX(), drive.getBottom() + 20, drive.getWidth(), 20);

    distortionIsPreFilter.setBounds (distortionMode.getX(), distortionMode.getBottom() + 20, 25, 25);

	cutoffLabel.setBounds (cutoff.getX(), cutoff.getBottom() - 5, cutoff.getWidth(), 15);
    resonanceLabel.setBounds (resonance.getX(), resonance.getBottom() - 5, resonance.getWidth(), 15);
    driveLabel.setBounds (drive.getX(), drive.getBottom() - 5, drive.getWidth(), 15);
    distortionPreFilterLabel.setBounds (distortionIsPreFilter.getRight(), distortionIsPreFilter.getY(), 150, distortionIsPreFilter.getHeight());
    infoLabel.setBounds ((getWidth() / 2) - 100, getHeight() - 20, 200, 20);
}

void PluginView::timerCallback()
{
    /**
     * This is updating the tooltip panel - Notice again we have had some 'leakage' from the controller in to the editor 
     * there is a certain level of knowledge about the controller here...
     */
    String info;
    if (auto* component = getComponentUnderTheMouse())
    {
        if (component == &cutoff)
            info = processor.getController().getParameterInfo (Controller::Parameter::cutoff);

        if (component == &resonance)
            info = processor.getController().getParameterInfo (Controller::Parameter::resonance);

        if (component == &drive)
            info = processor.getController().getParameterInfo (Controller::Parameter::drive);

        if (component == &distortionIsPreFilter)
            info = processor.getController().getParameterInfo (Controller::Parameter::distortionIsPreFilter);

        if (component == &filterMode)
            info = processor.getController().getParameterInfo (Controller::Parameter::filterMode);

        if (component == &distortionMode)
            info = processor.getController().getParameterInfo (Controller::Parameter::distortionMode);
    }

    infoLabel.setText (info, NotificationType::dontSendNotification);
}

Component* PluginView::getComponentUnderTheMouse() const
{
    if (auto* component = Desktop::getInstance().getMainMouseSource().getComponentUnderMouse())
    {
        // This is needed because combo boxes are composed of multiple sub components...
        auto componentID = component->getComponentID();
        while (componentID.isEmpty() && component != nullptr)
        {
            component = component->getParentComponent();
            if (component != nullptr)
                componentID = component->getComponentID();
        }
        
        return component;
    }
    
    return nullptr;
}

