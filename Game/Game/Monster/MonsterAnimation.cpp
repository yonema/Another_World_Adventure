#include "YonemaEnginePreCompile.h"
#include "Monster.h"
#include "MonsterAnimation.h"
#include "MonsterList.h"
#include "../CSV/CSVManager.h"
#include "../Utils/StringManipulation.h"

namespace nsAWA {

	namespace nsMonster {

		namespace {

			constexpr int kCSVTitleData = 0;		//CSVデータの見出し情報。
		}

		void CMonsterAnimation::Init(
			CModelRenderer* monsterModel,
			const std::vector<SAnimData>& animDataList,
			const std::vector<std::string>& animFilePathArray
		) {

			//モンスターのモデルのポインタを受け取る。
			m_monsterModel = monsterModel;

			//アニメーションデータを設定。
			m_animDataList = animDataList;

			//アニメーションファイルパスを設定。
			m_animFilePathArray = animFilePathArray;

			for (const auto& animData : m_animDataList) {

				//このアニメーションのイベント数を伝える。
				m_monsterModel->ReserveAnimationEventFuncArray(static_cast<int>(animData.animNum), static_cast<int>(animData.animationEvent.size()));

				//アニメーションイベントを順に参照。
				for (const auto& animEventData : animData.animationEvent) {

					//アニメーションイベントを追加。
					m_monsterModel->AddAnimationEventFunc(
						static_cast<unsigned int>(animData.animNum),
						[&]() {m_animationEvent.GetAnimationEvent(
							animEventData.eventName,
							animEventData.eventMaterial);
						}
					);
				}
			}
		}

		void CMonsterAnimation::Release() {

			//データを破棄。
			m_animDataList.clear();

			m_animFilePathArray.clear();
		}

		void CMonsterAnimation::Update(bool changeState, EnMonsterState state) {

			//ステートに変更があったら。
			if (changeState) {

				//ステートに対応するアニメーションを再生。
				PlayAnimation(state);
			}
		}

		void CMonsterAnimation::PlayAnimation(EnMonsterState state) {

			//ステートから対応アニメーションのindexを取得。
			const SAnimData& animationData = GetAnimationData(state);
			
			//対応するアニメーションがないなら。
			if (animationData.animNum == -1) {
			
				//再生できないので早期リターン。
				return;
			}
			else {
			
				//対応するアニメーションを再生。
				m_monsterModel->PlayAnimationFromBeginning(
					animationData.animNum,
					animationData.speed,
					animationData.isLoopAnim
				);
			}
		}

		const SAnimData& CMonsterAnimation::GetAnimationData(EnMonsterState state)const {

			std::string stateStr = "NoStr";

			//ステートを文字列に変換。
			switch (state) {

			case EnMonsterState::enIdle:
				stateStr = "Idle";
				break;
			case EnMonsterState::enWalk:
				stateStr = "Walk";
				break;
			case EnMonsterState::enRun:
				stateStr = "Run";
				break;
			case EnMonsterState::enBark:
				stateStr = "Bark";
				break;
			case EnMonsterState::enWeakAttack:
				stateStr = "WeakAttack";
				break;
			case EnMonsterState::enStrongAttack:
				stateStr = "StrongAttack";
				break;
			case EnMonsterState::enDamage:
				stateStr = "Damage";
				break;
			case EnMonsterState::enDeath:
				stateStr = "Death";
				break;
			}

			//アニメーションリストから対応するアニメーションの番号を検索。
			for (const auto& animation : m_animDataList) {

				//同じ名前のアニメーションが見つかった。
				if (animation.animName == stateStr) {

					//そのアニメーションをリターン。
					return animation;
				}
			}

			//見つからなかった。
			std::string errMsg = "対応するアニメーションが見つかりませんでした。 : ";
			errMsg += stateStr;
			nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errMsg).c_str());

