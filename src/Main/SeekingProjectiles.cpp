#include "pch.h"
#include "SeekingProjectiles.h"
#include "Vector2.h"

int SeekingProjectiles::GetDamage()
{
    return mDamage;
}

void SeekingProjectiles::SetDamage(int damage)
{
    mDamage = damage;
}

float SeekingProjectiles::GetSpeed()
{
    return mSpeed;
}

void SeekingProjectiles::OnUpdate()
{
    if (!mEnnemisList.empty())
    {
        mEnnemisList.erase(std::remove_if(mEnnemisList.begin(), mEnnemisList.end(), [](Ennemis* ennemi) { return ennemi == nullptr || !ennemi->IsAlive(); }), mEnnemisList.end());

        if (!mCurrentTarget || mCurrentTarget->IsAlive())
        {
            float miniDistance = std::numeric_limits<float>::max();
            Ennemis* nearestEnnemis = nullptr;

            for (Ennemis* ennemi : mEnnemisList)
            {
                if (ennemi && ennemi->IsAlive())
                {
                    _ASSERT(ennemi->GetPosition().x);
                    float dx = ennemi->GetPosition().x - GetPosition().x;
                    float dy = ennemi->GetPosition().y - GetPosition().y;
                    float distance = std::sqrt(dx * dx + dy * dy);

                    if (distance < miniDistance)
                    {
                        nearestEnnemis = ennemi;
                        miniDistance = distance;
                    }
                }
            }

            mCurrentTarget = nearestEnnemis;
        }

        if (!mCurrentTarget)
        {
            std::cout << "Aucune cible valide trouvée !" << std::endl;
            return;
        }

        Vector2<float> targetPosition = mCurrentTarget->GetPosition();
        Vector2<float> currentPosition = GetPosition();
        Vector2<float> direction = targetPosition - currentPosition;
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (distance > 0.f)
        {
            direction /= distance;
            Vector2<float> velocity = direction * GetSpeed() * GetDeltaTime();
            GoToPosition(targetPosition.x, targetPosition.y, GetSpeed());
        }

        if (currentPosition.x >= 2000)
        {
            Destroy();
        }
    }
    else
    {
        Destroy();
    }
}

void SeekingProjectiles::OnCollision(LESprite* collidedWith)
{

}

void SeekingProjectiles::OnInitialize()
{


}

void SeekingProjectiles::CheckWindow()
{
}

void SeekingProjectiles::SetEnnemisList(std::vector<Ennemis*>* ennemisList)
{
    mEnnemisList = *ennemisList;
}