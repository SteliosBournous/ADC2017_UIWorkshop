/*
  ==============================================================================

    GradientComponent.h
    Created: 4 Nov 2017 8:50:18pm
    Author:  Vlad Voina

  ==============================================================================
*/

#pragma once

class GradientComponent  : public Component
{
public:
    GradientComponent(){}
    
private:
    void paint (Graphics& g) override
    {
        ColourGradient gradient { ColourPalette::red, 0, 0,
            ColourPalette::orange, 0, (float)getLocalBounds().getBottom(),
            false };
        
        g.setGradientFill (gradient);
        g.fillRect (getLocalBounds());
    }
};
