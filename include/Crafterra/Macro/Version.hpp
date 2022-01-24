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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_MACRO_VERSION_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_MACRO_VERSION_HPP

// 正式バージョン数値
#ifndef CRAFTERRA_LIBRARY_VERSION
#define CRAFTERRA_LIBRARY_VERSION (20220120L)
#endif

// Crafterra 主要バージョン ( 0 がテスト版 , 1 から正式リリース版の予定 )
#ifndef CRAFTERRA_LIBRARY_MAJOR
#define CRAFTERRA_LIBRARY_MAJOR (0)
#endif

// Crafterra 補助バージョン
#ifndef CRAFTERRA_LIBRARY_MINOR
#define CRAFTERRA_LIBRARY_MINOR (1)
#endif

// Crafterra 微修正バージョン
#ifndef CRAFTERRA_LIBRARY_PATCHLEVEL
#define CRAFTERRA_LIBRARY_PATCHLEVEL (5)
#endif

// 正式バージョン名 ( https://github.com/AsPJT/Crafterra )
#ifndef CRAFTERRA_LIBRARY_VERSION_NAME
#define CRAFTERRA_LIBRARY_VERSION_NAME "5.0.0.1.5"
#endif

/*##########################################################################################
	更新履歴
	バージョン |     更新日    |           概要
	5.0.0.1.X  | 2022/0X/XX | コピペ用
	5.0.0.1.X  | 2022/01/20 | 広大な地形生成（ 1000 億マス × 1000 億マス ）機能を実装
	5.0.0.1.4  | 2022/01/18 | 崖上＆崖自動タイル独自規格とウディタオートタイル規格に対応
	5.0.0.1.3  | 2022/01/16 | Crafterra 独自のデータ型実装を追加
	5.0.0.1.2  | 2022/01/14 | GitHub での一般公開
	5.0.0.1.1  | 2022/01/12 | Crafterra をライブラリ化
	5.0.0.1.0  | 2022/01/08 | Crafterra をリニューアル
##########################################################################################*/

// AsDungeon 世代 ( Crafterra 第五世代 )
#ifndef CRAFTERRA_LIBRARY_GENERATION
#define CRAFTERRA_LIBRARY_GENERATION (5)
#endif

// AsDungeon 世代微修正バージョン
#ifndef CRAFTERRA_LIBRARY_GENERATION_PATCHLEVEL
#define CRAFTERRA_LIBRARY_GENERATION_PATCHLEVEL (0)
#endif

/*##########################################################################################
	AsDungeon 世代とは？

	As Project が開発する地形またはダンジョン生成システムの管理番号である。

	第一世代： AsRogueLike_C (First Generation AsDungeon)               | https://github.com/AsPJT/Roguelike ( C++ 版のみ公開 )
	第二世代： AsRogueLike_C++ (Second Generation AsDungeon)          | https://github.com/AsPJT/Roguelike
	第三世代： AsLib (Third Generation AsDungeon)                        | https://github.com/AsPJT/AsLib
	第四世代： DungeonTemplateLibrary (Fourth Generation AsDungeon)   | https://github.com/AsPJT/DungeonTemplateLibrary
	第五世代： Crafterra (Fifth Generation AsDungeon)                    | https://github.com/AsPJT/Crafterra

	詳しくはこちら
	https://github.com/AsPJT/DungeonTemplateLibrary/wiki/Version-History
##########################################################################################*/

namespace Crafterra {

	namespace Version {
		// using 定義
		constexpr long crafterra_library_version = (CRAFTERRA_LIBRARY_VERSION);
		constexpr int  crafterra_library_generation = (CRAFTERRA_LIBRARY_GENERATION);
		constexpr int  crafterra_library_generation_patchlevel = (CRAFTERRA_LIBRARY_GENERATION_PATCHLEVEL);
		constexpr int  crafterra_library_major = (CRAFTERRA_LIBRARY_MAJOR);
		constexpr int  crafterra_library_minor = (CRAFTERRA_LIBRARY_MINOR);
		constexpr int  crafterra_library_patchlevel = (CRAFTERRA_LIBRARY_PATCHLEVEL);

	}

}

#endif //Included Crafterra Library