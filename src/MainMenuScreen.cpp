#include "MainMenuScreen.h"

using namespace irr;

MainMenuScreen::MainMenuScreen(const ConfigData &configuration, gui::IGUIEnvironment &guiEnvironment) :
    IGUIScreen(configuration, guiEnvironment) {}

MainMenuScreen::~MainMenuScreen()
{
    terminate();
}

void MainMenuScreen::initialize(s32 buttonWidth, s32 buttonHeight)
{
    textScreenSize = std::shared_ptr<gui::IGUIStaticText>
        (guiEnvironment.addStaticText(L"SCREEN_SIZE", core::rect<s32>(10, 10, 200, 30), false));

    buttonStart = std::shared_ptr<gui::IGUIButton>(guiEnvironment.addButton(core::rect<s32>(0, 0, 0, 0)));
    buttonStart->setID(ID_BUTTON_START);
    buttonStart->setText(_wp("Start"));
    buttonStart->setToolTipText(_wp("Start game"));

    buttonSettings = std::shared_ptr<gui::IGUIButton>(guiEnvironment.addButton(core::rect<s32>(0, 0, 0, 0)));
    buttonSettings->setID(ID_BUTTON_SETTINGS);
    buttonSettings->setText(_wp("Settings"));
    buttonSettings->setToolTipText(_wp("Game settings"));

    buttonQuit = std::shared_ptr<gui::IGUIButton>(guiEnvironment.addButton(core::rect<s32>(0, 0, 0, 0)));
    buttonQuit->setID(ID_BUTTON_QUIT);
    buttonQuit->setText(_wp("Quit"));
    buttonQuit->setToolTipText(_wp("Exit game"));

    resize(buttonWidth, buttonHeight);
}

void MainMenuScreen::terminate()
{
    textScreenSize->remove();
    textScreenSize.reset();

    buttonStart->remove();
    buttonStart.reset();

    buttonSettings->remove();
    buttonSettings.reset();

    buttonQuit->remove();
    buttonQuit.reset();
}

void MainMenuScreen::resize(s32 buttonWidth, s32 buttonHeight)
{
    buttonStart->setRelativePosition(core::rect<s32>(configuration.resolution.Width - buttonWidth - 2 * space,
                                                     configuration.resolution.Height - 3 * buttonHeight - 3 * space,
                                                     configuration.resolution.Width - 2 * space,
                                                     configuration.resolution.Height - 2 * buttonHeight - 3 * space));

    buttonSettings->setRelativePosition(core::rect<s32>(configuration.resolution.Width - buttonWidth - 2 * space,
                                                        configuration.resolution.Height - 2 * buttonHeight - 2 * space,
                                                        configuration.resolution.Width - 2 * space,
                                                        configuration.resolution.Height - buttonHeight - 2 * space));

    buttonQuit->setRelativePosition(core::rect<s32>(configuration.resolution.Width - buttonWidth - 2 * space,
                                                    configuration.resolution.Height - buttonHeight - space,
                                                    configuration.resolution.Width - 2 * space,
                                                    configuration.resolution.Height - space));
}

std::vector<std::weak_ptr<gui::IGUIElement>> MainMenuScreen::getSelectableElements()
{
    return { buttonStart, buttonSettings, buttonQuit };
}

void MainMenuScreen::setVisible(bool visible)
{
    textScreenSize->setVisible(visible);
    buttonStart->setVisible(visible);
    buttonSettings->setVisible(visible);
    buttonQuit->setVisible(visible);
}