#include "pch.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Object.h"
#include "Collider.h"
void CollisionManager::update()
{
	for (UINT Row = 0; Row < (UINT)LAYER::END; ++Row)
	{
		for (UINT Col = Row; Col < (UINT)LAYER::END; ++Col)
		{
			if (_layers[Row] & (1 << Col))
			{
				//int a = 0;
				collisionLayerupdate((LAYER)Row, (LAYER)Col);
			}
		}
	}
}

void CollisionManager::checkLayer(LAYER _left, LAYER _right)
{
	// �������� ������ ���ô�.
	// ���� ���� LAYER�� ������, ū ���� ��
	UINT Row = (UINT)_left;
	UINT Col = (UINT)_right;
	//Row = min(Row, Col);
	if (Row > Col)
		std::swap(Row, Col);

	//// ��Ʈ ����
	// üũ�� �Ǿ��ִٸ�
	if (_layers[Row] & (1 << Col))
	{
		// üũ Ǯ��
		_layers[Row] &= ~(1 << Col);
	}
	// üũ�� �ȵǾ��ִٸ�r
	else
	{
		_layers[Row] |= (1 << Col);
	}
}

void CollisionManager::checkReset()
{
	// �޸� �ʱ�ȭ
	memset(_layers, 0, sizeof(UINT) * (UINT)LAYER::END);
}

void CollisionManager::collisionLayerupdate(LAYER _left, LAYER _right)
{
	std::shared_ptr<Scene> pCurrentScene = GET_SINGLETON(SceneManager)->getCurrentScene();
	const vector<Object*>& vecLeftLayer = pCurrentScene->getLayerObjects(_left);
	const vector<Object*>& vecRightLayer = pCurrentScene->getLayerObjects(_right);
	map<ULONGLONG, bool>::iterator iter;
	for (size_t i = 0; i < vecLeftLayer.size(); ++i)
	{
		Collider* pLeftCollider = vecLeftLayer[i]->getComponent<Collider>();
		// �浹ü ���� ���
		if (nullptr == pLeftCollider)
			continue;
		for (size_t j = 0; j < vecRightLayer.size(); j++)
		{
			Collider* pRightCollider = vecRightLayer[j]->getComponent<Collider>();
			// �浹ü�� ���ų�, �ڱ��ڽŰ��� �浹�� ���
			if (nullptr == pRightCollider || vecLeftLayer[i] == vecRightLayer[j])
				continue;

			COLLIDER_ID colliderID; // �� �浹ü�θ� ���� �� �ִ� ID
			colliderID.left_ID = pLeftCollider->getID();
			colliderID.right_ID = pRightCollider->getID();

			iter = _coliisionInfoMap.find(colliderID.ID);
			// ���� ������ �浹�� �� ����.
			if (iter == _coliisionInfoMap.end())
			{
				// �浹 ������ �̵�ϵ� ������ ��� ���(�浹���� �ʾҴٷ�)
				_coliisionInfoMap.insert({ colliderID.ID, false });
				//m_mapCollisionInfo[colliderID.ID] = false;
				iter = _coliisionInfoMap.find(colliderID.ID);
			}
			if (isCollision(pLeftCollider, pRightCollider))
			{
				// �������� �浹��
				if (iter->second)
				{
					if (vecLeftLayer[i]->isDead() || vecRightLayer[j]->isDead())
					{
						pLeftCollider->exitCollision(pRightCollider);
						pRightCollider->exitCollision(pLeftCollider);
						iter->second = false;
					}
					else
					{
						pLeftCollider->stayCollision(pRightCollider);
						pRightCollider->stayCollision(pLeftCollider);
					}
				}
				else // ������ �浹 x
				{
					if (!vecLeftLayer[i]->isDead() && !vecRightLayer[j]->isDead())
					{
						pLeftCollider->enterCollision(pRightCollider);
						pRightCollider->enterCollision(pLeftCollider);
						iter->second = true;
					}
				}
			}
			else // �浹 ���ϳ�?
			{
				if (iter->second) // �ٵ� ������ �浹��
				{
					pLeftCollider->exitCollision(pRightCollider);
					pRightCollider->exitCollision(pLeftCollider);
					iter->second = false;
				}
			}
		}
	}
}

bool CollisionManager::isCollision(Collider* _left, Collider* _right)
{
	Vector2 vLeftPos = _left->getPosition();
	Vector2 vRightPos = _right->getPosition();
	Vector2 vLeftSize = _left->getSize();
	Vector2 vRightSize = _right->getSize();

	RECT leftRt = RECT_MAKE(vLeftPos.x, vLeftPos.y, vLeftSize.x, vLeftSize.y);
	RECT rightRt = RECT_MAKE(vRightPos.x, vRightPos.y, vRightSize.x, vRightSize.y);
	RECT rt;
	return ::IntersectRect(&rt, &leftRt, &rightRt);
	/*if (abs(vRightPos.x - vLeftPos.x) < (vLeftSize.x + vRightSize.x) / 2.f
		&& abs(vRightPos.y - vLeftPos.y) < (vLeftSize.y + vRightSize.y) / 2.f)
	{
		return true;
	}

	return false;*/
}
