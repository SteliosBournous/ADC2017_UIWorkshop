/*
  ==============================================================================

    ProportionalSizesView.h
    Created: 5 Nov 2017 9:07:47am
    Author:  Vlad Voina

  ==============================================================================
*/

#pragma once

class ProportionalSizesView  : public Component
{
public:
    static constexpr auto preferedHeight = 40.f;
    
    ProportionalSizesView()
    {
        addAndMakeVisible (cardVenus);
        addAndMakeVisible (cardMars);
        addAndMakeVisible (cardPluto);
    }
    
    void resized() override
    {
        auto r = getLocalBounds();
        
        FlexBox box;
        box.justifyContent = FlexBox::JustifyContent::spaceBetween;
        
        // 1.
        box.items.addArray ({
            FlexItem (cardVenus).withWidth (r.getHeight()),
            FlexItem (cardMars).withWidth (r.getHeight()),
            FlexItem (cardPluto).withWidth (r.getHeight())
        });
        
        box.performLayout (r);
    }
    
    CardComponent cardVenus { "Venus" },
                  cardMars  { "Mars" },
                  cardPluto { "Pluto" };
    
    void examples()
    {
        // 2. without space
        //        box.items.addArray ({
        //            FlexItem (cardVenus).withWidth (r.getHeight()),
        //            FlexItem (cardMars).withFlex (1, 1).withWidth (r.getHeight()),
        //            FlexItem (cardPluto).withWidth (r.getHeight())
        //        });
        
        // 3. with spacers
        //        box.items.addArray ({
        //            FlexItem (cardVenus).withFlex (0, 1).withWidth (r.getHeight()),
        //            FlexItem().withFlex (2, 0, Sizes::margin),
        //            FlexItem (cardMars).withFlex (1, 1).withWidth (r.getHeight()),
        //            FlexItem().withFlex (2, 0, Sizes::margin),
        //            FlexItem (cardPluto).withFlex (0, 1).withWidth (r.getHeight())
        //        });
        
        // 4. with max width
        //        box.items.addArray ({
        //            FlexItem (cardVenus).withFlex (0, 1).withWidth (r.getHeight()),
        //            FlexItem().withFlex (2, 0, Sizes::margin),
        //            FlexItem (cardMars).withFlex (1, 1).withWidth (r.getHeight())
        //                                               .withMaxWidth (r.getHeight() * 2),
        //            FlexItem().withFlex (2, 0, Sizes::margin),
        //            FlexItem (cardPluto).withFlex (0, 1, r.getHeight())
        //        });
    }
};
