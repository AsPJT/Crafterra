/*##########################################################################################

	Crafterra Library 🌏

	[Planning and Production]
	2017-2022 Kasugaccho
	2018-2022 As Project

	[Contact Us]
	wanotaitei@gmail.com
	https://github.com/AsPJT/Crafterra

	[License]
	Distributed under the CC0 1.0.
	https://creativecommons.org/publicdomain/zero/1.0/

##########################################################################################*/

#ifndef INCLUDED_ASLIB2_ASLIB2_THIRD_PARTY_FRAMEWORK_FRAMEWORK_HPP
#define INCLUDED_ASLIB2_ASLIB2_THIRD_PARTY_FRAMEWORK_FRAMEWORK_HPP

// DxLib のメイン関数
#ifndef CRAFTERRA_FOR_DXLIB_MAIN_FUNCTION
#define CRAFTERRA_FOR_DXLIB_MAIN_FUNCTION

#include <Crafterra/Basic/InitRead.hpp>
#include <AsLib2/DataType/StringDataType.hpp>

// Windows 版の場合
#if defined(__DXLIB)
#if defined(__WINDOWS__)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#elif defined(__APPLE__)
int ios_main()
#endif // __WINDOWS__
#elif defined(SIV3D_INCLUDED)
void Main()
#endif // __DXLIB
{
	// 設定項目を読み込む
	::Crafterra::InitRead init_read("Settings.tsv");

	const int read_width = init_read.getInt("Window Width");
	const int read_height = init_read.getInt("Window Height");
	const int width =  ((read_width == 0) ? ::Crafterra::System::init_window_width : read_width);
	const int height = ((read_height == 0) ? ::Crafterra::System::init_window_height : read_height);

#if defined(__DXLIB)
	// ログ出力を行わない
	::DxLib::SetOutApplicationLogValidFlag(FALSE);
	// 背景色を指定
	::DxLib::SetBackgroundColor(75, 145, 230);
	// ウィンドウテキストにタイトル名を表示
	const ::As::DataType::String title_name = 
		::As::DataType::String("Crafterra v") + 
		::As::DataType::String(CRAFTERRA_LIBRARY_VERSION_NAME);
	::DxLib::SetMainWindowText(title_name.c_str());
	// フルスクリーンではなくウィンドウで表示
	if (!init_read.getBool("Fullscreen")) {
#ifdef __WINDOWS__
		::DxLib::ChangeWindowMode(TRUE);
#endif // __WINDOWS__
	}
		::DxLib::SetGraphMode(
			width, // Crafterra::System::init_window_width, 
			height, // Crafterra::System::init_window_height, 
			32);

	// UTF-8に変更
	::DxLib::SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);
	if (::DxLib::DxLib_Init() == -1) return -1;
	::DxLib::LoadGraphScreen(
		width / 2 - 320, height / 2 - 180,
		::std::string(init_read.getString("Picture Path") + "Logo/Init Logo(As).png").c_str(), FALSE);
	::DxLib::SetDrawScreen(DX_SCREEN_BACK);
#elif defined(SIV3D_INCLUDED)
	::s3d::Scene::SetBackground(::s3d::Color{ 75, 145, 230 });
	const ::s3d::ScopedRenderStates2D state(::s3d::SamplerState::ClampNearest);

	::s3d::Window::Resize(
		width,
		height
	);
#endif

	::Crafterra::ReadText read_text(init_read.getString("Data Path") + "MapChip.tsv");

	::As::Font font;
	::As::Music music;
	::As::MapChipImage map_chip_image(init_read.getString("Picture Path"), read_text);
	::As::CharacterChipImage character_chip_image;

	::Crafterra::Resource cm;

	cm.setFont(font);
	cm.setMusic(music);
	cm.setMapChip(map_chip_image);
	cm.setCharacterChip(character_chip_image);

	cm.setWindowWidth(width);
	cm.setWindowHeight(height);

	Crafterra::System::crafterraMain(cm);
#if defined(__DXLIB)
	return ::DxLib::DxLib_End();
#endif
}

#endif // CRAFTERRA_FOR_DXLIB_MAIN_FUNCTION

// 描画更新関数
#ifndef CRAFTERRA_FOR_DXLIB_UPDATE_FUNCTION
#define CRAFTERRA_FOR_DXLIB_UPDATE_FUNCTION
namespace Crafterra {
	namespace System {
		bool Update() {
#if defined(__DXLIB)
			return (::DxLib::ScreenFlip() != -1 && ::DxLib::ClearDrawScreen() != -1 && ::DxLib::ProcessMessage() != -1);
#elif defined(SIV3D_INCLUDED)
			return ::s3d::System::Update();
#endif // __DXLIB
		}
	}
}
#endif // CRAFTERRA_FOR_DXLIB_UPDATE_FUNCTION

#endif //Included Crafterra Library