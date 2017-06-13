// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/node.h"
#include "engine/group.h"
#include "engine/octree_renderable.h"
#include "engine/scene_system.h"
#include "engine/simple_list_renderable.h"
#include "engine/render_system.h"
#include "engine/script_system.h"
#include "engine/scene_reflection.h"
#include "foundation/type_to_document.h"

namespace gs {
namespace core {

struct SceneSerializationState : SerializationState {
	SceneSerializationState(IDocumentWriter *d = nullptr, Scene *s = nullptr, SerializationContext *c = nullptr) : SerializationState(d, c), scene(s) {}
	Scene *scene;
};

struct SceneDeserializationState : DeserializationState {
	SceneDeserializationState(const IDocumentReader *d = nullptr, Scene *s = nullptr, DeserializationContext *c = nullptr) : DeserializationState(d, c), scene(s) {}
	Scene *scene;
};

//
class Scene : public std::enable_shared_from_this<Scene> {
public:
	enum Phase { PhaseNone, PhaseUpdate, PhaseWaitUpdate, PhaseCommit, PhaseWaitCommit };

	Scene();
	virtual ~Scene();

	/// Return the current camera node.
	const sNode &GetCurrentCamera() const { return current_camera; }
	/// Set a node as the current camera.
	void SetCurrentCamera(sNode node);

	/// Add a group to the scene.
	sGroup AddGroup(sGroup group);
	/// Remove a group from the scene.
	void RemoveGroup(const sGroup &group);

	/// Find a group in the scene.
	sGroup FindGroup(const char *name) const;

	/// Return a list of all groups containing a reference to a specific node.
	std::vector<sGroup> GetNodeGroupList(const sNode &node) const;
	/// Remove a node from all scene groups.
	void UnregisterNodeFromGroups(const sNode &node) const;

	/// Return a list of all groups in the scene.
	const std::vector<sGroup> &GetGroups() const { return groups; }

	/// Activate all group members.
	void GroupMembersSetActive(const Group &group, bool active = true);
	/// Delete a group and its members from the scene.
	void DeleteGroupAndMembers(const sGroup &group);

	/// Clear the scene from all its components, groups and nodes.
	void Clear();
	/// Clear, commit and wait for commit.
	void Dispose();
	/// Return true if all scene components and nodes are ready.
	bool IsReady() const;

	/// Add a system to the scene.
	sSceneSystem AddSystem(sSceneSystem system);
	/// Return the first scene system with the specified name.
	sSceneSystem GetSystem(const char *name) const;

	template <class T> std::shared_ptr<T> GetSystem() const {
		auto i = std::find_if(systems.begin(), systems.end(), [](const sSceneSystem &s) {
			static auto type = g_type_registry.get().GetType<T>();
			return s->GetConcreteType() == type;
		});
		return i != systems.end() ? std::static_pointer_cast<T>(*i) : nullptr;
	}

	/// Return all scene systems.
	const std::vector<sSceneSystem> &GetSystems() const { return systems; }

	/// Add a node to the scene.
	void AddNode(sNode node);
	/// Remove a node from the scene.
	void RemoveNode(const sNode &node);

	/// Add a component to the scene systems.
	void AddComponentToSystems(sComponent component);
	/// Remove a component from the scene systems.
	void RemoveComponentFromSystems(const sComponent &component);

	/// Return a node from its unique identifier.
	sNode GetNode(uint uid) const;
	/// Return a  node from its name and parent.
	sNode GetNode(const char *name) const;
	sNode GetNode(const char *name, const sNode &parent) const;

	/// Return a list of all nodes in the scene.
	const std::vector<sNode> &GetNodes() const { return nodes; }
	/// Return a list of all child nodes of a node.
	std::vector<sNode> GetNodeChildren(const Node &node) const;
	/// Return a list of nodes filtered by their name.
	std::vector<sNode> GetNodes(const char *filter) const;

	/// Return a list of nodes with components implementing a specific aspect.
	std::vector<sNode> GetNodesWithAspect(const char *aspect) const;

	/// Update the scene.
	void Update();
	virtual void Update(time_t dt);
	/// Wait for the scene update to complete. Returns true when the scene update has completed.
	virtual bool WaitUpdate(bool blocking = true);

	/// Commit all scene writes.
	virtual void Commit();
	/// Wait for the scene commit to complete. Returns true when the scene commit has completed.
	virtual bool WaitCommit(bool blocking = true);

	/// Helper function to update and commit the scene, uses blocking waits.
	void UpdateAndCommitWaitAll(time_t dt = 0);

	/// Return the scene serialization signal.
	const Signal<void(SceneSerializationState &)> &GetSerializationSignal() const { return serialization_signal; }
	Signal<void(SceneSerializationState &)> &GetSerializationSignal() { return serialization_signal; }

	/// Return the scene deserialization signal.
	const Signal<void(SceneDeserializationState &)> &GetDeserializationSignal() const { return deserialization_signal; }
	Signal<void(SceneDeserializationState &)> &GetDeserializationSignal() { return deserialization_signal; }

