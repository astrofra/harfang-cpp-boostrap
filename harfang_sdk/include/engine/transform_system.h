// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/scene_system.h"
#include "engine/transform.h"
#include "engine/transform_modifier.h"
#include "foundation/task.h"

namespace gs {
namespace core {

class Node;

/// Transform system
class TransformSystem : public std::enable_shared_from_this<TransformSystem>, public SceneSystem {
public:
	friend class Transform;

	TransformSystem();

	const std::string &GetAspect() const override;

	void AddComponent(sComponent component) override;
	void RemoveComponent(const sComponent &component) override;

	void ComputeTransform(Transform &transform);
	void CommitTransform(Transform &transform);

	void Commit() override;

	void ResetWorldMatrix(Transform &transform, const Matrix4 &m);

	void DrawDebugPanel(render::RenderSystem &render_system) override;

	std::shared_ptr<SceneSystem> shared_from_base() override { return shared_from_this(); }

private:
	struct NextWorldMatrix {
		NextWorldMatrix(Transform &t_, const Matrix4 &m_) : t(t_), m(m_) {}
		Transform &t;
		Matrix4 m;
	};

	std::vector<NextWorldMatrix> reset_world_matrix_vector;

	void DoCommit();

	void StartTransformTasks();
	stask root_transform_barrier;
	std::vector<std::shared_ptr<Node>> transformed_nodes;

	void ApplyModifiers();
	std::vector<std::shared_ptr<TransformModifier>> transform_modifiers;

	std::vector<Matrix4> previous, current, next;
};

} // core
} // gs
