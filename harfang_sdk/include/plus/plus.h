// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/mixer_async.h"
#include "engine/raster_font.h"
#include "engine/render_system_async.h"
#include "engine/renderer_async.h"
#include "engine/scene.h"
#include "engine/simple_graphic_engine.h"
#include "foundation/global_object.h"
#include "platform/input_device.h"

namespace gs {

struct RenderWindow {
	Window window;
	Surface surface;
};

/// High-level API
class Plus {
	gpu::sRenderer renderer;
	gpu::sRendererAsync renderer_async;

	render::sRenderSystem render_system;
	render::sRenderSystemAsync render_system_async;

	render::SimpleGraphicEngine graphic_engine_2d;
	render::SimpleGraphicEngine graphic_engine_3d;

	bool hack_vsync_off = false;

public:
	Plus();
	~Plus();

	/// Start the worker pool.
	void CreateWorkers();
	/// Stop the worker pool.
	void DeleteWorkers();

	/// Mount a path on the global file system.
	void MountFilePath(const char *path);

	const gpu::sRenderer &GetRenderer() const { return renderer; }
	const gpu::sRendererAsync &GetRendererAsync() const { return renderer_async; }

	const render::sRenderSystem &GetRenderSystem() const { return render_system; }
	const render::sRenderSystemAsync &GetRenderSystemAsync() const { return render_system_async; }

	enum AppEndCondition { EndOnEscapePressed = 0x1,
		EndOnDefaultWindowClosed = 0x2,
		EndOnAny = 0xffff };

	/// Test if the application has ended.
	bool IsAppEnded(AppEndCondition flag = EndOnAny) const;
	/*!
	Render
	@{
*/
private:
	RenderWindow default_window;
	bool is_default_window_open = false;

	void OnCloseWindow(const Window &window);
	Signal<void(const Window &)>::Connection close_window_connection;

	bool origin_2d_is_top_left = false;

	void Apply3D();

	bool RenderInit_CreateRenderObjects(bool debug);
	bool RenderInit_EndInit(const char *core_path, int aa);

	int width = 0, height = 0;

public:
	/// Initialize the rendering engine.
	bool RenderInit(int width, int height, int aa = 1, Window::Visibility visibility = Window::Windowed, bool debug = false);
	bool RenderInit(int width, int height, const char *core_path, int aa = 1, Window::Visibility visibility = Window::Windowed, bool debug = false);
	/// Shutdown the rendering engine.
	void RenderUninit();

	/// Create a new output window.
	RenderWindow NewRenderWindow(int width, int height, Window::Visibility visibility = Window::Windowed);
	/// Delete output window.
	void FreeRenderWindow(RenderWindow &window);
	/// Set current output window.
	void SetRenderWindow(const RenderWindow &window);
	/// Update a render window.
	void UpdateRenderWindow(const RenderWindow &window);

	/// Initialize the rendering engine from externally created objects.
	void InitExtern(gpu::sRenderer renderer, gpu::sRendererAsync renderer_async, render::sRenderSystem render_system, render::sRenderSystemAsync render_system_async);
	/// Shutdown the rendering engine when initialized from externally created objects.
	void UninitExtern();

	/// Select between a top-left or bottom-left origin for 2D drawing.
	void Set2DOriginIsTopLeft(bool top_left) { origin_2d_is_top_left = top_left; }

	/// Commit all 2D calls.
	void Commit2D();
	/// Commit all 3D calls.
	void Commit3D();

	/// Return the system screen width.
	int GetScreenWidth() const { return width; }
	/// Return the system screen height.
	int GetScreenHeight() const { return height; }

	/// Draw and display frame.
	void Flip();

	/// Signal end of frame.
	void EndFrame();

	/// Set the 2D blend mode.
	void SetBlend2D(render::BlendMode mode) { graphic_engine_2d.SetBlendMode(mode); }
	/// Get the 2D blend mode.
	render::BlendMode GetBlend2D() const { return graphic_engine_2d.GetBlendMode(); }
	/// Set the 2D cull mode.
	void SetCulling2D(render::CullMode mode) { graphic_engine_2d.SetCullMode(mode); }
	/// Set the 2D cull mode.
	render::CullMode GetCulling2D() const { return graphic_engine_2d.GetCullMode(); }

