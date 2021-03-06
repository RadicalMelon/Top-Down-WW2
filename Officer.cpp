#include "Officer.h"

Officer::Officer(const SDL_Rect& tile_rect) : Enemy(tile_rect, Application::getTexture("Resources/Images/Officer.png"), Application::getTexture("Resources/Images/DeadOfficer.png"), 100, 150)
{
    weapon = Weapon::Rifle;
}

void Officer::update(Level& level, Player& player, std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<Projectile>& enemy_projectiles)
{
    Enemy::update(level, player, enemies, enemy_projectiles);

    if (alerted)
    {
        attack_timer += Application::getDeltaTime();
        if (attack_timer >= WEAPON_DELAYS.at(weapon))
        {
            attack_timer = 0.0;
            if (facing_player)
            {
                if (!Tools::randomInt(0, ATTACK_CHANCE))
                {
                    SDL_Point centre = { rect.x + (rect.w / 2), rect.y + (rect.h / 2) };

                    Mix_PlayChannel(-1, Application::getSound(GUN_SOUNDS.at(weapon)), 0);
                    enemy_projectiles.emplace_back(weapon, centre, angle);
                }
            }
        }
    }
}
