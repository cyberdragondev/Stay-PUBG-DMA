#pragma once

#include <windows.h>
#include "common/Data.h"
//#include <OS-ImGui/imgui/imgui.h>
#include "common/VectorHelper.h"
#include "RenderHelper.h"
#include <imgui/imgui.h>
#include <DMALibrary/Memory/Memory.h>
#include "Texture.h"
#include "HealthBar.h"
#include <Hack/Radar.h>

Throttler PlayerThrottlered;

class ESP {
public:
	static void DrawFPS(ImGuiIO& io)
	{
		if (!GameData.Config.Overlay.ShowFPS)
		{
			return;
		}
		auto GameScene = GameData.Scene;
		std::string Scene = "Unknown";
		std::string Items = "Hide";

		if (GameScene == Scene::FindProcess) {
			Scene = "FindProcess";
		}
		else if (GameScene == Scene::Lobby) {
			Scene = "Lobby";
		}
		else if (GameScene == Scene::Gaming) {
			Scene = "Gaming";
		}

		if (GameData.Config.ESP.FocusMode)
		{
			Items = "战斗模式";
		}
		else {
			if (GameData.Config.Item.ShowGroup == 2)
			{
				Items = "A";
			}
			else if (GameData.Config.Item.ShowGroup == 3) {
				Items = "B";
			}
			else if (GameData.Config.Item.ShowGroup == 4) {
				Items = "C";
			}
			else if (GameData.Config.Item.ShowGroup == 5) {
				Items = "D";
			}
			else if (GameData.Config.Item.ShowGroup == 1) {
				Items = "All";
			}

			Items = "物品模式: " + Items;
		}

		/*char FormattedText[256];
		snprintf(FormattedText, sizeof(FormattedText), U8("%s %.1f\nAimConfig: Profile%d\n%s\n观战 (%d)"), Scene, io.Framerate, GameData.Config.AimBot.ConfigIndex + 1, Items, GameData.FogPlayerCount, GameData.LocalPlayerInfo.SpectatedCount);
		*/
		auto TextPosition = ImVec2(5, 20);
		RenderHelper::Text(Utils::StringToUTF8(std::format("{} {}\n自瞄配置: Profile{}\n{}\n迷雾数量: {}\n观战数量 ({})", Scene, (int)io.Framerate, GameData.Config.AimBot.ConfigIndex + 1, Items, GameData.FogPlayerCount, GameData.LocalPlayerInfo.SpectatedCount)).c_str(), TextPosition, IM_COL32(255, 255, 255, 255), 16, false, false);
	










	};

	static void DrawSkeleton(Player Player, const ImU32 SkeletonUseColor, const float Thickness)
	{
		//ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
		/*auto DrawList = ImGui::GetWindowDrawList();
		auto CursorScreenPos = ImGui::GetCursorScreenPos();
		CursorScreenPos.x -= 8;
		CursorScreenPos.y -= 8;*/

		FVector2D neckpos = Player.Skeleton.ScreenBones[EBoneIndex::Neck_01];
		FVector2D pelvispos = Player.Skeleton.ScreenBones[EBoneIndex::Pelvis];
		std::vector<std::pair<ImVec2, ImVec2>> Bones;
		bool failed = false;

		for (const auto& a : SkeletonLists::Skeleton)
		{
			FVector2D previous = FVector2D(0, 0);
			FVector2D current, p1, c1;


			for (EBoneIndex bone : a)
			{
				current = (bone == EBoneIndex::Neck_01) ? neckpos : (bone == EBoneIndex::Pelvis) ? pelvispos : Player.Skeleton.ScreenBones[bone];

				if (previous.X != 0.f && previous.Y != 0.f)
				{
					p1 = previous;
					c1 = current;

					Bones.emplace_back(std::make_pair(ImVec2(p1.X, p1.Y), ImVec2(c1.X, c1.Y)));

					if (p1.X == INFINITY || p1.Y == INFINITY || c1.X == INFINITY || c1.Y == INFINITY) {
						failed = true;
						Bones.clear();
						break;
					}

				}
				previous = current;
			}

			if (failed)
				break;
		}

		//std::vector<ImVec2> Points;

		for (auto& line : Bones)
		{
			/*std::vector<ImVec2> Points;
			Points.emplace_back(line.first);
			Points.emplace_back(line.second);
			RenderHelper::PolyLine(Points, SkeletonUseColor, Thickness);*/
			RenderHelper::Line(line.first, line.second, SkeletonUseColor, Thickness);
		}

		//RenderHelper::PolyLine(Points, SkeletonUseColor, Thickness);
	}

	static void DrawFOV()
	{
		AimBotConfig Config = GameData.Config.AimBot.Configs[GameData.Config.AimBot.ConfigIndex].Weapon[WeaponTypeToString[GameData.LocalPlayerInfo.WeaponEntityInfo.WeaponType]];
		
		if (Config.DynamicFov) {
			Config.FOV = Config.FOV * (90.0f / GameData.Camera.FOV);
			Config.WheelFOV = Config.WheelFOV * (90.0f / GameData.Camera.FOV);
		}

		ImVec2 CenterPoint = { (float)GameData.Config.Overlay.ScreenWidth / 2, (float)GameData.Config.Overlay.ScreenHeight / 2 };

		if (GameData.Config.AimBot.ShowFOV && !GameData.AimBot.Lock && GameData.AimBot.Type == EntityType::Player)
		{
			if (Config.FOV <= 0) return;
			RenderHelper::Circle(CenterPoint, Config.FOV, Utils::FloatToImColor(GameData.Config.AimBot.FOVColor), 2, 360);
		} 
		
		if (GameData.Config.AimBot.ShowWheelFOV && !GameData.AimBot.Lock)
		{
			if (Config.WheelFOV <= 0) return;
			RenderHelper::Circle(CenterPoint, Config.WheelFOV, Utils::FloatToImColor(GameData.Config.AimBot.WheelFOVColor), 2, 360);
		}
	}

	static void DrawAimBotPoint()
	{
		if (GameData.Config.AimBot.ShowPoint && GameData.LocalPlayerInfo.IsScoping && !Utils::ValidPtr(GameData.AimBot.TargetPlayerInfo.Entity))
		{
			ImVec2 CenterPoint = { (float)GameData.Config.Overlay.ScreenWidth / 2, (float)GameData.Config.Overlay.ScreenHeight / 2 };
			if (GameData.AimBot.PredictedPos.X == 0 && GameData.AimBot.PredictedPos.Y == 0 && GameData.AimBot.PredictedPos.Z == 0) return;
			
			FVector2D PointPos = VectorHelper::WorldToScreen(GameData.AimBot.PredictedPos);
			
			ImVec2 ImPointPos = { PointPos.X, PointPos.Y };

			RenderHelper::CircleFilled(ImPointPos, GameData.Config.AimBot.PointSize, Utils::FloatToImColor(GameData.Config.AimBot.PointColor), GameData.Config.AimBot.PointSize * 2);
		}
	}

