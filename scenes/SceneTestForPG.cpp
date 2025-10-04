#include "SceneTestForPG.h"

SceneTestForPG::SceneTestForPG(kEngine* system) {
	system_ = system;
}

SceneTestForPG::~SceneTestForPG() {

}

void SceneTestForPG::Update() {
	
}

void SceneTestForPG::Draw() {
	printf("FPS:%f \n", system_->GetFPS());
}
