/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainView.h"


//==============================================================================
MainView::MainView()
{
    addAndMakeVisible (background);
    
    addAndMakeVisible (relativePositionsView);
    addAndMakeVisible (proportionalSizesView);
    addAndMakeVisible (mainAxisAndCrossAxisView);
    addAndMakeVisible (gridCardsView);
    
    setSize (600, 400);
}

MainView::~MainView()
{
}

void MainView::paint (Graphics& g)
{
}

void MainView::resized()
{
    background.setBounds (getLocalBounds());
 
    auto r = getLocalBounds();
    
// 1. positions
    relativePositionsView.setBounds (r);
    
// 2. sizes
//    FlexBox box;
//    box.flexDirection = FlexBox::Direction::column;
//    box.items.addArray ({
//        FlexItem (proportionalSizesView).withFlex (0, 1, ProportionalSizesView::preferedHeight)
//                                        .withMargin (Sizes::margin),
//    });
//    box.performLayout (r);
    
    
// 3. dynamic axis
//    auto isPortrait = r.getHeight() > r.getWidth();
//
//    FlexBox box;
//    box.flexDirection = isPortrait ? FlexBox::Direction::column : FlexBox::Direction::row;
//
//    box.items.addArray ({
//        FlexItem (mainAxisAndCrossAxisView).withFlex (0, 1, MainAxisAndCrossAxisView::preferedSize)
//                                           .withMargin (Sizes::margin),
//    });
//
//    box.performLayout (r);
    
// 4. with cards
//    auto isPortrait = r.getHeight() > r.getWidth();
//
//    FlexBox box;
//    box.flexDirection = isPortrait ? FlexBox::Direction::column : FlexBox::Direction::row;
//
//    box.items.addArray ({
//        FlexItem (mainAxisAndCrossAxisView).withFlex (0, 1, MainAxisAndCrossAxisView::preferedSize)
//                                           .withMargin (Sizes::margin),
//        FlexItem (gridCardsView).withFlex (1)
//                                .withMargin (Sizes::margin)
//    });
//
//    box.performLayout (r);
}
