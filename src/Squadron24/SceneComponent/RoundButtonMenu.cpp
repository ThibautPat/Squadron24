#include "RoundButtonMenu.h"
#include "../ManagerGroup/GameManager.h"

RoundButtonMenu::RoundButtonMenu(float x, float y, float width, float height, const std::string& textureFile, int link) :RoundButton(x, y, width, height, textureFile)
{
    m_link = link;
    std::string Score = "Score :";
    std::string money = "UI/Money";

    score = new TextBox(Score, money, x-125 , y+150, 0.75, 0.75, 34, link);
    Rank = new sf::Sprite;

    if (!RankText.loadFromFile("../../../res/UI/rank0.png"))
    {
        exit(1);
    }

    Rank->setTexture(RankText);

    Rank->setPosition(x-65 , y-75  );

    Rank->setScale(2, 2);
}

void RoundButtonMenu::Update(sf::Time deltaTime, const sf::RenderWindow& window)
{
    score->Update(deltaTime, window);

    if (GameManager::GetInstance()->m_PlayerInstance->m_LevelsScore[m_link] >= 10000)
    {
        if (!RankText.loadFromFile("../../../res/UI/rank1.png"))
        {
            exit(1);
        }
        Rank->setTexture(RankText);
    }

    if (GameManager::GetInstance()->m_PlayerInstance->m_LevelsScore[m_link] >= 20000)
    {
        if (!RankText.loadFromFile("../../../res/UI/rank2.png"))
        {
            exit(1);
        }
        Rank->setTexture(RankText);

    }

    if (GameManager::GetInstance()->m_PlayerInstance->m_LevelsScore[m_link] >= 40000)
    {
        if (!RankText.loadFromFile("../../../res/UI/rank3.png"))
        {
            exit(1);
        }
        Rank->setTexture(RankText);

    }    sf::Mouse mouse;
    
    if (isHover(mouse.getPosition(window), window)&& GameManager::GetInstance()->m_PlayerInstance->m_LevelUnlock[m_link]==1) {
        m_hover = 1;
        m_buttonShape.setOutlineColor(sf::Color::Yellow);
        m_buttonShape.setOutlineThickness(20);
        if (mouse.isButtonPressed(sf::Mouse::Button::Left))
        {
            GameManager::GetInstance()->m_GameState = m_link;
        }
    }
    else if (isHover(mouse.getPosition(window), window) && GameManager::GetInstance()->m_PlayerInstance->m_LevelUnlock[m_link] == 0)
    {
        m_Sprite.setColor(sf::Color::Red);
        m_buttonShape.setOutlineColor(sf::Color::Red);

    }
    else {
        m_hover = 0;

        m_Sprite.setColor(sf::Color::White);

        m_buttonShape.setOutlineColor(sf::Color::Transparent);
    }
}

void RoundButtonMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Mouse mouse;

    states.transform *= getTransform();
    target.draw(m_Sprite, states);

    target.draw(m_buttonShape, states);
    if (m_hover == 1) 
    {
        score->draw(target, states);
        target.draw(*Rank, states);
    }
}
