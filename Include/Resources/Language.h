#pragma once
#include "..\Font\IconsFontAwesome5.h"
#include "utils/utils.h"

namespace Lang
{
	struct
	{
		const char* SwitchButton;
		const char* FeatureSettings;
	} Global;

	struct
	{
		const char* FeatureName;
		const char* Box;
		const char* BoxRounding;
		const char* FilledBox;
		const char* FilledAlpha;
		const char* Skeleton;
		const char* HeadBox;
		const char* EyeRay;
		const char* HealthBar;
		const char* Weapon;
		const char* Distance;
		const char* PlayerName;
		const char* SnapLine;
		const char* LinePosList;
		const char* VisCheck;
		const char* Preview;
		const char* CollapseHead;
		const char* Penis;
		const char* PenisLength;
		const char* PenisSize;
		const char* MultiColor;
		const char* MultiColTip;

		const char* BoxType_Normal;
		const char* BoxType_Edge;
		const char* BoxType_Corner1;
		const char* BoxType_Corner2;
		const char* BarType_Top;
		const char* BarType_Vertical;
		const char* HeadBoxType_Normal;
		const char* HeadBoxType_Flat;
		const char* LinePos_1;
		const char* LinePos_2;
		const char* LinePos_3;
	} ESPtext;

	struct
	{
		const char* FeatureName;
		const char* HotKeyList;
		const char* Toggle;
		const char* DrawFov;
		const char* VisCheck;
		const char* JumpCheck;
		const char* FovSlider;
		const char* SmoothSlider;
		const char* BoneList;
		const char* Tip;

		const char* Bone_1;
		const char* Bone_2;
		const char* Bone_3;
		const char* Bone_4;
	} AimbotText;

	struct
	{
		const char* FeatureName;
	} GlowText;

	struct
	{
		const char* FeatureName;
		const char* StyleList;
		const char* CustomCheck;
		const char* CrossLine;
		const char* SizeSlider;
		const char* ProportionSlider;
		const char* RangeSlider;
		const char* AlphaSlider;

		const char* Style_1;
		const char* Style_2;
		const char* Style_3;
	} RadarText;

	struct
	{
		const char* FeatureName;
		const char* HotKeyList;
		const char* Toggle;
		const char* DelaySlider;
		const char* FakeShotSlider;
	} TriggerText;

	struct
	{
		const char* FeatureName;
		const char* PresetList;
		const char* ColorEditor;
		const char* Dot;
		const char* DotSizeSlider;
		const char* Outline;
		const char* Crossline;
		const char* hLengthSlider;
		const char* vLengthSilder;
		const char* GapSlider;
		const char* ThicknessSlider;
		const char* tStyle;
		const char* Circle;
		const char* RadiusSlider;
		const char* TargetCheck;
		const char* TeamCheck;
	} CrosshairsText;

	struct
	{
		const char* FeatureName;
		const char* ThemeList;
		const char* StyleList;
		const char* HeadshotLine;
		const char* SpecCheck;
		const char* NoFlash;
		const char* HitSound;
		const char* bmbTimer;
		const char* SpecList;
		const char* Bhop;
		const char* Watermark;
		const char* CheatList;
		const char* TeamCheck;
		const char* AntiRecord;

		const char* LanguageList;
	} MiscText;

	struct
	{
		const char* FeatureName;
		const char* Load;
		const char* Save;
		const char* Delete;
		const char* Reset;
		const char* Create;
		const char* OpenFolder;
		const char* SeparateLine;
	} ConfigText;

	struct
	{
		const char* FeatureName;
		const char* LastUpdate;
		const char* SourceButton;
		const char* DiscordButton;
		const char* OffsetsTitle;
	} ReadMeText;

	inline void English()
	{
		Global.SwitchButton = U8("Enable");
		Global.FeatureSettings = U8("Settings");

		// ESP
		ESPtext.FeatureName = U8(" ESP");
		ESPtext.Box = U8("Box");
		ESPtext.BoxRounding = U8("Box Rounding");
		ESPtext.FilledBox = U8("Filled Box");
		ESPtext.FilledAlpha = U8("Filled Box Alpha");
		ESPtext.Skeleton = U8("Skeleton");
		ESPtext.HeadBox = U8("Head Box");
		ESPtext.EyeRay = U8("Eye Ray");
		ESPtext.HealthBar = U8("Health Bar");
		ESPtext.Weapon = U8("Weapon");
		ESPtext.Distance = U8("Distance");
		ESPtext.PlayerName = U8("Name");
		ESPtext.SnapLine = U8("SnapLine");
		ESPtext.LinePosList = U8("LinePos");
		ESPtext.VisCheck = U8("Visible Check");
		ESPtext.Preview = U8("Preview Window");
		ESPtext.CollapseHead = U8("SexyESP");
		ESPtext.Penis = U8("Show Penis");
		ESPtext.PenisLength = U8("Length");
		ESPtext.PenisSize = U8("Size");
		ESPtext.MultiColor = U8("Multi-Color");
		ESPtext.MultiColTip = U8("Only work when the box has non-rounded corners.");

		// Aimbot
		AimbotText.FeatureName = U8(" Aimbot");
		AimbotText.HotKeyList = U8("Key");
		AimbotText.Toggle = U8("Toggle Mode");
		AimbotText.DrawFov = U8("Draw Fov");
		AimbotText.VisCheck = U8("Visible Only");
		AimbotText.JumpCheck = U8("On Ground Only");
		AimbotText.FovSlider = U8("FOV");
		AimbotText.SmoothSlider = U8("Smooth");
		AimbotText.BoneList = U8("Bone");
		AimbotText.Tip = U8("Aimbot will not work while the menu is opened");

		// Glow
		GlowText.FeatureName = U8(" Glow");

		// Radar
		RadarText.FeatureName = U8(" Radar");
		RadarText.StyleList = U8("Style");
		RadarText.CustomCheck = U8("Custom");
		RadarText.CrossLine = U8("Cross Line");
		RadarText.SizeSlider = U8("Point Size");
		RadarText.ProportionSlider = U8("Proportion");
		RadarText.RangeSlider = U8("Range");
		RadarText.AlphaSlider = U8("Window Background Alpha");

		// Triggerbot
		TriggerText.FeatureName = U8(" Triggerbot");
		TriggerText.HotKeyList = U8("HotKey");
		TriggerText.Toggle = U8("Always Active");
		TriggerText.DelaySlider = U8("Shot Delay");
		TriggerText.FakeShotSlider = U8("Shot Duration");

		// Crosshairs
		CrosshairsText.FeatureName = U8(" Crosshairs");
		CrosshairsText.PresetList = U8("Presets");
		CrosshairsText.ColorEditor = U8("Crosshairs Color");
		CrosshairsText.Dot = U8("Center Dot");
		CrosshairsText.DotSizeSlider = U8("Dot Size");
		CrosshairsText.Outline = U8("Outline");
		CrosshairsText.Crossline = U8("Cross Line");
		CrosshairsText.hLengthSlider = U8("Horizontal Length");
		CrosshairsText.vLengthSilder = U8("Vertical Length");
		CrosshairsText.GapSlider = U8("Gap");
		CrosshairsText.ThicknessSlider = U8("Thickness");
		CrosshairsText.tStyle = U8("T Style");
		CrosshairsText.Circle = U8("Circle");
		CrosshairsText.RadiusSlider = U8("Circle Radius");
		CrosshairsText.TargetCheck = U8("Targeting Crosshairs");
		CrosshairsText.TeamCheck = U8("TeamCheck");

		// Misc
		MiscText.FeatureName = U8(" Misc");
		MiscText.ThemeList = U8("Theme");
		MiscText.StyleList = U8("Style");
		MiscText.HeadshotLine = U8("Headshot Line");
		MiscText.SpecCheck = U8("Cheat in Spec");
		MiscText.NoFlash = U8("No Flash");
		MiscText.HitSound = U8("Hit Sound");
		MiscText.bmbTimer = U8("Bomb Timer");
		MiscText.SpecList = U8("Spec List");
		MiscText.Bhop = U8("Bunny Hop");
		MiscText.Watermark = U8("Watermark");
		MiscText.CheatList = U8("Cheat List");
		MiscText.TeamCheck = U8("TeamCheck");
		MiscText.AntiRecord = U8("Bypass OBS");

		MiscText.LanguageList = U8("Language");

		// Config Menu
		ConfigText.FeatureName = U8(" Config");
		ConfigText.Load = U8("Load Selected");
		ConfigText.Save = U8("Save Selected");
		ConfigText.Delete = U8("Delete Selected");
		ConfigText.Reset = U8("Reset Config");
		ConfigText.Create = U8("Create Config");
		ConfigText.OpenFolder = U8("Open Folder");
		ConfigText.SeparateLine = U8("Save Config");

		// Readme Menu
		ReadMeText.FeatureName = U8(" README");
		ReadMeText.LastUpdate = U8("Last update: ");
		ReadMeText.SourceButton = U8(" Source Code");
		ReadMeText.DiscordButton = U8(" Join Discord");
		ReadMeText.OffsetsTitle = U8("Offsets:");
	}

