#pragma once

#include "MPE/Base/Log.h"

#include <chrono>

namespace MPE
{
    template <typename FN>
    class _TIMER
    {
    private:
        const char *NAME;
        FN FUNC;
        std::chrono::time_point<std::chrono::steady_clock> START_POINT;
        bool STOPPED;

    public:
        _TIMER(const char *name)
            : NAME(name), STOPPED(false)
        {
            START_POINT = std::chrono::high_resolution_clock::now();
        }

        _TIMER(const char *name, FN&& func)
            : NAME(name), FUNC(func), STOPPED(false)
        {
            START_POINT = std::chrono::high_resolution_clock::now();
        }

        ~_TIMER()
        {
            if (!STOPPED)
            {
                Stop();
            }
        }

        void Stop()
        {
            auto END_POINT = std::chrono::high_resolution_clock::now();

            long long start = std::chrono::time_point_cast<std::chrono::microseconds>(START_POINT).time_since_epoch().count();
            long long end = std::chrono::time_point_cast<std::chrono::microseconds>(END_POINT).time_since_epoch().count();

            STOPPED = true;

            float duration = (end - start) * 0.001f;

            //MPE_CORE_TRACE("DURATION: {0}ms", duration);
            FUNC({NAME, duration});
        }
    };
}

//#define PROFILE_SCOPE(name) _TIMER timer##__LINE__(name, [&](auto profile){PROFILE.push_back(profile);})

// in used class:
    // struct PROFILE{
    //     const char* NAME;
    //     float TIME;
    // };

    // std::vector<PROFILE> SYS_PROFILE;

    //THEN

    // MPE::_TIMER timer("SANDBOX 2D ON UPDATE", [&](PROFILE profile){SYS_PROFILE.push_back(profile);});


    // IMGUI:
    //     for (auto&& [name, time] : SYS_PROFILE){
    //     char label[50];
    //     strcpy(label, name);
    //     strcat(label, " %.3fms");
    //     ImGui::Text(label, time);
    // }
    // SYS_PROFILE.clear();