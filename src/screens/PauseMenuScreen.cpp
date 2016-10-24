#include "screens/PauseMenuScreen.h"

PauseMenuScreen::PauseMenuScreen(const ConfigData &configuration, gui::IGUIEnvironment &guiEnvironment) :
    IGUIScreen(configuration, guiEnvironment) {}

PauseMenuScreen::~PauseMenuScreen()
{
    terminate();
}

void PauseMenuScreen::initialize(s32 buttonWidth, s32 buttonHeight)
{
    textScreenSize = guiEnvironment.addStaticText(L"SCREEN_SIZE",core::rect<s32>(10, 10, 200, 30));

    buttonResume = guiEnvironment.addButton(core::rect<s32>(0, 0, 0, 0));
    buttonResume->setID(ID_BUTTON_RESUME);

    buttonMenu = guiEnvironment.addButton(core::rect<s32>(0, 0, 0, 0));
    buttonMenu->setID(ID_BUTTON_MENU);

    buttonQuit = guiEnvironment.addButton(core::rect<s32>(0, 0, 0, 0));
    buttonQuit->setID(ID_BUTTON_QUIT);

    reload(buttonWidth, buttonHeight);
    resize(buttonWidth, buttonHeight);
}

void PauseMenuScreen::reload(s32 buttonWidth, s32 buttonHeight)
{
    buttonResume->setText(_wp("Resume"));
    buttonResume->setToolTipText(_wp("Resume game"));

    buttonMenu->setText(_wp("Menu"));
    buttonMenu->setToolTipText(_wp("Exit to main menu"));

    buttonQuit->setText(_wp("Quit"));
    buttonQuit->setToolTipText(_wp("Exit game"));
}

void PauseMenuScreen::terminate()
{
    textScreenSize->remove();
    buttonResume->remove();
    buttonMenu->remove();
    buttonQuit->remove();
}

void PauseMenuScreen::resize(s32 buttonWidth, s32 buttonHeight)
{
    buttonResume->setRelativePosition(core::rect<s32>(configuration.resolution.Width - buttonWidth - 2 * space,
                                                      configuration.resolution.Height - 3 * buttonHeight - 3 * space,
                                                      configuration.resolution.Width - 2 * space,
                                                      configuration.resolution.Height - 2 * buttonHeight - 3 * space));

    buttonMenu->setRelativePosition(core::rect<s32>(configuration.resolution.Width - buttonWidth - 2 * space,
                                                    configuration.resolution.Height - 2 * buttonHeight - 2 * space,
                                                    configuration.resolution.Width - 2 * space,
                                                    configuration.resolution.Height - buttonHeight - 2 * space));

    buttonQuit->setRelativePosition(core::rect<s32>(configuration.resolution.Width - buttonWidth - 2 * space,
                                                    configuration.resolution.Height - buttonHeight - space,
                                                    configuration.resolution.Width - 2 * space,
                                                    configuration.resolution.Height - space));
}

std::vector<gui::IGUIElement *> PauseMenuScreen::getSelectableElements()
{
    return { buttonResume, buttonMenu, buttonQuit };
}

void PauseMenuScreen::setVisible(bool visible)
{
    textScreenSize->setVisible(visible);
    buttonResume->setVisible(visible);
    buttonMenu->setVisible(visible);
    buttonQuit->setVisible(visible);
}
