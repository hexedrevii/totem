#include "totem/object.hpp"
#include "totem/component.hpp"
#include <memory>

ecf::Object::~Object() {
  for (auto& [id, component] : this->mComponents) {
    component->onDestroy();
  }

  this->mComponents.clear();
}

void ecf::Object::update() {
  if (this->isDead()) return;

  for (auto& [id, component] : this->mComponents) component->onUpdate();
  for (auto& child : this->mChildren) child->update();

  std::erase_if(this->mChildren, [](const std::unique_ptr<ecf::Object>& child) {
    return child->isDead();
  });
}

void ecf::Object::render() {
  if (this->isDead()) return;

  for (auto& [id, component] : this->mComponents) component->onRender();
  for (auto& child : this->mChildren) child->render();
}

ecf::Component* ecf::Object::getComponent(size_t id) {
  auto iter = this->mComponents.find(id);
  if (iter == this->mComponents.end()) {
    return nullptr;
  }

  return iter->second.get();
}

ecf::Component* ecf::Object::addComponent(std::unique_ptr<ecf::Component> component) {
  component->onCreate();

  size_t id = component->getTypeID();
  this->mComponents.try_emplace(id, std::move(component));

  return this->getComponent(id);
}

void ecf::Object::removeComponent(size_t id) {
  auto iter = this->mComponents.find(id);

  if (iter == this->mComponents.end()) {
    return;
  }

  ecf::Component* component = iter->second.get();
  component->onDestroy();
  this->mComponents.erase(iter);
}

ecf::Object* ecf::Object::addChild(std::string_view name) {
  std::unique_ptr<ecf::Object> child = std::make_unique<ecf::Object>(name);
  child->mParent = this;

  ecf::Object* raw = child.get();

  this->mChildren.emplace_back(std::move(child));
  return raw;
}

ecf::Object* ecf::Object::getChild(std::string_view name) {
  for (auto& child : this->mChildren) {
    if (child->getName() == name) {
      return child.get();
    }
  }

  return nullptr;
}
