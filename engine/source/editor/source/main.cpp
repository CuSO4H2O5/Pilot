#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>

#include "editor//include/editor.h"
#include "runtime/engine.h"

// https://gcc.gnu.org/onlinedocs/cpp/Stringizing.html
#define PILOT_XSTR(s) PILOT_STR(s)
#define PILOT_STR(s) #s

int main(int argc, char** argv)
{
    std::filesystem::path pilot_root_folder = std::filesystem::path(PILOT_XSTR(PILOT_ROOT_DIR));

    Pilot::EngineInitParams params;
    params.m_root_folder      = pilot_root_folder;
    params.m_config_file_path = pilot_root_folder / "PilotEditor.ini";

    Pilot::PublicSingleton<Pilot::PilotEngine>::getInstance().startEngine(params);          //获得引擎实例，启动引擎
    Pilot::PublicSingleton<Pilot::PilotEngine>::getInstance().initialize();                 //引擎初始化 TODO 为什么用实例化的方式而不保存他的索引 因为使用了单例模式

    Pilot::PublicSingleton<Pilot::PilotEditor>::getInstance().initialize(
        &(Pilot::PublicSingleton<Pilot::PilotEngine>::getInstance()));                      //实例化引擎编辑器

    Pilot::PublicSingleton<Pilot::PilotEditor>::getInstance().run();                        //启动编辑器

    Pilot::PublicSingleton<Pilot::PilotEditor>::getInstance().clear();

    Pilot::PublicSingleton<Pilot::PilotEngine>::getInstance().clear();                      //清除editor和engine的系数
    Pilot::PublicSingleton<Pilot::PilotEngine>::getInstance().shutdownEngine();             //清除引擎

    return 0;
}