	// Translated by @styx
	inline void German()
	{
		Global.SwitchButton = U8("Aktivieren");
		Global.FeatureSettings = U8("Settings");

		// ESP
		ESPtext.FeatureName = U8(" ESP");
		ESPtext.Box = U8("Box");
		ESPtext.BoxRounding = U8("Kasten rundung");
		ESPtext.FilledBox = U8("Gefüllte Kiste");
		ESPtext.FilledAlpha = U8("Gefülltes Feld Alpha");
		ESPtext.Skeleton = U8("Skelett");
		ESPtext.HeadBox = U8("Kopf kasten");
		ESPtext.EyeRay = U8("Auge Strahl");
		ESPtext.HealthBar = U8("Gesundheitsbar");
		ESPtext.Weapon = U8("Waffe");
		ESPtext.Distance = U8("Distanz");
		ESPtext.PlayerName = U8("Name");
		ESPtext.SnapLine = U8("Schnapp Linie");
		ESPtext.LinePosList = U8("Linie Pos");
		ESPtext.VisCheck = U8("Sichtbarer Scheck");
		ESPtext.Preview = U8("Vorschaufenster");
		ESPtext.CollapseHead = U8("SexyESP");
		ESPtext.Penis = U8("Penis Zeigen");
		ESPtext.PenisLength = U8("Länge");
		ESPtext.PenisSize = U8("Größe");

		// Aimbot
		AimbotText.FeatureName = U8(" Aimbot");
		AimbotText.HotKeyList = U8("Key");
		AimbotText.Toggle = U8("Toggle Modus");
		AimbotText.DrawFov = U8("Draw Fov");
		AimbotText.VisCheck = U8("Nur sichtbar");
		AimbotText.JumpCheck = U8("Nur am Boden");
		AimbotText.FovSlider = U8("FOV");
		AimbotText.SmoothSlider = U8("Smooth");
		AimbotText.BoneList = U8("Bone");
		AimbotText.Tip = U8("Aimbot funktioniert nicht, während das menü geöffnet ist.");

		// Glow
		GlowText.FeatureName = U8(" Glow");

		// Radar
		RadarText.FeatureName = U8(" Radar");
		RadarText.StyleList = U8("Style");
		RadarText.CustomCheck = U8("Custom");
		RadarText.CrossLine = U8("Cross Line");
		RadarText.SizeSlider = U8("Punktgröße");
		RadarText.ProportionSlider = U8("Proportion");
		RadarText.RangeSlider = U8("Range");
		RadarText.AlphaSlider = U8("Fensterhintergrund Alpha");

		// Triggerbot
		TriggerText.FeatureName = U8(" Triggerbot");
		TriggerText.HotKeyList = U8("HotKey");
		TriggerText.Toggle = U8("Immer aktiv");
		TriggerText.DelaySlider = U8("Shot Delay");
		TriggerText.FakeShotSlider = U8("Shot Duration");

		// Crosshair
		CrosshairsText.FeatureName = U8(" Crosshairs");
		CrosshairsText.PresetList = U8("Presets");
		CrosshairsText.ColorEditor = U8("Crosshairs Color");
		CrosshairsText.Dot = U8("Center Dot");
		CrosshairsText.DotSizeSlider = U8("Punktgröße");
		CrosshairsText.Outline = U8("Outline");
		CrosshairsText.Crossline = U8("Cross Line");
		CrosshairsText.hLengthSlider = U8("Horizontale Länge");
		CrosshairsText.vLengthSilder = U8("Vertikale Länge");
		CrosshairsText.GapSlider = U8("Gap");
		CrosshairsText.ThicknessSlider = U8("Thickness");
		CrosshairsText.tStyle = U8("T Style");
		CrosshairsText.Circle = U8("Circle");
		CrosshairsText.RadiusSlider = U8("Kreisradius");
		CrosshairsText.TargetCheck = U8("Ziel Fadenkreuz");
		CrosshairsText.TeamCheck = U8("TeamCheck");

		// Misc
		MiscText.FeatureName = U8(" Misc");
		MiscText.ThemeList = U8("Theme");
		MiscText.StyleList = U8("Style");
		MiscText.HeadshotLine = U8("Headshot Line");
		MiscText.SpecCheck = U8("Cheat in Spec");
		MiscText.NoFlash = U8("Kein Flash");
		MiscText.HitSound = U8("Hit Sound");
		MiscText.bmbTimer = U8("Bomben-Timer");
		MiscText.SpecList = U8("Spec List");
		MiscText.Bhop = U8("Bunny Hop");
		MiscText.Watermark = U8("Watermark");
		MiscText.CheatList = U8("Cheat Liste");
		MiscText.TeamCheck = U8("TeamCheck");
		MiscText.AntiRecord = U8("OBS umgehen");

		MiscText.LanguageList = U8("Sprache");

		// Config Menu
		ConfigText.FeatureName = U8(" Config");
		ConfigText.Load = U8("Ausgewählte laden");
		ConfigText.Save = U8("Ausgewählte speichern");
		ConfigText.Delete = U8("Ausgewählte löschen");
		ConfigText.Reset = U8("Konfiguration zurücksetzen");
		ConfigText.Create = U8("Konfiguration erstellen");
		ConfigText.OpenFolder = U8("Ordner öffnen");
		ConfigText.SeparateLine = U8("Konfiguration speichern");

		// Readme menu
		ReadMeText.FeatureName = U8(" README");
		ReadMeText.LastUpdate = U8("Letzte Aktualisierung: ");
		ReadMeText.SourceButton = U8(" Quellcode");
		ReadMeText.DiscordButton = U8(" Discord beitreten");
		ReadMeText.OffsetsTitle = U8("Offsets:");
	}

	// Translated by @Hazetick
	// @Hazetick: The translation could be slightly different than it should be
	inline void Polish()
	{
		Global.SwitchButton = U8("Włącz");
		Global.FeatureSettings = U8("Ustawienia");

		// ESP
		ESPtext.FeatureName = U8(" ESP");
		ESPtext.Box = U8("Box");
		ESPtext.BoxRounding = U8("Zaokrąglenie Boxa");
		ESPtext.FilledBox = U8("Wypełniony Box");
		ESPtext.FilledAlpha = U8("Przezroczystość Wypełnionego Boxa");
		ESPtext.Skeleton = U8("Szkielet");
		ESPtext.HeadBox = U8("Box Głowy");
		ESPtext.EyeRay = U8("Promień Oka");
		ESPtext.HealthBar = U8("Pasek Życia");
		ESPtext.Weapon = U8("Broń");
		ESPtext.Distance = U8("Dystans");
		ESPtext.PlayerName = U8("Imię Gracza");
		ESPtext.SnapLine = U8("Linia Łapania");
		ESPtext.LinePosList = U8("Lista Pozycji Linii");
		ESPtext.VisCheck = U8("Sprawdzenie Widoczności");
		ESPtext.Preview = U8("Okno Podglądu");
		ESPtext.CollapseHead = U8("SeksownyESP");
		ESPtext.Penis = U8("Pokaż Penis");
		ESPtext.PenisLength = U8("Długość Penisa");
		ESPtext.PenisSize = U8("Rozmiar Penisa");
		ESPtext.MultiColor = U8("Wielokolorowy");
		ESPtext.MultiColTip = U8("Działa tylko wtedy, gdy pudełko nie ma zaokrąglonych rogów.");

		// Aimbot
		AimbotText.FeatureName = U8(" Aimbot");
		AimbotText.HotKeyList = U8("Klawisz");
		AimbotText.Toggle = U8("Tryb Przełączania");
		AimbotText.DrawFov = U8("Rysuj FOV");
		AimbotText.VisCheck = U8("Tylko Widoczne");
		AimbotText.JumpCheck = U8("Tylko na Ziemi");
		AimbotText.FovSlider = U8("FOV");
		AimbotText.SmoothSlider = U8("Gładkość");
		AimbotText.BoneList = U8("Kości");
		AimbotText.Tip = U8("Aimbot nie będzie działał, gdy menu jest otwarte");

		// Glow
		GlowText.FeatureName = U8(" Podświetlenie");

		// Radar
		RadarText.FeatureName = U8(" Radar");
		RadarText.StyleList = U8("Styl");
		RadarText.CustomCheck = U8("Niesterowane");
		RadarText.CrossLine = U8("Linia Przekreślająca");
		RadarText.SizeSlider = U8("Rozmiar Punktu");
		RadarText.ProportionSlider = U8("Proporcje");
		RadarText.RangeSlider = U8("Zasięg");
		RadarText.AlphaSlider = U8("Przezroczystość Tła Okna");

		// Triggerbot
		TriggerText.FeatureName = U8(" Triggerbot");
		TriggerText.HotKeyList = U8("Klawisz");
		TriggerText.Toggle = U8("Zawsze Aktywny");
		TriggerText.DelaySlider = U8("Opóźnienie Strzału");
		TriggerText.FakeShotSlider = U8("Czas Trwania Strzału");

		// Crosshairs
		CrosshairsText.FeatureName = U8(" Celowniki");
		CrosshairsText.PresetList = U8("Ustawienia Wstępne");
		CrosshairsText.ColorEditor = U8("Kolor Celownika");
		CrosshairsText.Dot = U8("Kropka Środkowa");
		CrosshairsText.DotSizeSlider = U8("Rozmiar Kropki");
		CrosshairsText.Outline = U8("Kontur");
		CrosshairsText.Crossline = U8("Linia Przekreślająca");
		CrosshairsText.hLengthSlider = U8("Długość Pozioma");
		CrosshairsText.vLengthSilder = U8("Długość Pionowa");
		CrosshairsText.GapSlider = U8("Przerwa");
		CrosshairsText.ThicknessSlider = U8("Grubość");
		CrosshairsText.tStyle = U8("Styl T");
		CrosshairsText.Circle = U8("Okrąg");
		CrosshairsText.RadiusSlider = U8("Promień Okręgu");
		CrosshairsText.TargetCheck = U8("Celowanie Celownikiem");
		CrosshairsText.TeamCheck = U8("Sprawdzanie Drużyny");

		// Misc
		MiscText.FeatureName = U8(" Różne");
		MiscText.ThemeList = U8("Motyw");
		MiscText.StyleList = U8("Styl");
		MiscText.HeadshotLine = U8("Linia Headshot");
		MiscText.SpecCheck = U8("Czituj w Widoku Spec");
		MiscText.NoFlash = U8("Brak Ślepący");
		MiscText.HitSound = U8("Dźwięk Trafienia");
		MiscText.bmbTimer = U8("Minutnik Bomby");
		MiscText.SpecList = U8("Lista Widzów");
		MiscText.Bhop = U8("Bunny Hop");
		MiscText.Watermark = U8("Znak Wodny");
		MiscText.CheatList = U8("Lista Czitów");
		MiscText.TeamCheck = U8("Sprawdzanie Drużyny");
		MiscText.AntiRecord = U8("Ominięcie OBS");

		MiscText.LanguageList = U8("Język");

		// Config Menu
		ConfigText.FeatureName = U8(" Konfiguracja");
		ConfigText.Load = U8("Wczytaj Wybrane");
		ConfigText.Save = U8("Zapisz Wybrane");
		ConfigText.Delete = U8("Usuń Wybrane");
		ConfigText.Reset = U8("Resetuj Konfig");
		ConfigText.Create = U8("Utwórz Konfig");
		ConfigText.OpenFolder = U8("Otwórz Folder");
		ConfigText.SeparateLine = U8("Oddziel Linia");

		// Readme Menu
		ReadMeText.FeatureName = U8(" PRZECZYTAJ");
		ReadMeText.LastUpdate = U8("Ostatnia Aktualizacja: ");
		ReadMeText.SourceButton = U8("Kod Źródłowy");
		ReadMeText.DiscordButton = U8("Dołącz do Discorda");
		ReadMeText.OffsetsTitle = U8("Przesunięcia:");
	}

