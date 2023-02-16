#pragma once

/*
TODO: Instead of logging to JSON another approach could be to use UDP and broadcast to a running Telegraf instance.
Store in InfluxDB and explore with Grafana.
Allows for real-time exploration of a running game's timings and are built for real-time telemetry and used for micro-services all the time,
so can store a long history of a lot of data.
*/

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <thread>

namespace MPE
{
    struct ProfileResult
    {
        std::string Name;
        long long Start, End;
        uint32_t ThreadID;
    };

    struct ProfilerSession
    {
        std::string Name;
    };

    class Profiler
    {
    private:
        ProfilerSession *CURRENT_SESSION;
        std::ofstream OUTPUT;
        int PROFILE_COUNT;

    public:
        Profiler()
            : CURRENT_SESSION(nullptr), PROFILE_COUNT(0)
        {
        }

        void BeginSession(const std::string &name, const std::string &filepath = "results.json")
        {
            OUTPUT.open(filepath);
            WriteHeader();
            CURRENT_SESSION = new ProfilerSession{name};
        }

        void EndSession()
        {
            WriteFooter();
            OUTPUT.close();
            delete CURRENT_SESSION;
            CURRENT_SESSION = nullptr;
            PROFILE_COUNT = 0;
        }

        void WriteProfile(const ProfileResult &result)
        {
            if (PROFILE_COUNT++ > 0)
                OUTPUT << ",";

            std::string name = result.Name;
            std::replace(name.begin(), name.end(), '"', '\'');

            OUTPUT << "{";
            OUTPUT << "\"cat\":\"function\",";
            OUTPUT << "\"dur\":" << (result.End - result.Start) << ',';
            OUTPUT << "\"name\":\"" << name << "\",";
            OUTPUT << "\"ph\":\"X\",";
            OUTPUT << "\"pid\":0,";
            OUTPUT << "\"tid\":" << result.ThreadID << ",";
            OUTPUT << "\"ts\":" << result.Start;
            OUTPUT << "}";

            OUTPUT.flush();
        }

        void WriteHeader()
        {
            OUTPUT << "{\"otherData\": {},\"traceEvents\":[";
            OUTPUT.flush();
        }

        void WriteFooter()
        {
            OUTPUT << "]}";
            OUTPUT.flush();
        }

        static Profiler &Get()
        {
            static Profiler instance;
            return instance;
        }
    };

    class InstrumentationTimer
    {
    private:
        const char *NAME;
        std::chrono::time_point<std::chrono::high_resolution_clock> START_POINT;
        bool STOPPED;

    public:
        InstrumentationTimer(const char *name)
            : NAME(name), STOPPED(false)
        {
            START_POINT = std::chrono::high_resolution_clock::now();
        }

        ~InstrumentationTimer()
        {
            if (!STOPPED)
                Stop();
        }

        void Stop()
        {
            auto END_POINT = std::chrono::high_resolution_clock::now();

            long long start = std::chrono::time_point_cast<std::chrono::microseconds>(START_POINT).time_since_epoch().count();
            long long end = std::chrono::time_point_cast<std::chrono::microseconds>(END_POINT).time_since_epoch().count();

            uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
            Profiler::Get().WriteProfile({NAME, start, end, threadID});

            STOPPED = true;
        }
    };
}

#ifdef MPE_DEBUG_PROFILING
#define MPE_PROFILE_START(name, filepath) ::MPE::Profiler::Get().BeginSession(name, filepath)
#define MPE_PROFILE_END() ::MPE::Profiler::Get().EndSession()
#define MPE_PROFILE_SCOPE(name) ::MPE::InstrumentationTimer timer##__LINE__(name);
#define MPE_PROFILE_FUNCTION() MPE_PROFILE_SCOPE(__FUNCSIG__)
#else
#define MPE_PROFILE_START()
#define MPE_PROFILE_END()
#define MPE_PROFILE_SCOPE()
#define MPE_PROFILE_FUNCTION()
#endif