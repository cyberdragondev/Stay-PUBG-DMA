#pragma once

#include <Windows.h>
#include <RmlUi/Core.h>
#include <RmlUi/Debugger.h>
#include <Gui/Backends/RmlUi_Backend.h>
#include <Gui/Shell/include/Shell.h>

class Gui
{
public:

    static int Init()
    {
		int width = 1024;
		int height = 768;
		if (!RmlUiShell::Initialize()) {
			return -1;
		}

		if (!Backend::Initialize("test", width, height, true))
		{
			RmlUiShell::Shutdown();
			return -1;
		}

		Rml::SetSystemInterface(Backend::GetSystemInterface());
		Rml::SetRenderInterface(Backend::GetRenderInterface());
		Rml::Initialise();
		Rml::Context* context = Rml::CreateContext("main", Rml::Vector2i(width, height));
		if (context == nullptr)
		{
			Rml::Shutdown();
			Backend::Shutdown();
			RmlUiShell::Shutdown();
			return -1;
		}

		Utils::Log(1, "111");
		Rml::Debugger::Initialise(context);
		RmlUiShell::LoadFonts();
		Utils::Log(1, "ddd");
		auto docStr = R"(<rml><head><title>Demo</title>
<style>body{background:#fff;font-family: "Microsoft YaHei";font-size: 20dp;width: 100%;height:100%;color: #000;}</style></head>
<body>Hello World</body></rml>)";
		if (Rml::ElementDocument* document = context->LoadDocumentFromMemory(docStr))
		{
			document->Show();
		}
		/*if (Rml::ElementDocument* document = context->LoadDocument("Source/Gui/Res/tutorial.rml"))
		{
			document->Show();
		}*/
		bool running = true;
		while (running)
		{
			running = Backend::ProcessEvents(context, &RmlUiShell::ProcessKeyDownShortcuts);
			context->Update();
			Backend::BeginFrame();
			context->Render();
			Backend::PresentFrame();
		}
		Rml::Shutdown();
		Backend::Shutdown();
		RmlUiShell::Shutdown();
		return 0;
    }
};