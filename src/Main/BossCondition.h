#pragma once
#pragma once
#include "Condition.h"
#include "Boss.h"

class BossCondition_FullLife : public Condition<Boss>
{
public:
	bool OnTest(Boss* pBoss) override;
};

class BossCondition_HalfLife : public Condition<Boss>
{
public:
	bool OnTest(Boss* pBoss) override;
};

class BossCondtion_QuartLife : public Condition<Boss>
{
public:
	bool OnTest(Boss* pBoss) override;
};

