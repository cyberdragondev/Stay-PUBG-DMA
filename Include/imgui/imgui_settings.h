#include "imgui.h"
#include "imgui_internal.h"

//namespace c
//{
//	inline ImVec4 accent_color = ImColor(149, 1, 247);
//	inline ImVec4 accent_low_color = ImColor(149, 1, 247,255/2);
//	inline ImVec4 accent_low = ImColor(174, 197, 255, 255 / 2);
//
//	inline ImVec4 accent_text_color = ImColor(245, 245, 255);
//
//	inline ImVec4 accent_text_low_color = ImColor(245, 245, 255, 255 / 2);
//
//	inline ImVec4 notify = ImColor(43, 48, 54);
//
//
//	namespace bg
//	{
//		inline ImVec4 background = ImColor(27, 24, 29, 255);
//		inline ImVec4 outline_background = ImColor(27, 29, 32, 255);
//		inline ImVec2 size = ImVec2(650, 475);
//		inline float rounding = 6;
//	}
//
//	namespace child
//	{
//		inline ImVec4 background = ImColor(33, 31, 36, 250);
//		inline ImVec4 outline_background = ImColor(27, 29, 32, 255);
//		inline float rounding = 6;
//	}
//
//	namespace checkbox
//	{
//		inline ImVec4 circle_inactive = ImColor(43, 48, 54, 255);
//
//		inline ImVec4 background = ImColor(27, 29, 32, 255);
//		inline ImVec4 outline_background = ImColor(30, 32, 36, 255);
//		inline float rounding = 30;
//	}
//
//	namespace slider
//	{
//		inline ImVec4 circle_inactive = ImColor(43, 48, 54, 255);
//
//		inline ImVec4 background = ImColor(27, 29, 32, 255);
//		inline ImVec4 outline_background = ImColor(30, 32, 36, 255);
//		inline float rounding = 30;
//	}
//
//	namespace combo
//	{
//		inline ImVec4 background = ImColor(27, 29, 32, 255);
//		inline ImVec4 outline_background = ImColor(30, 32, 36, 255);
//		inline float rounding = 3;
//	}
//
//	namespace picker
//	{
//		inline ImVec4 background = ImColor(27, 29, 32, 255);
//		inline ImVec4 outline_background = ImColor(30, 32, 36, 255);
//		inline float rounding = 2;
//	}
//
//	namespace button
//	{
//		inline ImVec4 background = ImColor(149, 1, 247);
//		inline ImVec4 outline_background = ImColor(30, 32, 36, 255);
//		inline float rounding = 4;
//	}
//
//	namespace input
//	{
//		inline ImVec4 background = ImColor(27, 29, 32, 255);
//		inline ImVec4 outline_background = ImColor(30, 32, 36, 255);
//		inline float rounding = 4;
//	}
//
//	namespace keybind
//	{
//		inline ImVec4 background = ImColor(27, 29, 32, 255);
//		inline ImVec4 outline_background = ImColor(30, 32, 36, 255);
//		inline float rounding = 3;
//	}
//
//
//	namespace text
//	{
//		inline ImVec4 text_hov = ImColor(245, 245, 255);
//		inline ImVec4 text = ImColor(90, 93, 100);
//		inline ImVec4 text2 = ImColor(90, 93, 100,0);
//		inline ImVec4 hide_text = ImColor(43, 48, 54, 255);
//
//	}
//
//	namespace tab
//	{
//		inline ImVec4 background = ImColor(35, 35, 35, 255);
//		inline float rounding = 10.f;
//	}
//}

namespace Style
{
    inline ImVec4 AccentColor = ImColor(255, 215, 0); // PUBG的黄色
    inline ImVec4 AccentLowColor = ImColor(255, 215, 0, 127); // 半透明的黄色
    inline ImVec4 AccentLow = ImColor(255, 215, 0, 127); // 半透明的黄色

    inline ImVec4 AccentTextColor = ImColor(255, 255, 255); // 白色文字
    inline ImVec4 AccentTextLowColor = ImColor(255, 255, 255, 127); // 半透明的白色文字
    inline ImVec4 Notify = ImColor(43, 48, 54); // PUBG界面的通知颜色

