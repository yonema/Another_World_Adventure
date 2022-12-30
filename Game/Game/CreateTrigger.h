#pragma once

namespace nsAWA {

	//トリガー製造クラス
	class CCreateTrigger : public IGameObject
	{
		//トリガーの情報
		struct STriggerInfo {

			float size = 0.0f;	//サイズ
			CVector3 position = CVector3::Zero();	//座標
			std::list<std::vector<std::string>> m_featureList;		//効果のリスト
		};
	public:
		void Create(std::list<std::vector<std::string>> triggerMaterial,
			const CVector3& position = CVector3::Zero(),
			const CVector3& forwardDirection = CVector3::Zero()
		);

		void OnDestroy()override final;

		void Update(float deltaTime)override final;

	private:
		void OnTriggerEnter(CExtendedDataForRigidActor* otherData);

	private:
		CPhysicsTriggerObject m_trigger;	//トリガー
		STriggerInfo m_triggerInfo;			//トリガーの情報
		float m_triggerDurationTime = 0.0f;	//トリガーの持続時間
	};
}