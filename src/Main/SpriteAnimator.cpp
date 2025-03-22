#include "pch.h"
#include "SpriteAnimator.h"

SpriteAnimator::SpriteAnimator(LESprite* sprite) : mpSprite(sprite), mCurrentFrame(0), mElapsedTime(0.0f)
{
}

void SpriteAnimator::CreateAnimation(const char* animName, std::vector<const char*> listCharTexture, float animationTime)
{
    /*std::vector<LETexture*> listTextures;

    for(int i = 0; i < listCharTexture.size(); i++)
    {
        listTextures.push_back(GameManager::Get()->GetAssetManager().GetTexture(listCharTexture[i]));
    }

    const Animation& animation = {listTextures, animationTime};

	mAnimations[animName] = animation;*/

    Animation& animation = mAnimations[animName];

    std::vector<LETexture*> listTextures;

    for (int i = 0; i < listCharTexture.size(); i++)
    {
        listTextures.push_back(GameManager::Get()->GetAssetManager().GetTexture(listCharTexture[i]));
    }

    animation.textures = listTextures;
    animation.spritesDuration = animationTime;
}

void SpriteAnimator::SetAnimation(const char* name)
{
    if (mAnimations.find(name) != mAnimations.end()) {
        mCurrentAnimationName = name;
        mCurrentFrame = 0;
        mElapsedTime = 0.0f;
        mpSprite->SetTexture(mAnimations[name].textures[0]);
    }
}

void SpriteAnimator::Update(float dt)
{
    if (mAnimations.find(mCurrentAnimationName) != mAnimations.end()) {
        mElapsedTime += dt;

        const Animation& animation = mAnimations[mCurrentAnimationName];
        if (mElapsedTime >= animation.spritesDuration) {
            mElapsedTime -= animation.spritesDuration;
            mCurrentFrame = (mCurrentFrame + 1) % animation.textures.size();
            mpSprite->SetTexture(animation.textures[mCurrentFrame]);
        }
    }
}
