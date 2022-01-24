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

#ifndef INCLUDED_ASLIB2_ASLIB2_THIRD_PARTY_FRAMEWORK_KEYBOARD_HPP
#define INCLUDED_ASLIB2_ASLIB2_THIRD_PARTY_FRAMEWORK_KEYBOARD_HPP

#include <Crafterra/DataType/PrimitiveDataType.hpp>

#include <array>

namespace AsLib2 {

	enum class Key : ::Crafterra::IndexUint {
		  key_0
		, key_1
		, key_2
		, key_3
		, key_4
		, key_5
		, key_6
		, key_7
		, key_8
		, key_9
		, key_a
		, key_b
		, key_c
		, key_d
		, key_e
		, key_f
		, key_g
		, key_h
		, key_i
		, key_j
		, key_k
		, key_l
		, key_m
		, key_n
		, key_o
		, key_p
		, key_q
		, key_r
		, key_s
		, key_t
		, key_u
		, key_v
		, key_w
		, key_x
		, key_y
		, key_z
		, key_left
		, key_right
		, key_up
		, key_down
		, key_size
	};
#if defined(__DXLIB)
	std::array<::Crafterra::IndexUint, ::Crafterra::IndexUint(Key::key_size)> dxKey{ {
			KEY_INPUT_0
			,KEY_INPUT_1
			,KEY_INPUT_2
			,KEY_INPUT_3
			,KEY_INPUT_4
			,KEY_INPUT_5
			,KEY_INPUT_6
			,KEY_INPUT_7
			,KEY_INPUT_8
			,KEY_INPUT_9
			,KEY_INPUT_A
			,KEY_INPUT_B
			,KEY_INPUT_C
			,KEY_INPUT_D
			,KEY_INPUT_E
			,KEY_INPUT_F
			,KEY_INPUT_G
			,KEY_INPUT_H
			,KEY_INPUT_I
			,KEY_INPUT_J
			,KEY_INPUT_K
			,KEY_INPUT_L
			,KEY_INPUT_M
			,KEY_INPUT_N
			,KEY_INPUT_O
			,KEY_INPUT_P
			,KEY_INPUT_Q
			,KEY_INPUT_R
			,KEY_INPUT_S
			,KEY_INPUT_T
			,KEY_INPUT_U
			,KEY_INPUT_V
			,KEY_INPUT_W
			,KEY_INPUT_X
			,KEY_INPUT_Y
			,KEY_INPUT_Z
			,KEY_INPUT_LEFT
			,KEY_INPUT_RIGHT
			,KEY_INPUT_UP
			,KEY_INPUT_DOWN
} };
#endif

	class InputKey {
	private:
#if defined(__DXLIB)
		bool up_key[256]{};    // キーが離された瞬間
		bool down_key[256]{}; // キーが押された瞬間
		bool key[256]{};        // キーが押されているフレーム数

		char tmp_key[256]{}; // 現在のキーの入力状態
#endif
	public:
		void setKey() {
#if defined(__DXLIB)
#ifndef __APPLE__
			::DxLib::GetHitKeyStateAll(this->tmp_key); // 全てのキーの入力状態を取得
#endif // !__APPLE__


			for (int i = 0; i < 256; ++i) {
				if (this->tmp_key[i] != 0) {
					this->up_key[i] = false;
					this->down_key[i] = (this->key[i] == 0);
					// i 番のキーコードに対応するキーが押されていたら加算
					this->key[i] = true;
				}
				else {
					this->down_key[i] = false;
					this->up_key[i] = (this->key[i] != 0);
					this->key[i] = false;
				}
			}
#endif // __DXLIB
		}

		// キー出力

