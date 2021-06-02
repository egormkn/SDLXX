#include "sdlxx/gui/parent_node.h"

using namespace sdlxx::gui;

std::vector<std::unique_ptr<Node>>& ParentNode::GetChildren() { return children; }

void ParentNode::Update(uint32_t t, uint32_t dt) {
  for (auto& child : children) {
    child->Update(t, dt);
  }
}

void ParentNode::Render() {
  for (auto& child : children) {
    child->Render();
  }
}

bool ParentNode::HandleEvent(const sdlxx::core::Event& e) {
  for (auto& child : children) {
    if (child->HandleEvent(e)) {
      return true;
    }
  }
  return false;
}