	/// Set the current 3D blend mode.
	void SetBlend3D(render::BlendMode mode) { graphic_engine_3d.SetBlendMode(mode); }
	/// Get the current 3D blend mode.
	render::BlendMode GetBlend3D() const { return graphic_engine_3d.GetBlendMode(); }
	/// Set the 3D cull mode.
	void SetCulling3D(render::CullMode mode) { graphic_engine_3d.SetCullMode(mode); }
	/// Set the 3D cull mode.
	render::CullMode GetCulling3D() const { return graphic_engine_3d.GetCullMode(); }

	/// Enable/disable depth testing 2D.
	void SetDepthTest2D(bool enable) { graphic_engine_2d.SetDepthTest(enable); }
	/// Return the 2D depth test state.
	bool GetDepthTest2D() const { return graphic_engine_2d.GetDepthTest(); }
	/// Enable/disable depth writing in 2D.
	void SetDepthWrite2D(bool enable) { graphic_engine_2d.SetDepthWrite(enable); }
	/// Return the 2D depth writing state.
	bool GetDepthWrite2D() const { return graphic_engine_2d.GetDepthWrite(); }

	/// Enable/disable depth testing 3D.
	void SetDepthTest3D(bool enable) { graphic_engine_3d.SetDepthTest(enable); }
	/// Return the 3D depth test state.
	bool GetDepthTest3D() const { return graphic_engine_3d.GetDepthTest(); }
	/// Enable/disable depth writing in 3D.
	void SetDepthWrite3D(bool enable) { graphic_engine_3d.SetDepthWrite(enable); }
	/// Return the 3D depth writing state.
	bool GetDepthWrite3D() const { return graphic_engine_3d.GetDepthWrite(); }

	/// Clear.
	void Clear(Color color = Color::Black);

	/// Draw a 2D point.
	void Plot2D(float x, float y, Color color = Color::White) { graphic_engine_2d.Line(x, y, 0, x + 1, y + 1, 0, color, color); }
	/// Draw a 2D line.
	void Line2D(float sx, float sy, float ex, float ey, Color start_color = Color::White, Color end_color = Color::White) { graphic_engine_2d.Line(sx, sy, 0, ex, ey, 0, start_color, end_color); }
	/// Draw a 2D triangle.
	void Triangle2D(float ax, float ay, float bx, float by, float cx, float cy, Color a_color = Color::White, Color b_color = Color::White, Color c_color = Color::White) { graphic_engine_2d.Triangle(ax, ay, 0, bx, by, 0, cx, cy, 0, a_color, b_color, c_color); }
	/// Draw a 2D quad.
	void Quad2D(float ax, float ay, float bx, float by, float cx, float cy, float dx, float dy, Color a_color = Color::White, Color b_color = Color::White, Color c_color = Color::White, Color d_color = Color::White, gpu::sTexture tex = nullptr, float uv_sx = 0, float uv_sy = 0, float uv_ex = 1, float uv_ey = 1) { graphic_engine_2d.Quad(ax, ay, 0, bx, by, 0, cx, cy, 0, dx, dy, 0, uv_sx, uv_sy, uv_ex, uv_ey, tex, a_color, b_color, c_color, d_color); }

	/// Draw a 3D line.
	void Line3D(float sx, float sy, float sz, float ex, float ey, float ez, Color start_color = Color::White, Color end_color = Color::White) { graphic_engine_3d.Line(sx, sy, sz, ex, ey, ez, start_color, end_color); }
	/// Draw a 3D triangle.
	void Triangle3D(float ax, float ay, float az, float bx, float by, float bz, float cx, float cy, float cz, Color a_color = Color::White, Color b_color = Color::White, Color c_color = Color::White) { graphic_engine_3d.Triangle(ax, ay, az, bx, by, bz, cx, cy, cz, a_color, b_color, c_color); }
	/// Draw a 3D quad.
	void Quad3D(float ax, float ay, float az, float bx, float by, float bz, float cx, float cy, float cz, float dx, float dy, float dz, Color a_color = Color::White, Color b_color = Color::White, Color c_color = Color::White, Color d_color = Color::White, gpu::sTexture tex = nullptr, float uv_sx = 0, float uv_sy = 0, float uv_ex = 1, float uv_ey = 1) { graphic_engine_3d.Quad(ax, ay, az, bx, by, bz, cx, cy, cz, dx, dy, dz, uv_sx, uv_sy, uv_ex, uv_ey, tex, a_color, b_color, c_color, d_color); }

private:
	std::string current_font_path = "@core/fonts/default.ttf";

