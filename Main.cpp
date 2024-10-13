#include <winsock2.h>
#include <windows.h>
#include <Overlay/Overlay.h>
#include <Common/Data.h>
#include <Utils/Utils.h>
#include <Hack/Hack.h>
#include <Common/Offset.h>
#include <thread>
#include <DMALibrary/Memory/Memory.h>
#include <cstdint>
#include <Common/Config.h>
#include <Auth/Auth.h>
#include <Utils/MachineCodeGenerator.h>
#include <Utils/w3c/w3c.h>

FGameData GameData;

using namespace std;

void saveCardKey(const std::string& cardKey) {
	std::ofstream outFile("cardKey.txt");
	if (outFile.is_open()) {
		outFile << cardKey;
		outFile.close();
	}
	/*else {
		std::cerr << "Unable to open file for saving card key.\n";
	}*/
}

std::string loadCardKey() {
	std::ifstream inFile("cardKey.txt");
	std::string cardKey;
	if (inFile.is_open()) {
		inFile >> cardKey;
		inFile.close();
	}/*
	else {
		std::cerr << "No saved card key found.\n";
	}*/
	return cardKey;
}

void deleteCardKey() {
	remove("cardKey.txt");
}

// SingleLogin | 单码用户登录
bool SingleLogin() {
	std::string HWID = MachineCodeGenerator::GenerateMachineCode();
	W3Client w3;

	W3Client client;

	bool isLoggedIn = false;
	std::string cardKey;

	if (client.Connect("http://w.eydata.net")) {
		cardKey = loadCardKey();
		if (!cardKey.empty()) {
			//std::cout << "Please enter your card key: " << cardKey << std::endl;
			//std::cout << " "  << std::endl;
			//std::cout << "Loaded card key: " << cardKey << std::endl;
			//std::cout << "Press Enter to continue (or input a new key): ";
			//std::string input;
			//std::getline(std::cin, input);
			//if (!input.empty()) {
			//	cardKey = input;
			//}

			// 单码卡密
			client.AddPostArgument("SingleCode", cardKey.c_str());
			// 程序版本
			client.AddPostArgument("Ver", "1.0");
			// 机器码
			client.AddPostArgument("Mac", HWID.c_str());
			// 接口地址
			if (client.Request("/4BEACF45F084D8F1", W3Client::reqPost)) {
				char buf[1024] = "\0";
				while (client.Response(reinterpret_cast<unsigned char*>(buf), 1024) > 0) {
					if (strlen(buf) == 32)
					{
						std::cout << "Login Success" << std::endl;
						saveCardKey(cardKey);
						strncpy(GameData.Config.eyou.globalBuf, buf, 1024);
						memset(buf, 0x00, 1024);
						return TRUE;
					}
					else {
						std::cout << "Login Faild, Tips :" << buf << std::endl;
						deleteCardKey();  // 删除保存的卡密文件
						memset(buf, 0x00, 1024);
						return FALSE;
					}
				}
			}
			client.Close();
		}
		else
		{
			std::cout << "Please enter your card key: ";
			std::cin >> cardKey;
			// 单码卡密
			client.AddPostArgument("SingleCode", cardKey.c_str());
			// 程序版本
			client.AddPostArgument("Ver", "1.0");
			// 机器码
			client.AddPostArgument("Mac", HWID.c_str());
			// 接口地址
			if (client.Request("/4BEACF45F084D8F1", W3Client::reqPost)) {
				char buf[1024] = "\0";
				while (client.Response(reinterpret_cast<unsigned char*>(buf), 1024) > 0) {
					if (strlen(buf) == 32)
					{
						std::cout << "Login Success" << std::endl;
						saveCardKey(cardKey);
						strncpy(GameData.Config.eyou.globalBuf, buf, 1024);
						memset(buf, 0x00, 1024);
						return TRUE;
					}
					else {
						std::cout << "Login Faild, Tips :" << buf << std::endl;
						deleteCardKey();  // 删除保存的卡密文件
						memset(buf, 0x00, 1024);
						return FALSE;
					}
				}
			}
			client.Close();
		}

	}
}

// GetExpired | 获取用户的到期时间
void GetExpired() {

	W3Client w3;

	W3Client client;

	if (client.Connect("http://w.eydata.net")) {
		GameData.Config.eyou.cardKey = loadCardKey();
		if (GameData.Config.eyou.cardKey.empty())
		{
			std::cout << "Please enter your card key: ";
			std::cin >> GameData.Config.eyou.cardKey;
		}
		// 用户名
		client.AddPostArgument("UserName", GameData.Config.eyou.cardKey.c_str());
		// 接口地址
		if (client.Request("/F5AC89EE9006B5CA", W3Client::reqPost)) {
			char buf[1024] = "\0";
			while (client.Response(reinterpret_cast<unsigned char*>(buf), 1024) > 0) {
				int ret = atoi(buf);
				if (ret > 0)
				{
					std::cout << "Time : [" << buf << "]" << std::endl;
				}
				else {
					std::cout << "Code :" << buf << std::endl;
				}
				memset(buf, 0x00, 1024);
			}
		}
		client.Close();
	}
}


void SetConsoleStyle()
{
	SetConsoleOutputCP(CP_UTF8);

	SetConsoleTitle("Console");

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 14;

	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	DWORD dwMode = 0;
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);

	auto hStdin = ::GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	::GetConsoleMode(hStdin, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	::SetConsoleMode(hStdin, mode);
}

int Refresh()
{
	while (true)
	{
		mem.RefreshAll();
		Sleep(1000 * 60 * 15);
	}
}

int main() {
	//std::string HWID = MachineCodeGenerator::GenerateMachineCode();
	//std::cout << HWID << std::endl;
	//Sleep(5000000);
	//4081039822 小龙
	//if (HWID != "4081039822") exit(0);
	//std::cout << HWID << std::endl;
	//Sleep(500000);
	SetConsoleStyle();

	//if (SingleLogin())
	//{
	//	GetExpired();

		Auth::Init();

		//std::thread GuiThread(Gui::Init);

		std::thread HackThread(Hack::Init);
		//std::thread TimeOuthread(TimeOut);
		std::thread OverlayThread(Overlay::Init);


		while (true)
		{
			if (GameData.Config.Window.Main) {
				Sleep(500);
				continue;
			}
			break;
		}
	//}
	//else
	//{
	//	system("pause");
	//	exit(0);
	//}


	return 0;
}