		bool isPressed(const Key key_num_) const {
#if defined(__DXLIB)
			return (this->key[::AsLib2::dxKey[::Crafterra::IndexUint(key_num_)]]);
#elif defined(SIV3D_INCLUDED)
			switch (key_num_) {
			case Key::key_a: return ::s3d::KeyA.pressed(); break;
			case Key::key_b: return ::s3d::KeyB.pressed(); break;
			case Key::key_c: return ::s3d::KeyC.pressed(); break;
			case Key::key_d: return ::s3d::KeyD.pressed(); break;
			case Key::key_e: return ::s3d::KeyE.pressed(); break;
			case Key::key_f: return ::s3d::KeyF.pressed(); break;
			case Key::key_g: return ::s3d::KeyG.pressed(); break;
			case Key::key_h: return ::s3d::KeyH.pressed(); break;
			case Key::key_i: return ::s3d::KeyI.pressed(); break;
			case Key::key_j: return ::s3d::KeyJ.pressed(); break;
			case Key::key_k: return ::s3d::KeyK.pressed(); break;
			case Key::key_l: return ::s3d::KeyL.pressed(); break;
			case Key::key_m: return ::s3d::KeyM.pressed(); break;
			case Key::key_n: return ::s3d::KeyN.pressed(); break;
			case Key::key_o: return ::s3d::KeyO.pressed(); break;
			case Key::key_p: return ::s3d::KeyP.pressed(); break;
			case Key::key_q: return ::s3d::KeyQ.pressed(); break;
			case Key::key_r: return ::s3d::KeyR.pressed(); break;
			case Key::key_s: return ::s3d::KeyS.pressed(); break;
			case Key::key_t: return ::s3d::KeyT.pressed(); break;
			case Key::key_u: return ::s3d::KeyU.pressed(); break;
			case Key::key_v: return ::s3d::KeyV.pressed(); break;
			case Key::key_w: return ::s3d::KeyW.pressed(); break;
			case Key::key_x: return ::s3d::KeyX.pressed(); break;
			case Key::key_y: return ::s3d::KeyY.pressed(); break;
			case Key::key_z: return ::s3d::KeyZ.pressed(); break;
			case Key::key_0: return ::s3d::Key0.pressed(); break;
			case Key::key_1: return ::s3d::Key1.pressed(); break;
			case Key::key_2: return ::s3d::Key2.pressed(); break;
			case Key::key_3: return ::s3d::Key3.pressed(); break;
			case Key::key_4: return ::s3d::Key4.pressed(); break;
			case Key::key_5: return ::s3d::Key5.pressed(); break;
			case Key::key_6: return ::s3d::Key6.pressed(); break;
			case Key::key_7: return ::s3d::Key7.pressed(); break;
			case Key::key_8: return ::s3d::Key8.pressed(); break;
			case Key::key_9: return ::s3d::Key9.pressed(); break;
			case Key::key_left: return ::s3d::KeyLeft.pressed(); break;
			case Key::key_right: return ::s3d::KeyRight.pressed(); break;
			case Key::key_up: return ::s3d::KeyUp.pressed(); break;
			case Key::key_down: return ::s3d::KeyDown.pressed(); break;
			}
			return false;
#endif
		}
		bool isUp(const Key key_num_) const {
#if defined(__DXLIB)
			return this->up_key[::AsLib2::dxKey[::Crafterra::IndexUint(key_num_)]];
#elif defined(SIV3D_INCLUDED)
			switch (key_num_) {
			case Key::key_a: return ::s3d::KeyA.up(); break;
			case Key::key_b: return ::s3d::KeyB.up(); break;
			case Key::key_c: return ::s3d::KeyC.up(); break;
			case Key::key_d: return ::s3d::KeyD.up(); break;
			case Key::key_e: return ::s3d::KeyE.up(); break;
			case Key::key_f: return ::s3d::KeyF.up(); break;
			case Key::key_g: return ::s3d::KeyG.up(); break;
			case Key::key_h: return ::s3d::KeyH.up(); break;
			case Key::key_i: return ::s3d::KeyI.up(); break;
			case Key::key_j: return ::s3d::KeyJ.up(); break;
			case Key::key_k: return ::s3d::KeyK.up(); break;
			case Key::key_l: return ::s3d::KeyL.up(); break;
			case Key::key_m: return ::s3d::KeyM.up(); break;
			case Key::key_n: return ::s3d::KeyN.up(); break;
			case Key::key_o: return ::s3d::KeyO.up(); break;
			case Key::key_p: return ::s3d::KeyP.up(); break;
			case Key::key_q: return ::s3d::KeyQ.up(); break;
			case Key::key_r: return ::s3d::KeyR.up(); break;
			case Key::key_s: return ::s3d::KeyS.up(); break;
			case Key::key_t: return ::s3d::KeyT.up(); break;
			case Key::key_u: return ::s3d::KeyU.up(); break;
			case Key::key_v: return ::s3d::KeyV.up(); break;
			case Key::key_w: return ::s3d::KeyW.up(); break;
			case Key::key_x: return ::s3d::KeyX.up(); break;
			case Key::key_y: return ::s3d::KeyY.up(); break;
			case Key::key_z: return ::s3d::KeyZ.up(); break;
			case Key::key_0: return ::s3d::Key0.up(); break;
			case Key::key_1: return ::s3d::Key1.up(); break;
			case Key::key_2: return ::s3d::Key2.up(); break;
			case Key::key_3: return ::s3d::Key3.up(); break;
			case Key::key_4: return ::s3d::Key4.up(); break;
			case Key::key_5: return ::s3d::Key5.up(); break;
			case Key::key_6: return ::s3d::Key6.up(); break;
			case Key::key_7: return ::s3d::Key7.up(); break;
			case Key::key_8: return ::s3d::Key8.up(); break;
			case Key::key_9: return ::s3d::Key9.up(); break;
			case Key::key_left: return ::s3d::KeyLeft.up(); break;
			case Key::key_right: return ::s3d::KeyRight.up(); break;
			case Key::key_up: return ::s3d::KeyUp.up(); break;
			case Key::key_down: return ::s3d::KeyDown.up(); break;
			}
			return false;
#endif
		}
		bool isDown(const Key key_num_) const {
#if defined(__DXLIB)
			return this->down_key[::AsLib2::dxKey[::Crafterra::IndexUint(key_num_)]];
#elif defined(SIV3D_INCLUDED)
			switch (key_num_) {
			case Key::key_a: return ::s3d::KeyA.down(); break;
			case Key::key_b: return ::s3d::KeyB.down(); break;
			case Key::key_c: return ::s3d::KeyC.down(); break;
			case Key::key_d: return ::s3d::KeyD.down(); break;
			case Key::key_e: return ::s3d::KeyE.down(); break;
			case Key::key_f: return ::s3d::KeyF.down(); break;
			case Key::key_g: return ::s3d::KeyG.down(); break;
			case Key::key_h: return ::s3d::KeyH.down(); break;
			case Key::key_i: return ::s3d::KeyI.down(); break;
			case Key::key_j: return ::s3d::KeyJ.down(); break;
			case Key::key_k: return ::s3d::KeyK.down(); break;
			case Key::key_l: return ::s3d::KeyL.down(); break;
			case Key::key_m: return ::s3d::KeyM.down(); break;
			case Key::key_n: return ::s3d::KeyN.down(); break;
			case Key::key_o: return ::s3d::KeyO.down(); break;
			case Key::key_p: return ::s3d::KeyP.down(); break;
			case Key::key_q: return ::s3d::KeyQ.down(); break;
			case Key::key_r: return ::s3d::KeyR.down(); break;
			case Key::key_s: return ::s3d::KeyS.down(); break;
			case Key::key_t: return ::s3d::KeyT.down(); break;
			case Key::key_u: return ::s3d::KeyU.down(); break;
			case Key::key_v: return ::s3d::KeyV.down(); break;
			case Key::key_w: return ::s3d::KeyW.down(); break;
			case Key::key_x: return ::s3d::KeyX.down(); break;
			case Key::key_y: return ::s3d::KeyY.down(); break;
			case Key::key_z: return ::s3d::KeyZ.down(); break;
			case Key::key_0: return ::s3d::Key0.down(); break;
			case Key::key_1: return ::s3d::Key1.down(); break;
			case Key::key_2: return ::s3d::Key2.down(); break;
			case Key::key_3: return ::s3d::Key3.down(); break;
			case Key::key_4: return ::s3d::Key4.down(); break;
			case Key::key_5: return ::s3d::Key5.down(); break;
			case Key::key_6: return ::s3d::Key6.down(); break;
			case Key::key_7: return ::s3d::Key7.down(); break;
			case Key::key_8: return ::s3d::Key8.down(); break;
			case Key::key_9: return ::s3d::Key9.down(); break;
			case Key::key_left: return ::s3d::KeyLeft.down(); break;
			case Key::key_right: return ::s3d::KeyRight.down(); break;
			case Key::key_up: return ::s3d::KeyUp.down(); break;
			case Key::key_down: return ::s3d::KeyDown.down(); break;
			}
			return false;
#endif
		}

	};
}

#endif //Included Crafterra Library