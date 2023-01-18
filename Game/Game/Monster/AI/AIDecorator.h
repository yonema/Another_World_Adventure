#pragma once

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			//前方宣言
			struct SMonsterAIBlackboard;

			//AIのデコレーター
			//劣化版。boolのポインタ変数を持ち、フラグの参照を受け取って評価する
			class CAIDecorator : nsUtils::SNoncopyable
			{
			public:
				void Init(bool* flag);

				void Reverse() {

					//逆の評価をする。
					m_reverse = true;
				}

				void Release();

				bool Evaluate()const {

					//フラグから評価。
					if (m_reverse) {

						return *m_falgRef ? false : true;
					}
					else {

						return *m_falgRef;
					}
				}

			private:
				bool* m_falgRef = nullptr;	//何らかのフラグ
				bool m_reverse = false;		//逆の評価をする？
			};

			//デコレーター生成クラス
			class CAIDecoratorBuilder : nsUtils::SNoncopyable {

			public:
				CAIDecorator* CreateDecorator(const std::string& flagStr, SMonsterAIBlackboard* blackboard);
			};
		}
	}
}

