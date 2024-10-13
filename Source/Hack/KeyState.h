#pragma once
#include <Winsock2.h>
#include <DMALibrary/Memory/Memory.h>
#include <Common/Data.h>
#include <Utils/KmBox.h>
#include <Utils/KmBoxNet.h>
#include <Hack/Players.h>

namespace KeyState
{
	void Init()
	{
		GameData.Keyboard = mem.GetKeyboard();

		if (!GameData.Keyboard.InitKeyboard())
		{
			Utils::Log(2, "Failed to initialize keyboard hotkeys through kernel.");
		}
		else {
			Utils::Log(1, "Keyboard initialize success");
		}
	}
	void Update() {
		while (true)
		{
			GameData.Keyboard.UpdateKeys();

			std::unordered_map<int, std::vector<std::string>> Keys;
			Keys[GameData.Config.Menu.ShowKey].push_back("Menu");
			Keys[GameData.Config.AimBot.Configs[0].Key].push_back("AimBotConfig0");
			Keys[GameData.Config.AimBot.Configs[1].Key].push_back("AimBotConfig1");
			Keys[VK_END].push_back("RecoverOverlay");
			Keys[GameData.Config.Function.ClearKey].push_back("Clear");
			Keys[GameData.Config.Item.GroupKey].push_back("GroupKey");
			Keys[GameData.Config.Item.GroupAKey].push_back("GroupAKey");
			Keys[GameData.Config.Item.GroupBKey].push_back("GroupBKey");
			Keys[GameData.Config.Item.GroupCKey].push_back("GroupCKey");
			Keys[GameData.Config.Item.GroupDKey].push_back("GroupDKey");
			Keys[GameData.Config.Vehicle.EnableKey].push_back("VehicleEnable");
			Keys[GameData.Config.PlayerList.MarkKey].push_back("PlayerListMarkType");
			Keys[GameData.Config.ESP.FocusModeKey].push_back("FocusModeKey");
			Keys[GameData.Config.AirDrop.EnableKey].push_back("AirDropEnableKey");
			Keys[GameData.Config.DeadBox.EnableKey].push_back("DeadBoxEnableKey");

			for (auto Key : Keys)
			{
				if (GameData.Keyboard.WasKeyPressed(Key.first))
				{
					for (auto KeyName : Key.second)
					{
						if (KeyName == "AirDropEnableKey")
						{
							GameData.Config.AirDrop.Enable = !GameData.Config.AirDrop.Enable;
						}

						if (KeyName == "DeadBoxEnableKey")
						{
							GameData.Config.DeadBox.Enable = !GameData.Config.DeadBox.Enable;
						}

						if (KeyName == "FocusModeKey")
						{
							GameData.Config.ESP.FocusMode = !GameData.Config.ESP.FocusMode;
						}

						if (KeyName == "Clear")
						{
							if (GameData.Config.AimBot.Connected)
							{
								if (GameData.Config.AimBot.Controller == 0)
								{
									KmBox::Clear();
									Utils::Log(1, "KMBOX Clear Success");
								}

								if (GameData.Config.AimBot.Controller == 1)
								{
									KmBoxNet::Clear();
									Utils::Log(1, "KMBOXNET Clear Success");
								}
							}

							Data::SetCacheEntitys({});
							Data::SetCachePlayers({});
							Data::SetPlayers({});
							Data::SetPlayersData({});
							Data::SetCacheVehicles({});
							Data::SetVehicles({});
							Data::SetVehiclWheels({});
							Data::SetItems({});
							Data::SetCacheDroppedItems({});
							Data::SetCacheDroppedItemGroups({});
							GameData.AimBot.Target = 0;
							GameData.AimBot.Lock = false;
							mem.RefreshAll();
						}
						/*if (KeyName == "PlayerListMarkType")
						{
							Player player = GameData.AimBot.TargetPlayerInfo; 
							if (player.ListType >= 2) {
								player.ListType = 0;
							}
							else {
								player.ListType++;
							}
							if (player.ListType == 1) {

								Players::AddToBlackList(player.AccountId);
							}
							else if (player.ListType == 2) {
								Players::AddToWhiteList(player.AccountId);
							}
							else {
								Players::RemoveList(player.AccountId);
							}
						}*/

						if (KeyName == "GroupKey")
						{
							if (GameData.Config.Item.ShowGroup != 5)
							{
								GameData.Config.Item.Enable = 1;
								GameData.Config.Item.ShowGroup++;
							}
							else {
								GameData.Config.Item.ShowGroup = 0;
								GameData.Config.Item.Enable = 0;
							}
						}

						if (KeyName == "GroupAKey")
						{
							GameData.Config.Item.Enable = 1;
							GameData.Config.Item.ShowGroup = 2;
						}

						if (KeyName == "GroupBKey")
						{
							GameData.Config.Item.Enable = 1;
							GameData.Config.Item.ShowGroup = 3;
						}

						if (KeyName == "GroupCKey")
						{
							GameData.Config.Item.Enable = 1;
							GameData.Config.Item.ShowGroup = 4;
						}

						if (KeyName == "GroupDKey")
						{
							GameData.Config.Item.Enable = 1;
							GameData.Config.Item.ShowGroup = 5;
						}

						if (KeyName == "VehicleEnable")
						{
							GameData.Config.Vehicle.Enable = !GameData.Config.Vehicle.Enable;
						}
						if (KeyName == "Menu")
						{
							GameData.Config.Menu.Show = !GameData.Config.Menu.Show;
							if (GameData.Config.Menu.Show)
							{
								SetForegroundWindow(GameData.Config.Overlay.hWnd);
							}
							else {
								SetForegroundWindow(GetDesktopWindow());
							}
						}
						if (KeyName == "AimBotConfig0")
						{
							GameData.Config.AimBot.ConfigIndex = 0;
						}
						if (KeyName == "AimBotConfig1")
						{
							GameData.Config.AimBot.ConfigIndex = 1;
						}

					}
				}
			}

			Sleep(3);
		}
	}
}
