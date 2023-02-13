#include "Inn.h"
namespace nsAWA
{
	namespace nsFacility
	{
		bool CInn::Start()
		{
			m_enterSprite = NewGO<CSpriteRenderer>();
			SSpriteInitData initData;
			initData.filePath = m_kSpritePath.c_str();
			initData.spriteSize = m_kSpriteSize;
			initData.alphaBlendMode = EnAlphaBlendMode::enTrans;

			m_enterSprite->Init(initData);
			m_enterSprite->SetScale(m_kSpriteScale);
			m_enterSprite->SetPosition(m_kSpritePosition);

			m_enterSprite->SetDrawingFlag(false);
			return true;
		}

		void CInn::OnDestroy()
		{

			return;
		}

		void CInn::Update(float deltaTime)
		{

			return;
		}

		void CInn::OnTriggerEnter(CExtendedDataForRigidActor* otherData)
		{
			//����{�^���̉摜�\��
			m_enterSprite->SetDrawingFlag(true);
		}

		void CInn::OnTriggerStay(CExtendedDataForRigidActor* otherData)
		{
			//����{�^�������������ɁA�v���C���[���b�N���ďh��2D�摜(�v���C���[UI���D��x����������)��\���B
			//UI�͕ʂŕ\��(�h2D���D��x����������)�B
			//�h���̏�����UI�ɔC����?
			if (m_state == EnFacilityState::enClose && Input()->IsTrigger(EnActionMapping::enDecision))
			{
				m_state = EnFacilityState::enOpen;
				m_backGroundLevel.Clear();
				InitBackgroundLevel();
				m_enterSprite->SetDrawingFlag(false);

				//�w�i��\��
				m_backGroundLevel.PlayAnimation("InnAppear");

				//TODO:�hUI�\��
			}
			
			if (false/*TODO:�hUI�������̂��m�F������*/)
			{
				//�hUI��Delete

				//�w�i������
				m_backGroundLevel.PlayAnimation("InnDisappear");
			}
		}

		void CInn::OnTriggerExit(CExtendedDataForRigidActor* otherData)
		{
			//����{�^���̉摜��\��
			m_enterSprite->SetDrawingFlag(false);
		}


		void CInn::InitBackgroundLevel()
		{
			m_backGroundLevel.Load(m_kBackGroundLevelPath.c_str());

			//�h������Ĕw�i�����S�ɓ��߂��ꂽ���ɃC�x���g��o�^
			m_backGroundLevel.RegisterAnimationEvent("InnDisappear", "Disappeared", [this](const nsYMEngine::nsGraphics::nsAnimations2D::SAnimation2DFrameData& frameData)
				{
					m_enterSprite->SetDrawingFlag(true);
					m_state = EnFacilityState::enClose;

					//TODO:�v���C���[���b�N������

					//���̃^�C�~���O�Ń��x���̃X�v���C�g�����ׂĊJ�����������A�����Ń��x����Clear()���ĂԂƂ����炭�N���b�V������B(���̊֐��̓��x�����̃X�v���C�g�z��𑖍����Ȃ���Ă΂�邽��)
				}
			);
		}
	}
}