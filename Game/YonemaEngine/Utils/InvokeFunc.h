#pragma once
namespace nsYMEngine
{
	namespace nsUtils
	{
		class CInvokeFunc : private nsUtils::SNoncopyable
		{
		private:
			struct SInvokeFuncData
			{
				SInvokeFuncData(const std::function<void(void)>& func, float delayTime)
					:func(func), delayTime(delayTime) {};
				~SInvokeFuncData() = default;

				bool CountTime(float deltaTime) noexcept
				{
					delayTime -= deltaTime;
					if (delayTime <= 0.0f)
					{
						return true;
					}

					return false;
				}

				std::function<void(void)> func = {};
				float delayTime = 0.0f;
			};


		public:
			CInvokeFunc()
			{
				assert(m_instance == nullptr);
				m_instance = this;
			}
			~CInvokeFunc()
			{
				m_instance = nullptr;
			}

			void Update(float deltaTime);

			void PushInvokeFunc(const std::function<void(void)>& func, float delayTime)
			{
				m_invokeFuncList.emplace_back(SInvokeFuncData(func, delayTime));
			}

		private:
			static CInvokeFunc* m_instance;
			std::list<SInvokeFuncData> m_invokeFuncList = {};
		};

	}
}