	static void DrawHealthBar(DWORD Sign, float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size, ImColor Color, bool Horizontal, bool ShowBackupHealth = true)
	{
		static std::map<DWORD, HealthBar> HealthBarMap;
		if (!HealthBarMap.count(Sign))
		{
			HealthBarMap.insert({ Sign,HealthBar() });
		}
		if (HealthBarMap.count(Sign))
		{
			if (Horizontal)
				HealthBarMap[Sign].DrawHealthBar_Horizontal(MaxHealth, CurrentHealth, Pos, Size, Color, ShowBackupHealth);
			else
				HealthBarMap[Sign].DrawHealthBar_Vertical(MaxHealth, CurrentHealth, Pos, Size, Color, ShowBackupHealth);
		}
	}

	static ImVec4 Get2DBox(const Player& Player)
	{
		FVector2D Head = Player.Skeleton.ScreenBones.at(EBoneIndex::Head);
		FVector2D Root = Player.Skeleton.ScreenBones.at(EBoneIndex::Root);

		ImVec2 Size, Pos;
		Size.y = (Root.Y - Head.Y) * 1.09;
		Size.x = Size.y * 0.6;

		Pos = ImVec2(Root.X - Size.x / 2, Head.Y - Size.y * 0.08);

		return ImVec4{ Pos.x,Pos.y,Size.x,Size.y };
	}

	static std::unordered_map<int, std::list<ItemInfo>> GroupItems(std::vector<std::pair<uint64_t, ItemInfo>> Items, float ThresholdX, float ThresholdY) {
		static const auto IsNear = [&](const FVector2D& A, const FVector2D& B) {
			return std::abs(A.X - B.X) < ThresholdX && std::abs(A.Y - B.Y) < ThresholdY;
		};

		std::unordered_map<int, std::list<ItemInfo>> Groups;
		int GroupId = 0;

		for (auto& Key : Items) {
			auto& Item = Key.second;

			bool FoundGroup = false;
			Item.ScreenLocation = VectorHelper::WorldToScreen(Item.Location);

			for (auto& Group : Groups) {
				for (const auto& GroupItem : Group.second) {
					if (IsNear(Item.ScreenLocation, GroupItem.ScreenLocation)) {
						Group.second.push_back(Item);
						FoundGroup = true;
						break;
					}
				}
				if (FoundGroup) break;
			}

			if (!FoundGroup) {
				Groups[GroupId++] = std::list<ItemInfo>{ Item };
			}
		}
		return Groups;
	}

	static void DrawItems(std::unordered_map<uint64_t, ItemInfo> Items)
	{
		if (!GameData.Config.Item.Enable) return;

		std::vector<std::pair<uint64_t, ItemInfo>> Vectors(Items.begin(), Items.end());

		std::sort(Vectors.begin(), Vectors.end(), [](const std::pair<uint64_t, ItemInfo>& a, const std::pair<uint64_t, ItemInfo>& b) {
			return a.second.Distance > b.second.Distance;
		});

		ImColor FontSize = GameData.Config.Item.FontSize;
		ImColor TextColor = ImColor(255, 255, 255);

		if (GameData.Config.Item.Combination)
		{
			std::unordered_map<int, std::list<ItemInfo>> CombinationItems = GroupItems(Vectors, GameData.Config.Item.ThresholdX, GameData.Config.Item.ThresholdY);
			for (auto& Group : CombinationItems)
			{
				int Index = 0;
				int FistIndex = 0;
				FVector2D FistPos;

				Group.second.sort([](const ItemInfo& A, const ItemInfo& B) {
					return A.ItemType > B.ItemType;
				});

				for (ItemInfo& ItemInfo : Group.second)
				{
					if (ItemInfo.bHidden || ItemInfo.Distance > GameData.Config.Item.DistanceMax) continue;

					std::string Text = Utils::StringToUTF8(std::format("{}", ItemInfo.DisplayName));
					int GroupIndex = GameData.Config.Item.Lists[ItemInfo.Name].Group;
					if (GameData.Config.Item.ShowGroup != 1 && GroupIndex + 1 != GameData.Config.Item.ShowGroup) continue;

					switch (GroupIndex)
					{
					case 1:
						TextColor = Utils::FloatToImColor(GameData.Config.Item.GroupAColor);
						break;
					case 2:
						TextColor = Utils::FloatToImColor(GameData.Config.Item.GroupBColor);
						break;
					case 3:
						TextColor = Utils::FloatToImColor(GameData.Config.Item.GroupCColor);
						break;
					case 4:
						TextColor = Utils::FloatToImColor(GameData.Config.Item.GroupDColor);
						break;
					default:
						continue;
						break;
					}

					ItemInfo.ScreenLocation = VectorHelper::WorldToScreen(ItemInfo.Location);
					if (!VectorHelper::IsInScreen(ItemInfo.ScreenLocation)) continue;
					ItemInfo.Distance = GameData.Camera.Location.Distance(ItemInfo.Location) / 100.0f;

					if (FistPos.X == 0 && FistPos.Y == 0)
					{
						FistIndex = Index;
						FistPos = ItemInfo.ScreenLocation;
					}

					if (GameData.Config.Item.ShowDistance && Index == FistIndex)
					{
						if (Group.second.size() > 1)
						{
							Text += "\n";
						}

						if (Group.second.size() == 1) {
							Text += " ";
						}

						Text += "[" + std::to_string((int)ItemInfo.Distance) + "M]";
					}

					ImVec2 ScreenLocation = { FistPos.X, FistPos.Y - ((FontSize + 1) * Index) };
					ImVec2 TextSize = RenderHelper::StrokeText(Text.c_str(), { ScreenLocation.x, ScreenLocation.y }, TextColor, FontSize, false, false);
					if (GameData.Config.Item.ShowIcon) {
						float Scale = (FontSize / 14.f);
						std::string IconUrl = "Assets/Icons/Item/All/" + ItemInfo.Name + ".png";
						if (GImGuiTextureMap[IconUrl].Width > 0) {
							float TargetHeight = 14.f * Scale;
							float HeightZoom = TargetHeight / GImGuiTextureMap[IconUrl].Height;
							float IconWidth = GImGuiTextureMap[IconUrl].Width * HeightZoom;
							float IconHeight = TargetHeight;
							ScreenLocation.x -= (FontSize + 4);

							RenderHelper::Image(GImGuiTextureMap[IconUrl].Texture, ScreenLocation, ImVec2(IconWidth, IconHeight), false);
						}
					}

					Index++;
				}

			}
		}
		else {
			for (auto& Item : Vectors)
			{
				ItemInfo& ItemInfo = Item.second;

				if (ItemInfo.bHidden || ItemInfo.Distance > GameData.Config.Item.DistanceMax) continue;
				int GroupIndex = GameData.Config.Item.Lists[ItemInfo.Name].Group;
				if (GameData.Config.Item.ShowGroup != 1 && GroupIndex + 1 != GameData.Config.Item.ShowGroup) continue;

				switch (GroupIndex)
				{
				case 1:
					TextColor = Utils::FloatToImColor(GameData.Config.Item.GroupAColor);
					break;
				case 2:
					TextColor = Utils::FloatToImColor(GameData.Config.Item.GroupBColor);
					break;
				case 3:
					TextColor = Utils::FloatToImColor(GameData.Config.Item.GroupCColor);
					break;
				case 4:
					TextColor = Utils::FloatToImColor(GameData.Config.Item.GroupDColor);
					break;
				default:
					continue;
					break;
				}

				ItemInfo.ScreenLocation = VectorHelper::WorldToScreen(ItemInfo.Location);
				if (!VectorHelper::IsInScreen(ItemInfo.ScreenLocation)) continue;
				ItemInfo.Distance = GameData.Camera.Location.Distance(ItemInfo.Location) / 100.0f;

				std::string Text = Utils::StringToUTF8(std::format("{}", ItemInfo.DisplayName));
				ImColor InfoColor = ImColor(255, 255, 255);

				ImVec2 InfoSize = RenderHelper::StrokeText(Text.c_str(), { ItemInfo.ScreenLocation.X, ItemInfo.ScreenLocation.Y }, TextColor, FontSize, true, true);
				
				if (GameData.Config.Item.ShowDistance) RenderHelper::StrokeText(Utils::StringToUTF8(std::format("{}M", (int)ItemInfo.Distance)).c_str(), { ItemInfo.ScreenLocation.X, ItemInfo.ScreenLocation.Y }, ImColor(255, 255, 255, 255), FontSize - 1, true, false);

				if (GameData.Config.Item.ShowIcon) {
					float Scale = 1.f;
					if (ItemInfo.ItemType == WeaponType::AR || ItemInfo.ItemType == WeaponType::DMR || ItemInfo.ItemType == WeaponType::SG || ItemInfo.ItemType == WeaponType::SR || ItemInfo.ItemType == WeaponType::LMG)
					{
						Scale = 1.4f;
					}

					std::string IconUrl = "Assets/Icons/Item/All/" + ItemInfo.Name + ".png";
					if (GImGuiTextureMap[IconUrl].Width > 0) {
						{
							float TargetHeight = 24.f * (FontSize / 14.f) * Scale;
							float HeightZoom = TargetHeight / GImGuiTextureMap[IconUrl].Height;
							float IconWidth = GImGuiTextureMap[IconUrl].Width * HeightZoom;
							float IconHeight = TargetHeight;
							ItemInfo.ScreenLocation.X -= IconWidth / 2;
							ItemInfo.ScreenLocation.Y -= (IconHeight + FontSize + 2);

							RenderHelper::Image(GImGuiTextureMap[IconUrl].Texture, { ItemInfo.ScreenLocation.X, ItemInfo.ScreenLocation.Y }, ImVec2(IconWidth, IconHeight), false);
						}
					}
				}
			}
		}
	}

