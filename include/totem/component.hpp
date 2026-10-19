#pragma once

#include <cstddef>
#include <typeinfo>

#define ECF_COMPONENT_DEFINE(T) \
  static const char* getComponentName() { return #T; } \
  static size_t getComponentID() { return typeid(T).hash_code(); } \
  const size_t getTypeID() const override { return getComponentID(); } \
  T(ecf::Object& object) : ecf::Component(object) {}

namespace ecf {
  class Object;

  class Component {
  public:
    virtual const size_t getTypeID() const = 0;

    Component(ecf::Object& object) : mParent(object) {}
    virtual ~Component() = default;

    virtual void onCreate() {}
    virtual void onDestroy() {}

    virtual void onUpdate() {}
    virtual void onRender() {}
  protected:
    ecf::Object& getParent() { return this->mParent; }
  private:
    ecf::Object& mParent;
  };
}
