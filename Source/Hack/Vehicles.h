#pragma once
#include <DMALibrary/Memory/Memory.h>
#include <Common/Data.h>
#include <Common/Entitys.h>
#include <Utils/Utils.h>
#include <Utils/Throttler.h>
#include <Hack/GNames.h>
#include <Hack/Decrypt.h>

class Vehicles
{
public:
    static void Update()
    {
        auto hScatter = mem.CreateScatterHandle();
        std::unordered_map<uint64_t, VehicleInfo> CacheVehicles;
        while (true)
        {
            if (GameData.Scene != Scene::Gaming)
            {
                CacheVehicles.clear();
                Data::SetPackages({});
                Sleep(GameData.ThreadSleep);
                continue;
            }

            // ³µÁ¾
            {

                std::unordered_map<uint64_t, VehicleInfo> Vehicles = Data::GetCacheVehicles();
                std::unordered_map<uint64_t, VehicleWheelInfo> VehicleWheels = {};

                for (auto& Item : Vehicles)
                {
                    VehicleInfo& Vehicle = Item.second;

                    mem.AddScatterRead(hScatter, Vehicle.Entity + GameData.Offset["RootComponent"], (uint64_t*)&Vehicle.RootComponent);
                    mem.AddScatterRead(hScatter, Vehicle.Entity + GameData.Offset["VehicleMovement"], (uint64_t*)&Vehicle.VehicleMovement);
                }
                mem.ExecuteReadScatter(hScatter);

                for (auto& Item : Vehicles)
                {
                    VehicleInfo& Vehicle = Item.second;

                    Vehicle.RootComponent = Decrypt::Xe(Vehicle.RootComponent);
                    mem.AddScatterRead(hScatter, Vehicle.RootComponent + GameData.Offset["ComponentLocation"], (FVector*)&Vehicle.Location);
                    mem.AddScatterRead(hScatter, Vehicle.VehicleMovement + GameData.Offset["Wheels"], (uint64_t*)&Vehicle.pWheels);
                    mem.AddScatterRead(hScatter, Vehicle.VehicleMovement + GameData.Offset["Wheels"] + 0x8, (int*)&Vehicle.WheelsCount);
                }
                mem.ExecuteReadScatter(hScatter);

                for (auto& Item : Vehicles)
                {
                    VehicleInfo& Vehicle = Item.second;

                    Vehicle.ScreenLocation = VectorHelper::WorldToScreen(Vehicle.Location);
                    Vehicle.Distance = GameData.Camera.Location.Distance(Vehicle.Location) / 100.0f;

                    if (Vehicle.WheelsCount == 4)
                    {
                        for (size_t i = 0; i < Vehicle.WheelsCount; i++)
                        {
                            VehicleWheelInfo WheelInfo;
                            WheelInfo.pWheel = Vehicle.pWheels + (i * 8);

                            Vehicle.Wheels.emplace_back(WheelInfo);
                        }

                        for (auto& Wheel : Vehicle.Wheels)
                        {
                            mem.AddScatterRead(hScatter, Wheel.pWheel, (uint64_t*)&Wheel.Wheel);
                        }
                    }
                }
                mem.ExecuteReadScatter(hScatter);

                for (auto& Item : Vehicles)
                {
                    VehicleInfo& Vehicle = Item.second;

                    if (Vehicle.WheelsCount != 4) continue;

                    for (auto& Wheel : Vehicle.Wheels)
                    {
                        mem.AddScatterRead(hScatter, Wheel.Wheel + GameData.Offset["WheelLocation"], (FVector*)&Wheel.Location);
                        /*mem.AddScatterRead(hScatter, Wheel.Wheel + GameData.Offset["WheelOldLocation"], (FVector*)&Wheel.OldLocation);
                        mem.AddScatterRead(hScatter, Wheel.Wheel + GameData.Offset["WheelVelocity"], (FVector*)&Wheel.Velocity);*/
                        mem.AddScatterRead(hScatter, Wheel.Wheel + GameData.Offset["DampingRate"], &Wheel.DampingRate);
                        mem.AddScatterRead(hScatter, Wheel.Wheel + GameData.Offset["ShapeRadius"], &Wheel.ShapeRadius);
                    }
                }
                mem.ExecuteReadScatter(hScatter);

                for (auto& Item : Vehicles)
                {
                    VehicleInfo& Vehicle = Item.second;

                    if (Vehicle.WheelsCount != 4) continue;

                    for (auto& Wheel : Vehicle.Wheels)
                    {
                        if (Wheel.DampingRate > 2.f || Wheel.DampingRate == 0.1f || Wheel.DampingRate == 0.0f)
                        {
                            Wheel.State = WheelState::FlatTire;
                            Vehicle.FlatTireCount += 1;
                        }

                        Wheel.Vehicle = Vehicle.Entity;
                        Wheel.Distance = GameData.Camera.Location.Distance(Wheel.Location) / 100.f;
                        Wheel.ScreenLocation = VectorHelper::WorldToScreen(Wheel.Location);
                        VehicleWheels[Wheel.Wheel] = Wheel;
                    }

                    CacheVehicles[Vehicle.Entity] = Vehicle;
                }

                Data::SetVehicles(Vehicles);
                Data::SetVehiclWheels(VehicleWheels);

            }

            // °ü¹ü
            {
                std::unordered_map<uint64_t, PackageInfo> Packages = Data::GetPackages();
                std::unordered_map<uint64_t, PackageInfo> CachePackages = Data::GetCachePackages();

                for (auto& Item : CachePackages)
                {
                    PackageInfo& Package = Item.second;
                    mem.AddScatterRead(hScatter, Package.Entity + GameData.Offset["DroppedItemGroup"], (uint64_t*)&Package.pDroppedItemGroup);
                    mem.AddScatterRead(hScatter, Package.Entity + GameData.Offset["ItemPackageItems"], (uint64_t*)&Package.pItemArray);
                    mem.AddScatterRead(hScatter, Package.Entity + GameData.Offset["ItemPackageItems"] + 0x8, (int*)&Package.ItemCount);
                }

                mem.ExecuteReadScatter(hScatter);

                for (auto& Item : CachePackages)
                {
                    PackageInfo& Package = Item.second;

                    mem.AddScatterRead(hScatter, Package.pDroppedItemGroup, (uint64_t*)&Package.DroppedItemGroup);
                    if (Package.ItemCount <= 0 || Package.ItemCount > 100)
                    {
                        continue;
                    }
                    for (size_t i = 0; i < Package.ItemCount; i++)
                    {
                        PackageItem Item;
                        Item.pItem = Package.pItemArray + i * 0x8;

                        Package.Items.push_back(Item);
                    }
                }

                mem.ExecuteReadScatter(hScatter);

                for (auto& Item : CachePackages)
                {
                    PackageInfo& Package = Item.second;

                    mem.AddScatterRead(hScatter, Package.DroppedItemGroup + GameData.Offset["ComponentLocation"], (FVector*)&Package.Location);

                    for (PackageItem& Item : Package.Items)
                    {
                        mem.AddScatterRead(hScatter, Item.pItem, (uint64_t*)&Item.Item);
                    }
                }

                mem.ExecuteReadScatter(hScatter);

                for (auto& Item : CachePackages)
                {
                    PackageInfo& Package = Item.second;

                    for (PackageItem& Item : Package.Items)
                    {
                        mem.AddScatterRead(hScatter, Item.Item + GameData.Offset["ItemTable"], (uint64_t*)&Item.ItemTable);
                    }

                    Package.ScreenLocation = VectorHelper::WorldToScreen(Package.Location);
                    Package.Distance = GameData.Camera.Location.Distance(Package.Location) / 100.0f;
                }

                mem.ExecuteReadScatter(hScatter);

                for (auto& Item : CachePackages)
                {
                    PackageInfo& Package = Item.second;

                    for (PackageItem& Item : Package.Items)
                    {
                        mem.AddScatterRead(hScatter, Item.ItemTable + GameData.Offset["ItemID"], (int*)&Item.ItemID);
                    }
                }

                mem.ExecuteReadScatter(hScatter);

                for (auto& Item : CachePackages)
                {
                    PackageInfo& Package = Item.second;

                    for (PackageItem& Item : Package.Items)
                    {
                        EntityInfo ItemInfo = GNames::GetInfoByID(Item.ItemID);

                        if (ItemInfo.Type != EntityType::Item) continue;

                        Item.Type = ItemInfo.Type;
                        Item.DisplayName = ItemInfo.DisplayName;
                        Item.Name = ItemInfo.Name;
                        Item.ItemType = ItemInfo.WeaponType;
                    }
                }

                Data::SetPackages(CachePackages);
            }

            Sleep(100);
        }
        mem.CloseScatterHandle(hScatter);
    }
};