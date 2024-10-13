#pragma once
#include "Data.h"
#include "utils/utils.h"
#include <nlohmann/json.hpp>

class Config
{
public:
	template <typename T>
	static bool SetConfigItem(const nlohmann::json& config, const std::vector<std::string>& keys, T& value)
	{
		if (keys.empty()) {
			return false;
		}

		const std::string& currentKey = keys[0];

		if (config.count(currentKey) > 0) {
			if (keys.size() == 1) {
				value = config[currentKey].get<T>();
				return true;
			}
			else {
				return SetConfigItem(config[currentKey], std::vector<std::string>(keys.begin() + 1, keys.end()), value);
			}
		}
		else {
			return false;
		}
	}

	static void Save()
	{
		nlohmann::json Config;

		[&] {
			std::string ConfigName = "Function";
			Config[ConfigName]["ClearKey"] = GameData.Config.Function.ClearKey;
		}();

		[&] {
			std::string ConfigName = "Vehicle";
			Config[ConfigName]["Enable"] = GameData.Config.Vehicle.Enable;
			Config[ConfigName]["EnableKey"] = GameData.Config.Vehicle.EnableKey;
			Config[ConfigName]["DistanceMax"] = GameData.Config.Vehicle.DistanceMax;
			Config[ConfigName]["FontSize"] = GameData.Config.Vehicle.FontSize;

			Config[ConfigName]["Color"]["0"] = GameData.Config.Vehicle.Color[0];
			Config[ConfigName]["Color"]["1"] = GameData.Config.Vehicle.Color[1];
			Config[ConfigName]["Color"]["2"] = GameData.Config.Vehicle.Color[2];
			Config[ConfigName]["Color"]["3"] = GameData.Config.Vehicle.Color[3];
		}();

		[&] {
			std::string ConfigName = "AirDrop";
			Config[ConfigName]["Enable"] = GameData.Config.AirDrop.Enable;
			Config[ConfigName]["EnableKey"] = GameData.Config.AirDrop.EnableKey;
			Config[ConfigName]["DistanceMax"] = GameData.Config.AirDrop.DistanceMax;
			Config[ConfigName]["FontSize"] = GameData.Config.AirDrop.FontSize;
			Config[ConfigName]["ShowItems"] = GameData.Config.AirDrop.ShowItems;

			Config[ConfigName]["Color"]["0"] = GameData.Config.AirDrop.Color[0];
			Config[ConfigName]["Color"]["1"] = GameData.Config.AirDrop.Color[1];
			Config[ConfigName]["Color"]["2"] = GameData.Config.AirDrop.Color[2];
			Config[ConfigName]["Color"]["3"] = GameData.Config.AirDrop.Color[3];
		}();

		[&] {
			std::string ConfigName = "DeadBox";
			Config[ConfigName]["Enable"] = GameData.Config.AirDrop.Enable;
			Config[ConfigName]["EnableKey"] = GameData.Config.AirDrop.EnableKey;
			Config[ConfigName]["DistanceMax"] = GameData.Config.AirDrop.DistanceMax;
			Config[ConfigName]["FontSize"] = GameData.Config.AirDrop.FontSize;
			Config[ConfigName]["ShowItems"] = GameData.Config.AirDrop.ShowItems;

			Config[ConfigName]["Color"]["0"] = GameData.Config.AirDrop.Color[0];
			Config[ConfigName]["Color"]["1"] = GameData.Config.AirDrop.Color[1];
			Config[ConfigName]["Color"]["2"] = GameData.Config.AirDrop.Color[2];
			Config[ConfigName]["Color"]["3"] = GameData.Config.AirDrop.Color[3];
		}();

		[&] {
			std::string ConfigName = "Early";
			Config[ConfigName]["Enable"] = GameData.Config.Early.Enable;
			Config[ConfigName]["DistanceMax"] = GameData.Config.Early.DistanceMax;
			Config[ConfigName]["FontSize"] = GameData.Config.Early.FontSize;
			Config[ConfigName]["ShowDistance"] = GameData.Config.Early.ShowDistance;
		}();

		[&] {
			std::string ConfigName = "PlayerList";
			Config[ConfigName]["RankMode"] = GameData.Config.PlayerList.RankMode;
		}();

		[&] {
			std::string ConfigName = "Project";
			Config[ConfigName]["Enable"] = GameData.Config.Project.Enable;
			Config[ConfigName]["DistanceMax"] = GameData.Config.Project.DistanceMax;
			Config[ConfigName]["FontSize"] = GameData.Config.Project.FontSize;
			Config[ConfigName]["ShowChareTime"] = GameData.Config.Project.ShowChareTime;
			Config[ConfigName]["ChareFontSize"] = GameData.Config.Project.ChareFontSize;

			Config[ConfigName]["ChareColor"]["0"] = GameData.Config.Project.ChareColor[0];
			Config[ConfigName]["ChareColor"]["1"] = GameData.Config.Project.ChareColor[1];
			Config[ConfigName]["ChareColor"]["2"] = GameData.Config.Project.ChareColor[2];
			Config[ConfigName]["ChareColor"]["3"] = GameData.Config.Project.ChareColor[3];

			Config[ConfigName]["Color"]["0"] = GameData.Config.Project.Color[0];
			Config[ConfigName]["Color"]["1"] = GameData.Config.Project.Color[1];
			Config[ConfigName]["Color"]["2"] = GameData.Config.Project.Color[2];
			Config[ConfigName]["Color"]["3"] = GameData.Config.Project.Color[3];
		}();

		[&] {
			std::string ConfigName = "Radar";
			Config[ConfigName]["Main"]["ShowPlayer"] = GameData.Config.Radar.Main.ShowPlayer;
			Config[ConfigName]["Main"]["ShowVehicle"] = GameData.Config.Radar.Main.ShowVehicle;
			Config[ConfigName]["Main"]["ShowAirDrop"] = GameData.Config.Radar.Main.ShowAirDrop;
			Config[ConfigName]["Main"]["ShowDeadBox"] = GameData.Config.Radar.Main.ShowDeadBox;
			Config[ConfigName]["Main"]["FontSize"] = GameData.Config.Radar.Main.FontSize;

			Config[ConfigName]["Mini"]["ShowPlayer"] = GameData.Config.Radar.Mini.ShowPlayer;
			Config[ConfigName]["Mini"]["ShowVehicle"] = GameData.Config.Radar.Mini.ShowVehicle;
			Config[ConfigName]["Mini"]["ShowAirDrop"] = GameData.Config.Radar.Mini.ShowAirDrop;
			Config[ConfigName]["Mini"]["ShowDeadBox"] = GameData.Config.Radar.Mini.ShowDeadBox;
			Config[ConfigName]["Mini"]["FontSize"] = GameData.Config.Radar.Mini.FontSize;
		}();

		[&] {
			std::string ConfigName = "Item";
			Config[ConfigName]["Enable"] = GameData.Config.Item.Enable;
			Config[ConfigName]["EnableKey"] = GameData.Config.Item.EnableKey;
			Config[ConfigName]["GroupKey"] = GameData.Config.Item.GroupKey;
			Config[ConfigName]["DistanceMax"] = GameData.Config.Item.DistanceMax;
			Config[ConfigName]["FontSize"] = GameData.Config.Item.FontSize;
			Config[ConfigName]["Combination"] = GameData.Config.Item.Combination;
			Config[ConfigName]["ShowIcon"] = GameData.Config.Item.ShowIcon;
			Config[ConfigName]["ShowDistance"] = GameData.Config.Item.ShowDistance;
			Config[ConfigName]["AccessoriesFilter"] = GameData.Config.Item.AccessoriesFilter;
			Config[ConfigName]["ThresholdX"] = GameData.Config.Item.ThresholdX;
			Config[ConfigName]["ThresholdY"] = GameData.Config.Item.ThresholdY;
			Config[ConfigName]["GroupAKey"] = GameData.Config.Item.GroupAKey;
			Config[ConfigName]["GroupBKey"] = GameData.Config.Item.GroupBKey;
			Config[ConfigName]["GroupCKey"] = GameData.Config.Item.GroupCKey;
			Config[ConfigName]["GroupDKey"] = GameData.Config.Item.GroupDKey;
			Config[ConfigName]["ShowGroup"] = GameData.Config.Item.ShowGroup;

			Config[ConfigName]["GroupAColor"]["0"] = GameData.Config.Item.GroupAColor[0];
			Config[ConfigName]["GroupAColor"]["1"] = GameData.Config.Item.GroupAColor[1];
			Config[ConfigName]["GroupAColor"]["2"] = GameData.Config.Item.GroupAColor[2];
			Config[ConfigName]["GroupAColor"]["3"] = GameData.Config.Item.GroupAColor[3];

			Config[ConfigName]["GroupBColor"]["0"] = GameData.Config.Item.GroupBColor[0];
			Config[ConfigName]["GroupBColor"]["1"] = GameData.Config.Item.GroupBColor[1];
			Config[ConfigName]["GroupBColor"]["2"] = GameData.Config.Item.GroupBColor[2];
			Config[ConfigName]["GroupBColor"]["3"] = GameData.Config.Item.GroupBColor[3];

			Config[ConfigName]["GroupCColor"]["0"] = GameData.Config.Item.GroupCColor[0];
			Config[ConfigName]["GroupCColor"]["1"] = GameData.Config.Item.GroupCColor[1];
			Config[ConfigName]["GroupCColor"]["2"] = GameData.Config.Item.GroupCColor[2];
			Config[ConfigName]["GroupCColor"]["3"] = GameData.Config.Item.GroupCColor[3];

			Config[ConfigName]["GroupDColor"]["0"] = GameData.Config.Item.GroupDColor[0];
			Config[ConfigName]["GroupDColor"]["1"] = GameData.Config.Item.GroupDColor[1];
			Config[ConfigName]["GroupDColor"]["2"] = GameData.Config.Item.GroupDColor[2];
			Config[ConfigName]["GroupDColor"]["3"] = GameData.Config.Item.GroupDColor[3];

			Config[ConfigName]["Lists"] = {};

			for (const auto& pair : GameData.Config.Item.Lists) {
				const std::string& key = pair.first;
				const ItemDetail& detail = pair.second;

				nlohmann::json ItemDetail = {
					{"Name", detail.Name},
					{"DisplayName", Utils::StringToUTF8(detail.DisplayName)},
					{"Type", static_cast<int>(detail.Type)},
					{"Group", detail.Group}
				};
				Config[ConfigName]["Lists"][key] = ItemDetail;
			}

		}();

		[&] {
			std::string ConfigName = "ESP";
			Config[ConfigName]["Enable"] = GameData.Config.ESP.Enable;
			Config[ConfigName]["Stroke"] = GameData.Config.ESP.Stroke;
			Config[ConfigName]["DistanceStyle"] = GameData.Config.ESP.DistanceStyle;
			Config[ConfigName]["HealthBarStyle"] = GameData.Config.ESP.HealthBarStyle;
			Config[ConfigName]["VisibleCheck"] = GameData.Config.ESP.VisibleCheck;
			Config[ConfigName]["AimExpandInfo"] = GameData.Config.ESP.AimExpandInfo;
			Config[ConfigName]["TargetedRay"] = GameData.Config.ESP.TargetedRay;
			Config[ConfigName]["VisibleCheckRay"] = GameData.Config.ESP.VisibleCheckRay;
			Config[ConfigName]["LockedHiddenBones"] = GameData.Config.ESP.LockedHiddenBones;

			for (size_t i = 0; i < 17; i++)
			{
				Config[ConfigName]["ShowInfos"][std::to_string(i)] = GameData.Config.ESP.ShowInfos[i];
			}

			Config[ConfigName]["DistanceMax"] = GameData.Config.ESP.DistanceMax;
			Config[ConfigName]["SkeletonWidth"] = GameData.Config.ESP.SkeletonWidth;
			Config[ConfigName]["FontSize"] = GameData.Config.ESP.FontSize;
			Config[ConfigName]["WeaponDistanceMax"] = GameData.Config.ESP.WeaponDistanceMax;
			Config[ConfigName]["InfoDistanceMax"] = GameData.Config.ESP.InfoDistanceMax;
			Config[ConfigName]["RayWidth"] = GameData.Config.ESP.RayWidth;
			Config[ConfigName]["FocusModeKey"] = GameData.Config.ESP.FocusModeKey;
			Config[ConfigName]["FocusMode"] = GameData.Config.ESP.FocusMode;

			Config[ConfigName]["Color"]["Ray"]["Line"]["0"] = GameData.Config.ESP.Color.Ray.Line[0];
			Config[ConfigName]["Color"]["Ray"]["Line"]["1"] = GameData.Config.ESP.Color.Ray.Line[1];
			Config[ConfigName]["Color"]["Ray"]["Line"]["2"] = GameData.Config.ESP.Color.Ray.Line[2];
			Config[ConfigName]["Color"]["Ray"]["Line"]["3"] = GameData.Config.ESP.Color.Ray.Line[3];

			Config[ConfigName]["Color"]["Default"]["Info"]["0"] = GameData.Config.ESP.Color.Default.Info[0];
			Config[ConfigName]["Color"]["Default"]["Info"]["1"] = GameData.Config.ESP.Color.Default.Info[1];
			Config[ConfigName]["Color"]["Default"]["Info"]["2"] = GameData.Config.ESP.Color.Default.Info[2];
			Config[ConfigName]["Color"]["Default"]["Info"]["3"] = GameData.Config.ESP.Color.Default.Info[3];
			Config[ConfigName]["Color"]["Default"]["Skeleton"]["0"] = GameData.Config.ESP.Color.Default.Skeleton[0];
			Config[ConfigName]["Color"]["Default"]["Skeleton"]["1"] = GameData.Config.ESP.Color.Default.Skeleton[1];
			Config[ConfigName]["Color"]["Default"]["Skeleton"]["2"] = GameData.Config.ESP.Color.Default.Skeleton[2];
			Config[ConfigName]["Color"]["Default"]["Skeleton"]["3"] = GameData.Config.ESP.Color.Default.Skeleton[3];

			Config[ConfigName]["Color"]["Visible"]["Skeleton"]["0"] = GameData.Config.ESP.Color.Visible.Skeleton[0];
			Config[ConfigName]["Color"]["Visible"]["Skeleton"]["1"] = GameData.Config.ESP.Color.Visible.Skeleton[1];
			Config[ConfigName]["Color"]["Visible"]["Skeleton"]["2"] = GameData.Config.ESP.Color.Visible.Skeleton[2];
			Config[ConfigName]["Color"]["Visible"]["Skeleton"]["3"] = GameData.Config.ESP.Color.Visible.Skeleton[3];
			Config[ConfigName]["Color"]["Visible"]["Info"]["0"] = GameData.Config.ESP.Color.Visible.Info[0];
			Config[ConfigName]["Color"]["Visible"]["Info"]["1"] = GameData.Config.ESP.Color.Visible.Info[1];
			Config[ConfigName]["Color"]["Visible"]["Info"]["2"] = GameData.Config.ESP.Color.Visible.Info[2];
			Config[ConfigName]["Color"]["Visible"]["Info"]["3"] = GameData.Config.ESP.Color.Visible.Info[3];

			Config[ConfigName]["Color"]["Partner"]["Skeleton"]["0"] = GameData.Config.ESP.Color.Partner.Skeleton[0];
			Config[ConfigName]["Color"]["Partner"]["Skeleton"]["1"] = GameData.Config.ESP.Color.Partner.Skeleton[1];
			Config[ConfigName]["Color"]["Partner"]["Skeleton"]["2"] = GameData.Config.ESP.Color.Partner.Skeleton[2];
			Config[ConfigName]["Color"]["Partner"]["Skeleton"]["3"] = GameData.Config.ESP.Color.Partner.Skeleton[3];
			Config[ConfigName]["Color"]["Partner"]["Info"]["0"] = GameData.Config.ESP.Color.Partner.Info[0];
			Config[ConfigName]["Color"]["Partner"]["Info"]["1"] = GameData.Config.ESP.Color.Partner.Info[1];
			Config[ConfigName]["Color"]["Partner"]["Info"]["2"] = GameData.Config.ESP.Color.Partner.Info[2];
			Config[ConfigName]["Color"]["Partner"]["Info"]["3"] = GameData.Config.ESP.Color.Partner.Info[3];

			Config[ConfigName]["Color"]["Groggy"]["Skeleton"]["0"] = GameData.Config.ESP.Color.Groggy.Skeleton[0];
			Config[ConfigName]["Color"]["Groggy"]["Skeleton"]["1"] = GameData.Config.ESP.Color.Groggy.Skeleton[1];
			Config[ConfigName]["Color"]["Groggy"]["Skeleton"]["2"] = GameData.Config.ESP.Color.Groggy.Skeleton[2];
			Config[ConfigName]["Color"]["Groggy"]["Skeleton"]["3"] = GameData.Config.ESP.Color.Groggy.Skeleton[3];
			Config[ConfigName]["Color"]["Groggy"]["Info"]["0"] = GameData.Config.ESP.Color.Groggy.Info[0];
			Config[ConfigName]["Color"]["Groggy"]["Info"]["1"] = GameData.Config.ESP.Color.Groggy.Info[1];
			Config[ConfigName]["Color"]["Groggy"]["Info"]["2"] = GameData.Config.ESP.Color.Groggy.Info[2];
			Config[ConfigName]["Color"]["Groggy"]["Info"]["3"] = GameData.Config.ESP.Color.Groggy.Info[3];

			Config[ConfigName]["Color"]["Dangerous"]["Skeleton"]["0"] = GameData.Config.ESP.Color.Dangerous.Skeleton[0];
			Config[ConfigName]["Color"]["Dangerous"]["Skeleton"]["1"] = GameData.Config.ESP.Color.Dangerous.Skeleton[1];
			Config[ConfigName]["Color"]["Dangerous"]["Skeleton"]["2"] = GameData.Config.ESP.Color.Dangerous.Skeleton[2];
			Config[ConfigName]["Color"]["Dangerous"]["Skeleton"]["3"] = GameData.Config.ESP.Color.Dangerous.Skeleton[3];
			Config[ConfigName]["Color"]["Dangerous"]["Info"]["0"] = GameData.Config.ESP.Color.Dangerous.Info[0];
			Config[ConfigName]["Color"]["Dangerous"]["Info"]["1"] = GameData.Config.ESP.Color.Dangerous.Info[1];
			Config[ConfigName]["Color"]["Dangerous"]["Info"]["2"] = GameData.Config.ESP.Color.Dangerous.Info[2];
			Config[ConfigName]["Color"]["Dangerous"]["Info"]["3"] = GameData.Config.ESP.Color.Dangerous.Info[3];

			Config[ConfigName]["Color"]["Blacklist"]["Skeleton"]["0"] = GameData.Config.ESP.Color.Blacklist.Skeleton[0];
			Config[ConfigName]["Color"]["Blacklist"]["Skeleton"]["1"] = GameData.Config.ESP.Color.Blacklist.Skeleton[1];
			Config[ConfigName]["Color"]["Blacklist"]["Skeleton"]["2"] = GameData.Config.ESP.Color.Blacklist.Skeleton[2];
			Config[ConfigName]["Color"]["Blacklist"]["Skeleton"]["3"] = GameData.Config.ESP.Color.Blacklist.Skeleton[3];
			Config[ConfigName]["Color"]["Blacklist"]["Info"]["0"] = GameData.Config.ESP.Color.Blacklist.Info[0];
			Config[ConfigName]["Color"]["Blacklist"]["Info"]["1"] = GameData.Config.ESP.Color.Blacklist.Info[1];
			Config[ConfigName]["Color"]["Blacklist"]["Info"]["2"] = GameData.Config.ESP.Color.Blacklist.Info[2];
			Config[ConfigName]["Color"]["Blacklist"]["Info"]["3"] = GameData.Config.ESP.Color.Blacklist.Info[3];

			Config[ConfigName]["Color"]["Whitelist"]["Skeleton"]["0"] = GameData.Config.ESP.Color.Whitelist.Skeleton[0];
			Config[ConfigName]["Color"]["Whitelist"]["Skeleton"]["1"] = GameData.Config.ESP.Color.Whitelist.Skeleton[1];
			Config[ConfigName]["Color"]["Whitelist"]["Skeleton"]["2"] = GameData.Config.ESP.Color.Whitelist.Skeleton[2];
			Config[ConfigName]["Color"]["Whitelist"]["Skeleton"]["3"] = GameData.Config.ESP.Color.Whitelist.Skeleton[3];
			Config[ConfigName]["Color"]["Whitelist"]["Info"]["0"] = GameData.Config.ESP.Color.Whitelist.Info[0];
			Config[ConfigName]["Color"]["Whitelist"]["Info"]["1"] = GameData.Config.ESP.Color.Whitelist.Info[1];
			Config[ConfigName]["Color"]["Whitelist"]["Info"]["2"] = GameData.Config.ESP.Color.Whitelist.Info[2];
			Config[ConfigName]["Color"]["Whitelist"]["Info"]["3"] = GameData.Config.ESP.Color.Whitelist.Info[3];

			Config[ConfigName]["Color"]["AI"]["Skeleton"]["0"] = GameData.Config.ESP.Color.AI.Skeleton[0];
			Config[ConfigName]["Color"]["AI"]["Skeleton"]["1"] = GameData.Config.ESP.Color.AI.Skeleton[1];
			Config[ConfigName]["Color"]["AI"]["Skeleton"]["2"] = GameData.Config.ESP.Color.AI.Skeleton[2];
			Config[ConfigName]["Color"]["AI"]["Skeleton"]["3"] = GameData.Config.ESP.Color.AI.Skeleton[3];
			Config[ConfigName]["Color"]["AI"]["Info"]["0"] = GameData.Config.ESP.Color.AI.Info[0];
			Config[ConfigName]["Color"]["AI"]["Info"]["1"] = GameData.Config.ESP.Color.AI.Info[1];
			Config[ConfigName]["Color"]["AI"]["Info"]["2"] = GameData.Config.ESP.Color.AI.Info[2];
			Config[ConfigName]["Color"]["AI"]["Info"]["3"] = GameData.Config.ESP.Color.AI.Info[3];
		}();

		[&] {
			std::string ConfigName = "AimBot";
			Config[ConfigName]["Enable"] = GameData.Config.AimBot.Enable;
			Config[ConfigName]["COM"] = GameData.Config.AimBot.COM;
			Config[ConfigName]["ConfigIndex"] = GameData.Config.AimBot.ConfigIndex;
			Config[ConfigName]["Controller"] = GameData.Config.AimBot.Controller;
			Config[ConfigName]["IP"] = GameData.Config.AimBot.IP;
			Config[ConfigName]["Port"] = GameData.Config.AimBot.Port;
			Config[ConfigName]["UUID"] = GameData.Config.AimBot.UUID;
			Config[ConfigName]["ShowFOV"] = GameData.Config.AimBot.ShowFOV;
			Config[ConfigName]["ShowWheelFOV"] = GameData.Config.AimBot.ShowWheelFOV;
			Config[ConfigName]["ShowPoint"] = GameData.Config.AimBot.ShowPoint;
			Config[ConfigName]["PointSize"] = GameData.Config.AimBot.PointSize;

			Config[ConfigName]["FOVColor"]["0"] = GameData.Config.AimBot.FOVColor[0];
			Config[ConfigName]["FOVColor"]["1"] = GameData.Config.AimBot.FOVColor[1];
			Config[ConfigName]["FOVColor"]["2"] = GameData.Config.AimBot.FOVColor[2];
			Config[ConfigName]["FOVColor"]["3"] = GameData.Config.AimBot.FOVColor[3];

			Config[ConfigName]["WheelFOVColor"]["0"] = GameData.Config.AimBot.WheelFOVColor[0];
			Config[ConfigName]["WheelFOVColor"]["1"] = GameData.Config.AimBot.WheelFOVColor[1];
			Config[ConfigName]["WheelFOVColor"]["2"] = GameData.Config.AimBot.WheelFOVColor[2];
			Config[ConfigName]["WheelFOVColor"]["3"] = GameData.Config.AimBot.WheelFOVColor[3];

			Config[ConfigName]["PointColor"]["0"] = GameData.Config.AimBot.PointColor[0];
			Config[ConfigName]["PointColor"]["1"] = GameData.Config.AimBot.PointColor[1];
			Config[ConfigName]["PointColor"]["2"] = GameData.Config.AimBot.PointColor[2];
			Config[ConfigName]["PointColor"]["3"] = GameData.Config.AimBot.PointColor[3];

			for (auto & Item : GameData.Config.AimBot.Configs)
			{
				std::string Index = std::to_string(Item.first);
				Config[ConfigName]["Configs"][Index]["Key"] = Item.second.Key;

				for (auto & Weapon : Item.second.Weapon)
				{
					Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["VisibleCheck"] = Weapon.second.VisibleCheck;
					Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["AutoSwitch"] = Weapon.second.AutoSwitch;
					Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["NoBulletNotAim"] = Weapon.second.NoBulletNotAim;
					Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["HotkeyMerge"] = Weapon.second.HotkeyMerge;
					Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["AimWheel"] = Weapon.second.AimWheel;
					Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["NoRecoil"] = Weapon.second.NoRecoil;
					Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["OriginalRecoil"] = Weapon.second.OriginalRecoil;
					Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["Prediction"] = Weapon.second.Prediction;
					Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["DynamicFov"] = Weapon.second.DynamicFov;
					Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["InitialValue"] = Weapon.second.InitialValue;
					Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["FOV"] = Weapon.second.FOV;
					Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["WheelFOV"] = Weapon.second.WheelFOV;
					Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["SwitchingDelay"] = Weapon.second.SwitchingDelay;
					Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["AimDistance"] = Weapon.second.AimDistance;
					Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["XSpeed"] = Weapon.second.XSpeed;
					Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["YSpeed"] = Weapon.second.YSpeed;
					Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["AimWheelSpeed"] = Weapon.second.AimWheelSpeed;
					Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["RecoilTime"] = Weapon.second.RecoilTime;
					Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["FPS"] = Weapon.second.FPS;
					Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["AimSpeedMaxFactor"] = Weapon.second.AimSpeedMaxFactor;
					Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["IgnoreGroggy"] = Weapon.second.IgnoreGroggy;
					//Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["LineTraceSingle"] = Weapon.second.LineTraceSingle;
					Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["AimWheelBone"] = Weapon.second.AimWheelBone;
					Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["PredictionMode"] = Weapon.second.PredictionMode;

					Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["First"]["Key"] = Weapon.second.First.Key;
					for (size_t i = 0; i < 17; i++)
					{
						Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["First"]["Bones"][std::to_string(i)] = Weapon.second.First.Bones[i];
					}

					Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["Second"]["Key"] = Weapon.second.Second.Key;
					for (size_t i = 0; i < 17; i++)
					{
						Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["Second"]["Bones"][std::to_string(i)] = Weapon.second.Second.Bones[i];
					}

					Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["Groggy"]["Key"] = Weapon.second.Groggy.Key;
					for (size_t i = 0; i < 17; i++)
					{
						Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["Groggy"]["Bones"][std::to_string(i)] = Weapon.second.Groggy.Bones[i];
					}

					Config[ConfigName]["Configs"][Index]["Weapon"][Weapon.first]["Wheel"]["Key"] = Weapon.second.Wheel.Key;
				}
			}
			
		}();

		[&] {
			std::string ConfigName = "Overlay";
			Config[ConfigName]["VSync"] = GameData.Config.Overlay.VSync;
			Config[ConfigName]["Enable"] = GameData.Config.Overlay.Enable;
			Config[ConfigName]["UseLastFrameCameraCache"] = GameData.Config.Overlay.UseLastFrameCameraCache;
			Config[ConfigName]["UseThread"] = GameData.Config.Overlay.UseThread;
		}();

		Utils::WriteConfigFile("Config/1.bin", Config.dump());
	};

