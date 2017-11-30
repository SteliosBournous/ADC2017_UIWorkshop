#include "TabbedPanel.h"
#include "FontPanel.h"
#include "VectorPanel.h"
#include "RasterPanel.h"
#include "PathDataPanel.h"
#include "DrawablesPanel.h"

TabbedPanel::TabbedPanel()
           : TabbedComponent (TabbedButtonBar::TabsAtTop)
{
    addTab ("Drawable", Colours::white, new DrawablesPanel, true);
    addTab ("Vector",   Colours::white, new VectorPanel,    true);
    addTab ("Path",     Colours::white, new PathDataPanel,  true);
    addTab ("Raster",   Colours::white, new RasterPanel,    true);
    addTab ("Fonts",    Colours::white, new FontPanel,      true);
}
