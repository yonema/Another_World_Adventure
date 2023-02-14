#pragma once
#include "../PlayerObserver.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace nsObserver {

			class CPlayerLevelObserver : public CPlayerObserver
			{
				//�o���l�e�[�u���̏ڍ׃f�[�^
				enum class EnExpTableVectorInfo {

					enLevel,		//���x��
					enNeedExp		//�K�v�o���l
				};

				void InitSub(CObservablePlayer* observablePlayer)override final;

				void Update(CObservablePlayer* observablePlayer, const std::string& message = "")override final;

			private:
				std::vector<std::vector<int>> m_expTable;		//�o���l�e�[�u��
				int m_oldPlayerLevel = 0;					//�ʒm�O�̃v���C���[�̃��x��
			};
		}
	}
}

