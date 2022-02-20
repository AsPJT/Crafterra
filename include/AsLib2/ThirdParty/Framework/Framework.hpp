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

// Graphic ライブラリ のメイン関数
#ifndef CRAFTERRA_FOR_GRAPHIC_MAIN_FUNCTION
#define CRAFTERRA_FOR_GRAPHIC_MAIN_FUNCTION

#include <Crafterra/Basic/InitRead.hpp>
#include <AsLib2/DataType/StringDataType.hpp>

#include <AsLib2/ThirdParty/Framework/DataType.hpp>

#include <AsLib2/Basic/Unicode.hpp>

// Crafterra のメイン関数を宣言
#ifndef CRAFTERRA_MAIN_FUNCTION
#define CRAFTERRA_MAIN_FUNCTION
namespace Crafterra {
		void playCrafterra(::Crafterra::Resource&);
}
#endif // CRAFTERRA_MAIN_FUNCTION

namespace As {

	int initCrafterra(const ::Crafterra::InitRead& init_read, const int width, const int height) {

		::std::unique_ptr<::As::Font> font(CRAFTERRA_NEW::As::Font); // フォントのポインタ
		if (!font) return -1; // メモリ確保できなかった時は return

		::std::unique_ptr<::As::Music> music(CRAFTERRA_NEW::As::Music); // 音楽のポインタ
		if (!music) return -2; // メモリ確保できなかった時は return

		::std::unique_ptr<::As::MapChipImage> map_chip_image(CRAFTERRA_NEW::As::MapChipImage(
			init_read.getString("Picture Path"), init_read.getString("Data Path") + "MapChip.tsv")); // マップチップのポインタ
		if (!map_chip_image) return -3; // メモリ確保できなかった時は return

		::std::unique_ptr<::As::MapChipImage> character_chip_image(CRAFTERRA_NEW::As::MapChipImage(
			init_read.getString("Picture Path"), init_read.getString("Data Path") + "CharacterChip.tsv")); // キャラチップのポインタ
		if (!character_chip_image) return -4; // メモリ確保できなかった時は return
		
		::Crafterra::Resource cm;

		cm.setFont(*font);
		cm.setMusic(*music);
		cm.setMapChip(*map_chip_image);
		cm.setCharacterChip(*character_chip_image);

		cm.setWindowWidth(width);
		cm.setWindowHeight(height);

		::Crafterra::playCrafterra(cm);
		return 0;
	}

}

namespace As {
	namespace Window {

		// タイトル名を変更
		void setTitle(const ::As::String& title_name_) {
#if defined(__DXLIB)
			::DxLib::SetMainWindowText(title_name_.c_str());
#elif defined(SIV3D_INCLUDED)
			::s3d::Window::SetTitle(::As::utf32(title_name_));
#endif // __DXLIB
		}

		// タイトル名を変更
		void setBackgroundColor(const ::As::Uint8 r_, const ::As::Uint8 g_, const ::As::Uint8 b_) {
#if defined(__DXLIB)
			::DxLib::SetBackgroundColor(int(r_), int(g_), int(b_));
#elif defined(SIV3D_INCLUDED)
			::s3d::Scene::SetBackground(::s3d::Color{ r_, g_, b_ }); // 背景色を変更
#endif // __DXLIB
		}

	}
}

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
#if defined(CRAFTERRA_USE_SAVE_SCREEN)
	::Crafterra::InitRead init_read("SettingsSaveScreen.tsv");
#else
	::Crafterra::InitRead init_read("Settings.tsv");
#endif

	const int read_width = init_read.getInt("Window Width");
	const int read_height = init_read.getInt("Window Height");
	const int width =  ((read_width == 0) ? ::Crafterra::System::init_window_width : read_width);
	const int height = ((read_height == 0) ? ::Crafterra::System::init_window_height : read_height);

#if defined(__DXLIB)
		// ログ出力を行わない
		::DxLib::SetOutApplicationLogValidFlag(::As::dx_false);
#endif

		// 背景色を指定
		::As::Window::setBackgroundColor(75, 145, 230);
		// ウィンドウテキストにタイトル名を表示
		const ::As::String title_name =
			::As::String("Crafterra v") +
			::As::String(CRAFTERRA_LIBRARY_VERSION_NAME);
		::As::Window::setTitle(title_name);

#if defined(__DXLIB)
	{
		// フルスクリーンではなくウィンドウで表示
		if (!init_read.getBool("Fullscreen")) {
#ifdef __WINDOWS__
			::DxLib::ChangeWindowMode(::As::dx_true);
#endif // __WINDOWS__
		}
#if !defined(CRAFTERRA_USE_SAVE_SCREEN)
#ifdef __WINDOWS__
		::DxLib::SetWindowSizeChangeEnableFlag(TRUE, TRUE);
#endif // __WINDOWS__
		::DxLib::SetGraphMode(width, height, 32);
#endif

		// UTF-8に変更
		::DxLib::SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);
		if (::DxLib::DxLib_Init() == -1) return -1;
		const int crafterra_logo = ::DxLib::LoadGraph(::As::String(init_read.getString("Picture Path") + "Logo/Init Logo(As).png").c_str());
		::DxLib::DrawRotaGraph(width / 2, height / 2, 1.0, 0.0, crafterra_logo, ::As::dx_true);

#if defined(CRAFTERRA_USE_SAVE_SCREEN)
		const int screen = ::DxLib::MakeScreen(width, height, FALSE);
		::DxLib::SetDrawScreen(screen);
#else
		::DxLib::SetDrawScreen(DX_SCREEN_BACK);
#endif // CRAFTERRA_USE_SAVE_SCREEN
	}
#elif defined(SIV3D_INCLUDED)
	::s3d::Window::Resize(width, height); // 画面サイズを変更
	if (!::s3d::System::Update()) return; // 一旦、画面を更新
	Texture(::As::utf32(::As::String(init_read.getString("Picture Path") + "Logo/Init Logo(As).png"))).drawAt(width / 2, height / 2); // ロゴ表示
	if (!::s3d::System::Update()) return; // もう一度、画面を更新
	const ::s3d::ScopedRenderStates2D state(::s3d::SamplerState::ClampNearest); // ドット絵を見栄え良くする
#endif

#if !defined(CRAFTERRA_USE_SAVE_SCREEN)
	::As::initCrafterra(init_read, width, height); // Crafterra を初期化・実行
#endif

#if defined(__DXLIB)
#if defined(CRAFTERRA_USE_SAVE_SCREEN)
	int save_index = 111;
	const int save_count = 15;
	const int save_max = save_index + save_count;
	for (; save_index < save_max; ++save_index) {
		::As::initCrafterra(init_read, width, height); // Crafterra を初期化・実行
		::DxLib::SaveDrawScreenToPNG(0, 0, width, height, ::std::string("PictureTest/test" + ::std::to_string(save_index) + ".png").c_str());
	}
#endif // CRAFTERRA_USE_SAVE_SCREEN
#endif

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
		bool update() {
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