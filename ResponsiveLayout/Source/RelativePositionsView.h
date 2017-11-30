/*
  ==============================================================================

    AbsoluteVsRelativeView.h
    Created: 5 Nov 2017 7:35:25am
    Author:  Vlad Voina

  ==============================================================================
*/

#pragma once

class RelativePositionsView  : public Component
{
public:
    RelativePositionsView()
    {
        addAndMakeVisible (cardVenus);
        addAndMakeVisible (cardMars);
        addAndMakeVisible (cardPluto);
    }
    
    void resized() override
    {
        auto r = getLocalBounds();
        
        const auto cardSize = 40.f;
        
        
        // 1. setBounds example
        r = r.reduced (Sizes::margin);
        
        cardVenus.setBounds (r.getX(), r.getY(), cardSize, cardSize);
        cardMars.setBounds (Rectangle<int> (cardSize, cardSize).withCentre (Point<int> (r.getCentreX(), r.getY() + cardSize / 2)));
        cardPluto.setBounds (r.getRight() - cardSize, r.getY(), cardSize, cardSize);
    }
    
    CardComponent cardVenus { "Venus" },
                  cardMars { "Mars" },
                  cardPluto { "Pluto" };
    
    void examples()
    {
        // 2. FlexBox example
        //        FlexBox box;
        //        box.justifyContent = FlexBox::JustifyContent::spaceBetween;
        //        box.items.addArray ({
        //            FlexItem (cardVenus).withWidth (cardSize).withHeight (cardSize),
        //            FlexItem (cardMars).withWidth (cardSize).withHeight (cardSize),
        //            FlexItem (cardPluto).withWidth (cardSize).withHeight (cardSize)
        //        });
        //
        //        box.performLayout (r.reduced (Sizes::margin));
    }
};

