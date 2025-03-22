#include "pch.h"
#include "BossCondition.h"

bool BossCondition_FullLife::OnTest(Boss* pBoss)
{
	return pBoss->GetVie();
}

bool BossCondition_HalfLife::OnTest(Boss* pBoss)
{
	return pBoss->GetVie() == pBoss->GetVie() / 2;
}

bool BossCondtion_QuartLife::OnTest(Boss* pBoss)
{
	return pBoss->GetVie() == pBoss->GetVie() / 4;
}