	static void DrawProjects(std::unordered_map<uint64_t, ProjectInfo> Items)
	{
		if (!GameData.Config.Project.Enable) return;

		std::vector<std::pair<uint64_t, ProjectInfo>> Vectors(Items.begin(), Items.end());

		std::sort(Vectors.begin(), Vectors.end(), [](const std::pair<uint64_t, ProjectInfo>& a, const std::pair<uint64_t, ProjectInfo>& b) {
			return a.second.Distance > b.second.Distance;
		});

		for (auto& Item : Vectors)
		{
			ProjectInfo& Project = Item.second;

			if (Project.bVisible == 1 || Project.TimeTillExplosion <= 0 || Project.Distance > GameData.Config.Project.DistanceMax) continue;

			Project.ScreenLocation = VectorHelper::WorldToScreen(Project.Location);
			Project.Distance = GameData.Camera.Location.Distance(Project.Location) / 100.0f;

			const int FontSize = GameData.Config.Project.FontSize;
			const float Scale = (float)FontSize / 14.f;

			std::string Text = Utils::StringToUTF8(std::format("{} [{}M]", Project.Name, (int)Project.Distance));
			ImColor InfoColor = Utils::FloatToImColor(GameData.Config.Project.Color);
			Project.ScreenLocation.Y += 5 * Scale;
			ImVec2 InfoSize = RenderHelper::StrokeText(Text.c_str(), { Project.ScreenLocation.X, Project.ScreenLocation.Y}, InfoColor, FontSize, true, false);
			if (Project.EntityName == "ProjGrenade_C")
			{
				ImVec2 HealthBarPos, HealthBarSize;
				HealthBarSize = { 26 * Scale, 5 * Scale };
				HealthBarPos = { Project.ScreenLocation.X - ( HealthBarSize.x / 2), Project.ScreenLocation.Y + (InfoSize.y + 3 * Scale) };
				DrawHealthBar(Project.Entity, 100.f, Project.TimeTillExplosion / 4.0f * 100.0f, HealthBarPos, HealthBarSize, InfoColor, true, false);
			}
		}
	}

	static void DrawLocalPlayerProject()
	{
		if (!GameData.Config.Project.ShowChareTime) return;

		if (GameData.LocalPlayerInfo.ElapsedCookingTime > 0 && GameData.LocalPlayerInfo.WeaponClass == EWeaponClass::Class_Throwable)
		{
			static bool flashTriggered = false;
			float totalTime = 5.05f;
			if (GameData.LocalPlayerInfo.WeaponName== "闪光弹")
			{
				totalTime /= 2.f;
			}
			float progressValue = GameData.LocalPlayerInfo.ElapsedCookingTime / totalTime;

			if (progressValue >= 0.75f && !flashTriggered) {
				flashTriggered = true;
				progressValue = 0.f;
			}
			else if (flashTriggered) {
				flashTriggered = false;
			}

			ImColor Color = Utils::FloatToImColor(GameData.Config.Project.ChareColor);

			RenderHelper::DrawDashboardProgress(
				ImVec2(GameData.Config.Overlay.ScreenWidth / 2, GameData.Config.Overlay.ScreenHeight / 2),
				120.f * (GameData.Config.Project.ChareFontSize / 14.f),
				2, 
				20,
				8,
				progressValue,
				Color
			);
		}
	}

	static void DrawVehicles(std::unordered_map<uint64_t, VehicleInfo> Vehicles)
	{
		if (!GameData.Config.Vehicle.Enable) return;

		std::vector<std::pair<uint64_t, VehicleInfo>> Vectors(Vehicles.begin(), Vehicles.end());

		std::sort(Vectors.begin(), Vectors.end(), [](const std::pair<uint64_t, VehicleInfo>& a, const std::pair<uint64_t, VehicleInfo>& b) {
			return a.second.Distance > b.second.Distance;
		});

		for (auto& Item : Vectors)
		{
			VehicleInfo& Vehicle = Item.second;

			if (Vehicle.Distance > GameData.Config.Vehicle.DistanceMax) continue;

			Vehicle.ScreenLocation = VectorHelper::WorldToScreen(Vehicle.Location);
			Vehicle.Distance = GameData.Camera.Location.Distance(Vehicle.Location) / 100.0f;
			std::string Text = Utils::StringToUTF8(std::format("{} [{}M]", Vehicle.Name, (int)Vehicle.Distance));
			ImColor InfoColor = Utils::FloatToImColor(GameData.Config.Vehicle.Color);

			ImVec2 HeadInfoSize = RenderHelper::StrokeText(Text.c_str(), { Vehicle.ScreenLocation.X, Vehicle.ScreenLocation.Y }, InfoColor, GameData.Config.Vehicle.FontSize, true, true);

		}
	}