	// Translated by @gScream.
	inline void Russian()
	{
		Global.SwitchButton = U8("Включить");
		Global.FeatureSettings = U8("Настройки");

		// ESP
		ESPtext.FeatureName = U8(" ESP (WH)");
		ESPtext.Box = U8("Обводка");
		ESPtext.BoxRounding = U8("Округление обводки");
		ESPtext.FilledBox = U8("Заполненная обводка");
		ESPtext.FilledAlpha = U8("Прозрачность заполненной обводки");
		ESPtext.Skeleton = U8("Скелет цели");
		ESPtext.HeadBox = U8("Бокс головы цели");
		ESPtext.EyeRay = U8("Направление зрения цели");
		ESPtext.HealthBar = U8("Полоска здоровья цели");
		ESPtext.Weapon = U8("Оружие цели");
		ESPtext.Distance = U8("Дистанция до цели");
		ESPtext.PlayerName = U8("Имя цели");
		ESPtext.SnapLine = U8("Линия к противнику");
		ESPtext.LinePosList = U8("Позиция линии");
		ESPtext.VisCheck = U8("Только если цель в поле зрения");
		ESPtext.Preview = U8("Отобразить предпросмотр WH");
		ESPtext.CollapseHead = U8("Секс WH");
		ESPtext.Penis = U8("Показать пенис");
		ESPtext.PenisLength = U8("Длина");
		ESPtext.PenisSize = U8("Размер");
		ESPtext.MultiColor = U8("Мульти-цвет");
		ESPtext.MultiColTip = U8("Работает только когда обводка не имеет закругленные края.");

		// Aimbot
		AimbotText.FeatureName = U8(" Аимбот");
		AimbotText.HotKeyList = U8("Горячая клавиша");
		AimbotText.Toggle = U8("Режим переключения");
		AimbotText.DrawFov = U8("Отобразить поле зрение");
		AimbotText.VisCheck = U8("Только если цель в поле зрения");
		AimbotText.JumpCheck = U8("Только на земле ");
		AimbotText.FovSlider = U8("Радиус поля зрения");
		AimbotText.SmoothSlider = U8("Сглаживание");
		AimbotText.BoneList = U8("Скелет");
		AimbotText.Tip = U8("Для работы Аимбота нужно закрыть меню (Insert)");

		// Glow
		GlowText.FeatureName = U8(" Свечение");

		// Radar
		RadarText.FeatureName = U8(" Радар");
		RadarText.StyleList = U8("Стиль");
		RadarText.CustomCheck = U8("Кастомный");
		RadarText.CrossLine = U8("Перекрестье");
		RadarText.SizeSlider = U8("Размер точки");
		RadarText.ProportionSlider = U8("Пропорции");
		RadarText.RangeSlider = U8("Радиус");
		RadarText.AlphaSlider = U8("Прозрачность радара");

		// Triggerbot
		TriggerText.FeatureName = U8(" Триггербот");
		TriggerText.HotKeyList = U8("Горячая клавиша");
		TriggerText.Toggle = U8("Всегда активен");
		TriggerText.DelaySlider = U8("Задержка перед выстрелом");
		TriggerText.FakeShotSlider = U8("Продолжительность выстрела");

		// Crosshairs
		CrosshairsText.FeatureName = U8(" Прицелы");
		CrosshairsText.PresetList = U8("Пресеты");
		CrosshairsText.ColorEditor = U8("Цвета прицела");
		CrosshairsText.Dot = U8("Точка в центре");
		CrosshairsText.DotSizeSlider = U8("Размер точки");
		CrosshairsText.Outline = U8("Контур");
		CrosshairsText.Crossline = U8("Перекрестье");
		CrosshairsText.hLengthSlider = U8("Горизонтальная длина");
		CrosshairsText.vLengthSilder = U8("Вертикальная длина");
		CrosshairsText.GapSlider = U8("Пробел");
		CrosshairsText.ThicknessSlider = U8("Широта");
		CrosshairsText.tStyle = U8("Прицел в стиле буквы Т");
		CrosshairsText.Circle = U8("Круг");
		CrosshairsText.RadiusSlider = U8("Радиус круга");
		CrosshairsText.TargetCheck = U8("Нацеливание прицела");
		CrosshairsText.TeamCheck = U8("Режим своих напарников");

		// Misc
		MiscText.FeatureName = U8(" Дополнительно");
		MiscText.ThemeList = U8("Тема");
		MiscText.StyleList = U8("Стиль");
		MiscText.HeadshotLine = U8("Высотная линия головы");
		MiscText.SpecCheck = U8("Отображение при наблюдении");
		MiscText.NoFlash = U8("Анти-слепота");
		MiscText.HitSound = U8("Звук попадания");
		MiscText.bmbTimer = U8("Таймер до взрыва C4");
		MiscText.SpecList = U8("Список наблюдателей");
		MiscText.Bhop = U8("Бхоп");
		MiscText.Watermark = U8("Водяной знак");
		MiscText.CheatList = U8("Список активных читов");
		MiscText.TeamCheck = U8("Режим своих напарников");
		MiscText.AntiRecord = U8("Обход записи/демонстрации");

		MiscText.LanguageList = U8("Язык");

		// Config Menu
		ConfigText.FeatureName = U8(" Конфигурация");
		ConfigText.Load = U8("Загрузить выделенное");
		ConfigText.Save = U8("Сохранить выделенное");
		ConfigText.Delete = U8("Удалить выделенное");
		ConfigText.Reset = U8("Восстановить стандартные настройки");
		ConfigText.Create = U8("Создать конфигурацию");
		ConfigText.OpenFolder = U8("Открыть папку с конфигурациями");
		ConfigText.SeparateLine = U8("Сохранить конфигурацию");

		// Readme Menu
		ReadMeText.FeatureName = U8(" ОТКРОЙ");
		ReadMeText.LastUpdate = U8("Последнее обновление: ");
		ReadMeText.SourceButton = U8(" Исходный код");
		ReadMeText.DiscordButton = U8(" Присоединиться к дискорд серверу");
		ReadMeText.OffsetsTitle = U8("Оффсеты:");
	}

