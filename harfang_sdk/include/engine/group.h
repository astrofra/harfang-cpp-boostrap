// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <memory>
#include <string>
#include <vector>

namespace gs {
namespace core {

class Node;

/// Group of nodes
class Group {
public:
	/// Return the group node member list.
	inline const std::vector<std::shared_ptr<Node>> &GetNodes() const { return nodes; }
	inline const std::vector<std::shared_ptr<Group>> &GetGroups() const { return groups; }

	std::shared_ptr<Node> AddNode(std::shared_ptr<Node> node);
	void RemoveNode(const std::shared_ptr<Node> &node);
	bool IsMember(const std::shared_ptr<Node> &node) const;

	bool IsReady() const;

	std::shared_ptr<Node> GetNode(uint32_t uid) const;
	std::shared_ptr<Node> GetNode(const char *name) const;
	std::shared_ptr<Node> GetNode(const char *name, const std::shared_ptr<Node> &parent) const;

	std::shared_ptr<Group> AddGroup(std::shared_ptr<Group> group);
	void RemoveGroup(const std::shared_ptr<Group> &group);
	bool IsMember(const std::shared_ptr<Group> &group) const;

	std::shared_ptr<Group> GetGroup(const char *name) const;

	/// Append a group content to this group.
	void AppendGroup(const Group &group);

	const std::string &GetName() const { return name; }
	void SetName(const char *name_) { name = name_; }

private:
	std::string name;

	std::vector<std::shared_ptr<Node>> nodes;
	std::vector<std::shared_ptr<Group>> groups;
};

typedef std::shared_ptr<Group> sGroup;

} // core
} // gs
