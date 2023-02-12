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
			//入るボタンの画像表示
			m_enterSprite->SetDrawingFlag(true);
		}

		void CInn::OnTriggerStay(CExtendedDataForRigidActor* otherData)
		{
			//入るボタンを押した時に、プレイヤーロックして宿の2D画像(プレイヤーUIより優先度を高くする)を表示。
			//UIは別で表示(宿2Dより優先度を高くする)。
			//宿内の処理はUIに任せる?
			if (m_state == EnFacilityState::enClose && Input()->IsTrigger(EnActionMapping::enDecision))
			{
				m_state = EnFacilityState::enOpen;
				m_backGroundLevel.Clear();
				InitBackgroundLevel();
				m_enterSprite->SetDrawingFlag(false);

				//背景を表示
				m_backGroundLevel.PlayAnimation("InnAppear");

				//TODO:宿UI表示
			}
			
			if (false/*TODO:宿UIが閉じたのを確認したら*/)
			{
				//宿UIをDelete

				//背景を消す
				m_backGroundLevel.PlayAnimation("InnDisappear");
			}
		}

		void CInn::OnTriggerExit(CExtendedDataForRigidActor* otherData)
		{
			//入るボタンの画像非表示
			m_enterSprite->SetDrawingFlag(false);
		}


		void CInn::InitBackgroundLevel()
		{
			m_backGroundLevel.Load(m_kBackGroundLevelPath.c_str());

			//宿屋を閉じて背景が完全に透過された時にイベントを登録
			m_backGroundLevel.RegisterAnimationEvent("InnDisappear", "Disappeared", [this](const nsYMEngine::nsGraphics::nsAnimations2D::SAnimation2DFrameData& frameData)
				{
					m_enterSprite->SetDrawingFlag(true);
					m_state = EnFacilityState::enClose;

					//TODO:プレイヤーロックを解除

					//このタイミングでレベルのスプライトをすべて開放したいが、ここでレベルのClear()を呼ぶとおそらくクラッシュする。(この関数はレベル内のスプライト配列を走査しながら呼ばれるため)
				}
			);
		}
	}
}