	// Translated by @5mmod
	inline void Danish()
	{
		Global.SwitchButton = U8("Slå til");
		Global.FeatureSettings = U8("Indstillinger");

		// ESP
		ESPtext.FeatureName = U8(" ESP");
		ESPtext.Box = U8("Boks");
		ESPtext.BoxRounding = U8("Boks Runding");
		ESPtext.FilledBox = U8("Fyldet Boks");
		ESPtext.FilledAlpha = U8("Fyldet Boks Alfa");
		ESPtext.Skeleton = U8("Skelet");
		ESPtext.HeadBox = U8("Hoved Boks");
		ESPtext.EyeRay = U8("Øjenståle");
		ESPtext.HealthBar = U8("Liv Bar");
		ESPtext.Weapon = U8("Våben");
		ESPtext.Distance = U8("Distance");
		ESPtext.PlayerName = U8("Navn");
		ESPtext.SnapLine = U8("SnapLinje");
		ESPtext.LinePosList = U8("LinjePos");
		ESPtext.VisCheck = U8("Synlig Tjek");
		ESPtext.Preview = U8("Visnings Vindue");
		ESPtext.CollapseHead = U8("Sexet ESP");
		ESPtext.Penis = U8("Vis Pik");
		ESPtext.PenisLength = U8("Længde");
		ESPtext.PenisSize = U8("Størrelse");
		ESPtext.MultiColor = U8("Multi-farvet");
		ESPtext.MultiColTip = U8("Virker kun, når boksen ikke har afrundede hjørner.");


		// Aimbot
		AimbotText.FeatureName = U8(" Aimbot");
		AimbotText.HotKeyList = U8("Nøgle");
		AimbotText.Toggle = U8("Skift tilstand");
		AimbotText.DrawFov = U8("Tegn Fov");
		AimbotText.VisCheck = U8("Synlig Kun");
		AimbotText.JumpCheck = U8("På jorden kun");
		AimbotText.FovSlider = U8("FOV");
		AimbotText.SmoothSlider = U8("Glat");
		AimbotText.BoneList = U8("Knogle");
		AimbotText.Tip = U8("Aimbot vil ikke virke i mens menuen er åbent");

		// Glow
		GlowText.FeatureName = U8(" Glød");

		// Radar
		RadarText.FeatureName = U8(" Radar");
		RadarText.StyleList = U8("Stil");
		RadarText.CustomCheck = U8("Brugerdefineret");
		RadarText.CrossLine = U8("Krydslinje");
		RadarText.SizeSlider = U8("Point Størrelse");
		RadarText.ProportionSlider = U8("Del");
		RadarText.RangeSlider = U8("Afstand");
		RadarText.AlphaSlider = U8("Vindue Bagground Alfa");

		// Triggerbot
		TriggerText.FeatureName = U8(" Triggerbot");
		TriggerText.HotKeyList = U8("HotNøgle");
		TriggerText.Toggle = U8("Altid Aktiv");
		TriggerText.DelaySlider = U8("Skud forsinkelse");
		TriggerText.FakeShotSlider = U8("Skud Varighed");

		// Crosshairs
		CrosshairsText.FeatureName = U8(" Crosshairs");
		CrosshairsText.PresetList = U8("Forudindstillinger");
		CrosshairsText.ColorEditor = U8("Crosshairs Farvet");
		CrosshairsText.Dot = U8("Centrum Prik");
		CrosshairsText.DotSizeSlider = U8("Prik Størrelse");
		CrosshairsText.Outline = U8("Udelinje");
		CrosshairsText.Crossline = U8("Kryds Linje");
		CrosshairsText.hLengthSlider = U8("Vandret Længte");
		CrosshairsText.vLengthSilder = U8("Lodret Længte");
		CrosshairsText.GapSlider = U8("Mellemrum");
		CrosshairsText.ThicknessSlider = U8("Tykhed");
		CrosshairsText.tStyle = U8("T Stil");
		CrosshairsText.Circle = U8("Cirkel");
		CrosshairsText.RadiusSlider = U8("Cirkel Radius");
		CrosshairsText.TargetCheck = U8("Rettet Mod Crosshairs");
		CrosshairsText.TeamCheck = U8("Holdtjek");

		// Misc
		MiscText.FeatureName = U8(" Diverse");
		MiscText.ThemeList = U8("Tema");
		MiscText.StyleList = U8("Stil");
		MiscText.HeadshotLine = U8("Hovedskud Linje");
		MiscText.SpecCheck = U8("Snyd i Spec");
		MiscText.NoFlash = U8("Ingen Flash");
		MiscText.HitSound = U8("Skud Lyd");
		MiscText.bmbTimer = U8("Bombe Timer");
		MiscText.SpecList = U8("Spec Liste");
		MiscText.Bhop = U8("Kanin Hop");
		MiscText.Watermark = U8("Vandmærke");
		MiscText.CheatList = U8("Snyd Liste");
		MiscText.TeamCheck = U8("HoldTjek");
		MiscText.AntiRecord = U8("Bypass OBS");

		MiscText.LanguageList = U8("Sprog");

		// Config Menu
		ConfigText.FeatureName = U8(" Config");
		ConfigText.Load = U8("Load Valgt");
		ConfigText.Save = U8("Gem Valgt");
		ConfigText.Delete = U8("Slet Valgt");
		ConfigText.Reset = U8("Nulstil Config");
		ConfigText.Create = U8("Lav Config");
		ConfigText.OpenFolder = U8("Åben Mappe");
		ConfigText.SeparateLine = U8("Gem Config");

		// Readme Menu
		ReadMeText.FeatureName = U8(" LÆSMIG");
		ReadMeText.LastUpdate = U8("Sidste opdatering: ");
		ReadMeText.SourceButton = U8(" Source Code");
		ReadMeText.DiscordButton = U8(" Join Discord");
		ReadMeText.OffsetsTitle = U8("Offsets:");
	}

	// Translated by @vsantos1
	inline void Portuguese()
	{
		Global.SwitchButton = U8("Ativar");
		Global.FeatureSettings = U8("Definições");

		// ESP
		ESPtext.FeatureName = U8(" ESP");
		ESPtext.Box = U8("Box");
		ESPtext.BoxRounding = U8("Borda da Caixa");
		ESPtext.FilledBox = U8("Preenchimento da Caixa");
		ESPtext.FilledAlpha = U8("Preenchimento da Caixa Alfa");
		ESPtext.Skeleton = U8("Esqueleto");
		ESPtext.HeadBox = U8("Caixa na CabeÃ§a");
		ESPtext.EyeRay = U8("Mirando em");
		ESPtext.HealthBar = U8("Barra de Vida");
		ESPtext.Weapon = U8("Arma");
		ESPtext.Distance = U8("Distancia");
		ESPtext.PlayerName = U8("Nome");
		ESPtext.SnapLine = U8("Linha de Distancia");
		ESPtext.LinePosList = U8("Linha de Posicao");
		ESPtext.VisCheck = U8("Apenas Visiveis");
		ESPtext.Preview = U8("Janela de Visualizacao");
		ESPtext.CollapseHead = U8("ESP Sensual");
		ESPtext.Penis = U8("Mostrar Penis");
		ESPtext.PenisLength = U8("Comprimento");
		ESPtext.PenisSize = U8("Tamanho");
		ESPtext.MultiColor = U8("Multicolorido");
		ESPtext.MultiColTip = U8("Só funciona quando a caixa tem cantos não arredondados.");

		// Aimbot
		AimbotText.FeatureName = U8(" Aimbot");
		AimbotText.HotKeyList = U8("Tecla");
		AimbotText.Toggle = U8("Modo Alternado");
		AimbotText.DrawFov = U8("Desenhar Campo de Visao");
		AimbotText.VisCheck = U8("Apenas Visiveis");
		AimbotText.JumpCheck = U8("Apenas no Chao");
		AimbotText.FovSlider = U8("Campo de Visao");
		AimbotText.SmoothSlider = U8("Suavidade");
		AimbotText.BoneList = U8("Target");
		AimbotText.Tip = U8("Aimbot nao funcionara com menu aberto");

		// Glow
		GlowText.FeatureName = U8(" Glow");

		// Radar
		RadarText.FeatureName = U8(" Radar");
		RadarText.StyleList = U8("Estilo");
		RadarText.CustomCheck = U8("Customizado");
		RadarText.CrossLine = U8("Linha cruzada");
		RadarText.SizeSlider = U8("Tamanho do Ponto");
		RadarText.ProportionSlider = U8("Proporcao");
		RadarText.RangeSlider = U8("Alcance");
		RadarText.AlphaSlider = U8("Fundo da Janela Alfa");

		// Triggerbot
		TriggerText.FeatureName = U8(" Triggerbot");
		TriggerText.HotKeyList = U8("Tecla");
		TriggerText.Toggle = U8("Sempre ativo");
		TriggerText.DelaySlider = U8("Tempo de Disparo");
		TriggerText.FakeShotSlider = U8("Duracao de Disparo");

		// Crosshairs
		CrosshairsText.FeatureName = U8(" Miras");
		CrosshairsText.PresetList = U8("Predefinidos");
		CrosshairsText.ColorEditor = U8("Cores da Mira");
		CrosshairsText.Dot = U8("Ponto Central");
		CrosshairsText.DotSizeSlider = U8("Tamanho do Ponto");
		CrosshairsText.Outline = U8("Contorno");
		CrosshairsText.Crossline = U8("Linhas Cruzadas");
		CrosshairsText.hLengthSlider = U8("Comprimento Horizontal");
		CrosshairsText.vLengthSilder = U8("Comprimento Vertical");
		CrosshairsText.GapSlider = U8("Espacamento");
		CrosshairsText.ThicknessSlider = U8("Largura");
		CrosshairsText.tStyle = U8("T Estilo");
		CrosshairsText.Circle = U8("Circulo");
		CrosshairsText.RadiusSlider = U8("Raio do Circulo");
		CrosshairsText.TargetCheck = U8("Verificacao de Alvo");
		CrosshairsText.TeamCheck = U8("Apenas Inimigos");

		// Misc
		MiscText.FeatureName = U8(" Diversos");
		MiscText.ThemeList = U8("Tema");
		MiscText.StyleList = U8("Estilo");
		MiscText.HeadshotLine = U8("Linha de Headshot");
		MiscText.SpecCheck = U8("Funcionar no Espectador");
		MiscText.NoFlash = U8("Remover Flashbang");
		MiscText.HitSound = U8("Som de Acerto");
		MiscText.bmbTimer = U8("Temporizador da Bomba");
		MiscText.SpecList = U8("Lista de Espectadores");
		MiscText.Bhop = U8("Bunny hop");
		MiscText.Watermark = U8("Marca dagua");
		MiscText.CheatList = U8("Lista de Trapacas");
		MiscText.TeamCheck = U8("Apenas Inimigos");
		MiscText.AntiRecord = U8("Anti-OBS");

		MiscText.LanguageList = U8("Linguagem");

		// Config Menu
		ConfigText.FeatureName = U8(" Configuracao");
		ConfigText.Load = U8("Carregar Selecionada");
		ConfigText.Save = U8("Salvar Selecionada");
		ConfigText.Delete = U8("Deletar Selecionada");
		ConfigText.Reset = U8("Reseta Configuracao");
		ConfigText.Create = U8("Criar Configuracao");
		ConfigText.OpenFolder = U8("Abrir Pasta");
		ConfigText.SeparateLine = U8("Salvar Configuracao");

		// Readme Menu
		ReadMeText.FeatureName = U8(" LEIAME");
		ReadMeText.LastUpdate = U8("Ultima Atualizacao: ");
		ReadMeText.SourceButton = U8(" Codigo Fonte");
		ReadMeText.DiscordButton = U8(" Entre no Discord");
		ReadMeText.OffsetsTitle = U8("Offsets:");
	}