	static void DrawVehicleWheels(std::unordered_map<uint64_t, VehicleWheelInfo> VehicleWheels)
	{
		std::vector<std::pair<uint64_t, VehicleWheelInfo>> Vectors(VehicleWheels.begin(), VehicleWheels.end());

		std::sort(Vectors.begin(), Vectors.end(), [](const std::pair<uint64_t, VehicleWheelInfo>& a, const std::pair<uint64_t, VehicleWheelInfo>& b) {
			return a.second.Distance > b.second.Distance;
		});

		for (auto& Item : Vectors)
		{
			VehicleWheelInfo& Wheel = Item.second;

			Wheel.ScreenLocation = VectorHelper::WorldToScreen(Wheel.Location);
			float Distance = Utils::CalculateDistance(GameData.Config.Overlay.ScreenWidth / 2, GameData.Config.Overlay.ScreenHeight / 2, Wheel.ScreenLocation.X, Wheel.ScreenLocation.Y);

			std::string Text = std::format("{}M {}", (int)Distance, Wheel.DampingRate);
			ImColor InfoColor = ImColor(255, 255, 255);


			ImVec2 HeadInfoSize = RenderHelper::StrokeText(Text.c_str(), { Wheel.ScreenLocation.X, Wheel.ScreenLocation.Y }, InfoColor, 14, true, true);
		}
	}

	static PlayerRankInfo GetPlayerRankInfo(const std::unordered_map<std::string, PlayerRankList> PlayerRankLists, const Player Player)
	{
		PlayerRankInfo PlayerRankData;
		if (PlayerRankLists.count(Player.Name) > 0)
		{
			PlayerRankList PlayerRank = PlayerRankLists.at(Player.Name);

			switch (GameData.Config.PlayerList.RankMode) {
			case 1:
				PlayerRankData = PlayerRank.TPP;
				break;
			case 2:
				PlayerRankData = PlayerRank.SquadTPP;
				break;
			case 3:
				PlayerRankData = PlayerRank.FPP;
				break;
			case 4:
				PlayerRankData = PlayerRank.SquadFPP;
				break;
			default:
				break;
			}
		}
		return PlayerRankData;
	}

	static void DrawRadars(std::unordered_map<uint64_t, Player> Players, std::unordered_map<uint64_t, VehicleInfo> Vehicles, std::unordered_map<uint64_t, PackageInfo> Packages)
	{
		for (auto& Item : Vehicles)
		{
			VehicleInfo& Vehicle = Item.second;

			std::string IconUrl = "Assets/Icons/Radar/T_Icon_WorldMap_Vehicle_Land.png";

			if (GameData.Radar.Visibility && GameData.Config.Radar.Main.ShowVehicle)
			{
				FVector2D RadarLocation = Radar::WorldToRadarLocation(Vehicle.Location);

				if (GImGuiTextureMap[IconUrl].Width > 0) {
					float IconSize = GImGuiTextureMap[IconUrl].Width * (0.25f * (GameData.Config.Radar.Main.FontSize / 14.f));
					RenderHelper::AddImageRotated(GImGuiTextureMap[IconUrl].Texture, { RadarLocation.X, RadarLocation.Y }, ImVec2(IconSize, IconSize), 0);
				}
			}

			if (GameData.Radar.MiniRadarVisibility && Vehicle.Distance < GameData.Radar.MiniRadarDistance && GameData.Config.Radar.Mini.ShowVehicle)
			{
				FVector2D MiniRadarLocation = Radar::WorldToMiniRadarLocation(Vehicle.Location);

				if (GImGuiTextureMap[IconUrl].Width > 0) {
					float IconSize = GImGuiTextureMap[IconUrl].Width * (0.20f * (GameData.Config.Radar.Mini.FontSize / 14.f));
					RenderHelper::AddImageRotated(GImGuiTextureMap[IconUrl].Texture, { MiniRadarLocation.X, MiniRadarLocation.Y }, ImVec2(IconSize, IconSize), 0);
				}
			}

		}

		for (auto& Item : Packages)
		{
			PackageInfo& Package = Item.second;

			if (Package.Type == EntityType::AirDrop)
			{
				std::string IconUrl = "Assets/Icons/Radar/CarePackage_normal.png";

				if (GameData.Radar.Visibility && GameData.Config.Radar.Main.ShowAirDrop)
				{
					FVector2D RadarLocation = Radar::WorldToRadarLocation(Package.Location);

					if (GImGuiTextureMap[IconUrl].Width > 0) {
						float IconSize = (0.18f * (GameData.Config.Radar.Main.FontSize / 14.f));
						float IconWidth = GImGuiTextureMap[IconUrl].Width * IconSize;
						float IconHeight = GImGuiTextureMap[IconUrl].Height * IconSize;
						RenderHelper::AddImageRotated(GImGuiTextureMap[IconUrl].Texture, { RadarLocation.X, RadarLocation.Y }, ImVec2(IconWidth, IconHeight), 0);
					}
				}

				if (GameData.Radar.MiniRadarVisibility && Package.Distance < GameData.Radar.MiniRadarDistance && GameData.Config.Radar.Mini.ShowAirDrop)
				{
					FVector2D MiniRadarLocation = Radar::WorldToMiniRadarLocation(Package.Location);

					if (GImGuiTextureMap[IconUrl].Width > 0) {
						float IconSize = (0.14f * (GameData.Config.Radar.Main.FontSize / 14.f));
						float IconWidth = GImGuiTextureMap[IconUrl].Width * IconSize;
						float IconHeight = GImGuiTextureMap[IconUrl].Height * IconSize;
						RenderHelper::AddImageRotated(GImGuiTextureMap[IconUrl].Texture, { MiniRadarLocation.X, MiniRadarLocation.Y }, ImVec2(IconWidth, IconHeight), 0);
					}
				}
			}
			else {
				std::string IconUrl = "Assets/Icons/Radar/indicator_onscreen_status_dead.png";

				if (GameData.Radar.Visibility && GameData.Config.Radar.Main.ShowDeadBox)
				{
					FVector2D RadarLocation = Radar::WorldToRadarLocation(Package.Location);

					if (GImGuiTextureMap[IconUrl].Width > 0) {
						float IconSize = GImGuiTextureMap[IconUrl].Width * (0.45f * (GameData.Config.Radar.Main.FontSize / 14.f));
						RenderHelper::AddImageRotated(GImGuiTextureMap[IconUrl].Texture, { RadarLocation.X, RadarLocation.Y }, ImVec2(IconSize, IconSize), 0);
					}
				}

				if (GameData.Radar.MiniRadarVisibility && Package.Distance < GameData.Radar.MiniRadarDistance && GameData.Config.Radar.Mini.ShowDeadBox)
				{
					FVector2D MiniRadarLocation = Radar::WorldToMiniRadarLocation(Package.Location);

					if (GImGuiTextureMap[IconUrl].Width > 0) {
						float IconSize = GImGuiTextureMap[IconUrl].Width * (0.40f * (GameData.Config.Radar.Mini.FontSize / 14.f));
						RenderHelper::AddImageRotated(GImGuiTextureMap[IconUrl].Texture, { MiniRadarLocation.X, MiniRadarLocation.Y }, ImVec2(IconSize, IconSize), 0);
					}
				}
			}
		}

		for (auto& Item : Players)
		{
			Player& Player = Item.second;

			if (Player.InFog || Player.IsMe || Player.IsMyTeam || (Player.State == CharacterState::Dead))
			{
				continue;
			}

			RenderHelper::PlayerColor PlayerColors = RenderHelper::GetPlayerColor(Player);

			FVector AimDirection = FRotator(0.0f, Player.AimOffsets.Yaw, 0.0f).GetUnitVector();
			FVector2D Direction = FVector2D{ AimDirection.X, AimDirection.Y };
			float AngleRadians = atan2(Direction.Y, Direction.X);
			float AngleDegrees = AngleRadians;

			if (GameData.Radar.Visibility && GameData.Config.Radar.Main.ShowPlayer)
			{
				FVector2D RadarLocation = Radar::WorldToRadarLocation(Player.Location);

				//RenderHelper::Line({ RadarLocation.X, RadarLocation.Y }, { Direction.X, Direction.Y }, ImColor(255, 255, 255, 255), 1.f);
				RenderHelper::DrawRadarPlayerCircleWithText(Player.Type == EntityType::AI ? "AI" : std::to_string(Player.TeamID).c_str(), PlayerColors.teamNumberColor, 10 * (GameData.Config.Radar.Main.FontSize / 14.f), { RadarLocation.X, RadarLocation.Y }, AngleDegrees, Player.RadarState);
			}

			if (GameData.Radar.MiniRadarVisibility && Player.Distance < GameData.Radar.MiniRadarDistance && GameData.Config.Radar.Mini.ShowPlayer)
			{
				FVector2D MiniRadarLocation = Radar::WorldToMiniRadarLocation(Player.Location);
				RenderHelper::DrawRadarPlayerCircleWithText(Player.Type == EntityType::AI ? "AI" : std::to_string(Player.TeamID).c_str(), PlayerColors.teamNumberColor, 10 * (GameData.Config.Radar.Mini.FontSize / 14.f), { MiniRadarLocation.X, MiniRadarLocation.Y }, AngleDegrees, Player.RadarState);
			}

		}
	}

