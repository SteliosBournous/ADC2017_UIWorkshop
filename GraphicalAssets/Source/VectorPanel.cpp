#include "VectorPanel.h"

VectorPanel::VectorPanel()
{
    
}

void VectorPanel::paint (Graphics& g)
{
    g.fillAll (Colours::white);

    auto innerBounds  = getLocalBounds().toFloat().reduced (30.0f, 10.0f);
    auto minDimension = std::min<float> (innerBounds.getWidth(), innerBounds.getHeight());
    auto logoBounds   = innerBounds.withSizeKeepingCentre (minDimension, minDimension).reduced (20.0f);
    
    paintJuceLogo (g, logoBounds);
}

void VectorPanel::paintJuceLogo (Graphics& g, Rectangle<float> logoBounds)
{
    static constexpr float circleInset  = 26.0f;
    static constexpr int numberOfWedges = 8;
    
    const auto innerBounds  = logoBounds.reduced (logoBounds.getWidth() / circleInset);
    const auto wedgeBounds  = innerBounds.reduced (innerBounds.getWidth() / circleInset);
    
    g.setColour (Colour(0xFF6CC04A));
    g.fillEllipse (logoBounds);
    
    g.setColour (Colours::white);
    g.fillEllipse (innerBounds);
    
    const Colour wedgeColours[numberOfWedges]
    {
        Colour (0xFFF5BD47),
        Colour (0xFFF0E049),
        Colour (0xFF9CB6D3),
        Colour (0xFF268DC1),
        Colour (0xFFA65A95),
        Colour (0xFFE73E51),
        Colour (0xFFE67E3C),
        Colour (0xFFF19F53),
    };
    
    const auto radiusX     = wedgeBounds.getWidth()  * 0.5f;
    const auto radiusY     = wedgeBounds.getHeight() * 0.5f;
    const auto innerRadius = (wedgeBounds.getWidth() * 0.09f) * 0.5f;
    const auto centre      = wedgeBounds.getCentre();
    
    for (int wedge = 0; wedge < numberOfWedges; ++wedge)
    {
        const auto degrees = float (wedge) * 45.0f;
        
        Path wedgePath;
        wedgePath.startNewSubPath (centre.getPointOnCircumference (radiusX, radiusY, degreesToRadians (degrees + 1.5f)));
        wedgePath.addArc (wedgeBounds.getX(), wedgeBounds.getY(), wedgeBounds.getWidth(), wedgeBounds.getHeight(), degreesToRadians (degrees + 1.5f), degreesToRadians (degrees + 45.0f - 3.0f));
        wedgePath.lineTo (centre.getPointOnCircumference (innerRadius, innerRadius, degreesToRadians (degrees + 22.5f)));
        wedgePath.closeSubPath();
        
        g.setColour (wedgeColours[wedge]);
        g.fillPath (wedgePath);
    }
}
