// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/audio_data.h"
#include "engine/sound.h"
#include "foundation/cext.h"
#include "foundation/matrix4.h"
#include "foundation/task_system.h"
#include "foundation/timer.h"
#include "foundation/vector3.h"

namespace gs {
namespace audio {

enum MixerLoopMode : uint8_t { MixerNoLoop, MixerRepeat, MixerLoopInvalidChannel };
enum MixerPlayState : uint8_t { MixerStopped, MixerPlaying, MixerPaused, MixerStateInvalidChannel };

typedef int32_t MixerChannel;
typedef uint8_t MixerPriority;

struct MixerChannelState {
	MixerChannelState() = default;
	MixerChannelState(float volume_) : volume(volume_) {}
	MixerChannelState(MixerPriority priority_, float volume_ = 1, MixerLoopMode loop_mode_ = MixerNoLoop, float pitch_ = 1)
		: priority(priority_), volume(volume_), pitch(pitch_), loop_mode(loop_mode_) {}

	MixerPriority priority = 63;
	MixerLoopMode loop_mode = MixerNoLoop;

	float volume = 1;
	float pitch = 1;
};

struct MixerChannelLocation {
	MixerChannelLocation() = default;
	MixerChannelLocation(const Vector3 &p) : position(p) {}

	Vector3 position{0, 0, 0};
	Vector3 velocity{0, 0, 0};
};

/// Mixer interface
struct Mixer {
	static MixerChannelState DefaultState, RepeatState;
	static MixerChannelLocation DefaultLocation;

	static const MixerPriority DefaultPriority;
	static const MixerChannel ChannelError;

	Mixer();
	~Mixer();

	task_affinity GetWorkerAffinity() const { return worker_affinity; }
	void SetWorkerAffinity(task_affinity affinity) { worker_affinity = affinity; }

	virtual bool Open() = 0;
	virtual void Close() = 0;

	virtual float GetMasterVolume() = 0;
	virtual void SetMasterVolume(float volume = 1) = 0;

	virtual bool EnableSpatialization(bool enable) = 0;

	/// Play a sound, returns the channel on which the stream was started.
	virtual MixerChannel Start(Sound &sound, MixerChannelLocation location, MixerChannelState state) = 0;
	MixerChannel Start(Sound &sound, MixerChannelLocation location) { return Start(sound, location, DefaultState); }
	MixerChannel Start(Sound &sound, MixerChannelState state) { return Start(sound, DefaultLocation, state); }
	MixerChannel Start(Sound &sound) { return Start(sound, DefaultLocation, DefaultState); }
	/// Start a stream, returns the channel on which the str1eam was started.
	virtual MixerChannel StreamData(sAudioData data, MixerChannelLocation location, MixerChannelState state, bool paused = false) = 0;
	MixerChannel StreamData(sAudioData data, MixerChannelLocation location, bool paused = false) { return StreamData(data, location, DefaultState, paused); }
	MixerChannel StreamData(sAudioData data, MixerChannelState state, bool paused = false) { return StreamData(data, DefaultLocation, state, paused); }
	MixerChannel StreamData(sAudioData data, bool paused = false) { return StreamData(data, DefaultLocation, DefaultState, paused); }

	virtual MixerPlayState GetPlayState(MixerChannel channel) = 0;

	virtual MixerChannelState GetChannelState(MixerChannel channel) = 0;
	virtual void SetChannelState(MixerChannel channel, MixerChannelState state) = 0;

	virtual MixerChannelLocation GetChannelLocation(MixerChannel channel) = 0;
	virtual void SetChannelLocation(MixerChannel channel, MixerChannelLocation location) = 0;

	/// Return the channel timestamp in the currently played back media.
	virtual time_t GetChannelTimestamp(MixerChannel channel) = 0;

	virtual void Stop(MixerChannel channel) = 0;
	virtual void Pause(MixerChannel channel) = 0;
	virtual void Resume(MixerChannel channel) = 0;
	virtual void StopAll() = 0;

	virtual void SetStreamLoopPoint(MixerChannel channel, uint64_t t_ns) = 0;
	virtual void SeekStream(MixerChannel channel, uint64_t t_ns) = 0;
	/// Return the percentage of buffers available [0;100] for the stream running on a channel. Returns -1 if no stream is playing on the channel.
	virtual int GetStreamBufferingPercentage(MixerChannel channel) = 0;

	/// Set the transformation on a stream audio data.
	virtual void SetChannelStreamDataTransform(MixerChannel channel, const Matrix4 &transform) = 0;
	virtual void FlushChannelBuffers(MixerChannel channel) = 0;

	virtual Matrix4 GetListener() = 0;
	virtual void SetListener(const Matrix4 &transform) = 0;

	virtual sSound LoadSoundData(sAudioData data, const char *path = "") = 0;
	virtual void FreeSound(Sound &sound) = 0;

	/// Start streaming an audio file, returns the channel on which the stream was started.
	virtual MixerChannel Stream(const char *path, MixerChannelLocation location, MixerChannelState state, bool paused = false);
	MixerChannel Stream(const char *path, MixerChannelLocation location, bool paused = false) { return Stream(path, location, DefaultState, paused); }
	MixerChannel Stream(const char *path, MixerChannelState state, bool paused = false) { return Stream(path, DefaultLocation, state, paused); }
	MixerChannel Stream(const char *path, bool paused = false) { return Stream(path, DefaultLocation, DefaultState, paused); }
	/// Load a sound from an audio file.
	virtual sSound LoadSound(const char *path);

protected:
	task_affinity worker_affinity;
	timer_thread::handle update_timer;

	friend void PeriodicMixerUpdateCallback(Mixer *mixer);

	virtual void Update() = 0;
};

typedef std::shared_ptr<Mixer> sMixer;

/// Create a periodic timer task to call the specified mixer Update method.
timer_thread::handle StartMixerUpdateTimer(Mixer *);
/// Cancel a mixer Update periodic timer task.
void CancelMixerUpdateTimer(timer_thread::handle);

} // audio
} // gs
