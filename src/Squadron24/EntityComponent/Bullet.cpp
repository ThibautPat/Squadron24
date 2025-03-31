#include "Bullet.h"
#include "../ManagerGroup/GameManager.h"

Bullet::Bullet(Module* Origine, sf::Vector2f DirectionBullet, int AngleRotation)
{
    Originemodule = Origine;
    m_Faction = Originemodule->m_Faction;
    if (Originemodule->m_Faction == GameManager::Faction::Gentil)
    {
        m_Texture = *GameManager::GetInstance()->m_DataManager->m_TextureMap[DataManager::GREENBULLET]; 
        m_TextureAnim = *GameManager::GetInstance()->m_DataManager->m_TextureMap[DataManager::GREENHITANIMATION];
    }
    else 
    {
        m_Texture = *GameManager::GetInstance()->m_DataManager->m_TextureMap[DataManager::REDBULLET];
        m_TextureAnim = *GameManager::GetInstance()->m_DataManager->m_TextureMap[DataManager::REDHITANIMATION];
    }

    m_Sprite.setTexture(m_Texture);
    m_Sprite.setOrigin((float)m_Texture.getSize().x / 2.f, (float)m_Texture.getSize().y / 2.f);
    m_Sprite.setPosition(Origine->m_CooX, Origine->m_CooY);
    
    m_HitBox = new sf::CircleShape(); 
    m_HitBox->setRadius(5.f); 

    float hitboxX = m_Sprite.getPosition().x;
    float hitboxY = m_Sprite.getPosition().y - (m_Texture.getSize().y / 2.f) - m_HitBox->getRadius();

    m_HitBox->setPosition(hitboxX, hitboxY);

    m_DirectionBullet = DirectionBullet;
    m_Sprite.setRotation(AngleRotation);
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_Sprite, states);
}

void Bullet::Movint(sf::Time deltaTime,Module* Originemodule)
{
        m_Sprite.move(m_DirectionBullet.x * (float)deltaTime.asMilliseconds(), -(m_DirectionBullet.y) * (float)deltaTime.asMilliseconds());
}

void Bullet::CollitionUpdate(sf::Time deltaTime)
{
    m_HitBox->setPosition(m_Sprite.getPosition().x, m_Sprite.getPosition().y - (m_Texture.getSize().y / 2.f) - m_HitBox->getRadius());

    if (m_Sprite.getPosition().y < 0 || m_Sprite.getPosition().y > 1080)
    {
        GameManager::GetInstance()->m_SceneManagerInstance->GetCurrentScene()->RemoveEntity(this);
        return;
    }

    std::vector<Entity*> m_EntityList = GameManager::GetInstance()->m_SceneManagerInstance->m_CurrentScene->m_EntityList;
    for (int i = m_EntityList.size() - 1; i >= 0; --i)
    {
        if (m_EntityList[i] != nullptr && Hit(m_EntityList[i]->m_HitBox, m_HitBox) && m_EntityList[i]->m_Faction != m_Faction)
        {
            if (Alive* aliveEntity = dynamic_cast<Alive*>(m_EntityList[i]))
            {
                attack(aliveEntity);
                m_IsExploding = true;  
                return;                
            }
        }
    }
}

void Bullet::Update(sf::Time deltaTime, const sf::RenderWindow& window)
{
    if (m_IsExploding)
    {
        AnimationExplode(deltaTime);
        return;
    }
    else
    {
        Movint(deltaTime, Originemodule);
        CollitionUpdate(deltaTime);
    }
}

void Bullet::attack(Alive* ennemie)
{
    int TotalDamage = this->Originemodule->m_preModule->m_PistolDamage;
    while (TotalDamage > 0)
    {
        if (ennemie->m_Shield > 0)
        {
            ennemie->m_Shield--;
            TotalDamage--;
        }
        else
        {
            ennemie->SubtractHealth(TotalDamage);
            TotalDamage = 0;
        }
    }
}

void Bullet::AnimationExplode(sf::Time deltaTime)
{
    static float timer = 0.0f;
    const float frameTime = 0.05f;
    const int totalFrames = 4;

    timer += deltaTime.asSeconds();
    
    if (timer >= frameTime)
    {
        m_AnimationFrame++;
        timer = 0.0f;

        if (m_AnimationFrame >= totalFrames)
        {

            
            GameManager::GetInstance()->m_SceneManagerInstance->GetCurrentScene()->RemoveEntity(this);

            return;
        }
        if (m_AnimationFrame >= 0 && m_AnimationFrame <=1 && Originemodule->m_Faction == GameManager::Faction::Gentil)
        {
            GameManager::GetInstance()->m_AudioManagerInstance->ChangeSound("hitmarker.mp3");
            GameManager::GetInstance()->m_AudioManagerInstance->PlaySound();
        }
        if (m_AnimationFrame >= 0 && m_AnimationFrame <= 1 && Originemodule->m_Faction == GameManager::Faction::Mechant)
        {
            GameManager::GetInstance()->m_AudioManagerInstance->ChangeSound("Ough.mp3");
            GameManager::GetInstance()->m_AudioManagerInstance->PlaySound();
        }


        int frameWidth = m_TextureAnim.getSize().x / totalFrames;
        int frameHeight = m_TextureAnim.getSize().y;

        sf::IntRect textureRect(
            m_AnimationFrame * frameWidth,
            0,
            frameWidth,
            frameHeight
        );

        m_Sprite.setTexture(m_TextureAnim);
        m_Sprite.setTextureRect(textureRect);
    }
}

Bullet::~Bullet()
{
    if (m_HitBox != nullptr)
    {
        delete m_HitBox;
        m_HitBox = nullptr;
    }
}