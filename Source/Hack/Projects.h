#pragma once
#include <DMALibrary/Memory/Memory.h>
#include <Common/Data.h>
#include <Common/Entitys.h>
#include <Utils/Utils.h>
#include <Utils/Throttler.h>
#include <Hack/GNames.h>

class Projects
{
public:
    static void Update()
    {
        auto hScatter = mem.CreateScatterHandle();
        std::unordered_map<uint64_t, float> Times;
        Throttler Throttlered;
        while (true)
        {
            if (GameData.Scene != Scene::Gaming)
            {
                Times.clear();
                Data::SetCacheProjects({});
                Sleep(GameData.ThreadSleep);
                continue;
            }

            Throttlered.executeTaskWithSleep("ProjectsUpdateSleep", std::chrono::milliseconds(4), [] {});

            std::unordered_map<uint64_t, ProjectInfo> CacheProjects = Data::GetCacheProjects();

            if (CacheProjects.size() > 0)
            {
                for (auto& Item : CacheProjects)
                {
                    auto& CacheProject = Item.second;

                    mem.AddScatterRead(hScatter, CacheProject.Entity + GameData.Offset["RootComponent"], (uint64_t*)&CacheProject.RootComponent);
                    mem.AddScatterRead(hScatter, CacheProject.Entity + GameData.Offset["TimeTillExplosion"], (float*)&CacheProject.TimeTillExplosion);
                    mem.AddScatterRead(hScatter, CacheProject.Entity + GameData.Offset["ExplodeState"], (EProjectileExplodeState*)&CacheProject.ExplodeState);
                }

                mem.ExecuteReadScatter(hScatter);

                for (auto& Item : CacheProjects)
                {
                    auto& CacheProject = Item.second;

                    if (CacheProject.bVisible == 1)
                    {
                        continue;
                    }

                    if (CacheProject.EntityName != "ProjGrenade_C")
                    {
                        if (abs(CacheProject.TimeTillExplosion) > 0.0f && CacheProject.TimeTillExplosion == Times[CacheProject.Entity])
                        {
                            CacheProject.bVisible = 1;
                            continue;
                        }
                        else {
                            Times[CacheProject.Entity] = CacheProject.TimeTillExplosion;
                        }
                    }

                    CacheProject.RootComponent = Decrypt::Xe(CacheProject.RootComponent);
                    mem.AddScatterRead(hScatter, CacheProject.RootComponent + GameData.Offset["ComponentLocation"], (FVector*)&CacheProject.Location);
                }

                mem.ExecuteReadScatter(hScatter);

                for (auto& Item : CacheProjects)
                {
                    auto& CacheProject = Item.second;

                    CacheProject.ScreenLocation = VectorHelper::WorldToScreen(CacheProject.Location);
                    CacheProject.Distance = GameData.Camera.Location.Distance(CacheProject.Location) / 100.0f;
                }
            }

            Data::SetProjects(CacheProjects);
        }
        mem.CloseScatterHandle(hScatter);
    }
};