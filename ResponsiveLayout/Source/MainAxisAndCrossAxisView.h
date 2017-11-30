/*
  ==============================================================================

    MainAxisAndCrossAxisView.h
    Created: 7 Nov 2017 8:48:39am
    Author:  Vlad Voina

  ==============================================================================
*/

#pragma once

class MainAxisAndCrossAxisView : public Component
{
public:
    static constexpr auto preferedSize = 40.f;
    
    MainAxisAndCrossAxisView()
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

// 1. previous example that doesn't look well when portrait because we are defining the width
//        box.items.addArray ({
//            FlexItem (cardVenus).withFlex (0, 1).withWidth (r.getHeight()),
//            FlexItem().withFlex (2, 0, Sizes::margin),
//            FlexItem (cardMars).withFlex (1, 1).withWidth (r.getHeight())
//                                               .withMaxWidth (r.getHeight() * 2),
//            FlexItem().withFlex (2, 0, Sizes::margin),
//            FlexItem (cardPluto).withFlex (0, 1, r.getHeight())
//        });
        
        box.performLayout (r);
    }
    
    CardComponent cardVenus { "Venus" },
                  cardMars  { "Mars" },
                  cardPluto { "Pluto" };
    
    void examples()
    {
        // 2. example with flex-basis (size along the main-axis)
        //        box.items.addArray ({
        //            FlexItem (cardVenus).withFlex (0, 1, r.getHeight()),
        //            FlexItem().withFlex (2, 0, Sizes::margin),
        //            FlexItem (cardMars).withFlex (1, 1, r.getHeight()).withMaxWidth (r.getHeight() * 2)
        //                                                              .withMaxHeight (r.getHeight() * 2),
        //            FlexItem().withFlex (2, 0, Sizes::margin),
        //            FlexItem (cardPluto).withFlex (0, 1, r.getHeight())
        //        });
        
        // 3. example that reacts well
        //        const auto itemSize = juce::jmin (r.getHeight(), r.getWidth());
        //        const bool isPortrait = r.getHeight() > r.getWidth();
        //
        //        box.flexDirection = isPortrait ? FlexBox::Direction::column : FlexBox::Direction::row;
        //        box.items.addArray ({
        //            FlexItem (cardVenus).withFlex (0, 1, itemSize),
        //            FlexItem().withFlex (2, 0, Sizes::margin),
        //            FlexItem (cardMars).withFlex (1, 1, itemSize).withMaxWidth (itemSize * 2)
        //                                                         .withMaxHeight (itemSize * 2),
        //            FlexItem().withFlex (2, 0, Sizes::margin),
        //            FlexItem (cardPluto).withFlex (0, 1, itemSize)
        //        });
    }
};
