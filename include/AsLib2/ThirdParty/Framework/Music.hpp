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

#ifndef INCLUDED_ASLIB2_ASLIB2_THIRD_PARTY_FRAMEWORK_MUSIC_HPP
#define INCLUDED_ASLIB2_ASLIB2_THIRD_PARTY_FRAMEWORK_MUSIC_HPP

namespace As {

	class Music {
	private:

#if defined(__DXLIB)
		using Music_ = int;
#elif defined(SIV3D_INCLUDED)
		using Music_ = ::s3d::Audio;
#endif

#if defined(__DXLIB)
		Music_ m_music = -1;
#elif defined(SIV3D_INCLUDED)
		Music_ m_music{};
#endif
        double volume_offset = 0.1;
	public:

		Music() {
#if defined(__DXLIB)
			m_music = ::DxLib::LoadSoundMem("./../../../resource/Music/First Journey (takai).mp3");
#elif defined(SIV3D_INCLUDED)
			m_music = ::s3d::Audio(U"./../../../../resource/Music/First Journey (takai).mp3", ::s3d::Loop::Yes);
#endif // __DXLIB
		}

		~Music() {

		}

		Music_ getMusic() const { return this->m_music; }
		void playLoop() const {
#if defined(__DXLIB)
			if (this->m_music == -1) return;
			::DxLib::PlaySoundMem(this->m_music, DX_PLAYTYPE_LOOP, TRUE);
#elif defined(SIV3D_INCLUDED)
			m_music.play();

#endif // __DXLIB
		}
        
        // BGM音量ダウン
        void volumeDown() const {
#if defined(__DXLIB)
            // DXLIB用の音量調整未実装
#elif defined(SIV3D_INCLUDED)
            double val = m_music.getVolume();
            if (val <= 0.0) return;
            m_music.setVolume(val - volume_offset);
#endif // __DXLIB
        }

        // BGM音量アップ
        void volumeUp() const {
#if defined(__DXLIB)
            // DXLIB用の音量調整未実装
#elif defined(SIV3D_INCLUDED)
            double val = m_music.getVolume();
            if (val >= 1.0) return;
            m_music.setVolume(val + volume_offset);
#endif // __DXLIB
        }
        
        // ミュート
        void mute() const {
#if defined(__DXLIB)
            // DXLIB用の音量調整未実装
#elif defined(SIV3D_INCLUDED)
            m_music.setVolume(0.0);
#endif // __DXLIB
        }
        
	};
}

#endif //Included Crafterra Library