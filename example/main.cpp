#include <totem/totem.hpp>
#include <iostream>

struct Vec2 {
  float x, y;
};

class Transform : public ecf::Component {
private:
  Vec2 mTransform = Vec2{0, 0};
public:
  ECF_COMPONENT_DEFINE(Transform)

  void setPosition(int x, int y) {
    this->mTransform.x = x;
    this->mTransform.y = y;
  }

  Vec2 getPosition() const {
    return this->mTransform;
  }
};

class MovementBehaviour : public ecf::Component {
private:
  float mSpeed = 1.5f;
  Transform *mTransform;
public:
  ECF_COMPONENT_DEFINE(MovementBehaviour)

  void onCreate() override {
    this->mTransform = this->getParent().getComponent<Transform>();
  }

  void onUpdate() override {
    Vec2 pos = this->mTransform->getPosition();

    this->mTransform->setPosition(pos.x + this->mSpeed, pos.y + this->mSpeed);
  }

  void onRender() override {
    Vec2 pos = this->mTransform->getPosition();
    std::cout << std::format("x: {}\ny: {}", pos.x, pos.y) << std::endl;
  }
};

int main() {
  ecf::Object root = ecf::Object("Root");
  ecf::Object* player = root.addChild("player");
  player->addComponent<Transform>();
  player->addComponent<MovementBehaviour>();

  while (true) {
    root.update();
    root.render();
  }
}