	static void DrawPlayers(std::unordered_map<uint64_t, Player> Players)
	{
		if (!GameData.Config.ESP.Enable) return;

		std::vector<std::pair<uint64_t, Player>> PlayersVector(Players.begin(), Players.end());

		std::sort(PlayersVector.begin(), PlayersVector.end(), [](const std::pair<uint64_t, Player>& a, const std::pair<uint64_t, Player>& b) {
			return a.second.Distance > b.second.Distance;
		});

		std::unordered_map<std::string, PlayerRankList> PlayerRankLists = Data::GetPlayerRankLists();

		for (auto& Item : PlayersVector)
		{
			Player& Player = Item.second;

			if (!Player.InScreen || Player.IsMe || Player.IsMyTeam || (Player.State == CharacterState::Dead))
			{
				continue;
			}

			Player.Distance = GameData.Camera.Location.Distance(Player.Location) / 100.0f;

			if (Player.Distance > GameData.Config.ESP.DistanceMax)
			{
				continue;
			}

			//是否可以显示信息
			bool bShowInfo = (Player.Distance <= GameData.Config.ESP.InfoDistanceMax || (GameData.Config.ESP.AimExpandInfo && GameData.AimBot.TargetPlayerInfo.Entity == Player.Entity));
			bool bShowWeapon = ((Player.Distance <= GameData.Config.ESP.WeaponDistanceMax && GameData.Config.ESP.ShowInfos[14]) || bShowInfo) && Player.WeaponName != "fail" && Player.WeaponName != "Unknown" && Player.WeaponID > 0;
			
			for (EBoneIndex Bone : SkeletonLists::Bones)
			{
				Player.Skeleton.LocationBones[Bone] = VectorHelper::GetBoneWithRotation(Player.Skeleton.Bones[Bone], Player.ComponentToWorld);
				Player.Skeleton.ScreenBones[Bone] = VectorHelper::WorldToScreen(Player.Skeleton.LocationBones[Bone]);
			}

			RenderHelper::PlayerColor PlayerColors = RenderHelper::GetPlayerColor(Player);

			ImColor UseColor = GameData.Config.ESP.DynamicHealthColor ? ImColor(0, 0, 0, 0) : PlayerColors.infoUseColor;

			//UseColor = PlayerColors.teamNumberColor;

			if (GameData.Config.ESP.ShowInfos[0] &&
				(!GameData.Config.ESP.LockedHiddenBones ||
					(GameData.AimBot.Target != Player.Entity || !GameData.AimBot.Lock))) 
			{
				if (!Player.IsVisible && GameData.Config.ESP.VisibleCheck)
				{
					PlayerColors.skeletonUseColor = Utils::FloatToImColor(GameData.Config.ESP.Color.Default.Skeleton);
				}
				DrawSkeleton(Player, PlayerColors.skeletonUseColor, GameData.Config.ESP.SkeletonWidth);
			}

			ImVec2 Pos = { (float)(int)Player.Skeleton.ScreenBones[EBoneIndex::Root].X, (float)(int)Player.Skeleton.ScreenBones[EBoneIndex::ForeHead].Y };
			int FontSize = GameData.Config.ESP.FontSize;
			const float Scale = (float)FontSize / 14.f;

			//RenderHelper::DrawInvertedTriangle(ImVec2(Pos.x, Pos.y), 5, PlayerColors.teamNumberColor);

			auto Rect = Get2DBox(Player);
			ImVec2 HealthBarPos, HealthBarSize;
			float Health = Player.State == CharacterState::Groggy ? Player.GroggyHealth : Player.Health;
			if (Player.State == CharacterState::Groggy) UseColor = Utils::FloatToImColor(GameData.Config.ESP.Color.Groggy.Info);
			if (GameData.Config.ESP.ShowInfos[3] && bShowInfo) {
				if (GameData.Config.ESP.HealthBarStyle == 0)
				{
					HealthBarSize = { 26 * Scale, 5 * Scale };
					HealthBarPos = { Rect.x + Rect.z / 2 - HealthBarSize.x / 2, Pos.y - HealthBarSize.y - 1 };
					DrawHealthBar(Player.Entity, 100.f, Health, HealthBarPos, HealthBarSize, UseColor, true);
					Pos.y -= 8 * Scale;
				}
				else {
					HealthBarPos = { Rect.x - 2, Rect.y + 2 };
					HealthBarSize = { std::clamp(Rect.w / 4.f, 0.f, 4.f), Rect.w - 2 };
					DrawHealthBar(Player.Entity, 100.f, Health, HealthBarPos, HealthBarSize, UseColor, false);
				}
			}

			std::string InfoText = "";
			if (GameData.Config.ESP.ShowInfos[5] && bShowInfo) RenderHelper::DrawRadarPlayerCircleWithText(
				std::to_string(Player.TeamID).c_str(), 
				PlayerColors.teamNumberColor, 10 * (GameData.Config.Radar.Main.FontSize / 14.f), 
				{ HealthBarPos.x - 15.f, HealthBarPos.y + 15.0f },
				0);
			if (GameData.Config.ESP.ShowInfos[1] && Player.ClanName != "") InfoText += std::format("[{}] ", Player.ClanName);
			if (GameData.Config.ESP.ShowInfos[2] && bShowInfo) InfoText += Player.Name + " ";

			if (GameData.Config.ESP.ShowInfos[4] && GameData.Config.ESP.DistanceStyle == 0) {
				InfoText += std::format("[{}M] ", (int)Player.Distance);
			}

			Utils::Trim(InfoText);
			if (InfoText != "") {
				ImVec2 HeadInfoSize = RenderHelper::StrokeText(Utils::StringToUTF8(InfoText).c_str(), { Pos.x, Pos.y }, PlayerColors.infoUseColor, FontSize, true, true);
				Pos.y -= HeadInfoSize.y;
			}

			if (GameData.Config.ESP.ShowInfos[14] && bShowWeapon) {
				std::string IconUrl = "Assets/Icons/Item/Weapon/Main/Item_Weapon_" + Player.WeaponEntityInfo.Name.replace(Player.WeaponEntityInfo.Name.find(Player.WeaponEntityInfo.Name), 4, "") + ".png";
				if (GImGuiTextureMap[IconUrl].Width > 0) {
					float TargetHeight = 10.f * Scale;
					float HeightZoom = TargetHeight / GImGuiTextureMap[IconUrl].Height;
					float IconWidth = GImGuiTextureMap[IconUrl].Width * HeightZoom;
					float IconHeight = TargetHeight;
					Pos.x -= IconWidth / 2;
					Pos.y -= IconHeight;

					RenderHelper::Image(GImGuiTextureMap[IconUrl].Texture, Pos, ImVec2(IconWidth, IconHeight), true, PlayerColors.infoUseColor);
				}
			}

			Pos.x = (float)(int)Player.Skeleton.ScreenBones[EBoneIndex::Root].X;
			Pos.y = (float)(int)Player.Skeleton.ScreenBones[EBoneIndex::Root].Y;

			//距离
			if (GameData.Config.ESP.ShowInfos[4] && GameData.Config.ESP.DistanceStyle == 1) {
				InfoText = "";

				InfoText += std::format("{}M", (int)Player.Distance);

				if (InfoText != "") {
					ImVec2 HeadInfoSize = RenderHelper::StrokeText(Utils::StringToUTF8(InfoText).c_str(), { Pos.x, Pos.y }, PlayerColors.infoUseColor, FontSize, true, false);
					Pos.y += HeadInfoSize.y - 2;
				}
			}

			FontSize -= 1;

			auto InfoUseColor = ImVec4(PlayerColors.infoUseColor);
			InfoUseColor.w = InfoUseColor.w - InfoUseColor.w * 0.2f;
			PlayerColors.infoUseColor = ImVec4(InfoUseColor);

			PlayerRankInfo PlayerRankData = GetPlayerRankInfo(PlayerRankLists, Player);

			//掉线状态
			if (GameData.Config.ESP.ShowInfos[9] && bShowInfo) {
				InfoText = "";
				switch (Player.CharacterState)
				{
				case ECharacterState::Offline:
					InfoText = U8("掉线");
					break;
				default:
					break;
				}
				if (InfoText != "") {
					ImVec2 HeadInfoSize = RenderHelper::StrokeText(InfoText.c_str(), { Pos.x, Pos.y }, PlayerColors.infoUseColor, FontSize, true, false);
					Pos.y += HeadInfoSize.y - 2;
				}
			}

			//武器
			if (GameData.Config.ESP.ShowInfos[15] && bShowWeapon) {
				InfoText = "";

				InfoText += std::format("{}", Player.WeaponName);

				if (InfoText != "") {
					ImVec2 HeadInfoSize = RenderHelper::StrokeText(Utils::StringToUTF8(InfoText).c_str(), { Pos.x, Pos.y }, PlayerColors.infoUseColor, FontSize, true, false);
					Pos.y += HeadInfoSize.y - 2;
				}
			}

			//击杀
			if (bShowInfo) {
				InfoText = "";

				if (GameData.Config.ESP.ShowInfos[16]) InfoText += std::format("LV{} ", Player.SurvivalLevel);
				if (GameData.Config.ESP.ShowInfos[6] && Player.KillCount > 0) InfoText += std::format("{}K ", Player.KillCount);
				if (GameData.Config.ESP.ShowInfos[7] && Player.SpectatedCount > 0) InfoText += std::format("{}S ", Player.SpectatedCount);
				if (GameData.Config.ESP.ShowInfos[8] && Player.DamageDealtOnEnemy > 0) InfoText += std::format("{}D ", (int)Player.DamageDealtOnEnemy);

				Utils::Trim(InfoText);

				if (InfoText != "") {
					ImVec2 HeadInfoSize = RenderHelper::StrokeText(Utils::StringToUTF8(InfoText).c_str(), { Pos.x, Pos.y }, PlayerColors.infoUseColor, FontSize, true, false);
					Pos.y += HeadInfoSize.y - 2;
				}
			}

			//合作者
			if (GameData.Config.ESP.ShowInfos[10] && Player.PartnerLevel > 0 && bShowInfo) {
				InfoText = "";

				InfoText += std::format("合作者Lvl.{}", (int)Player.PartnerLevel);

				if (InfoText != "") {
					ImVec2 HeadInfoSize = RenderHelper::StrokeText(Utils::StringToUTF8(InfoText).c_str(), { Pos.x, Pos.y }, PlayerColors.infoUseColor, FontSize, true, false);
					Pos.y += HeadInfoSize.y - 2;
				}
			}

			//段位信息
			if (bShowInfo) {
				std::string RankText = "";

				if (GameData.Config.ESP.ShowInfos[11] && PlayerRankData.RankPoint > 0)
				{
					/*if (PlayerRankData.Tier == "Master")
					{
						PlayerRankData.SubTier = "";
					}*/
					RankText += RankTierToLChinese[PlayerRankData.Tier] /*+ PlayerRankData.SubTier*/;
					if (GameData.Config.ESP.ShowInfos[12])
					{
						RankText += " (" + std::to_string(PlayerRankData.RankPoint) + ")";
					}
				}

				std::string KDAText = "";
				if (GameData.Config.ESP.ShowInfos[13] && PlayerRankData.KDA > 0.0f)
				{
					std::ostringstream oss;
					oss << std::fixed << std::setprecision(2) << PlayerRankData.KDA;
					KDAText += "KD:" + oss.str();
				}

				if (GameData.Config.ESP.ShowInfos[11] && PlayerRankData.RankPoint > 0)
				{
					ImVec2 HeadInfoSize = RenderHelper::StrokeText(Utils::StringToUTF8(RankText).c_str(), { Pos.x, Pos.y }, PlayerColors.infoUseColor, FontSize, true, false);
					Pos.y += HeadInfoSize.y - 2;
				}

				if (GameData.Config.ESP.ShowInfos[13] && PlayerRankData.KDA > 0.0f)
				{
					ImVec2 HeadInfoSize = RenderHelper::StrokeText(Utils::StringToUTF8(KDAText).c_str(), { Pos.x, Pos.y }, PlayerColors.infoUseColor, FontSize, true, false);
					Pos.y += HeadInfoSize.y - 2;
				}
			}

			//被瞄射线
			if (Player.IsAimMe && GameData.Config.ESP.TargetedRay)
			{
				auto IsAimMeX = Player.Skeleton.ScreenBones[EBoneIndex::ForeHead].X;
				auto IsAimMeY = Player.Skeleton.ScreenBones[EBoneIndex::ForeHead].Y;

				if (!Player.InScreen)
				{
					FVector2D LoctionToScreen = VectorHelper::WorldToScreen(Player.Location);
					IsAimMeY = LoctionToScreen.Y;
					IsAimMeY = LoctionToScreen.X;
				}

				if (!GameData.Config.ESP.VisibleCheckRay || Player.IsVisible)
				{
					RenderHelper::Line(ImVec2(IsAimMeX, IsAimMeY), ImVec2(GameData.Config.Overlay.ScreenWidth / 2, GameData.Config.Overlay.ScreenHeight / 2), ImGui::ColorConvertFloat4ToU32(Utils::FloatToImColor(GameData.Config.ESP.Color.Ray.Line)), GameData.Config.ESP.RayWidth);
				}
			}

		}
	}