	// Translated by @faster_bbc
	inline void Slovak()
	{
		Global.SwitchButton = U8("Zapnúť");
		Global.FeatureSettings = U8("Nastavenia");

		// ESP
		ESPtext.FeatureName = U8(" ESP");
		ESPtext.Box = U8("Box");
		ESPtext.BoxRounding = U8("Zaoblenie Boxu");
		ESPtext.FilledBox = U8("Vyplnený box");
		ESPtext.FilledAlpha = U8("Prehliadnosť vyplneného boxu");
		ESPtext.Skeleton = U8("Kostra");
		ESPtext.HeadBox = U8("Box na hlavu");
		ESPtext.EyeRay = U8("Čiara videnia hráča");
		ESPtext.HealthBar = U8("Hrubá čiara života");
		ESPtext.Weapon = U8("Zbraň");
		ESPtext.Distance = U8("Zdialenosť");
		ESPtext.PlayerName = U8("Meno");
		ESPtext.SnapLine = U8("Čiara ku hráčovy");
		ESPtext.LinePosList = U8("Lokácia čiary");
		ESPtext.VisCheck = U8("Skontrolovať viditelnosť");
		ESPtext.Preview = U8("Náhľad");
		ESPtext.CollapseHead = U8("Sex ESP");
		ESPtext.Penis = U8("Penis/Pipik/Bakuľa");
		ESPtext.PenisLength = U8("Dĺžka");
		ESPtext.PenisSize = U8("Velkosť");
		ESPtext.MultiColor = U8("Viacfarebné");
		ESPtext.MultiColTip = U8("Funguje len vtedy, keď má rámček nezaoblené rohy.");

		// Aimbot
		AimbotText.FeatureName = U8(" Aimbo");
		AimbotText.HotKeyList = U8("Tlačítko");
		AimbotText.Toggle = U8("Prepínaci mód");
		AimbotText.DrawFov = U8("Ukázať FOV");
		AimbotText.VisCheck = U8("Skontrolovať viditelnosť");
		AimbotText.JumpCheck = U8("Iba na zemy");
		AimbotText.FovSlider = U8("FOV");
		AimbotText.SmoothSlider = U8("Hladkosť");
		AimbotText.BoneList = U8("Kosť");
		AimbotText.Tip = U8("Aimbot nebude fungovať pokiaľ je menu otvorené");

		// Glow
		GlowText.FeatureName = U8(" Žiarenie");

		// Radar
		RadarText.FeatureName = U8(" Radar");
		RadarText.StyleList = U8("Štýl");
		RadarText.CustomCheck = U8("Vlastné");
		RadarText.CrossLine = U8("Kríž");
		RadarText.SizeSlider = U8("Velkosť bodky");
		RadarText.ProportionSlider = U8("Proporcia");
		RadarText.RangeSlider = U8("Rozsah");
		RadarText.AlphaSlider = U8("Prehliadnosť pozadia okna");

		// Triggerbot
		TriggerText.FeatureName = U8(" Triggerbot");
		TriggerText.HotKeyList = U8("Tlačítko");
		TriggerText.Toggle = U8("Vždy aktívne");
		TriggerText.DelaySlider = U8("Oneskorenie výstrelu");
		TriggerText.FakeShotSlider = U8("Trvanie výstrelu");

		// Crosshairs
		CrosshairsText.FeatureName = U8(" Crosshair");
		CrosshairsText.PresetList = U8("Predvoľby");
		CrosshairsText.ColorEditor = U8("Farba crosshairu");
		CrosshairsText.Dot = U8("Stredová bodka");
		CrosshairsText.DotSizeSlider = U8("Velkosť bodky");
		CrosshairsText.Outline = U8("Obrys");
		CrosshairsText.Crossline = U8("Kríž");
		CrosshairsText.hLengthSlider = U8("Horizontálna dĺžka");
		CrosshairsText.vLengthSilder = U8("Vertikálna dĺžka");
		CrosshairsText.GapSlider = U8("Medzera");
		CrosshairsText.ThicknessSlider = U8("Hrubosť");
		CrosshairsText.tStyle = U8("T štýl");
		CrosshairsText.Circle = U8("Kruh");
		CrosshairsText.RadiusSlider = U8("Velkosť Kruhu");
		CrosshairsText.TargetCheck = U8("Zameriavanie Crosshairu");
		CrosshairsText.TeamCheck = U8("Kontrola tímu");

		// Misc
		MiscText.FeatureName = U8(" Ostatné");
		MiscText.ThemeList = U8("Téma");
		MiscText.StyleList = U8("Štýl");
		MiscText.HeadshotLine = U8("Čiara strely do hlavy");
		MiscText.SpecCheck = U8("Cheat keď si divák");
		MiscText.NoFlash = U8("Žiadny flash");
		MiscText.HitSound = U8("Zvuk udretia");
		MiscText.bmbTimer = U8("Časovač bomby");
		MiscText.SpecList = U8("List divákov");
		MiscText.Bhop = U8("Automatické skákanie");
		MiscText.Watermark = U8("Vodný znak");
		MiscText.CheatList = U8("List cheatov");
		MiscText.TeamCheck = U8("Kontrola tímu");
		MiscText.AntiRecord = U8("Bypass OBS");

		MiscText.LanguageList = U8("Jazyk");

		// Config Menu
		ConfigText.FeatureName = U8(" Nastavenie");
		ConfigText.Load = U8("Načítať vybraté");
		ConfigText.Save = U8("Uložiť vybraté");
		ConfigText.Delete = U8("Vymazať vybraté");
		ConfigText.Reset = U8("Obnoviť vybraté");
		ConfigText.Create = U8("Vytvoriť nastavenie");
		ConfigText.OpenFolder = U8("Otvoriť priečinok");
		ConfigText.SeparateLine = U8("Uložiť nastavenie");

		// Readme Menu
		ReadMeText.FeatureName = U8(" Prečítaj ma");
		ReadMeText.LastUpdate = U8("Posledná aktulizácia: ");
		ReadMeText.SourceButton = U8(" Zdrojový Kód");
		ReadMeText.DiscordButton = U8(" Pripoj sa na Discord");
		ReadMeText.OffsetsTitle = U8("Offsety:");
	}

