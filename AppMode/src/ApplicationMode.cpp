#include "../include/ApplicationMode.h"


ApplicationMode::ApplicationMode(GameSettings &settings, SoundManager &sound_manager, change_state_callback change_status_cb)
    : change_status_cb_(change_status_cb)
    , settings_(settings)
    , sound_manager_(sound_manager)
{

}

const sf::Font &ApplicationMode::getFont() const
{
    return settings_.getFont();
}

float ApplicationMode::getHeight() const
{
    return static_cast<float>(settings_.getScreenHeightParam().getValue());
}

float ApplicationMode::getWidth() const
{
    return static_cast<float>(settings_.getScreenWidthParam().getValue());
}

void ApplicationMode::tick()
{
    //empty realization
}
