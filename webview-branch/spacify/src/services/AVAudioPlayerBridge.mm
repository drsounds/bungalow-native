/// AVAudioPlayerBridge.mm
/// Thin Objective-C++ wrapper around AVAudioPlayer, exposed as plain C
/// functions so that the pure-C++ LocalMediaService can call them.

#import <AVFoundation/AVFoundation.h>
#include <string>

// ── Global player state ───────────────────────────────────────────────────────

static AVAudioPlayer* g_player = nil;

// ── C bridge ─────────────────────────────────────────────────────────────────

extern "C" {

/// Load a local file path (not a URI — caller strips "file://").
/// Returns true on success.
bool sp_audio_load(const char* path) {
    @autoreleasepool {
        if (!path || path[0] == '\0') return false;

        NSString* nsPath = [NSString stringWithUTF8String:path];
        NSURL*    url    = [NSURL fileURLWithPath:nsPath];

        NSError* err = nil;
        AVAudioPlayer* player = [[AVAudioPlayer alloc] initWithContentsOfURL:url
                                                                       error:&err];
        if (err || !player) {
            NSLog(@"[AVAudioPlayerBridge] load failed: %@", err.localizedDescription);
            g_player = nil;
            return false;
        }

        [player prepareToPlay];
        g_player = player;
        return true;
    }
}

void sp_audio_play() {
    [g_player play];
}

void sp_audio_pause() {
    [g_player pause];
}

void sp_audio_stop() {
    if (!g_player) return;
    [g_player stop];
    g_player.currentTime = 0.0;
}

/// @param seconds  Seek target in seconds.
void sp_audio_seek(double seconds) {
    if (!g_player) return;
    if (seconds < 0.0) seconds = 0.0;
    if (seconds > g_player.duration) seconds = g_player.duration;
    g_player.currentTime = seconds;
}

/// Returns total duration in seconds, or 0.0 if no player.
double sp_audio_get_duration() {
    return g_player ? g_player.duration : 0.0;
}

/// Returns current playback position in seconds, or 0.0 if no player.
double sp_audio_get_position() {
    return g_player ? g_player.currentTime : 0.0;
}

/// Returns true if the player is currently playing.
bool sp_audio_is_playing() {
    return g_player && g_player.isPlaying;
}

} // extern "C"