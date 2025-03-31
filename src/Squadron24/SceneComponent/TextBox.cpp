#include "TextBox.h"
#include "../ManagerGroup/GameManager.h"
#include <sstream>
#include <iostream>

TextBox::TextBox(std::string text, std::string texture, float X, float Y, float ScaleX, float ScaleY, unsigned int police,int id) {
    if (!m_Font.loadFromFile("../../../res/FONT/Menu.ttf"))
    {
        exit(1);
    }

    m_Text.setFont(m_Font);
    m_Text.setCharacterSize(police);
    m_police = police;
    m_Text.setFillColor(sf::Color::Black);
    m_id = id;
    if (!m_Texture.loadFromFile("../../../res/"+texture+".png"))
    {
        exit(1);
    }

    m_Sprite.setTexture(m_Texture);
    m_Sprite.setPosition(X, Y);
    m_Sprite.setScale(ScaleX, ScaleY);

    sf::FloatRect spriteBounds = m_Sprite.getGlobalBounds();
    float boxWidth = spriteBounds.width;

    splitTextIntoLines(text, boxWidth, police);

    m_Text.setPosition(spriteBounds.left, spriteBounds.top);
}

void TextBox::SetText(std::string& text)
{
    sf::FloatRect spriteBounds = m_Sprite.getGlobalBounds();

    float boxWidth = spriteBounds.width;

    splitTextIntoLines(text, boxWidth, m_police);

}

void TextBox::splitTextIntoLines(const std::string& text, float boxWidth, unsigned int charSize)
{
    m_Lines.clear();  

    std::string currentLine;
    std::istringstream ss(text);
    std::string word;

    while (ss >> word)
    {
        std::string tempLine = currentLine.empty() ? word : currentLine + " " + word;

        m_Text.setString(tempLine);

        if (m_Text.getLocalBounds().width > boxWidth)
        {
            if (!currentLine.empty())
            {
                m_Lines.push_back(currentLine);
            }
            currentLine = word;
        }
        else
        {
            currentLine = tempLine;
        }
    }

    if (!currentLine.empty())
    {
        m_Lines.push_back(currentLine);
    }
}

void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_Sprite, states);

    float currentY = m_Sprite.getPosition().y;

    float lineSpacing = 5.0f;

    for (size_t i = 0; i < m_Lines.size(); ++i)
    {
        sf::Text tempText = m_Text; 
        tempText.setString(m_Lines[i]);  

        sf::FloatRect textBounds = tempText.getLocalBounds();
        float centerX = m_Sprite.getPosition().x + (m_Sprite.getGlobalBounds().width - textBounds.width) / 2;

        tempText.setPosition(centerX, currentY+10);

        target.draw(tempText, states);

        currentY += m_Text.getCharacterSize() + lineSpacing; 
    }
}

void TextBox::Update(sf::Time deltaTime, const sf::RenderWindow& window)
{
    if (m_id == 1)
    {
        float time = (GameManager::GetInstance()->m_SceneManagerInstance->GetCurrentScene()->m_clock->getElapsedTime().asSeconds() / 240) * 100;
        std::string PourcentageLvl = std::to_string(time);
        size_t dot_pos = PourcentageLvl.find('.');
        if (dot_pos != std::string::npos) {
            PourcentageLvl = PourcentageLvl.substr(0, dot_pos + 2); 
        }
        PourcentageLvl += " %";
        m_Sprite.setColor(sf::Color::Transparent);
        SetText(PourcentageLvl);
    }
    if (m_id == 2)
    {
        std::string Score = std::to_string((int)GameManager::GetInstance()->m_SceneManagerInstance->GetCurrentScene()->m_Score);

        Score += " Pt";
        m_Sprite.setColor(sf::Color::Transparent);
        SetText(Score);
    }
    if (m_id == 3)
    {
        std::string ScoreMultiplicator = "x" + std::to_string(GameManager::GetInstance()->m_SceneManagerInstance->GetCurrentScene()->m_ScoreMultiplicatorCombine);
        size_t dot_pos = ScoreMultiplicator.find('.');
        if (dot_pos != std::string::npos) {
            ScoreMultiplicator = ScoreMultiplicator.substr(0, dot_pos + 2); 
        }
        m_Sprite.setColor(sf::Color::Transparent);
        SetText(ScoreMultiplicator);
    }
    if (m_id == 4)
    {
        std::string winScore = "Score : " + std::to_string((int)GameManager::GetInstance()->m_SceneManagerInstance->GetCurrentScene()->m_Score);

        m_Sprite.setColor(sf::Color::Transparent);
        SetText(winScore);
    }
    if (m_id == 5)
    {
        std::string winScore = "$ " + std::to_string((int)GameManager::GetInstance()->m_PlayerInstance->m_Money);
        m_Sprite.setColor(sf::Color::Transparent);
        SetText(winScore);
    }
    if (m_id >=8)
    {
        if(GameManager::GetInstance()->m_PlayerInstance->m_LevelUnlock[m_id]==1)
        {
            std::string winScore = "Score : " + std::to_string((int)GameManager::GetInstance()->m_PlayerInstance->m_LevelsScore[m_id]);
            SetText(winScore);
        }
    }
}
