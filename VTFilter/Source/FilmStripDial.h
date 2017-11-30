#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class FilmStripDial : public Slider
{
public:

    FilmStripDial (const Image& dial, const Image& aSurround)
    : Slider (Slider::SliderStyle::RotaryVerticalDrag, Slider::TextEntryBoxPosition::NoTextBox )
    , filmStrip (dial)
    , surround (aSurround)
    , numberOfFrames (dial.getHeight() / dial.getWidth())
    {
        jassert (numberOfFrames != 0);
    }
    
    ~FilmStripDial() = default;

    void paint(Graphics& g) override
    {
        if (surround.isValid())
            g.drawImage (surround, 0, 0, getWidth(), getHeight(), 0, 0, surround.getWidth(), surround.getHeight());
        
        int value = roundToInt ((1.0f - getNormalisedValue()) * (numberOfFrames - 1));
        g.drawImage (filmStrip, 0, 0, getWidth(), getHeight(), 0, value * getFrameHeight(), getFrameWidth(), getFrameHeight());
    }

private:

    int getFrameWidth() const { return filmStrip.getWidth(); }
    int getFrameHeight() const { return filmStrip.getHeight() / numberOfFrames; }
    float getNormalisedValue() { return float ((getValue() - getMinimum()) / (getMaximum() - getMinimum())); }
    
    Image filmStrip;
    Image surround;
    int numberOfFrames;
};