	std::map<std::string, render::sRasterFont> fonts;

	render::sRasterFont CacheFont(std::string path, float size);

	struct TextRenderState {
		render::BlendMode blend_mode;
		bool depth_test;
	};

	TextRenderState ValidateTextRenderState(render::SimpleGraphicEngine &engine);
	void RestoreRenderState(render::SimpleGraphicEngine &engine, const TextRenderState &state);

public:
	/// Set the current font path.
	void SetFont(const char *path) { current_font_path = path; }
	/// Get the current font path.
	const char *GetFont() const { return current_font_path.c_str(); }

	/// Draw 2D text.
	void Text2D(float x, float y, const char *text, float size = 16, Color color = Color::White, const char *font_path = "");
	/// Draw 3D text.
	void Text3D(float x, float y, float z, const char *text, float size = 16, Color color = Color::White, const char *font_path = "");

	/// Draw a sprite.
	void Sprite2D(float x, float y, float size, const char *image_path, Color color = Color::White, float pivot_x = 0.5, float pivot_y = 0.5, bool flip_h = false, bool flip_v = false);
	/// Draw an image.
	void Image2D(float x, float y, float scale, const char *image_path, Color color = Color::White);
	/// Draw an image rect.
	void Blit2D(float src_x, float src_y, float src_w, float src_h, float dst_x, float dst_y, float dst_w, float dst_h, const char *image_path, Color color = Color::White);
	/// Draw a texture.
	void Texture2D(float x, float y, float scale, const gpu::sTexture &tex, Color color = Color::White, bool flip_h = false, bool flip_v = false);

	/// Load a texture from its path.
	gpu::sTexture LoadTexture(const char *path);
	/// Load a render material from its path.
	render::sMaterial LoadMaterial(const char *path);
	/// Load a render geometry from its path.
	render::sGeometry LoadGeometry(const char *path);
	/// Create a render geometry from a core geometry.
	render::sGeometry CreateGeometry(const core::sGeometry &core_geo, bool use_cache = true);

	/// Draw a geometry in 2D.
	void Geometry2D(float x, float y, render::sGeometry geo, float angle_x = 0, float angle_y = 0, float angle_z = 0, float scale = 1);
	/// Draw a geometry in 3D.
	void Geometry3D(float x, float y, float z, render::sGeometry geo, float angle_x = 0, float angle_y = 0, float angle_z = 0, float scale = 1);

private:
	struct Camera3DState {
		Matrix4 view;
		Matrix44 projection;
	};

	Camera3DState camera3d_state;

public:
	/// Set the render system 3D camera properties.
	void SetCamera3D(float x, float y, float z, float angle_x = 0, float angle_y = 0, float angle_z = 0, float fov = 60, float znear = 0.1, float zfar = 1000);
	void SetCamera3D(const Matrix4 &view, const Matrix44 &projection);

	Matrix4 GetCamera3DMatrix() const { return camera3d_state.view; }
	Matrix44 GetCamera3DProjectionMatrix() const { return camera3d_state.projection; }
/// @}

/*!
	Audio
	@{
*/
private:
	audio::sMixer mixer;
	audio::sMixerAsync mixer_async;

public:
	/// Initialize the audio engine.
	bool AudioInit();
	/// Uninitialize the audio engine.
	void AudioUninit();

