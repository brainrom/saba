﻿#ifndef VMDANIMATION_H_
#define VMDANIMATION_H_

#include "MMDModel.h"
#include "MMDNode.h"
#include "VMDFile.h"
#include "MMDIkSolver.h"


#include <vector>
#include <algorithm>
#include <memory>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

namespace saba
{
	struct VMDBezier
	{
		float EvalX(float t) const;
		float EvalY(float t) const;
		glm::vec2 Eval(float t) const;

		glm::vec2	m_cp[4];
	};

	struct VMDNodeAnimationKey
	{
		void Set(const VMDMotion& motion);

		float		m_time;
		glm::vec3	m_translate;
		glm::quat	m_rotate;

		VMDBezier	m_txBezier;
		VMDBezier	m_tyBezier;
		VMDBezier	m_tzBezier;
		VMDBezier	m_rotBezier;
	};

	struct VMDBlendShapeAnimationKey
	{
		float	m_time;
		float	m_weight;
	};

	struct VMDIKAnimationKey
	{
		float	m_time;
		bool	m_enable;
	};

	class VMDNodeController
	{
	public:
		using KeyType = VMDNodeAnimationKey;

		VMDNodeController();

		void SetNode(MMDNode* node);
		void Evaluate(float t);
		
		void AddKey(const KeyType& key)
		{
			m_keys.push_back(key);
		}
		void SortKeys();

	private:
		MMDNode*	m_node;
		glm::vec3	m_initTranslate;
		glm::quat	m_initRotate;
		glm::vec3	m_initScale;
		std::vector<KeyType>	m_keys;
	};

	class VMDBlendShapeController
	{
	public:
		using KeyType = VMDBlendShapeAnimationKey;

		VMDBlendShapeController();

		void SetBlendKeyShape(MMDBlendShape* shape);
		void Evaluate(float t);

		void AddKey(const KeyType& key)
		{
			m_keys.push_back(key);
		}
		void SortKeys();

	private:
		MMDBlendShape*			m_keyShape;
		std::vector<KeyType>	m_keys;
	};

	class VMDIKController
	{
	public:
		using KeyType = VMDIKAnimationKey;

		VMDIKController();

		void SetIKSolver(MMDIkSolver* ikSolver);
		void Evaluate(float t);

		void AddKey(const KeyType& key)
		{
			m_keys.push_back(key);
		}
		void SortKeys();

	private:
		MMDIkSolver*					m_ikSolver;
		std::vector<VMDIKAnimationKey>	m_keys;
	};

	class VMDAnimation
	{
	public:
		bool Create(const VMDFile& vmd, std::shared_ptr<MMDModel> model);
		void Destroy();

		void Evaluate(float t);

	private:
		using NodeControllerPtr = std::unique_ptr<VMDNodeController>;
		using IKControllerPtr = std::unique_ptr<VMDIKController>;
		using BlendShapeControllerPtr = std::unique_ptr<VMDBlendShapeController>;

		std::shared_ptr<MMDModel>		m_model;
		std::vector<NodeControllerPtr>	m_nodeControllers;
		std::vector<IKControllerPtr>	m_ikControllers;
		std::vector<BlendShapeControllerPtr>	m_blendShapeControllers;
	};

}

#endif // !VMDANIMATION_H_