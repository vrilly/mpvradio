#include "mpvradio.h"

mpv_control::mpv_control()
{
    setlocale(LC_NUMERIC, "C");
    this->handle = mpv_create();
    if (!this->handle)
    {
        fprintf(stderr, "MPV Error!\n");
        exit(EXIT_FAILURE);
    }
    mpv_initialize(this->handle);
    this->current_track =
            mpv_get_property_string(this->handle, "track-list/0/title");
}

void mpv_control::play_url(const char *url)
{
    char cmd[256];

    sprintf(cmd, "loadfile %s", url);
    mpv_command_string(this->handle, cmd);
}

void mpv_control::update_track()
{
    mpv_free(this->current_track);
    this->current_track = mpv_get_property_string(this->handle, "media-title");
}

void mpv_control::end()
{

}