	/// Return the mixer.
	const audio::sMixer &GetMixer() const { return mixer; }
	/// Return the asynchronous mixer.
	const audio::sMixerAsync &GetMixerAsync() const { return mixer_async; }
/// @}

/*!
	Input
	@{
*/
public:
	/// Return the mouse input device.
	sInputDevice GetMouse() const;
	/// Return the keyboard input device.
	sInputDevice GetKeyboard() const;

	/// Return the mouse position.
	void GetMousePos(float &x, float &y) const;
	/// Return the mouse position change since last update.
	void GetMouseDt(float &x, float &y) const;

	/// Return True if the mouse button is down.
	bool MouseButtonDown(InputDevice::ButtonCode btn = InputDevice::Button0) const;
	/// Return True if a key is down.
	bool KeyDown(InputDevice::KeyCode key) const;
	/// Return True if a key was pressed.
	bool KeyPress(InputDevice::KeyCode key) const;
	/// Return True if a key was released.
	bool KeyReleased(InputDevice::KeyCode key) const;
/// @}

/*!
	Clock
	@{
*/
private:
	Clock clock;

public:
	/// Reset the elapsed time counter.
	void ResetClock();
	/// Update clock and return the elapsed time since last update in second.
	time_t UpdateClock();

	/// Return elapsed time since last update in second.
	time_t GetClockDt() const;
	/// Return the total elapsed time since the object creation or the last call to Reset.
	time_t GetClock() const;
/// @}

/*!
	Geometry
	@{
*/
private:
	std::string default_material_path = "@core/materials/default.mat";

public:
	/// Create a capsule geometry.
	core::sGeometry CreateCapsule(float radius = 0.5f, float height = 2, int subdiv_x = 6, int subdiv_y = 16, const char *material_path = nullptr, const char *name = nullptr);
	/// Create a cone geometry.
	core::sGeometry CreateCone(float radius = 0.5f, float height = 1, int subdiv_x = 16, const char *material_path = nullptr, const char *name = nullptr);
	/// Create a cube geometry.
	core::sGeometry CreateCube(float width = 1, float height = 1, float length = 1, const char *material_path = nullptr, const char *name = nullptr);
	/// Create a cylinder geometry.
	core::sGeometry CreateCylinder(float radius = 0.5f, float height = 1, int subdiv_x = 16, const char *material_path = nullptr, const char *name = nullptr);
	/// Create a plane geometry.
	core::sGeometry CreatePlane(float width = 1, float length = 1, int subdiv = 1, const char *material_path = nullptr, const char *name = nullptr);
	/// Create a sphere geometry.
	core::sGeometry CreateSphere(float radius = 0.5f, int subdiv_x = 6, int subdiv_y = 16, const char *material_path = nullptr, const char *name = nullptr);
	/// Create a geometry from heightmap.
	core::sGeometry CreateGeometryFromHeightmap(uint width, uint height, const std::vector<float> &heightmap, float scale = 1, const char *_material_path = nullptr, const char *_name = nullptr);
/// @}

/*!
	Scene
	@{
*/
	/// Create a new scene.
	core::sScene NewScene(bool use_physics = true, bool use_lua = true);
	/// Update scene.
	void UpdateScene(core::Scene &scene, time_t dt);
	void UpdateScene(core::Scene &scene);

