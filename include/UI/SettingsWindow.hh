#ifndef SETTINGSWINDOW_HH_
#define SETTINGSWINDOW_HH_

#include "utils.hh"

class SettingsWindow
{
public:
    SettingsWindow();

    void update();
    void draw();

    bool _showSettings;
private:
    std::string ramDataSize;
    std::string ramAddrSize;
};

#endif /* !SETTINGSWINDOW_HH_ */