	static void DrawTakeHitInstigator()
	{
		float Size = 200.f;
		float AngleXSize = 2.f;
		float AngleYSize = 5.f;
		float Angle = atan2(GameData.LocalPlayerInfo.Location.Y - GameData.LocalPlayerInfo.TakeHitInfo.AttackerLocation.Y, GameData.LocalPlayerInfo.Location.X - GameData.LocalPlayerInfo.TakeHitInfo.AttackerLocation.X);
		Angle = Angle * 180 / M_PI;
		Angle = GameData.Camera.Rotation.Yaw + 360 - Angle; // Note: Y is actually X due to storage order differences

		ImVec2 A, B, C;
		A.x = (Size + AngleYSize) * sin(Angle * M_PI / 180) + GameData.Config.Overlay.ScreenWidth / 2;
		A.y = (Size + AngleYSize) * cos(Angle * M_PI / 180) + GameData.Config.Overlay.ScreenHeight / 2;

		ImU32 Color = ImColor(255, 255, 255, 255);

		ImVec2 HeadInfoSize = RenderHelper::StrokeText(std::format("{}", GameData.LocalPlayerInfo.TakeHitInfo.ActualDamage).c_str(), A, Color, 20, true, false);
	}

	static void DrawPlayersEarly(std::unordered_map<uint64_t, Player> Players)
	{
		if (!GameData.Config.Early.Enable) return;

		const float Scale = (float)GameData.Config.Early.FontSize / 14.f;
		float Size = 200.f * Scale;
		float AngleXSize = 2.f * Scale;
		float AngleYSize = 5.f * Scale;

		for (auto& Item : Players)
		{
			Player& Player = Item.second;

			if (Player.IsMe || Player.IsMyTeam || (Player.State == CharacterState::Dead))
			{
				continue;
			}

			float Distance = (GameData.Camera.Location).Distance(Player.Location) / 100;
			float Angle = atan2(GameData.Camera.Location.Y - Player.Location.Y, GameData.Camera.Location.X - Player.Location.X);
			Angle = Angle * 180 / M_PI;
			Angle = GameData.Camera.Rotation.Yaw + 360 - Angle; // Note: Y is actually X due to storage order differences

			ImVec2 A, B, C;
			A.x = (Size + AngleYSize) * sin(Angle * M_PI / 180) + GameData.Config.Overlay.ScreenWidth / 2;
			A.y = (Size + AngleYSize) * cos(Angle * M_PI / 180) + GameData.Config.Overlay.ScreenHeight / 2;

			B.x = (Size - AngleYSize) * sin((Angle - AngleXSize) * M_PI / 180) + GameData.Config.Overlay.ScreenWidth / 2;
			B.y = (Size - AngleYSize) * cos((Angle - AngleXSize) * M_PI / 180) + GameData.Config.Overlay.ScreenHeight / 2;

			C.x = (Size - AngleYSize) * sin((Angle + AngleXSize) * M_PI / 180) + GameData.Config.Overlay.ScreenWidth / 2;
			C.y = (Size - AngleYSize) * cos((Angle + AngleXSize) * M_PI / 180) + GameData.Config.Overlay.ScreenHeight / 2;

			ImU32 Color = ImColor(255, 0, 0, 255);

			float MaxDistance = GameData.Config.Early.DistanceMax;
			float Segment = MaxDistance / 4.0f;

			if (Distance < MaxDistance)
			{
				/*if (Distance < 150.0f)
					Color = ImColor(255, 0, 255, 255);
				else if (Distance < 300.0f)
					Color = ImColor(255, 255, 0, 255);
				else if (Distance < 400.0f)
					Color = ImColor(255, 0, 0, 255);*/

				if (Distance >= Segment && Distance < Segment * 2)
				{
					Color = ImColor(255, 165, 0, 255); // 红色
				}
				else if (Distance >= Segment * 2 && Distance < Segment * 3)
				{
					Color = ImColor(0, 255, 0, 255); // 橙黄色
				}
				else if (Distance >= Segment * 3)
				{
					Color = ImColor(255, 255, 255, 255); // 绿色
				}

				if (GameData.Config.Early.ShowDistance) ImVec2 HeadInfoSize = RenderHelper::StrokeText(std::format("{}M", (int)Distance).c_str(), {A.x + 13 * Scale, A.y}, Color, 13 * Scale, false, true);
				RenderHelper::DrawTriangle(A, B, C, Color, Player.IsAimMe);
			}
		}
	}

