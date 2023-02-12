#pragma once
namespace nsYMEngine
{
	namespace nsGraphics
	{
		namespace nsAssimpCommon
		{
			struct SLocalTransform;
		}
		namespace nsAnimations
		{
			class CSkelton;
		}
	}
}
namespace Assimp
{
	class Importer;
}

typedef float ai_real;

template <typename TReal>
class aiVector3t;
typedef aiVector3t<ai_real> aiVector3D;

template <typename TReal>
class aiQuaterniont;
typedef aiQuaterniont<ai_real> aiQuaternion;

struct aiScene;
struct aiNode;
struct aiAnimation;
struct aiNodeAnim;

namespace nsYMEngine
{
	namespace nsGraphics
	{
		namespace nsAnimations
		{
			class CAnimationClip : nsUtils::SNoncopyable
			{
			public:
				using AnimEventFunc = std::function<void(void)> ;
				using AnimEventFuncArray = std::vector<AnimEventFunc>;
			private:
				static const std::string m_kAnimEventKeyNodeName;

			public:
				constexpr CAnimationClip() = default;
				~CAnimationClip();

				bool Init(const char* animFilePath, bool registerAnimBank);

				void Release();

				bool CalcAndGetAnimatedBoneTransforms(
					float timeInSeconds,
					std::vector<nsMath::CMatrix>* pMTransforms,
					CSkelton* pSkelton,
					const AnimEventFuncArray& animEventFuncArray,
					unsigned int* prevAnimEventIdxInOut,
					bool onlyAnimEvent,
					unsigned int animIdx = 0,
					bool isLoop = true
				) noexcept;

				constexpr void ResetAnimationParam() noexcept
				{
					//m_prevAnimEventIdx = 0;
					//m_isPlayedAnimationToEnd = false;
					m_animLoopCounter = 0;
				}

				constexpr bool IsLoaded() const noexcept
				{
					return m_isLoaded;
				}

				constexpr bool IsShared() const noexcept
				{
					return m_isShared;
				}

				constexpr void SetIsShared(bool isShared) noexcept
				{
					m_isShared = isShared;
				}

			private:

				void Terminate();

				bool ImportScene(const char* animFilePath);

				float CalcAnimationTimeTicks(
					float timeInSeconds, 
					unsigned int animIdx, 
					bool isLoop,
					bool* isPlayedAnimationToEndOut,
					unsigned int* prevAnimEventIdxOut
				) noexcept;

				void ReadNodeHierarchy(
					float animTimeTicks,
					const aiNode& node,
					const nsMath::CMatrix& parentTransform,
					const aiAnimation& animation,
					CSkelton* pSkelton,
					unsigned int animIdx
				) noexcept;

				const aiNodeAnim* FindNodeAnim(
					const aiAnimation& Animation,
					const std::string& NodeName,
					unsigned int animIdx) const noexcept;

				void CalcLocalTransform(
					nsAssimpCommon::SLocalTransform& localTransform,
					float animTimeTicks,
					const aiNodeAnim& nodeAnim
				) const noexcept;
				void CalcInterpolatedScaling(
					aiVector3D* pScaling, float animTimeTicks, const aiNodeAnim& nodeAnim) const noexcept;

				void CalcInterpolatedRotation(
					aiQuaternion* pRotation, float animTimeTicks, const aiNodeAnim& nodeAnim) const noexcept;

				void CalcInterpolatedPosition(
					aiVector3D* pPosition, float animTimeTicks, const aiNodeAnim& nodeAnim) const noexcept;

				unsigned int FindScaling(float animTimeTicks, const aiNodeAnim& nodeAnim) const noexcept;

				unsigned int FindRotation(float animTimeTicks, const aiNodeAnim& nodeAnim) const noexcept;

				unsigned int FindPosition(float animTimeTicks, const aiNodeAnim& nodeAnim) const noexcept;


				bool FindAnimKeyEventNode(const aiNode& node);

				void ReadAnimKeyEventNode(
					float animTimeTicks,
					const aiNode& node,
					const aiAnimation& animation,
					unsigned int animIdx,
					const AnimEventFuncArray& animEventFuncArray,
					unsigned int* prevAnimEventIdxInOut
				) noexcept;

			private:
				Assimp::Importer* m_importer = nullptr;
				const aiScene* m_scene = nullptr;
				int m_animLoopCounter = 0;
				bool m_isLoaded = false;
				bool m_isShared = false;
				std::vector<std::unordered_map<std::string, const aiNodeAnim*>>
					m_nodeAnimMapArray = {};
				const aiNode* m_animEventNode = nullptr;
			};

		}
	}
}