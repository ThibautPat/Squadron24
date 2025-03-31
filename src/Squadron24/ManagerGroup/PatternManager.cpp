#include "PatternManager.h"
#include "GameManager.h"

PatternManager::PatternManager()
{
    std::map<int, std::map<int, sf::Vector2f>> ListeDesDifférenteListe;

    std::map<int, sf::Vector2f> MapGaucheHautDroiteBas;

    MapGaucheHautDroiteBas[0] = sf::Vector2f(0.f, 100.f);
    MapGaucheHautDroiteBas[1] = sf::Vector2f(660.f, 100.f);
    MapGaucheHautDroiteBas[2] = sf::Vector2f(1920.f, 100.f);
    MapGaucheHautDroiteBas[3] = sf::Vector2f(0.f, 600.f);
    MapGaucheHautDroiteBas[4] = sf::Vector2f(1320.f, 600.f);
    MapGaucheHautDroiteBas[5] = sf::Vector2f(1920.f, 600.f);
    ListeDesDifférenteListe[0] = MapGaucheHautDroiteBas;

    std::map<int, sf::Vector2f> MapDroiteHautGaucheBas;

    MapDroiteHautGaucheBas[0] = sf::Vector2f(1920.f - 0.f, 100.f);
    MapDroiteHautGaucheBas[1] = sf::Vector2f(1920.f - 660.f, 100.f);
    MapDroiteHautGaucheBas[2] = sf::Vector2f(1920.f - 1920.f, 100.f);
    MapDroiteHautGaucheBas[3] = sf::Vector2f(1920.f - 0.f, 600.f);
    MapDroiteHautGaucheBas[4] = sf::Vector2f(1920.f - 1320.f, 600.f);
    MapDroiteHautGaucheBas[5] = sf::Vector2f(1920.f - 1920.f, 600.f);
    ListeDesDifférenteListe[1] = MapDroiteHautGaucheBas;

    std::map<int, sf::Vector2f> PiqueHaut;

    PiqueHaut[0] = sf::Vector2f(0.f, 600.f);
    PiqueHaut[1] = sf::Vector2f(1920.f, 0.f);
    PiqueHaut[2] = sf::Vector2f(0.f, 0.f);
    PiqueHaut[3] = sf::Vector2f(1920.f, 600.f);
    ListeDesDifférenteListe[2] = PiqueHaut;

    std::map<int, sf::Vector2f> PiqueBas;

    PiqueBas[0] = sf::Vector2f(0.f, 100.f);
    PiqueBas[1] = sf::Vector2f(1920.f, 600.f);
    PiqueBas[2] = sf::Vector2f(0.f, 600.f);
    PiqueBas[3] = sf::Vector2f(1920.f, 100.f);
    ListeDesDifférenteListe[3] = PiqueBas;

    std::map<int, sf::Vector2f> HautGauche;

    HautGauche[0] = sf::Vector2f(640.f, 0.f);
    HautGauche[1] = sf::Vector2f(0.f, 300.f);
    HautGauche[2] = sf::Vector2f(640.f, 600.f);
    HautGauche[3] = sf::Vector2f(0.f, 600.f);
    ListeDesDifférenteListe[4] = HautGauche;

    std::map<int, sf::Vector2f> HautDroite;

    HautDroite[0] = sf::Vector2f(1280.f, 0.f);
    HautDroite[1] = sf::Vector2f(1920.f, 300.f);
    HautDroite[2] = sf::Vector2f(1280.f, 600.f);
    HautDroite[3] = sf::Vector2f(1920.f, 600.f);
    ListeDesDifférenteListe[5] = HautDroite;

    for (int i = 0; i <= 6; i++)
    {
        std::map<int, sf::Vector2f> Temp;

        PatternManager::CurveBezier(ListeDesDifférenteListe[i], Temp);

        ListPath[i] = Temp;
    }
}

void PatternManager::DrawPatternPath(const std::map<int, sf::Vector2f>& patternPath, sf::RenderWindow& window)
{
        sf::VertexArray curve(sf::LinesStrip, patternPath.size());
        int index = 0;
        for (const auto& pair : patternPath)
        {
            curve[index].position = pair.second;
            curve[index].color = sf::Color::Red;
            index++;
        }
        window.draw(curve);
}