	static void DrawPackages(std::unordered_map<uint64_t, PackageInfo> Packages)
	{
		if (!GameData.Config.AirDrop.Enable && !GameData.Config.DeadBox.Enable) return;

		std::vector<std::pair<uint64_t, PackageInfo>> VectorItems(Packages.begin(), Packages.end());

		std::sort(VectorItems.begin(), VectorItems.end(), [](const std::pair<uint64_t, PackageInfo>& a, const std::pair<uint64_t, PackageInfo>& b) {
			return a.second.Distance > b.second.Distance;
		});

		for (auto& Item : VectorItems)
		{
			PackageInfo& Package = Item.second;

			if (Package.Type == EntityType::AirDrop)
			{
				if (Package.Distance > GameData.Config.AirDrop.DistanceMax || !GameData.Config.AirDrop.Enable) continue;

				Package.ScreenLocation = VectorHelper::WorldToScreen(Package.Location);
				Package.Distance = GameData.Camera.Location.Distance(Package.Location) / 100.0f;

				std::string Text = Utils::StringToUTF8(std::format("空投 [{}M]", (int)Package.Distance));

				ImColor InfoColor = Utils::FloatToImColor(GameData.Config.AirDrop.Color);

				ImVec2 HeadInfoSize = RenderHelper::StrokeText(Text.c_str(), { Package.ScreenLocation.X, Package.ScreenLocation.Y }, InfoColor, GameData.Config.AirDrop.FontSize, false, false);
			
				if (GameData.Config.AirDrop.ShowItems)
				{
					int Index = 0;
					int FistIndex = 0;
					FVector2D FistPos;

					for (auto& ItemInfo : Package.Items)
					{
						std::string Text = Utils::StringToUTF8(std::format("{}", ItemInfo.DisplayName));
						int GroupIndex = GameData.Config.Item.Lists[ItemInfo.Name].Group;
						ImColor TextColor = InfoColor;
						float FontSize = GameData.Config.AirDrop.FontSize - 1;

						switch (GroupIndex)
						{
						case 1:
							TextColor = Utils::FloatToImColor(GameData.Config.Item.GroupAColor);
							break;
						case 2:
							TextColor = Utils::FloatToImColor(GameData.Config.Item.GroupBColor);
							break;
						case 3:
							TextColor = Utils::FloatToImColor(GameData.Config.Item.GroupCColor);
							break;
						case 4:
							TextColor = Utils::FloatToImColor(GameData.Config.Item.GroupDColor);
							break;
						default:
							continue;
							break;
						}

						FistPos = Package.ScreenLocation;
						FistPos.Y += HeadInfoSize.y;

						ImVec2 ScreenLocation = { FistPos.X, FistPos.Y + ((FontSize + 1) * Index) };
						ImVec2 TextSize = RenderHelper::StrokeText(Text.c_str(), { ScreenLocation.x, ScreenLocation.y }, TextColor, FontSize, false, false);
						if (GameData.Config.Item.ShowIcon) {
							float Scale = (FontSize / 14.f);
							std::string IconUrl = "Assets/Icons/Item/All/" + ItemInfo.Name + ".png";
							if (GImGuiTextureMap[IconUrl].Width > 0) {
								float TargetHeight = 14.f * Scale;
								float HeightZoom = TargetHeight / GImGuiTextureMap[IconUrl].Height;
								float IconWidth = GImGuiTextureMap[IconUrl].Width * HeightZoom;
								float IconHeight = TargetHeight;
								ScreenLocation.x -= (FontSize + 4);

								RenderHelper::Image(GImGuiTextureMap[IconUrl].Texture, ScreenLocation, ImVec2(IconWidth, IconHeight), false);
							}
						}

						Index++;
					}
				}
			
			}
			else {

				if (Package.Distance > GameData.Config.DeadBox.DistanceMax || !GameData.Config.DeadBox.Enable) continue;

				Package.ScreenLocation = VectorHelper::WorldToScreen(Package.Location);
				Package.Distance = GameData.Camera.Location.Distance(Package.Location) / 100.0f;

				std::string Text = Utils::StringToUTF8(std::format("死亡盒 [{}M]", (int)Package.Distance));

				ImColor InfoColor = Utils::FloatToImColor(GameData.Config.DeadBox.Color);

				ImVec2 HeadInfoSize = RenderHelper::StrokeText(Text.c_str(), { Package.ScreenLocation.X, Package.ScreenLocation.Y }, InfoColor, GameData.Config.DeadBox.FontSize, false, false);
			
				if (GameData.Config.DeadBox.ShowItems)
				{
					int Index = 0;
					int FistIndex = 0;
					FVector2D FistPos;

					for (auto& ItemInfo : Package.Items)
					{
						std::string Text = Utils::StringToUTF8(std::format("{}", ItemInfo.DisplayName));
						int GroupIndex = GameData.Config.Item.Lists[ItemInfo.Name].Group;
						ImColor TextColor = InfoColor;
						float FontSize = GameData.Config.DeadBox.FontSize - 1;

						switch (GroupIndex)
						{
						case 1:
							TextColor = Utils::FloatToImColor(GameData.Config.Item.GroupAColor);
							break;
						case 2:
							TextColor = Utils::FloatToImColor(GameData.Config.Item.GroupBColor);
							break;
						case 3:
							TextColor = Utils::FloatToImColor(GameData.Config.Item.GroupCColor);
							break;
						case 4:
							TextColor = Utils::FloatToImColor(GameData.Config.Item.GroupDColor);
							break;
						default:
							continue;
							break;
						}

						FistPos = Package.ScreenLocation;
						FistPos.Y += HeadInfoSize.y + 2;

						ImVec2 ScreenLocation = { FistPos.X, FistPos.Y + ((FontSize + 1) * Index) };
						ImVec2 TextSize = RenderHelper::StrokeText(Text.c_str(), { ScreenLocation.x, ScreenLocation.y }, TextColor, FontSize, false, false);
						if (GameData.Config.Item.ShowIcon) {
							float Scale = (FontSize / 14.f);
							std::string IconUrl = "Assets/Icons/Item/All/" + ItemInfo.Name + ".png";
							if (GImGuiTextureMap[IconUrl].Width > 0) {
								float TargetHeight = 14.f * Scale;
								float HeightZoom = TargetHeight / GImGuiTextureMap[IconUrl].Height;
								float IconWidth = GImGuiTextureMap[IconUrl].Width * HeightZoom;
								float IconHeight = TargetHeight;
								ScreenLocation.x -= (FontSize + 4);

								RenderHelper::Image(GImGuiTextureMap[IconUrl].Texture, ScreenLocation, ImVec2(IconWidth, IconHeight), false);
							}
						}

						Index++;
					}
				}
			}
		}
	}

