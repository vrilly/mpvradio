#include "mpvradio.h"

mpv_control::mpv_control()
{
    paused = 1;
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
    mpv_set_property_string(this->handle, "vid", "no");
}

void mpv_control::update_track()
{
    mpv_free(this->current_track);
    this->current_track = mpv_get_property_string(this->handle, "media-title");
}

void mpv_control::toggle_pause()
{
    mpv_get_property(handle, "pause", MPV_FORMAT_FLAG, &paused);
    if (paused)
    {
        paused = 0;
        mpv_set_property_string(handle, "pause", "no");
    }
    else
    {
        paused = 1;
        mpv_set_property_string(handle, "pause", "yes");
    }
}

void mpv_control::end()
{
    mpv_free(this->current_track);
    mpv_terminate_destroy(this->handle);
}