	static void Load()
	{
		std::string ConfigText = Utils::ReadConfigFile("Config/1.bin");

		if (ConfigText == "")
		{
			return;
		}

		std::string Text = Utils::ReadConfigFile("Config/1.bin");

		auto Config = nlohmann::json::parse(Text);

		[&] {
			std::string ConfigName = "AimBot";
			SetConfigItem(Config, { ConfigName, "Enable" }, GameData.Config.AimBot.Enable);
			SetConfigItem(Config, { ConfigName, "COM" }, GameData.Config.AimBot.COM);
			SetConfigItem(Config, { ConfigName, "ConfigIndex" }, GameData.Config.AimBot.ConfigIndex);
			SetConfigItem(Config, { ConfigName, "Controller" }, GameData.Config.AimBot.Controller);

			if (Config[ConfigName].count("IP"))
			{
				snprintf(GameData.Config.AimBot.IP, sizeof(GameData.Config.AimBot.IP), "%s", Utils::StringToUTF8(Config[ConfigName]["IP"]));
			}

			if (Config[ConfigName].count("Port"))
			{
				snprintf(GameData.Config.AimBot.Port, sizeof(GameData.Config.AimBot.Port), "%s", Utils::StringToUTF8(Config[ConfigName]["Port"]));
			}

			if (Config[ConfigName].count("UUID"))
			{
				snprintf(GameData.Config.AimBot.UUID, sizeof(GameData.Config.AimBot.UUID), "%s", Utils::StringToUTF8(Config[ConfigName]["UUID"]));
			}

			SetConfigItem(Config, { ConfigName, "ShowFOV" }, GameData.Config.AimBot.ShowFOV);
			SetConfigItem(Config, { ConfigName, "ShowWheelFOV" }, GameData.Config.AimBot.ShowWheelFOV);
			SetConfigItem(Config, { ConfigName, "ShowPoint" }, GameData.Config.AimBot.ShowPoint);
			SetConfigItem(Config, { ConfigName, "PointSize" }, GameData.Config.AimBot.PointSize);
			SetConfigItem(Config, { ConfigName, "FOVColor", "0"}, GameData.Config.AimBot.FOVColor[0]);
			SetConfigItem(Config, { ConfigName, "FOVColor", "1" }, GameData.Config.AimBot.FOVColor[1]);
			SetConfigItem(Config, { ConfigName, "FOVColor", "2" }, GameData.Config.AimBot.FOVColor[2]);
			SetConfigItem(Config, { ConfigName, "FOVColor", "3" }, GameData.Config.AimBot.FOVColor[3]);
			SetConfigItem(Config, { ConfigName, "WheelFOVColor", "0" }, GameData.Config.AimBot.WheelFOVColor[0]);
			SetConfigItem(Config, { ConfigName, "WheelFOVColor", "1" }, GameData.Config.AimBot.WheelFOVColor[1]);
			SetConfigItem(Config, { ConfigName, "WheelFOVColor", "2" }, GameData.Config.AimBot.WheelFOVColor[2]);
			SetConfigItem(Config, { ConfigName, "WheelFOVColor", "3" }, GameData.Config.AimBot.WheelFOVColor[3]);
			SetConfigItem(Config, { ConfigName, "PointColor", "0" }, GameData.Config.AimBot.PointColor[0]);
			SetConfigItem(Config, { ConfigName, "PointColor", "1" }, GameData.Config.AimBot.PointColor[1]);
			SetConfigItem(Config, { ConfigName, "PointColor", "2" }, GameData.Config.AimBot.PointColor[2]);
			SetConfigItem(Config, { ConfigName, "PointColor", "3" }, GameData.Config.AimBot.PointColor[3]);

			for (auto& Item : GameData.Config.AimBot.Configs)
			{
				std::string Index = std::to_string(Item.first);
				SetConfigItem(Config, { ConfigName, "Configs", Index, "Key" }, Item.second.Key);


				for (auto& Weapon : Item.second.Weapon)
				{
					SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "VisibleCheck" }, Weapon.second.VisibleCheck);
					SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "AutoSwitch" }, Weapon.second.AutoSwitch);
					SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "NoBulletNotAim" }, Weapon.second.NoBulletNotAim);
					SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "HotkeyMerge" }, Weapon.second.HotkeyMerge);
					SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "AimWheel" }, Weapon.second.AimWheel);
					SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "NoRecoil" }, Weapon.second.NoRecoil);
					SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "OriginalRecoil" }, Weapon.second.OriginalRecoil);
					SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "Prediction" }, Weapon.second.Prediction);
					SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "DynamicFov" }, Weapon.second.DynamicFov);
					SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "InitialValue" }, Weapon.second.InitialValue);
					SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "FOV" }, Weapon.second.FOV);
					SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "WheelFOV" }, Weapon.second.WheelFOV);
					SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "SwitchingDelay" }, Weapon.second.SwitchingDelay);
					SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "AimDistance" }, Weapon.second.AimDistance);
					SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "XSpeed" }, Weapon.second.XSpeed);
					SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "YSpeed" }, Weapon.second.YSpeed);
					SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "AimWheelSpeed" }, Weapon.second.AimWheelSpeed);
					SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "RecoilTime" }, Weapon.second.RecoilTime);
					SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "FPS" }, Weapon.second.FPS);
					SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "AimSpeedMaxFactor" }, Weapon.second.AimSpeedMaxFactor);
					SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "IgnoreGroggy" }, Weapon.second.IgnoreGroggy);
					//SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "LineTraceSingle" }, Weapon.second.LineTraceSingle);
					SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "AimWheelBone" }, Weapon.second.AimWheelBone);
					SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "PredictionMode" }, Weapon.second.PredictionMode);

					SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "First", "Key" }, Weapon.second.First.Key);
					for (size_t i = 0; i < 17; i++)
					{
						SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "First", "Bones", std::to_string(i) }, Weapon.second.First.Bones[i]);
					}

					SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "Second", "Key" }, Weapon.second.Second.Key);
					for (size_t i = 0; i < 17; i++)
					{
						SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "Second", "Bones", std::to_string(i) }, Weapon.second.Second.Bones[i]);
					}

					SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "Groggy", "Key" }, Weapon.second.Groggy.Key);
					for (size_t i = 0; i < 17; i++)
					{
						SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "Groggy", "Bones", std::to_string(i) }, Weapon.second.Groggy.Bones[i]);
					}

					SetConfigItem(Config, { ConfigName, "Configs", Index, "Weapon", Weapon.first, "Wheel", "Key" }, Weapon.second.Wheel.Key);
				}
			}
		}();

		[&] {
			std::string ConfigName = "Overlay";
			SetConfigItem(Config, { ConfigName, "VSync" }, GameData.Config.Overlay.VSync);
			SetConfigItem(Config, { ConfigName, "Enable" }, GameData.Config.Overlay.Enable);
			SetConfigItem(Config, { ConfigName, "UseLastFrameCameraCache" }, GameData.Config.Overlay.UseLastFrameCameraCache);
			SetConfigItem(Config, { ConfigName, "UseThread" }, GameData.Config.Overlay.UseThread);
		}();

		[&] {
			std::string ConfigName = "Function";
			SetConfigItem(Config, { ConfigName, "ClearKey" }, GameData.Config.Function.ClearKey);
		}();

		[&] {
			std::string ConfigName = "Vehicle";
			SetConfigItem(Config, { ConfigName, "Enable" }, GameData.Config.Vehicle.Enable);
			SetConfigItem(Config, { ConfigName, "EnableKey" }, GameData.Config.Vehicle.EnableKey);
			SetConfigItem(Config, { ConfigName, "DistanceMax" }, GameData.Config.Vehicle.DistanceMax);
			SetConfigItem(Config, { ConfigName, "FontSize" }, GameData.Config.Vehicle.FontSize);

			SetConfigItem(Config, { ConfigName, "Color", "0" }, GameData.Config.Vehicle.Color[0]);
			SetConfigItem(Config, { ConfigName, "Color", "1" }, GameData.Config.Vehicle.Color[1]);
			SetConfigItem(Config, { ConfigName, "Color", "2" }, GameData.Config.Vehicle.Color[2]);
			SetConfigItem(Config, { ConfigName, "Color", "3" }, GameData.Config.Vehicle.Color[3]);
		}();

		[&] {
			std::string ConfigName = "AirDrop";
			SetConfigItem(Config, { ConfigName, "Enable" }, GameData.Config.AirDrop.Enable);
			SetConfigItem(Config, { ConfigName, "EnableKey" }, GameData.Config.AirDrop.EnableKey);
			SetConfigItem(Config, { ConfigName, "DistanceMax" }, GameData.Config.AirDrop.DistanceMax);
			SetConfigItem(Config, { ConfigName, "FontSize" }, GameData.Config.AirDrop.FontSize);
			SetConfigItem(Config, { ConfigName, "ShowItems" }, GameData.Config.AirDrop.ShowItems);

			SetConfigItem(Config, { ConfigName, "Color", "0" }, GameData.Config.AirDrop.Color[0]);
			SetConfigItem(Config, { ConfigName, "Color", "1" }, GameData.Config.AirDrop.Color[1]);
			SetConfigItem(Config, { ConfigName, "Color", "2" }, GameData.Config.AirDrop.Color[2]);
			SetConfigItem(Config, { ConfigName, "Color", "3" }, GameData.Config.AirDrop.Color[3]);
		}();

		[&] {
			std::string ConfigName = "DeadBox";
			SetConfigItem(Config, { ConfigName, "Enable" }, GameData.Config.AirDrop.Enable);
			SetConfigItem(Config, { ConfigName, "EnableKey" }, GameData.Config.AirDrop.EnableKey);
			SetConfigItem(Config, { ConfigName, "DistanceMax" }, GameData.Config.AirDrop.DistanceMax);
			SetConfigItem(Config, { ConfigName, "FontSize" }, GameData.Config.AirDrop.FontSize);
			SetConfigItem(Config, { ConfigName, "ShowItems" }, GameData.Config.AirDrop.ShowItems);

			SetConfigItem(Config, { ConfigName, "Color", "0" }, GameData.Config.AirDrop.Color[0]);
			SetConfigItem(Config, { ConfigName, "Color", "1" }, GameData.Config.AirDrop.Color[1]);
			SetConfigItem(Config, { ConfigName, "Color", "2" }, GameData.Config.AirDrop.Color[2]);
			SetConfigItem(Config, { ConfigName, "Color", "3" }, GameData.Config.AirDrop.Color[3]);
		}();

		[&] {
			std::string ConfigName = "Early";
			SetConfigItem(Config, { ConfigName, "Enable" }, GameData.Config.Early.Enable);
			SetConfigItem(Config, { ConfigName, "DistanceMax" }, GameData.Config.Early.DistanceMax);
			SetConfigItem(Config, { ConfigName, "FontSize" }, GameData.Config.Early.FontSize);
			SetConfigItem(Config, { ConfigName, "ShowDistance" }, GameData.Config.Early.ShowDistance);
		}();

		[&] {
			std::string ConfigName = "PlayerList";
			SetConfigItem(Config, { ConfigName, "RankMode" }, GameData.Config.PlayerList.RankMode);
		}();

		[&] {
			std::string ConfigName = "Item";
			SetConfigItem(Config, { ConfigName, "Enable" }, GameData.Config.Item.Enable);
			SetConfigItem(Config, { ConfigName, "EnableKey" }, GameData.Config.Item.EnableKey);
			SetConfigItem(Config, { ConfigName, "GroupKey" }, GameData.Config.Item.GroupKey);
			SetConfigItem(Config, { ConfigName, "DistanceMax" }, GameData.Config.Item.DistanceMax);
			SetConfigItem(Config, { ConfigName, "FontSize" }, GameData.Config.Item.FontSize);
			SetConfigItem(Config, { ConfigName, "Combination" }, GameData.Config.Item.Combination);
			SetConfigItem(Config, { ConfigName, "ShowIcon" }, GameData.Config.Item.ShowIcon);
			SetConfigItem(Config, { ConfigName, "ShowDistance" }, GameData.Config.Item.ShowDistance);
			SetConfigItem(Config, { ConfigName, "AccessoriesFilter" }, GameData.Config.Item.AccessoriesFilter);
			SetConfigItem(Config, { ConfigName, "ThresholdX" }, GameData.Config.Item.ThresholdX);
			SetConfigItem(Config, { ConfigName, "ThresholdY" }, GameData.Config.Item.ThresholdY);
			SetConfigItem(Config, { ConfigName, "GroupAKey" }, GameData.Config.Item.GroupAKey);
			SetConfigItem(Config, { ConfigName, "GroupBKey" }, GameData.Config.Item.GroupBKey);
			SetConfigItem(Config, { ConfigName, "GroupCKey" }, GameData.Config.Item.GroupCKey);
			SetConfigItem(Config, { ConfigName, "GroupDKey" }, GameData.Config.Item.GroupDKey);
			SetConfigItem(Config, { ConfigName, "ShowGroup" }, GameData.Config.Item.ShowGroup);

			SetConfigItem(Config, { ConfigName, "GroupAColor", "0" }, GameData.Config.Item.GroupAColor[0]);
			SetConfigItem(Config, { ConfigName, "GroupAColor", "1" }, GameData.Config.Item.GroupAColor[1]);
			SetConfigItem(Config, { ConfigName, "GroupAColor", "2" }, GameData.Config.Item.GroupAColor[2]);
			SetConfigItem(Config, { ConfigName, "GroupAColor", "3" }, GameData.Config.Item.GroupAColor[3]);

			SetConfigItem(Config, { ConfigName, "GroupBColor", "0" }, GameData.Config.Item.GroupBColor[0]);
			SetConfigItem(Config, { ConfigName, "GroupBColor", "1" }, GameData.Config.Item.GroupBColor[1]);
			SetConfigItem(Config, { ConfigName, "GroupBColor", "2" }, GameData.Config.Item.GroupBColor[2]);
			SetConfigItem(Config, { ConfigName, "GroupBColor", "3" }, GameData.Config.Item.GroupBColor[3]);

			SetConfigItem(Config, { ConfigName, "GroupCColor", "0" }, GameData.Config.Item.GroupCColor[0]);
			SetConfigItem(Config, { ConfigName, "GroupCColor", "1" }, GameData.Config.Item.GroupCColor[1]);
			SetConfigItem(Config, { ConfigName, "GroupCColor", "2" }, GameData.Config.Item.GroupCColor[2]);
			SetConfigItem(Config, { ConfigName, "GroupCColor", "3" }, GameData.Config.Item.GroupCColor[3]);

			SetConfigItem(Config, { ConfigName, "GroupDColor", "0" }, GameData.Config.Item.GroupDColor[0]);
			SetConfigItem(Config, { ConfigName, "GroupDColor", "1" }, GameData.Config.Item.GroupDColor[1]);
			SetConfigItem(Config, { ConfigName, "GroupDColor", "2" }, GameData.Config.Item.GroupDColor[2]);
			SetConfigItem(Config, { ConfigName, "GroupDColor", "3" }, GameData.Config.Item.GroupDColor[3]);

			for (auto& pair : GameData.Config.Item.Lists) {
				const std::string& key = pair.first;
				ItemDetail& detail = pair.second;
				SetConfigItem(Config, { ConfigName, "Lists", key, "Group" }, detail.Group);
			}
		}();

		[&] {
			std::string ConfigName = "ESP";
			SetConfigItem(Config, { ConfigName, "Enable" }, GameData.Config.ESP.Enable);
			SetConfigItem(Config, { ConfigName, "Stroke" }, GameData.Config.ESP.Stroke);
			SetConfigItem(Config, { ConfigName, "DistanceStyle" }, GameData.Config.ESP.DistanceStyle);
			SetConfigItem(Config, { ConfigName, "HealthBarStyle" }, GameData.Config.ESP.HealthBarStyle);
			SetConfigItem(Config, { ConfigName, "VisibleCheck" }, GameData.Config.ESP.VisibleCheck);
			SetConfigItem(Config, { ConfigName, "AimExpandInfo" }, GameData.Config.ESP.AimExpandInfo);
			SetConfigItem(Config, { ConfigName, "TargetedRay" }, GameData.Config.ESP.TargetedRay);
			SetConfigItem(Config, { ConfigName, "VisibleCheckRay" }, GameData.Config.ESP.VisibleCheckRay);
			SetConfigItem(Config, { ConfigName, "LockedHiddenBones" }, GameData.Config.ESP.LockedHiddenBones);

			for (size_t i = 0; i < 17; i++)
			{
				SetConfigItem(Config, { ConfigName, "ShowInfos", std::to_string(i) }, GameData.Config.ESP.ShowInfos[i]);
			}

			SetConfigItem(Config, { ConfigName, "DistanceMax" }, GameData.Config.ESP.DistanceMax);
			SetConfigItem(Config, { ConfigName, "SkeletonWidth" }, GameData.Config.ESP.SkeletonWidth);
			SetConfigItem(Config, { ConfigName, "FontSize" }, GameData.Config.ESP.FontSize);
			SetConfigItem(Config, { ConfigName, "WeaponDistanceMax" }, GameData.Config.ESP.WeaponDistanceMax);
			SetConfigItem(Config, { ConfigName, "InfoDistanceMax" }, GameData.Config.ESP.InfoDistanceMax);
			SetConfigItem(Config, { ConfigName, "RayWidth" }, GameData.Config.ESP.RayWidth);
			SetConfigItem(Config, { ConfigName, "FocusModeKey" }, GameData.Config.ESP.FocusModeKey);
			SetConfigItem(Config, { ConfigName, "FocusMode" }, GameData.Config.ESP.FocusMode);

			SetConfigItem(Config, { ConfigName, "Color", "Ray", "Line", "0" }, GameData.Config.ESP.Color.Ray.Line[0]);
			SetConfigItem(Config, { ConfigName, "Color", "Ray", "Line", "1" }, GameData.Config.ESP.Color.Ray.Line[1]);
			SetConfigItem(Config, { ConfigName, "Color", "Ray", "Line", "2" }, GameData.Config.ESP.Color.Ray.Line[2]);
			SetConfigItem(Config, { ConfigName, "Color", "Ray", "Line", "3" }, GameData.Config.ESP.Color.Ray.Line[3]);

			SetConfigItem(Config, { ConfigName, "Color", "Default", "Info", "0" }, GameData.Config.ESP.Color.Default.Info[0]);
			SetConfigItem(Config, { ConfigName, "Color", "Default", "Info", "1" }, GameData.Config.ESP.Color.Default.Info[1]);
			SetConfigItem(Config, { ConfigName, "Color", "Default", "Info", "2" }, GameData.Config.ESP.Color.Default.Info[2]);
			SetConfigItem(Config, { ConfigName, "Color", "Default", "Info", "3" }, GameData.Config.ESP.Color.Default.Info[3]);

			SetConfigItem(Config, { ConfigName, "Color", "Default", "Skeleton", "0" }, GameData.Config.ESP.Color.Default.Skeleton[0]);
			SetConfigItem(Config, { ConfigName, "Color", "Default", "Skeleton", "1" }, GameData.Config.ESP.Color.Default.Skeleton[1]);
			SetConfigItem(Config, { ConfigName, "Color", "Default", "Skeleton", "2" }, GameData.Config.ESP.Color.Default.Skeleton[2]);
			SetConfigItem(Config, { ConfigName, "Color", "Default", "Skeleton", "3" }, GameData.Config.ESP.Color.Default.Skeleton[3]);

			SetConfigItem(Config, { ConfigName, "Color", "Visible", "Skeleton", "0" }, GameData.Config.ESP.Color.Visible.Skeleton[0]);
			SetConfigItem(Config, { ConfigName, "Color", "Visible", "Skeleton", "1" }, GameData.Config.ESP.Color.Visible.Skeleton[1]);
			SetConfigItem(Config, { ConfigName, "Color", "Visible", "Skeleton", "2" }, GameData.Config.ESP.Color.Visible.Skeleton[2]);
			SetConfigItem(Config, { ConfigName, "Color", "Visible", "Skeleton", "3" }, GameData.Config.ESP.Color.Visible.Skeleton[3]);

			SetConfigItem(Config, { ConfigName, "Color", "Visible", "Info", "0" }, GameData.Config.ESP.Color.Visible.Info[0]);
			SetConfigItem(Config, { ConfigName, "Color", "Visible", "Info", "1" }, GameData.Config.ESP.Color.Visible.Info[1]);
			SetConfigItem(Config, { ConfigName, "Color", "Visible", "Info", "2" }, GameData.Config.ESP.Color.Visible.Info[2]);
			SetConfigItem(Config, { ConfigName, "Color", "Visible", "Info", "3" }, GameData.Config.ESP.Color.Visible.Info[3]);

			SetConfigItem(Config, { ConfigName, "Color", "Partner", "Skeleton", "0" }, GameData.Config.ESP.Color.Partner.Skeleton[0]);
			SetConfigItem(Config, { ConfigName, "Color", "Partner", "Skeleton", "1" }, GameData.Config.ESP.Color.Partner.Skeleton[1]);
			SetConfigItem(Config, { ConfigName, "Color", "Partner", "Skeleton", "2" }, GameData.Config.ESP.Color.Partner.Skeleton[2]);
			SetConfigItem(Config, { ConfigName, "Color", "Partner", "Skeleton", "3" }, GameData.Config.ESP.Color.Partner.Skeleton[3]);

			SetConfigItem(Config, { ConfigName, "Color", "Partner", "Info", "0" }, GameData.Config.ESP.Color.Partner.Info[0]);
			SetConfigItem(Config, { ConfigName, "Color", "Partner", "Info", "1" }, GameData.Config.ESP.Color.Partner.Info[1]);
			SetConfigItem(Config, { ConfigName, "Color", "Partner", "Info", "2" }, GameData.Config.ESP.Color.Partner.Info[2]);
			SetConfigItem(Config, { ConfigName, "Color", "Partner", "Info", "3" }, GameData.Config.ESP.Color.Partner.Info[3]);

			SetConfigItem(Config, { ConfigName, "Color", "Groggy", "Skeleton", "0" }, GameData.Config.ESP.Color.Groggy.Skeleton[0]);
			SetConfigItem(Config, { ConfigName, "Color", "Groggy", "Skeleton", "1" }, GameData.Config.ESP.Color.Groggy.Skeleton[1]);
			SetConfigItem(Config, { ConfigName, "Color", "Groggy", "Skeleton", "2" }, GameData.Config.ESP.Color.Groggy.Skeleton[2]);
			SetConfigItem(Config, { ConfigName, "Color", "Groggy", "Skeleton", "3" }, GameData.Config.ESP.Color.Groggy.Skeleton[3]);

			SetConfigItem(Config, { ConfigName, "Color", "Groggy", "Info", "0" }, GameData.Config.ESP.Color.Groggy.Info[0]);
			SetConfigItem(Config, { ConfigName, "Color", "Groggy", "Info", "1" }, GameData.Config.ESP.Color.Groggy.Info[1]);
			SetConfigItem(Config, { ConfigName, "Color", "Groggy", "Info", "2" }, GameData.Config.ESP.Color.Groggy.Info[2]);
			SetConfigItem(Config, { ConfigName, "Color", "Groggy", "Info", "3" }, GameData.Config.ESP.Color.Groggy.Info[3]);

			SetConfigItem(Config, { ConfigName, "Color", "Dangerous", "Skeleton", "0" }, GameData.Config.ESP.Color.Dangerous.Skeleton[0]);
			SetConfigItem(Config, { ConfigName, "Color", "Dangerous", "Skeleton", "1" }, GameData.Config.ESP.Color.Dangerous.Skeleton[1]);
			SetConfigItem(Config, { ConfigName, "Color", "Dangerous", "Skeleton", "2" }, GameData.Config.ESP.Color.Dangerous.Skeleton[2]);
			SetConfigItem(Config, { ConfigName, "Color", "Dangerous", "Skeleton", "3" }, GameData.Config.ESP.Color.Dangerous.Skeleton[3]);

			SetConfigItem(Config, { ConfigName, "Color", "Dangerous", "Info", "0" }, GameData.Config.ESP.Color.Dangerous.Info[0]);
			SetConfigItem(Config, { ConfigName, "Color", "Dangerous", "Info", "1" }, GameData.Config.ESP.Color.Dangerous.Info[1]);
			SetConfigItem(Config, { ConfigName, "Color", "Dangerous", "Info", "2" }, GameData.Config.ESP.Color.Dangerous.Info[2]);
			SetConfigItem(Config, { ConfigName, "Color", "Dangerous", "Info", "3" }, GameData.Config.ESP.Color.Dangerous.Info[3]);

			SetConfigItem(Config, { ConfigName, "Color", "Blacklist", "Skeleton", "0" }, GameData.Config.ESP.Color.Blacklist.Skeleton[0]);
			SetConfigItem(Config, { ConfigName, "Color", "Blacklist", "Skeleton", "1" }, GameData.Config.ESP.Color.Blacklist.Skeleton[1]);
			SetConfigItem(Config, { ConfigName, "Color", "Blacklist", "Skeleton", "2" }, GameData.Config.ESP.Color.Blacklist.Skeleton[2]);
			SetConfigItem(Config, { ConfigName, "Color", "Blacklist", "Skeleton", "3" }, GameData.Config.ESP.Color.Blacklist.Skeleton[3]);

			SetConfigItem(Config, { ConfigName, "Color", "Blacklist", "Info", "0" }, GameData.Config.ESP.Color.Blacklist.Info[0]);
			SetConfigItem(Config, { ConfigName, "Color", "Blacklist", "Info", "1" }, GameData.Config.ESP.Color.Blacklist.Info[1]);
			SetConfigItem(Config, { ConfigName, "Color", "Blacklist", "Info", "2" }, GameData.Config.ESP.Color.Blacklist.Info[2]);
			SetConfigItem(Config, { ConfigName, "Color", "Blacklist", "Info", "3" }, GameData.Config.ESP.Color.Blacklist.Info[3]);

			SetConfigItem(Config, { ConfigName, "Color", "Whitelist", "Skeleton", "0" }, GameData.Config.ESP.Color.Whitelist.Skeleton[0]);
			SetConfigItem(Config, { ConfigName, "Color", "Whitelist", "Skeleton", "1" }, GameData.Config.ESP.Color.Whitelist.Skeleton[1]);
			SetConfigItem(Config, { ConfigName, "Color", "Whitelist", "Skeleton", "2" }, GameData.Config.ESP.Color.Whitelist.Skeleton[2]);
			SetConfigItem(Config, { ConfigName, "Color", "Whitelist", "Skeleton", "3" }, GameData.Config.ESP.Color.Whitelist.Skeleton[3]);

			SetConfigItem(Config, { ConfigName, "Color", "Whitelist", "Info", "0" }, GameData.Config.ESP.Color.Whitelist.Info[0]);
			SetConfigItem(Config, { ConfigName, "Color", "Whitelist", "Info", "1" }, GameData.Config.ESP.Color.Whitelist.Info[1]);
			SetConfigItem(Config, { ConfigName, "Color", "Whitelist", "Info", "2" }, GameData.Config.ESP.Color.Whitelist.Info[2]);
			SetConfigItem(Config, { ConfigName, "Color", "Whitelist", "Info", "3" }, GameData.Config.ESP.Color.Whitelist.Info[3]);

			SetConfigItem(Config, { ConfigName, "Color", "AI", "Skeleton", "0" }, GameData.Config.ESP.Color.AI.Skeleton[0]);
			SetConfigItem(Config, { ConfigName, "Color", "AI", "Skeleton", "1" }, GameData.Config.ESP.Color.AI.Skeleton[1]);
			SetConfigItem(Config, { ConfigName, "Color", "AI", "Skeleton", "2" }, GameData.Config.ESP.Color.AI.Skeleton[2]);
			SetConfigItem(Config, { ConfigName, "Color", "AI", "Skeleton", "3" }, GameData.Config.ESP.Color.AI.Skeleton[3]);
		}();

	}
};