	/// Create a new dummy node and add it to a scene.
	core::sNode AddDummy(core::Scene &scene, Matrix4 mat = Matrix4::Identity);
	/// Create a new camera node and add it to a scene.
	core::sNode AddCamera(core::Scene &scene, Matrix4 mat = Matrix4::Identity, bool orthographic = false, bool set_as_current = true);
	/// Create a new light node and add it to a scene.
	core::sNode AddLight(core::Scene &scene, Matrix4 mat = Matrix4::Identity, core::Light::Model model = core::Light::Model_Point, float range = 0.f, bool shadow = true, Color diffuse = Color(0.8f, 0.8f, 0.8f), Color specular = Color(0.5f, 0.5f, 0.5f));
	/// Create a new object node and add it to a scene.
	core::sNode AddObject(core::Scene &scene, render::sGeometry geo, Matrix4 mat = Matrix4::Identity);
	/// Create a new object node and add it to a scene.
	core::sNode AddGeometry(core::Scene &scene, const char *geo_name, Matrix4 mat = Matrix4::Identity);
	/// Create a new plane node and add it to a scene.
	core::sNode AddPlane(core::Scene &scene, Matrix4 mat = Matrix4::Identity, float width = 1000.f, float depth = 1000.f, const char *material_path = nullptr);
	/// Create a new cube node and add it to a scene.
	core::sNode AddCube(core::Scene &scene, Matrix4 mat = Matrix4::Identity, float width = 1.f, float height = 1.f, float depth = 1.f, const char *material_path = nullptr);
	/// Create a new sphere node and add it to a scene.
	core::sNode AddSphere(core::Scene &scene, Matrix4 mat = Matrix4::Identity, float radius = 0.5f, int subdiv_x = 6, int subdiv_y = 16, const char *material_path = nullptr);
	/// Create a new geometry node from an heightmap and add it to a scene.
	core::sNode AddGeometryFromHeightmap(core::Scene &scene, Matrix4 mat, int width, int height, const std::vector<float> &heightmap, float scale = 1.0f, const char *_material_path = nullptr);
	/// Create a new environment component and add it to a scene.
	std::shared_ptr<core::Environment> AddEnvironment(core::Scene &scene, Color bg_color = Color::Black, Color ambient_color = Color::Black, Color fog_color = Color::Black, float fog_near = 0.f, float fog_far = 0.f);
	/// Create a new cube node, configure its physic attributes, and add it to a scene.
	core::sNode AddPhysicCube(core::sComponent &rigid_body, core::Scene &scene, Matrix4 mat = Matrix4::Identity, float width = 1.f, float height = 1.f, float depth = 1.f, float mass = 1.f, const char *material_path = nullptr);
	/// Create a new plane node, configure its physic attributes, and add it to a scene.
	core::sNode AddPhysicPlane(core::sComponent &rigid_body, core::Scene &scene, Matrix4 mat = Matrix4::Identity, float width = 1000.f, float length = 1000.f, float mass = 0.f, const char *material_path = nullptr);
	/// Create a new sphere node, configure its physic attributes, and add it to a scene.
	core::sNode AddPhysicSphere(core::sComponent &rigid_body, core::Scene &scene, Matrix4 mat = Matrix4::Identity, float radius = 0.5f, int subdiv_x = 6, int subdiv_y = 16, float mass = 1.f, const char *material_path = nullptr);
/// @}
};

//
class OrbitalController {
public:
	void ApplyToNode(core::Node &node);

	void Update(time_t dt);
	void UpdateAndApplyToNode(core::Node &node, time_t dt);

private:
	Vector3 tgt;
	Matrix3 rot;
	float d = 10;

	float k_orbit_speed = 1.5f;
	float k_wheel = 20.f;
};

class FPSController {
public:
	FPSController(float x = 0, float y = 0, float z = 0, float _speed = 10, float _turbo = 4) : pos(x, y, z), rot(0, 0, 0), speed(_speed), turbo(_turbo), raw_pos(pos), raw_rot(rot), smooth_pos(1), smooth_rot(1) {}

	void Reset(Vector3 _pos, Vector3 _rot) {
		pos = raw_pos = _pos;
		rot = raw_rot = _rot;
	}

	void SetSmoothFactor(float k_pos, float k_rot);

	void ApplyToNode(core::Node &node);

	void Update(time_t dt);
	void UpdateAndApplyToNode(core::Node &node, time_t dt);

	Vector3 GetPos() const { return pos; }
	Vector3 GetRot() const { return rot; }

	void SetPos(const Vector3 &v) { raw_pos = pos = v; }
	void SetRot(const Vector3 &v) { raw_rot = rot = v; }

	float GetSpeed() const { return speed; }
	void SetSpeed(float s) { speed = s; }
	float GetTurbo() const { return turbo; }
	void SetTurbo(float t) { turbo = t; }

private:
	Vector3 pos, rot;
	Vector3 raw_pos, raw_rot;

	float speed, turbo;
	float smooth_pos, smooth_rot;
};

} // gs
