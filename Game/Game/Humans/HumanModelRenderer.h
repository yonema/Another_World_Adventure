#pragma once
#include "HumanAnimationType.h"

namespace nsAWA
{
	namespace nsHumans
	{
		class CHumanModelRenderer : public IGameObject
		{
		private:
			static const float m_kModelScale;
			static const float m_kVertexBiasXDegAngle;
			static const float m_kDistanceToReducingUpdate;

		public:
			bool Start() override final;

			void Update(float deltaTime) override final;

			void OnDestroy() override final;

		public:
			constexpr CHumanModelRenderer() = default;
			~CHumanModelRenderer() = default;

			void Init(
				const char* name,
				const CVector3& position,
				const CQuaternion& rotation,
				const char* filePath,
				bool isShadowReceiver = true
			);

			void Release();


			constexpr const CModelRenderer* GetModelRenderer() const noexcept
			{
				return m_modelRenderer;
			}

			constexpr bool IsValid() const noexcept
			{
				return GetModelRenderer();
			}

			constexpr const auto& GetPosition() const noexcept
			{
				return IsValid() ? GetModelRenderer()->GetPosition() : CVector3::Zero();
			}

			constexpr const auto& GetRotation() const noexcept
			{
				return IsValid() ? GetModelRenderer()->GetRotation() : CQuaternion::Identity();
			}

			constexpr auto GetLoadingState() const noexcept
			{
				return m_loadingState;
			}

			constexpr bool IsLoaded() const noexcept
			{
				return GetLoadingState() == EnLoadingState::enAfterLoading;
			}

			inline void PlayAnimation(EnHumanAnimType animType, bool isLoop = true, float speed = 1.0f)
			{
				if (IsValid())
				{
					m_modelRenderer->PlayAnimation(
						static_cast<unsigned int>(animType), isLoop, speed);
				}
			}

			inline void PlayAnimation(EnHumanAnimType animType, float speed, bool isLoop = true)
			{
				PlayAnimation(animType, isLoop, speed);
			}

			constexpr void ModelActivate() noexcept
			{
				if (m_modelRenderer)
				{
					m_modelRenderer->ModelActivate();
				}
			}

			constexpr void ModelDeactivate() noexcept
			{
				if (m_modelRenderer)
				{
					m_modelRenderer->ModelDeactivate();
				}
			}

			constexpr bool IsModelActivate() const noexcept
			{
				return m_modelRenderer ? m_modelRenderer->IsModelActivate() : false;
			}

		private:

			void CheckLoading();

		private:
			CModelRenderer* m_modelRenderer = nullptr;
			EnLoadingState m_loadingState = EnLoadingState::enBeforeLoading;
		};

	}
}