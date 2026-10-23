#pragma once

#include "component.hpp"
#include <memory>
#include <string_view>
#include <unordered_map>
#include <vector>
#include <string>
namespace ecf {
  class Object {
  public:
    ~Object();
    Object(std::string_view name) : mName(name) {};

    void update();
    void render();

    void queueDestroy() { this->mDead = true; }
    bool isDead() const { return this->mDead; }

    ecf::Object* addChild(std::string_view name);
    ecf::Object* getChild(std::string_view name);

    Component* addComponent(std::unique_ptr<ecf::Component>);
    template<typename T>
    T* addComponent() {
      return static_cast<T*>(this->addComponent(std::make_unique<T>(*this)));
    }

    Component* getComponent(size_t id);
    template<typename T>
    T* getComponent() {
      return static_cast<T*>(this->getComponent(T::getComponentID()));
    }

    void removeComponent(size_t id);
    template<typename T>
    void removeComponent() {
      this->removeComponent(T::getComponentID());
    }

    const ecf::Object* getParent() const { return this->mParent; }
    const ecf::Object* getRoot() const;

    const std::string getName() const { return mName; }
    void setName(std::string_view name) { this->mName = name; };
  protected:
    std::unordered_map<size_t, std::unique_ptr<ecf::Component>> mComponents;
  private:
    ecf::Object* mParent = nullptr;
    std::vector<std::unique_ptr<ecf::Object>> mChildren;

    std::string mName;

    bool mDead = false;
  };
}