	// Translated by @CowNow
	inline void SimplifiedChinese()
	{
		Global.SwitchButton = U8("启用功能");
		Global.FeatureSettings = U8("详细设置");

		// ESP
		ESPtext.FeatureName = U8(" ESP");
		ESPtext.Box = U8("方框");
		ESPtext.BoxRounding = U8("圆角化");
		ESPtext.FilledBox = U8("填充方框");
		ESPtext.FilledAlpha = U8("填充透明度");
		ESPtext.Skeleton = U8("骨骼");
		ESPtext.HeadBox = U8("头部方框");
		ESPtext.EyeRay = U8("视线朝向");
		ESPtext.HealthBar = U8("生命栏");
		ESPtext.Weapon = U8("武器");
		ESPtext.Distance = U8("距离");
		ESPtext.PlayerName = U8("玩家名");
		ESPtext.SnapLine = U8("射线");
		ESPtext.LinePosList = U8("射线位置");
		ESPtext.VisCheck = U8("可视检查");
		ESPtext.Preview = U8("效果预览");
		ESPtext.CollapseHead = U8("性感设置");
		ESPtext.Penis = U8("显示牛子");
		ESPtext.PenisLength = U8("牛子长度");
		ESPtext.PenisSize = U8("牛子粗细");
		ESPtext.MultiColor = U8("渐变色");
		ESPtext.MultiColTip = U8("仅在圆角度为0时显示.");

		// Aimbot
		AimbotText.FeatureName = U8(" 瞄准辅助");
		AimbotText.HotKeyList = U8("热键");
		AimbotText.Toggle = U8("热键切换模式");
		AimbotText.DrawFov = U8("显示范围");
		AimbotText.VisCheck = U8("仅可见目标");
		AimbotText.JumpCheck = U8("仅在地面上");
		AimbotText.FovSlider = U8("FOV");
		AimbotText.SmoothSlider = U8("平滑度");
		AimbotText.BoneList = U8("瞄准部位");
		AimbotText.Tip = U8("此功能在菜单打开时不会工作");

		// Glow
		GlowText.FeatureName = U8(" 发光");

		// Radar
		RadarText.FeatureName = U8(" 外部雷达");
		RadarText.StyleList = U8("雷达样式");
		RadarText.CustomCheck = U8("自定义设置");
		RadarText.CrossLine = U8("十字线");
		RadarText.SizeSlider = U8("标记大小");
		RadarText.ProportionSlider = U8("缩放比例");
		RadarText.RangeSlider = U8("范围");
		RadarText.AlphaSlider = U8("窗口透明度");

		// Triggerbot
		TriggerText.FeatureName = U8(" 自动扳机");
		TriggerText.HotKeyList = U8("热键");
		TriggerText.Toggle = U8("保持激活");
		TriggerText.DelaySlider = U8("延迟射击");
		TriggerText.FakeShotSlider = U8("射击持续时间");

		// Crosshairs
		CrosshairsText.FeatureName = U8(" 外部准星");
		CrosshairsText.PresetList = U8("预设");
		CrosshairsText.ColorEditor = U8("准星颜色");
		CrosshairsText.Dot = U8("中心点");
		CrosshairsText.DotSizeSlider = U8("中心点大小");
		CrosshairsText.Outline = U8("轮廓线");
		CrosshairsText.Crossline = U8("十字线");
		CrosshairsText.hLengthSlider = U8("水平长度");
		CrosshairsText.vLengthSilder = U8("垂直长度");
		CrosshairsText.GapSlider = U8("间隙");
		CrosshairsText.ThicknessSlider = U8("粗细");
		CrosshairsText.tStyle = U8("T形准星");
		CrosshairsText.Circle = U8("圆环");
		CrosshairsText.RadiusSlider = U8("圆环半径");
		CrosshairsText.TargetCheck = U8("瞄准变色");
		CrosshairsText.TeamCheck = U8("队伍检查");

		// Misc
		MiscText.FeatureName = U8(" 杂项功能");
		MiscText.ThemeList = U8("主题配色");
		MiscText.StyleList = U8("窗口样式");
		MiscText.HeadshotLine = U8("爆头线");
		MiscText.SpecCheck = U8("旁观者保持运行");
		MiscText.NoFlash = U8("无视闪光弹");
		MiscText.HitSound = U8("命中音效");
		MiscText.bmbTimer = U8("C4计时器");
		MiscText.SpecList = U8("旁观者列表");
		MiscText.Bhop = U8("连跳");
		MiscText.Watermark = U8("水印浮窗");
		MiscText.CheatList = U8("功能列表");
		MiscText.TeamCheck = U8("队伍检查");
		MiscText.AntiRecord = U8("直播模式");
		MiscText.LanguageList = U8("语言");

		// Config Menu
		ConfigText.FeatureName = U8(" 参数配置");
		ConfigText.Load = U8("加载选中");
		ConfigText.Save = U8("保存选中");
		ConfigText.Delete = U8("删除选中");
		ConfigText.Reset = U8("重置配置");
		ConfigText.Create = U8("创建配置");
		ConfigText.OpenFolder = U8("打开文件夹");
		ConfigText.SeparateLine = U8("新建配置");

		// Readme Menu
		ReadMeText.FeatureName = U8(" 其他信息");
		ReadMeText.LastUpdate = U8("最后更新: ");
		ReadMeText.SourceButton = U8(" 开源代码");
		ReadMeText.DiscordButton = U8(" 加入Discord");
		ReadMeText.OffsetsTitle = U8("相关基址: ");
	}


	// Translated by @Yashing
	inline void French()
	{
		Global.SwitchButton = U8("Enable");
		Global.FeatureSettings = U8("Paramètres");

		// ESP
		ESPtext.FeatureName = U8(" BOITE");
		ESPtext.Box = U8("Boite");
		ESPtext.BoxRounding = U8("Tour de boite");
		ESPtext.FilledBox = U8("Remplissage de boite");
		ESPtext.FilledAlpha = U8("Remplissage de boite Alpha");
		ESPtext.Skeleton = U8("Squelette");
		ESPtext.HeadBox = U8("Boite de tête");
		ESPtext.EyeRay = U8("Regarde des yeux");
		ESPtext.HealthBar = U8("Barre de vie");
		ESPtext.Weapon = U8("Arme");
		ESPtext.Distance = U8("Distance");
		ESPtext.PlayerName = U8("Nom");
		ESPtext.SnapLine = U8("Line d'allé");
		ESPtext.LinePosList = U8("Position des lignes");
		ESPtext.VisCheck = U8("Vérification visible");
		ESPtext.Preview = U8("Fenêtre de prevision de boite");
		ESPtext.CollapseHead = U8("SexyBoite");
		ESPtext.Penis = U8("MontréPénis");
		ESPtext.PenisLength = U8("Longueur");
		ESPtext.PenisSize = U8("Taille");
		ESPtext.MultiColor = U8("Multi-couleurs");
		ESPtext.MultiColTip = U8("Ne fonctionne que si la boîte a des coins non arrondis.");

		// Aimbot
		AimbotText.FeatureName = U8(" Visée automatique");
		AimbotText.HotKeyList = U8("Clef");
		AimbotText.Toggle = U8("Rester activé");
		AimbotText.DrawFov = U8("Déssiner la vue");
		AimbotText.VisCheck = U8("Visible uniquement");
		AimbotText.JumpCheck = U8("Au sol uniquement");
		AimbotText.FovSlider = U8("Visée");
		AimbotText.SmoothSlider = U8("Vitesse");
		AimbotText.BoneList = U8("Os");
		AimbotText.Tip = U8("La visée automatique ne fonctionne pas avec la fenetre ouverte");

		// Glow
		GlowText.FeatureName = U8(" Brillance");

		// Radar
		RadarText.FeatureName = U8(" Radar");
		RadarText.StyleList = U8("Style");
		RadarText.CustomCheck = U8("Personnalisation");
		RadarText.CrossLine = U8("Ligne ccroisée");
		RadarText.SizeSlider = U8("Taille des points");
		RadarText.ProportionSlider = U8("Proportion");
		RadarText.RangeSlider = U8("Rang");
		RadarText.AlphaSlider = U8("Arrière plan windows");

		// Triggerbot
		TriggerText.FeatureName = U8(" Tir a vue");
		TriggerText.HotKeyList = U8("Raccourci clavier");
		TriggerText.Toggle = U8("Toujours actif");
		TriggerText.DelaySlider = U8("Délai de tir");
		TriggerText.FakeShotSlider = U8("Durée du tir");

		// Crosshairs
		CrosshairsText.FeatureName = U8(" Viseur personnalisé");
		CrosshairsText.PresetList = U8("Sauvegarde");
		CrosshairsText.ColorEditor = U8("Couleur du viseur");
		CrosshairsText.Dot = U8("Point central");
		CrosshairsText.DotSizeSlider = U8("Taille du point");
		CrosshairsText.Outline = U8("Contour");
		CrosshairsText.Crossline = U8("Ligne croisées");
		CrosshairsText.hLengthSlider = U8("Taille horizontale");
		CrosshairsText.vLengthSilder = U8("Taille");
		CrosshairsText.GapSlider = U8("Ecart");
		CrosshairsText.ThicknessSlider = U8("Epaisseur");
		CrosshairsText.tStyle = U8("Style du T");
		CrosshairsText.Circle = U8("Cercle");
		CrosshairsText.RadiusSlider = U8("Rayon du cercle");
		CrosshairsText.TargetCheck = U8("Cibler la réticule");
		CrosshairsText.TeamCheck = U8("Vérification de l'équipe");

		// Misc
		MiscText.FeatureName = U8(" Divers");
		MiscText.ThemeList = U8("Theme");
		MiscText.StyleList = U8("Style");
		MiscText.HeadshotLine = U8("Lignes de tirs a la tête");
		MiscText.SpecCheck = U8("Listes3");
		MiscText.NoFlash = U8("Pas d'effet flash");
		MiscText.HitSound = U8("Bruit de touches");
		MiscText.bmbTimer = U8("Temp de la bombe");
		MiscText.SpecList = U8("Liste des spectateurs");
		MiscText.Bhop = U8("Sauts en continues");
		MiscText.Watermark = U8("Afficher FPS");
		MiscText.CheatList = U8("Lsite des triches");
		MiscText.TeamCheck = U8("Vérifications d'équipe");
		MiscText.AntiRecord = U8("Invisible OBS Studio");

		MiscText.LanguageList = U8("Langue");

		// Config Menu
		ConfigText.FeatureName = U8(" Configuration(s)");
		ConfigText.Load = U8("Charger la séléction");
		ConfigText.Save = U8("Sauvegarder la séléction");
		ConfigText.Delete = U8("Supprimer la séléction");
		ConfigText.Reset = U8("Reintiallisé les configuration");
		ConfigText.Create = U8("Crée une configuration");
		ConfigText.OpenFolder = U8("Ouvrir fichier");
		ConfigText.SeparateLine = U8("Sauvegarder la configuration");

		// Readme Menu
		ReadMeText.FeatureName = U8(" Lis moi");
		ReadMeText.LastUpdate = U8("Dèrnière MAJ: ");
		ReadMeText.SourceButton = U8(" Code de la source");
		ReadMeText.DiscordButton = U8(" Rejoindre DISCORD");
		ReadMeText.OffsetsTitle = U8("Compensations:");
	}