	/// Add aspect to scene.
	sComponent AddComponent(sComponent component, int index = -1);
	/// Remove component from scene.
	void RemoveComponent(const sComponent &component);

	/// Return a list of all components in the scene.
	const std::vector<sComponent> &GetComponents() const { return components; }
	/// Return all components implementing a given aspect.
	std::vector<sComponent> GetComponents(const char *aspect) const;

	/// Return the first scene component implementing a specific aspect.
	sComponent GetComponent(const char *aspect) const {
		auto i = std::find_if(components.begin(), components.end(), [aspect](const sComponent &c) { return c->GetAspect() == aspect; });
		return i != components.end() ? *i : nullptr;
	}

	/// Return the first scene component of a specific type.
	template <class T> std::shared_ptr<T> GetComponent() const {
		auto i = std::find_if(components.begin(), components.end(), [](const sComponent &c) {
			static auto type = g_type_registry.get().GetType<T>();
			return c->GetConcreteType() == type;
		});
		return i != components.end() ? std::static_pointer_cast<T>(*i) : nullptr;
	}

	/// Return true if the scene has a component implementing the specified aspect.
	bool HasAspect(const char *aspect) const;

	/// Return the scene (approximate) bounding box.
	MinMax GetMinMax() const;

	call_queue_mt commit_queue;

	/// Return the scene detailed phase identifier.
	uint_fast32_t GetPhaseDetailed() const { return phase_detailed; }

	Signal<void(Scene &, render::RenderSystem &)> &GetFrameClearedSignal() { return frame_cleared_signal; }
	Signal<void(Scene &, render::RenderSystem &)> &GetFrameCompleteSignal() { return frame_complete_signal; }
	Signal<void(Scene &, render::RenderSystem &)> &GetRenderablesDrawnSignal() { return renderables_drawn_signal; }

	time_t force_dt;

private:
	friend void SetSceneLoading(Scene &scene, bool is_loading);

	std::mutex phase_mutex;
	std::mutex commit_mutex; ///< acquire this mutex to ensure that the scene is not in the commit phase

	std::atomic<int> phase_detailed;

	std::atomic<bool> loading;

	Signal<void(SceneSerializationState &)> serialization_signal;
	Signal<void(SceneDeserializationState &)> deserialization_signal;

	std::vector<sSceneSystem> systems;

	std::vector<sGroup> groups;

	uint current_node_uid;
	std::vector<sNode> nodes;

	void commit_AddNode(sNode node);
	void commit_RemoveNode(const sNode &node);

	void commit_Clear();

	std::vector<sComponent> components;

	void commit_AddComponent(sComponent, int index);
	void commit_RemoveComponent(const sComponent &component);

	void commit_AddComponentToSystems(sComponent component);
	void commit_RemoveComponentFromSystems(const sComponent &component);

	sNode current_camera;
	void commit_SetCurrentCamera(sNode node);

	void UpdateMouse();

	void OnRenderableSystemPreRenderFrame(render::RenderSystem &render_system);
	void OnRenderableSystemPostRenderFrame(render::RenderSystem &render_system);

	Signal<void(Scene &, render::RenderSystem &)> frame_cleared_signal; ///< Emitted after frame has been cleared
	Signal<void(Scene &, render::RenderSystem &)> frame_complete_signal; ///< Emitted after frame render has complete
	Signal<void(Scene &, render::RenderSystem &)> renderables_drawn_signal; ///< Emitted when all scene renderables have been drawn

	void OnRenderSystemFrameCleared(render::RenderSystem &render_system);
	void OnRenderSystemRenderablesDrawn(render::RenderSystem &render_system);
	void OnRenderSystemFrameComplete(render::RenderSystem &render_system);

	Signal<void(render::RenderSystem &)>::Connection render_system_frame_cleared_connection;
	Signal<void(render::RenderSystem &)>::Connection render_system_frame_complete_connection;
	Signal<void(render::RenderSystem &)>::Connection render_system_renderables_drawn_connection;

	void OnScriptSystemUpdateLogicContext(script::VM &vm, const ScriptSystem::LogicDlgts &dlgt);
};

typedef std::shared_ptr<Scene> sScene;

/// Create a new default scene.
sScene NewDefaultScene(render::sRenderSystem render_system);
/// Load scene content.
bool LoadScene(Scene &scene, const char *path, render::sRenderSystem render_system, std::vector<sNode> *new_nodes = nullptr);

/// Set the scene is loading flag state.
void SetSceneLoading(Scene &scene, bool loading);

extern Signal<void(Scene &)> new_scene_signal;
extern Signal<void(Scene &)> delete_scene_signal;

extern Signal<void(Scene &)> scene_update_signal;

// Setup the default core system and components for a scene.
void SceneSetupCoreSystemsAndComponents(std::shared_ptr<Scene> scene, std::shared_ptr<render::RenderSystem> render_system);

} // core
} // gs
