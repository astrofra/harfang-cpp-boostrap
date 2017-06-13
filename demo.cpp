// Chivas 2017

#include "engine/engine_factories.h"
#include "engine/engine_plugins.h"
#include "engine/native_api.h"
#include "engine/engine.h"
#include "foundation/filesystem.h"
#include "foundation/io_cfile.h"
#include "foundation/log.h"
#include "plus/plus.h"

using namespace gs;

//
#if HARFANG_PUBLISHED
void PublishedMain() {
	core::Init();
#else
int main(int argc, char *argv[]) {
	core::Init(argv[0]);
#endif
	SetDefaultLogOutputLevelMask(LogLevel::All);

#if HARFANG_PUBLISHED
	g_fs.get().Mount(NewAppDataDriver(), "@data/");
#else
	g_fs.get().Mount(std::make_shared<io::CFile>("C:/boulot/works/ChivasVR/source/executable/data"), "@data");
#endif

	//
	core::LoadPlugins();

	Plus plus;
	//plus.CreateWorkers();
	plus.AudioInit();
	plus.RenderInit(1280, 720, 8);

	// application loop
	core::ResetLastFrameDuration();

//	while (!plus.IsAppEnded(Plus::EndOnAny)) {
	while (true) {
		plus.UpdateClock();

		plus.GetRendererAsync()->FitViewportToOutputSurface();
		plus.Flip();

		plus.EndFrame();
	}

	plus.AudioUninit();
	plus.RenderUninit();

	core::Uninit();
}