	static void DrawESP()
	{
		if (GameData.Scene != Scene::Gaming)
		{
			return;
		}

		std::unordered_map<uint64_t, Player> Players = Data::GetPlayers();
		std::unordered_map<uint64_t, VehicleWheelInfo> VehicleWheels = Data::GetVehicleWheels();
		std::unordered_map<uint64_t, VehicleInfo> Vehicles = Data::GetVehicles();
		std::unordered_map<uint64_t, ItemInfo> Items = Data::GetItems();
		std::unordered_map<uint64_t, ProjectInfo> Projects = Data::GetProjects();
		std::unordered_map<uint64_t, PackageInfo> Packages = Data::GetPackages();

		if (!GameData.bShowMouseCursor && !GameData.AimBot.Lock)
		{
			if (!GameData.Config.ESP.FocusMode)
			{
				DrawItems(Items);
				//DrawVehicleWheels(VehicleWheels);
				DrawVehicles(Vehicles);
				DrawPackages(Packages);
			}

			DrawFOV();

			DrawPlayersEarly(Players);
			//DrawTakeHitInstigator();
		}

		DrawPlayers(Players);
		DrawLocalPlayerProject();
		DrawRadars(Players, Vehicles, Packages);
		DrawAimBotPoint();
		DrawProjects(Projects);
	};
};

