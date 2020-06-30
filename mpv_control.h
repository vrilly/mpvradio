#ifndef MPV_CONTROL_H
#define MPV_CONTROL_H

#include <mpv/client.h>


class mpv_control
{
public:
    mpv_control();
    void play_url(const char *url);
    void update_track();
    void toggle_pause();
    void end();
    mpv_handle *handle;
    mpv_handle *client_handle;

    char *current_track;
    int paused;
};

#endif // MPV_CONTROL_H
