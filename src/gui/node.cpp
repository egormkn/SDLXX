#include "sdlxx/gui/node.h"

using namespace sdlxx::core;
using namespace sdlxx::gui;

void Node::SetContext(Node::Context* ptr) { context = ptr; }

void Node::OnLoad() {}

void Node::OnUnload() {}

Window& Node::GetWindow() const { return context->window; }

Renderer& Node::GetRenderer() const { return context->renderer; }