bool PatternManager::ValidatePointList(const std::map<int, sf::Vector2f>& PointList)
{
    if (PointList.size() < 2) {
        return false;
    }
    return true;
}

void PatternManager::CurveBezier(const std::map<int, sf::Vector2f>& PointList, std::map<int, sf::Vector2f>& Link)
{
    if (!ValidatePointList(PointList)) {
        return;
    }

    int Taille = PointList.size();
    std::vector<sf::Vector2f> points;

    for (const auto& point : PointList)
    {
        points.push_back(point.second);
    }

    int index = 0;
    for (float t = 0; t <= 1; t += 0.001f)
    {
        std::vector<sf::Vector2f> tempPoints = points;

        for (int level = 1; level < Taille; ++level)
        {
            for (int i = 0; i < Taille - level; ++i)
            {
                tempPoints[i].x = std::lerp(tempPoints[i].x, tempPoints[i + 1].x, t);
                tempPoints[i].y = std::lerp(tempPoints[i].y, tempPoints[i + 1].y, t);
            }
        }

        sf::Vector2f C = tempPoints[0];
        Link[index] = C;
        index++;
    }
}

void PatternManager::InitPattern(int Link, float TimeScreen, int Type)
{
    if (Link > 6) 
    {
        return;
    }
    switch (Type)
    {
    case (0):
    {
        SpaceShip* VaisseauxEnnemie = new SpaceShip(0, GameManager::Faction::Mechant, 0);

        Module* EnnemieModule1 = new Module(0.f, 40.f, 10, 10, GameManager::Faction::Mechant, 0);
        EnnemieModule1->m_Sprite.setRotation(-180);
        VaisseauxEnnemie->SetModule(0, EnnemieModule1);

        Ennemis* Ennemie = new Ennemis(5, TimeScreen, GameManager::GetInstance()->m_PatternManager->ListPath[Link]);
        Ennemie->SetCurrentSpaceShip(VaisseauxEnnemie);
        GameManager::GetInstance()->m_SceneManagerInstance->GetCurrentScene()->AddEntity(Ennemie);
        break;
    }
    case (1):
    {
        SpaceShip* VaisseauxEnnemie = new SpaceShip(0, GameManager::Faction::Mechant, 1);

        Module* EnnemieModule1 = new Module(0.f, 0.f, 10, 10, GameManager::Faction::Mechant, 2);
        EnnemieModule1->m_Sprite.setRotation(-180);
        VaisseauxEnnemie->SetModule(0, EnnemieModule1);

        Ennemis* Ennemie = new Ennemis(8, TimeScreen, GameManager::GetInstance()->m_PatternManager->ListPath[Link]);
        Ennemie->SetCurrentSpaceShip(VaisseauxEnnemie);
        GameManager::GetInstance()->m_SceneManagerInstance->GetCurrentScene()->AddEntity(Ennemie);
        break;
    }
    case (2):
    {
        SpaceShip* VaisseauxEnnemie = new SpaceShip(1, GameManager::Faction::Mechant, 0);

        Module* EnnemieModule1 = new Module(-20.f, 30.f, 10, 10, GameManager::Faction::Mechant, 0); 
        EnnemieModule1->m_Sprite.setRotation(-180); 
        VaisseauxEnnemie->SetModule(0, EnnemieModule1); 

        Module* EnnemieModule2 = new Module(20.f, 30.f, 10, 10, GameManager::Faction::Mechant, 0);
        EnnemieModule2->m_Sprite.setRotation(-180);
        VaisseauxEnnemie->SetModule(1, EnnemieModule2);

        Ennemis* Ennemie = new Ennemis(10, TimeScreen, GameManager::GetInstance()->m_PatternManager->ListPath[Link]); 
        Ennemie->SetCurrentSpaceShip(VaisseauxEnnemie); 
        GameManager::GetInstance()->m_SceneManagerInstance->GetCurrentScene()->AddEntity(Ennemie); 
        break;
    }
    default:
        break;
    }
}
