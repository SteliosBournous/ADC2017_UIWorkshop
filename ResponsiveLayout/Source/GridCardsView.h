/*
  ==============================================================================

    GridCardsView.h
    Created: 9 Nov 2017 10:46:22am
    Author:  Vlad Voina

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class GridCardsView : public Component
{
public:
    GridCardsView()
    {
        addNewCard ("Moon");
        addNewCard ("Earth");
        addNewCard ("Jupiter");
        addNewCard ("Pluto");
        addNewCard ("Mars");
        
        // only for 8 and 9
//        addNewCard ("Trappist-1");
//        addNewCard ("Cygni");
//        addNewCard ("Andromedae");
//        addNewCard ("Andromedaeeeeeeeeee");
//        addNewCard ("Kepler");
    }
    
    void resized() override
    {
        juce::Grid grid;
        
// 1.
        grid.templateColumns = { 1_fr, 1_fr, 1_fr };
        grid.templateRows    = { 1_fr,
                                 1_fr, };
        grid.setGap (20_px);

        grid.items.addArray ({
            GridItem (cards[0]).withRow ({ 1 }).withColumn ({ 1 }),
            GridItem (cards[1]).withRow ({ 1 }).withColumn ({ 2 }),
            GridItem (cards[2]).withRow ({ 1 }).withColumn ({ 3 }),
            GridItem (cards[3]).withRow ({ 2 }).withColumn ({ 1 }),
            GridItem (cards[4]).withRow ({ 2 }).withColumn ({ 2 })
        });

        grid.performLayout (getLocalBounds());

// 2.
//        grid.templateColumns = { 1_fr, 1_fr, 1_fr };
//        grid.templateRows    = { 1_fr,
//                                 1_fr, };
//        grid.setGap (20_px);
//        grid.autoFlow = Grid::AutoFlow::row;
//
//        for (auto* card : cards)
//            grid.items.add (GridItem (card));
//
//        grid.performLayout (getLocalBounds());
        
// 3.
//        grid.templateColumns = { 1_fr, 1_fr, 1_fr };
//        grid.autoRows = { 1_fr };
//        grid.setGap (20_px);
//
//        for (auto* card : cards)
//            grid.items.add (GridItem (card));
//
//        grid.performLayout (getLocalBounds());
        
        // ---- FlexBox ------
        
// 4.
//        auto r = getLocalBounds();
//
//        FlexBox flexBox;
//        flexBox.flexWrap = FlexBox::Wrap::wrap;
//
//        for (auto* card : cards)
//        {
//            card->setPadding (Sizes::margin / 2); // not actually the same since the gap is also on the outside
//            flexBox.items.add (FlexItem (*card).withWidth (r.proportionOfWidth (0.33f)));
//        }
//
//        flexBox.performLayout (getLocalBounds());
        
        
// 5.
//        grid.templateColumns = { 1_fr, 1_fr, 1_fr };
//        grid.autoRows = { 1_fr };
//        grid.setGap (20_px);
//
//        for (auto* card : cards)
//            grid.items.add (card->getText() == "Mars" ? GridItem (card).withColumn ({ GridItem::Span (2) })
//                                                      : GridItem (card));
//
//        grid.performLayout (getLocalBounds());
        
        
// 6.
//        auto r = getLocalBounds();
//
//        FlexBox flexBox;
//        flexBox.flexWrap = FlexBox::Wrap::wrap;
//
//        for (auto* card : cards)
//        {
//            card->setPadding (Sizes::margin / 2); // not actually the same since the gap is also on the outside
//            flexBox.items.add (FlexItem (*card).withWidth (r.proportionOfWidth (card->getText() == "Mars" ? 0.66f : 0.33f)));
//        }
//
//        flexBox.performLayout (getLocalBounds());
        
// 7.
//        grid.templateColumns = { 1_fr, 1_fr, 1_fr };
//        grid.autoRows = { 1_fr };
//        grid.setGap (20_px);
//
//        for (auto* card : cards)
//            grid.items.add (card->getText() == "Earth" ? GridItem (card).withRow ({ GridItem::Span (2) }) //.withColumn ({ GridItem::Span (2) })
//                                                       : GridItem (card));
//
//        grid.performLayout (getLocalBounds());
        
// 8. FlexBox is not inferrior
//        auto r = getLocalBounds();
//
//        FlexBox flexBox;
//        flexBox.flexWrap = FlexBox::Wrap::wrap;
//        flexBox.alignContent = FlexBox::AlignContent::flexStart;
//
//        for (auto* card : cards)
//        {
//            card->setPadding (Sizes::margin / 2); // not actually the same since the gap is also on the outside
//            flexBox.items.add (FlexItem (*card).withWidth (card->getDesiredWidth() + Sizes::margin)
//                                               .withHeight (card->getDesiredHeight() + Sizes::margin));
//        }
//
//        flexBox.performLayout (getLocalBounds());
        
// 9. interesting breakpoints
//        auto r = getLocalBounds();
//
//        //const auto maximumItemWidth = 100.f;
//        const auto numberOfColumns = (int)jmap (r.getWidth(), 200, 1500, 3, 6);
//
//        for (int i = 0; i < numberOfColumns; i++)
//            grid.templateColumns.add (Grid::TrackInfo (1_fr));
//
//        grid.autoRows = { 1_fr };
//        grid.setGap (20_px);
//
//        for (auto* card : cards)
//            grid.items.add (card->getText() == "Earth" ? GridItem (card).withRow ({ GridItem::Span (2) }) //.withColumn ({ GridItem::Span (2) })
//                                                       : GridItem (card));
//
//        grid.performLayout (getLocalBounds());
        
        
        // 10. Show images
        
    }
    
    void addNewCard (const String& text)
    {
        addAndMakeVisible (cards.add (new CardComponent (text, /* Show images */ false)));
    }
    
private:
    OwnedArray<CardComponent> cards;
};