	// Translated by @TRINITRAMIN
	inline void Korean()
	{
		Global.SwitchButton = U8("할 수 있게 하다");
		Global.FeatureSettings = U8("설정");

		// ESP
		ESPtext.FeatureName = U8(" 이에스피 ");
		ESPtext.Box = U8("박스");
		ESPtext.BoxRounding = U8("박스 랜더링");
		ESPtext.FilledBox = U8("채워진 상자");
		ESPtext.FilledAlpha = U8("채워진 상자 알파");
		ESPtext.Skeleton = U8("해골");
		ESPtext.HeadBox = U8("머리 ");
		ESPtext.EyeRay = U8("아이 레이");
		ESPtext.HealthBar = U8("채력 줄");
		ESPtext.Weapon = U8("무기");
		ESPtext.Distance = U8("거리");
		ESPtext.PlayerName = U8("이름");
		ESPtext.SnapLine = U8("스냅라인");
		ESPtext.LinePosList = U8("라인포스");
		ESPtext.VisCheck = U8("벽뒤 구분");
		ESPtext.Preview = U8("esp미리보기");
		ESPtext.CollapseHead = U8("섹시ESP");
		ESPtext.Penis = U8("그곳을 보여주세요");
		ESPtext.PenisLength = U8("길이");
		ESPtext.PenisSize = U8("크기");
		ESPtext.MultiColor = U8("멀티 컬러");
		ESPtext.MultiColTip = U8("상자의 모서리가 둥글지 않은 경우에만 작동합니다.");

		// Aimbot
		AimbotText.FeatureName = U8("에임봇");
		AimbotText.HotKeyList = U8("키");
		AimbotText.Toggle = U8("껏다 키기");
		AimbotText.DrawFov = U8("FOV 그리기");
		AimbotText.VisCheck = U8("보이는 것만");
		AimbotText.JumpCheck = U8("지상에서만");
		AimbotText.SmoothSlider = U8("매끄러운");
		AimbotText.BoneList = U8("뼈");
		AimbotText.Tip = U8("메뉴가 열려 있는 동안에는 Aimbot이 작동하지 않습니다.");

		// Glow
		GlowText.FeatureName = U8(" 불타는 듯한 빛깔");

		// Radar
		RadarText.FeatureName = U8(" 레이더");
		RadarText.StyleList = U8("스타일");
		RadarText.CustomCheck = U8("커스텀");
		RadarText.CrossLine = U8("Cross 라인");
		RadarText.SizeSlider = U8("포인트 크기");
		RadarText.ProportionSlider = U8("비율");
		RadarText.RangeSlider = U8("범위");
		RadarText.AlphaSlider = U8("창 배경 알파");

		// Triggerbot
		TriggerText.FeatureName = U8(" 트리거봇");
		TriggerText.HotKeyList = U8("핫키");
		TriggerText.Toggle = U8("항상 활성");
		TriggerText.DelaySlider = U8("샷 딜레이");
		TriggerText.FakeShotSlider = U8("촬영 시간");

		// Crosshairs
		CrosshairsText.FeatureName = U8(" 십자선");
		CrosshairsText.PresetList = U8("사전 설정");
		CrosshairsText.ColorEditor = U8("십자선 색상");
		CrosshairsText.Dot = U8("센터 도트");
		CrosshairsText.DotSizeSlider = U8("도트 크기");
		CrosshairsText.Outline = U8("개요");
		CrosshairsText.Crossline = U8("크로스 라인");
		CrosshairsText.hLengthSlider = U8("가로 길이");
		CrosshairsText.vLengthSilder = U8("수직 길이");
		CrosshairsText.GapSlider = U8("갭");
		CrosshairsText.ThicknessSlider = U8("두께");
		CrosshairsText.tStyle = U8("T 스타일");
		CrosshairsText.Circle = U8("원");
		CrosshairsText.RadiusSlider = U8("원 반경");
		CrosshairsText.TargetCheck = U8("십자선 타겟팅");
		CrosshairsText.TeamCheck = U8("팀체크");

		// Misc
		MiscText.FeatureName = U8(" 기타");
		MiscText.ThemeList = U8("주제");
		MiscText.StyleList = U8("스타일");
		MiscText.HeadshotLine = U8("헤드샷 라인");
		MiscText.SpecCheck = U8("사양 속 치트");
		MiscText.NoFlash = U8("No 플래시");
		MiscText.HitSound = U8("히트 사운드");
		MiscText.bmbTimer = U8("폭탄 타이머");
		MiscText.SpecList = U8("사양 목록");
		MiscText.Bhop = U8("버니홉");
		MiscText.Watermark = U8("양수표");
		MiscText.CheatList = U8("치트 목록");
		MiscText.TeamCheck = U8("팀체크");
		MiscText.AntiRecord = U8("방속 우회 ");

		MiscText.LanguageList = U8("언어");

		// Config Menu
		ConfigText.FeatureName = U8(" 구성");
		ConfigText.Load = U8("선택 항목 로드");
		ConfigText.Save = U8("선택 항목 저장");
		ConfigText.Delete = U8("선택된 것을 지워 라");
		ConfigText.Reset = U8("구성 재설정");
		ConfigText.Create = U8("구성 만들기");
		ConfigText.OpenFolder = U8("폴더 열기 ");
		ConfigText.SeparateLine = U8("구성 저장");

		// Readme Menu
		ReadMeText.FeatureName = U8(" 주의상황 ");
		ReadMeText.LastUpdate = U8("마지막 업데이트: ");
		ReadMeText.SourceButton = U8(" 소스 코드");
		ReadMeText.DiscordButton = U8(" 디스코드에 참여하세요");
		ReadMeText.OffsetsTitle = U8("오프셋:");
	}

	// Written by ! FleX#0001 / flex0001
	inline void Turkish()
	{
		Global.SwitchButton = U8("Etkinleştir");
		Global.FeatureSettings = U8("Ayarlar");

		// ESP
		ESPtext.FeatureName = U8(" Görüş Hilesi");
		ESPtext.Box = U8("Çerçeve");
		ESPtext.BoxRounding = U8("Köşe Yuvarlaklığı");
		ESPtext.FilledBox = U8("Dolu Çerçeve");
		ESPtext.FilledAlpha = U8("Dolu Çerçeve Saydamlığı");
		ESPtext.Skeleton = U8("İskelet");
		ESPtext.HeadBox = U8("Kafa Göstergesi");
		ESPtext.EyeRay = U8("Göz Işını");
		ESPtext.HealthBar = U8("Can Göstergesi");
		ESPtext.Weapon = U8("Silah Göstergesi");
		ESPtext.Distance = U8("Mesafe Göstergesi");
		ESPtext.PlayerName = U8("İsim Göstergesi");
		ESPtext.SnapLine = U8("Kilitli Çizgi");
		ESPtext.LinePosList = U8("Çizgi Pozisyonu");
		ESPtext.VisCheck = U8("Görünürlük Kontrolü");
		ESPtext.Preview = U8("Önizleme Penceresi");
		ESPtext.CollapseHead = U8("Küçük Baş");
		ESPtext.Penis = U8("Sik Göstergesi");
		ESPtext.PenisLength = U8("Uzunluk");
		ESPtext.PenisSize = U8("Boyut");
		ESPtext.MultiColor = U8("Çoklu Renk");
		ESPtext.MultiColTip = U8("Sadece köşeleri yuvarlatılmamış çerçevelerde çalışır.");

		// Aimbot
		AimbotText.FeatureName = U8(" Hedef Bot");
		AimbotText.HotKeyList = U8("Tuş");
		AimbotText.Toggle = U8("Aç/Kapa Modu");
		AimbotText.DrawFov = U8("Görüş Açısı Çizgisi");
		AimbotText.VisCheck = U8("Sadece Görünürler");
		AimbotText.JumpCheck = U8("Sadece Yerdeyken");
		AimbotText.FovSlider = U8("Görüş Açısı");
		AimbotText.SmoothSlider = U8("Hızlandırma");
		AimbotText.BoneList = U8("Hedef Nokta");
		AimbotText.Tip = U8("Menü açıkken Hedefleme Bot'u çalışmaz");

		// Glow
		GlowText.FeatureName = U8(" Glow");

		// Radar
		RadarText.FeatureName = U8(" Radar");
		RadarText.StyleList = U8("Stil");
		RadarText.CustomCheck = U8("Özel");
		RadarText.CrossLine = U8("Çizgi");
		RadarText.SizeSlider = U8("Nokta Boyutu");
		RadarText.ProportionSlider = U8("Oran");
		RadarText.RangeSlider = U8("Görüş Menzili");
		RadarText.AlphaSlider = U8("Pencere Arka Planı Saydamlığı");

		// Triggerbot
		TriggerText.FeatureName = U8(" Tetikbot");
		TriggerText.HotKeyList = U8("Kısayol Tuşu");
		TriggerText.Toggle = U8("Her Zaman Aktif");
		TriggerText.DelaySlider = U8("Atış Gecikmesi");
		TriggerText.FakeShotSlider = U8("Atış Süresi");

		// Crosshairs
		CrosshairsText.FeatureName = U8(" Nişangah");
		CrosshairsText.PresetList = U8("Ön ayarlar");
		CrosshairsText.ColorEditor = U8("Nişangah Rengi");
		CrosshairsText.Dot = U8("Merkez Nokta");
		CrosshairsText.DotSizeSlider = U8("Nokta Boyutu");
		CrosshairsText.Outline = U8("Çizgi");
		CrosshairsText.Crossline = U8("Çapraz Çizgi");
		CrosshairsText.hLengthSlider = U8("Yatay Uzunluk");
		CrosshairsText.vLengthSilder = U8("Dikey Uzunluk");
		CrosshairsText.GapSlider = U8("Boşluk");
		CrosshairsText.ThicknessSlider = U8("Kalınlık");
		CrosshairsText.tStyle = U8("T Stili");
		CrosshairsText.Circle = U8("Çember");
		CrosshairsText.RadiusSlider = U8("Çember Yarıçapı");
		CrosshairsText.TargetCheck = U8("Hedefleme Nişangahı");
		CrosshairsText.TeamCheck = U8("Takım Arkadaşlarını Öne Çıkar");

		// Misc
		MiscText.FeatureName = U8(" Genel");
		MiscText.ThemeList = U8("Tema");
		MiscText.StyleList = U8("Stil");
		MiscText.HeadshotLine = U8("Baş Atışı Çizgisi");
		MiscText.SpecCheck = U8("Hile Seçenekleri");
		MiscText.NoFlash = U8("Flash Yok");
		MiscText.HitSound = U8("İsabet Sesi");
		MiscText.bmbTimer = U8("Bomba Zamanlayıcı");
		MiscText.SpecList = U8("İzleme Listesi");
		MiscText.Bhop = U8("Tavşan Zıplama");
		MiscText.Watermark = U8("Filigran");
		MiscText.CheatList = U8("Hile Listesi");
		MiscText.TeamCheck = U8("Takım Kontrol");
		MiscText.AntiRecord = U8("Kayıt Engelleyici");

		MiscText.LanguageList = U8("Dil");

		// Config Menu
		ConfigText.FeatureName = U8(" Konfigürasyon");
		ConfigText.Load = U8("Seçili Olanı Yükle");
		ConfigText.Save = U8("Seçili Olanı Kaydet");
		ConfigText.Delete = U8("Seçili Olanı Sil");
		ConfigText.Reset = U8("Konfigürasyonu Sıfırla");
		ConfigText.Create = U8("Konfigürasyon Oluştur");
		ConfigText.OpenFolder = U8("Klasörü Aç");
		ConfigText.SeparateLine = U8("Konfigürasyonu Kaydet");

		// Readme Menu
		ReadMeText.FeatureName = U8(" Beni Oku");
		ReadMeText.LastUpdate = U8("Son Güncelleme: ");
		ReadMeText.SourceButton = U8("Açık Kaynak");
		ReadMeText.DiscordButton = U8("Discord'a Katıl");
		ReadMeText.OffsetsTitle = U8("Ofsetler:");
	}

