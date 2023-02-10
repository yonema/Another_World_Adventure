#include "YonemaEnginePreCompile.h"
#include "Feature.h"
#include "FeatureManager.h"
#include "AbnormalStatus/Paralysis.h"
#include "AbnormalStatus/Poison.h"

namespace nsAWA {

	namespace nsFeature {

		void CFeatureManager::Release() {

			//���ʂ�j���B
			for (auto itr = m_feature.begin(); itr != m_feature.end(); ) {

				//�j���B
				if ((*itr) != nullptr) {
					delete (*itr);
				}

				itr = m_feature.erase(itr);

				continue;
			}
		}

		void CFeatureManager::UpdateFeature(float deltaTime) {

			//�X�e�[�^�X�ω��̃��X�g�̃C�e���[�^�����ɎQ�ƁB
			for (auto itr = m_feature.begin(); itr != m_feature.end(); ) {

				//�X�e�[�^�X�ω��̋@�\���X�V�B
				bool isDead = (*itr)->Update(deltaTime);

				//�I���������B
				if (isDead) {

					//���̃X�e�[�^�X�ω���j���B
					(*itr)->Release();
					itr = m_feature.erase(itr);

					//�j�����ꂽ���Ƃɂ��A���Ɏ��̃C�e���[�^�������Ă���̂ňڂ鏈�����X�L�b�v�B
					continue;
				}

				//���̃C�e���[�^�Ɉڂ�B
				itr++;
			}

			//�X�e�[�^�X�ω��̏�Ԃ��X�V�B
			UpdateFeatureState();
		}

		void CFeatureManager::UpdateFeatureState() {

			//��Ԃ��������B
			m_isParalysis = false;
			m_isPoison = false;

			//�X�e�[�^�X�ω��̃��X�g�����ɎQ�ƁB
			for (const auto& feature : m_feature) {

				//�Ȃ�̏�Ԃ����ׂ�B
				const type_info& id = typeid(*feature);

				//���̃N���X����ჃN���X��������B
				if (typeid(nsStatusChanger::CParalysis) == id) {

					//��჏�Ԃł���B
					m_isParalysis = true;
				}
				else if (typeid(nsStatusChanger::CPoison) == id) {

					//�ŏ�Ԃł���B
					m_isPoison = true;
				}
			}
		}

		bool CFeatureManager::CanUseActiveSkill() {

			//����������჏�ԁi�₻�̑��g�p�ł��Ȃ���ԁj�ł͂Ȃ��B
			if (!m_isParalysis) {

				//�����܂ł��Ȃ��A�N�e�B�u�X�L�����g�p�ł���̂ő������^�[���B
				return true;
			}

			//�X�e�[�^�X�ω��̃��X�g�����ɎQ�ƁB
			for (const auto& feature : m_feature) {

				//�Ȃ�̏�Ԃ����ׂ�B
				const type_info& id = typeid(*feature);

				//���̃N���X����ჃN���X��������B
				if (typeid(nsStatusChanger::CParalysis) == id) {

					//��ჃN���X�ɃL���X�g���A�A�N�e�B�u�X�L�����g�p�\���ǂ������ׂ�B
					bool canAttack = dynamic_cast<nsStatusChanger::CParalysis*>(feature)->CanUseActiveSkill();

					//���̖�჋@�\����A�N�e�B�u�X�L�����g�p�ł��Ȃ��Ɠ`����ꂽ��B
					if (!canAttack) {

						//�����炩��Ăяo�����ɃA�N�e�B�u�X�L�����g�p�ł��Ȃ��Ɠ`����B
						return false;
					}
				}
			}

			//�A�N�e�B�u�X�L�����g�p�ł���B
			return true;
		}
	}
}