			//仮に終端をリターン。
			return *m_animDataList.end();
		}

		void CMonsterAnimation::LoadAnimation(
			const std::string& monsterName,
			const wchar_t* monsterAnimationCSVFilePath,
			const wchar_t* monsterAnimationEventCSVFilePath
		) {

			//CSV管理クラスを生成。
			nsCSV::CCsvManager csvManager;

			//アニメーションのCSVを読み込む。
			csvManager.LoadCSV(monsterAnimationCSVFilePath);

			//データカウントを初期化。
			int dataIndex = 0;

			//アニメーションのカウント。
			int animNum = -1;						

			std::string topData = "";

			//アニメーションデータの雛形を生成。
			SAnimData animDataBase;

			//アニメーション情報を取り出す。
			for (const auto& animData : csvManager.GetCsvData()) {

				if (animData[kCSVTitleData] == "*") {

					//アニメーション情報の終端なので情報を追加。

					//データを格納。
					m_animDataList.emplace_back(animDataBase);

					//データを進める。
					dataIndex++;

					//アニメーションデータの雛形を初期化。
					SAnimData clearData;
					animDataBase = clearData;

					//次へ。
					continue;
				}

				if (animData[kCSVTitleData] == "NAME") {

					//ファイルパスを取得、設定。
					std::string filePath = "Assets/Animations/Monsters/";
					filePath = filePath + monsterName + "/";
					filePath = filePath + animData[1] + ".fbx";

					//アニメーションのファイルパスを配列に追加。
					m_animFilePathArray.emplace_back(filePath);

					//区切り文字からアニメーションの名前を取得、設定する。
					//名前に「_」はいらないため、+ 1で分割。
					animDataBase.animName = animData[1].substr(animData[1].find("_") + 1);

					//アニメーション番号を設定。
					animNum++;
					animDataBase.animNum = animNum;
				}

				if (animData[kCSVTitleData] == "SPEED") {

					//速さを取得。
					animDataBase.speed = std::stof(animData[1]);
				}

				if (animData[kCSVTitleData] == "LOOP") {

					//ループフラグを取得。
					animDataBase.isLoopAnim = animData[1] == "TRUE" ? true : false;
				}

				if (animData[kCSVTitleData] == "EVENT") {

					SAnimationEventData animEventData;

					//イベントを取得。
					animEventData.eventName = animData[1];
					animEventData.hasEventMaterial = animData[2] == "TRUE" ? true : false;

					animDataBase.animationEvent.emplace_back(animEventData);
				}
			}

			//CSVデータを初期化。
			csvManager.ClearCSV();

			//アニメーションイベントのCSVを読み込む。
			csvManager.LoadCSV(monsterAnimationEventCSVFilePath);

			//アニメーションイベントを追加するための雛形を初期化。
			std::list<std::list<std::vector<std::string>>> animEventDataList;
			std::list<std::vector<std::string>> animEventData;

			//アニメーションイベントのデータをリスト化。
			for (const auto& animEventStr : csvManager.GetCsvData()) {

				//一つのデータの終端なら。
				if (animEventStr[0] == "*") {

					//リストにイベントデータを追加。
					animEventDataList.emplace_back(animEventData);

					//雛形のデータを破棄。
					animEventData.clear();

					//次へ。
					continue;
				}

				//イベントの情報を追加。
				animEventData.emplace_back(animEventStr);
			}

			//アニメーションデータを順に参照。
			for (auto& animData : m_animDataList) {

				//アニメーションイベントを順に参照。
				for (auto& animEvent : animData.animationEvent) {

					//イベント情報が必要ないなら。
					if (!animEvent.hasEventMaterial) {

						//次のイベントへ。
						continue;
					}
					//イベントに情報が必要なら。
					else {

						//アニメーションイベントデータの先頭情報を取り出す。
						auto animEventDataItr = animEventDataList.begin();

						//データを格納。
						animEvent.eventMaterial = *animEventDataItr;

						//先頭情報を破棄。
						animEventDataList.erase(animEventDataItr);
					}
				}
			}
		}
	}
}