#ifndef __SCENE_STATES__
#define __SCENE_STATES__

typedef enum {
    SCENE_DEACTIVATED = 0, // starts deactivated
    SCENE_ACTIVATED = 1, // when added to scenemanager
    SCENE_SHOWN = 2,
    SCENE_HIDDEN = 3
  } SceneStates;

  #endif // __SCENE_STATES__