// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <map>
#include <vector>
#include <memory>

namespace gs {
namespace core {

class Node;

class GetNodeChildrenAccelerator {
public:
	void Build(const std::vector<std::shared_ptr<Node>> &nodes);
	std::vector<std::shared_ptr<Node>> GetChildren(const std::vector<std::shared_ptr<Node>> &nodes, const Node &node) const;

private:
	struct ChildrenInfo {
		uint32_t count;
		uint32_t start_index;
	};

	std::map<const Node *, uint32_t> node_to_idx;

	std::vector<ChildrenInfo> children_info;
	std::vector<uint32_t> children;
};

} // core
} // gs
