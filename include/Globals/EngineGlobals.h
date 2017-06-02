#ifndef __ENGINE_GLOBALS__
#define __ENGINE_GLOBALS__

#include <string>

namespace EngineGlobals {
const std::string engine_name = "SquareOrDie";
const std::string engine_version = "0.1";
const std::string window_title = engine_name + " " + engine_version;

const int screen_width = 1024;
const int screen_height = 800;

const float fixed_update_rate = 50;
const float fixed_update_interval = 1000 / fixed_update_rate;

const float update_rate = 60;
const float update_rate_interval = 1000 / update_rate;
} // namespace EngineGlobals

#endif // __ENGINE_GLOBALS__