	inline void Hungarian()
	{
		Global.SwitchButton = U8("Kitiltási eszköz");
		Global.FeatureSettings = U8("Beállítások");

		// ESP
		ESPtext.FeatureName = U8("Extraszenzoros észlelés");
		ESPtext.Box = U8("Doboz");
		ESPtext.BoxRounding = U8("Doboz kerekítés");
		ESPtext.FilledBox = U8("Megtöltött doboz");
		ESPtext.FilledAlpha = U8("Megtöltött Alfa doboz");
		ESPtext.Skeleton = U8("Csontváz");
		ESPtext.HeadBox = U8("Fej doboz");
		ESPtext.EyeRay = U8("Szem sáv");
		ESPtext.HealthBar = U8("Egészségügyi bár");
		ESPtext.Weapon = U8("Deshi oncsel meg");
		ESPtext.Distance = U8("Bombayt a koktelba");
		ESPtext.PlayerName = U8("Név");
		ESPtext.SnapLine = U8("Csattan vonal");
		ESPtext.LinePosList = U8("Vonal pozicio");
		ESPtext.VisCheck = U8("Látható ellenőrzés");
		ESPtext.Preview = U8("Előnézet ablak");
		ESPtext.CollapseHead = U8("Szexi Extraszenzoros észlelés");
		ESPtext.Penis = U8("Pénisz megjelenítése");
		ESPtext.PenisLength = U8("Pénisz hossza");
		ESPtext.PenisSize = U8("Pénisz mérete");

		// Aimbot
		AimbotText.FeatureName = U8(" Célzozzon robot");
		AimbotText.HotKeyList = U8("Kulcs");
		AimbotText.Toggle = U8("Mód váltása");
		AimbotText.DrawFov = U8("Rajzolja meg a látómezőt");
		AimbotText.VisCheck = U8("Csak látható");
		AimbotText.JumpCheck = U8("Csak a földön");
		AimbotText.FovSlider = U8("Látómegő");
		AimbotText.SmoothSlider = U8("Kurva anyád");
		AimbotText.BoneList = U8("Buta zsidó");
		AimbotText.Tip = U8("A Célozzon Robot nem fog működni, amíg a menü meg van nyitva, te fasz");

		// Glow
		GlowText.FeatureName = U8(" Központi Hírszerző Ügynökség Mód");

		// Radar
		RadarText.FeatureName = U8(" Madár");
		RadarText.StyleList = U8("Kipattantba van stiló");
		RadarText.CustomCheck = U8("Egyedi");
		RadarText.CrossLine = U8("Kereszt vonale");
		RadarText.SizeSlider = U8("Pontméret");
		RadarText.ProportionSlider = U8("Hányad");
		RadarText.RangeSlider = U8("Sor");
		RadarText.AlphaSlider = U8("Ablak háttér Alpha");

		// Triggerbot
		TriggerText.FeatureName = U8(" Néger robot");
		TriggerText.HotKeyList = U8("Forró kulcs");
		TriggerText.Toggle = U8("Mindig aktív");
		TriggerText.DelaySlider = U8("Lövés késleltetése");
		TriggerText.FakeShotSlider = U8("Lövés időtartama");

		// Crosshairs
		CrosshairsText.FeatureName = U8(" Szájkeresztek");
		CrosshairsText.PresetList = U8("Előbeállítások");
		CrosshairsText.ColorEditor = U8("Célkereszt színe");
		CrosshairsText.Dot = U8("Közép pont");
		CrosshairsText.DotSizeSlider = U8("Pont méret");
		CrosshairsText.Outline = U8("Vázlat");
		CrosshairsText.Crossline = U8("kereszt vonal");
		CrosshairsText.hLengthSlider = U8("Vízszintes hossz");
		CrosshairsText.vLengthSilder = U8("Függőleges hossz");
		CrosshairsText.GapSlider = U8("Rés");
		CrosshairsText.ThicknessSlider = U8("Vastagság mérés");
		CrosshairsText.tStyle = U8("Pattintott stiló");
		CrosshairsText.Circle = U8("Kör");
		CrosshairsText.RadiusSlider = U8("Kör sugara");
		CrosshairsText.TargetCheck = U8("Cél kereszt");
		CrosshairsText.TeamCheck = U8("Csapatellenőrzés");

		// Misc
		MiscText.FeatureName = U8(" Különféle");
		MiscText.ThemeList = U8("Téma");
		MiscText.StyleList = U8("Pattintott stiló");
		MiscText.HeadshotLine = U8("Fej lövés vonal");
		MiscText.SpecCheck = U8("Csalás a Nézésben");
		MiscText.NoFlash = U8("Nincs villanás");
		MiscText.HitSound = U8("Ütés hang");
		MiscText.bmbTimer = U8("Bomba időzítő");
		MiscText.SpecList = U8("Specifikációs lista");
		MiscText.Bhop = U8("Nyuszi ugrás");
		MiscText.Watermark = U8("Vízpiac");
		MiscText.CheatList = U8("Csal lista");
		MiscText.TeamCheck = U8("Csapat fene");
		MiscText.AntiRecord = U8("Kerülje meg az OBS-t");

		MiscText.LanguageList = U8("Beszélt nyelv");

		// Config Menu
		ConfigText.FeatureName = U8(" Konfigurációt");
		ConfigText.Load = U8("Betöltés a kiválaszt");
		ConfigText.Save = U8("Kijelöltek mentése");
		ConfigText.Delete = U8("Apád halott");
		ConfigText.Reset = U8("Anyád baszom");
		ConfigText.Create = U8("Te meg buzi");
		ConfigText.OpenFolder = U8("Nyitott mappa");
		ConfigText.SeparateLine = U8("Konfiguráció mentése");

		// Readme Menu
		ReadMeText.FeatureName = U8(" Olvassa el te geci");
		ReadMeText.LastUpdate = U8("Utoljára lemásolva: ");
		ReadMeText.SourceButton = U8(" Szar kód");
		ReadMeText.DiscordButton = U8(" Ne lépj be a Discordba");
		ReadMeText.OffsetsTitle = U8("Ellentételezések:");
	}

	inline void ChangeLang(int LangIndex)
	{
		switch (LangIndex)
		{
		case 0:
			English();
			break;
		case 1:
			Danish();
			break;
		case 2:
			German();
			break;
		case 3:
			Polish();
			break;
		case 4:
			Portuguese();
			break;
		case 5:
			Russian();
			break;
		case 6:
			SimplifiedChinese();
			break;
		case 7:
			Slovak();
			break;
		case 8:
			French();
			break;
		//case 9:
			//Korean();
			//break;
		case 9:
			Turkish();
			break;
		case 10:
			Hungarian();
			break;
		default:
			English();
			break;
		}
	}
}