// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/global_object.h"
#include "foundation/shared_object_factory.h"

namespace gs {

namespace audio { struct Mixer; }
namespace gpu { class Renderer; }

namespace core {

class IMovie;
class IPhysicSystem;
struct IFrameRenderer;

typedef SharedObjectFactory<IMovie> MovieFactory;
typedef SharedObjectFactory<IPhysicSystem> PhysicSystemFactory;
typedef SharedObjectFactory<audio::Mixer> MixerFactory;
typedef SharedObjectFactory<gpu::Renderer> RendererFactory;
typedef SharedObjectFactory<IFrameRenderer> FrameRendererFactory;

extern global_object<MovieFactory> g_movie_factory;
extern global_object<PhysicSystemFactory> g_physic_system_factory;
extern global_object<MixerFactory> g_mixer_factory;
extern global_object<RendererFactory> g_renderer_factory;
extern global_object<FrameRendererFactory> g_frame_renderer_factory;

} // core
} // gs