    inline float Padding = 18; // 设定一致的内边距

    namespace Text
    {
        inline ImVec4 TextHov = ImColor(255, 255, 255); // 文字悬停颜色
        inline ImVec4 Text = ImColor(255, 255, 255); // 白色文字
        inline ImVec4 Text2 = ImColor(255, 255, 255, 0); // 透明的文字
        inline ImVec4 HideText = ImColor(43, 48, 54, 255); // 隐藏文字颜色
    }

    namespace Window
    {
        inline ImVec2 Size = ImVec2(800, 500); // 窗口大小
        inline ImVec2 PlayerListsSize = ImVec2(736, 473); // 玩家列表大小
        inline ImVec4 Background = ImColor(20, 20, 20, 255); // 背景颜色
        inline ImVec4 OutlineBackground = ImColor(27, 29, 32, 255); // 外部背景颜色
        inline float Rounding = 10; // 圆角
    }

    namespace Keybind
    {
        inline ImVec4 Background = ImColor(35, 35, 35, 255); // 按键绑定背景色
        inline ImVec4 OutlineBackground = ImColor(0, 0, 0, 0); // 按键绑定外部背景色
        inline float Rounding = 3; // 圆角
    }

    namespace Tab
    {
        inline ImVec2 Size = ImVec2(150, 35); // 标签大小
        inline ImVec4 Background = ImColor(35, 35, 35, 255); // 标签背景色
        inline float Rounding = 10.f; // 圆角
    }

    namespace SubTab
    {
        inline ImVec2 Size = ImVec2(25, 25); // 子标签大小
        inline ImVec4 Background = ImColor(40, 40, 40, 255); // 子标签背景色
        inline ImVec4 DefBackground = ImColor(23, 23, 23, 255); // 默认子标签背景色
        inline float Rounding = 50; // 子标签圆角
        inline ImVec4 AccentTextColor = ImColor(0, 0, 0, 255); // 子标签文字颜色
    }

    namespace Layout
    {
        inline ImVec4 Background = ImColor(25, 25, 25, 255); // 布局背景色
    }

    namespace Input
    {
        inline ImVec4 Background = ImColor(30, 30, 30, 255); // 输入框背景色
        inline ImVec4 OutlineBackground = ImColor(0, 0, 0, 0); // 输入框外部背景色
        inline float Rounding = 4; // 圆角
    }

    namespace Child
    {
        inline ImVec4 Background = ImColor(25, 25, 25, 255); // 子窗口背景色
        inline ImVec4 OutlineBackground = ImColor(0, 0, 0, 0); // 子窗口外部背景色
        inline float Rounding = 6; // 圆角
    }

    namespace Checkbox
    {
        inline ImVec4 CircleInactive = ImColor(43, 48, 54, 255); // 未选中的复选框圆圈颜色
        inline ImVec4 Background = ImColor(30, 30, 30, 255); // 复选框背景色
        inline ImVec4 OutlineBackground = ImColor(0, 0, 0, 0); // 复选框外部背景色
        inline float Rounding = 30; // 圆角
    }

    namespace Slider
    {
        inline ImVec4 CircleInactive = ImColor(255, 255, 255, 255); // 未选中的滑块圆圈颜色
        inline ImVec4 Background = ImColor(30, 30, 30, 255); // 滑块背景色
        inline ImVec4 OutlineBackground = ImColor(0, 0, 0, 0); // 滑块外部背景色
        inline float Rounding = 30; // 圆角
    }

    namespace Combo
    {
        inline ImVec4 Background = ImColor(35, 35, 35, 255); // 下拉框背景色
        inline ImVec4 OutlineBackground = ImColor(0, 0, 0, 0); // 下拉框外部背景色
        inline float Rounding = 3; // 圆角
    }

    namespace Picker
    {
        inline ImVec4 Background = ImColor(35, 35, 35, 255); // 颜色选择器背景色
        inline ImVec4 OutlineBackground = ImColor(0, 0, 0, 0); // 颜色选择器外部背景色
        inline float Rounding = 2; // 圆角
    }
}