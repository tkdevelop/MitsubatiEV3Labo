#ifndef _SCENE_H_
#define _SCENE_H_

typedef struct {
	int scene;
}Scene;
void Scene_init(Scene* self);
int Scene_get_scene(Scene* self,float distance);

#endif