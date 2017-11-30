#include "MainWindow.h"
#include "MainContentComponent.h"

MainWindow::MainWindow (String name)
          : DocumentWindow (name, Colours::lightgrey, DocumentWindow::allButtons)
{
    setUsingNativeTitleBar (true);
    setContentOwned (new MainContentComponent(), true);
    
    setResizable (true, false);
    setResizeLimits (500, 500, std::numeric_limits<int>::max(), std::numeric_limits<int>::max());
    
    centreWithSize (getWidth(), getHeight());
    setVisible (true);
}

void MainWindow::closeButtonPressed()
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}
