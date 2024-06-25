#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../server_src/headers/jazz.h"
#include "../server_src/headers/mapa.h"
#include "../server_src/headers/lista_objetos.h"
#include "../server_src/GamesManager.cpp"
#include "../common_src/headers/queue.h"
#include "../common_src/headers/Container.h"
#include "../server_src/headers/ghost.h"
#include "../server_src/headers/bullet.h"
#include "../server_src/headers/zanahoria.h"
#include "../server_src/headers/zanahoria_envenenada.h"

#include <string>
#include <map>
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <memory>


TEST(personaje, moverse_en_ambas_direcciones)
{
    Queue<Container> q;
    std::map<std::string, float> config = load_config_YAML("../config.yml");
    Jazz jazz = Jazz(0, 0, config, q, "jazz");
    float pos = jazz.x;

    jazz.moveRigth();
    jazz.update_position();

    ASSERT_EQ(pos + jazz.velx, jazz.x);

    pos = jazz.x;
    jazz.stopMovingRight();
    jazz.moveLeft();
    jazz.update_position();

    ASSERT_EQ(pos - jazz.velx, jazz.x);
}


TEST(personaje, recibe_danio_de_un_enemigo)
{
    Queue<Container> q;
    std::map<std::string, float> config = load_config_YAML("../config.yml");
    Jazz jazz = Jazz(0, 0, config, q, "jazz");
    jazz.espera_hurt = -1;
    int vida = jazz.vida;
    Ghost ghost = Ghost(0, 0, config);
    
    jazz.colision(ghost);

    ASSERT_EQ(vida - ghost.get_damage(), jazz.vida);
}

TEST(personaje, con_accion_especial_activa_hace_danio_al_enemigo)
{
    Queue<Container> q;
    std::map<std::string, float> config = load_config_YAML("../config.yml");
    Jazz jazz = Jazz(0, 0, config, q, "jazz");
    jazz.espera_hurt = -1;
    jazz.special_action();
    Ghost ghost = Ghost(0, 0, config);
    int vida = ghost.vida;

    jazz.colision(ghost);

    ASSERT_EQ(vida - jazz.danio_ataque_especial, ghost.vida);
}

TEST(personaje, recibe_danio_de_una_bala)
{
    Queue<Container> q;
    std::map<std::string, float> config = load_config_YAML("../config.yml");
    Jazz jazz = Jazz(0, 0, config, q, "jazz");
    jazz.espera_hurt = -1;
    int vida = jazz.vida;
    Bullet bullet = Bullet(0, 0, 1, 1, config);

    jazz.colision(bullet);

    ASSERT_EQ(vida - bullet.danio, jazz.vida);
    ASSERT_EQ(PlayerState::HURTED, jazz.get_state());
}

TEST(personaje, personaje_revive_despues_de_3_segundos)
{
    std::map<uint32_t, std::shared_ptr<Personaje>> m;
    ListaObjetos lista;
    Queue<Container> q;
    std::map<std::string, float> config = load_config_YAML("../config.yml");
    std::shared_ptr<Jazz> jazz(new Jazz(0, 0, config, q, "jazz"));
    jazz->vida = 0;

    jazz->update_vivo(lista, q, m, jazz);
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    jazz->update_vivo(lista, q, m, jazz);

    ASSERT_EQ(100, jazz->vida);
}

TEST(personaje, si_persoanje_come_una_zanahoria_le_aumenta_la_vida)
{
    Queue<Container> q;
    std::map<std::string, float> config = load_config_YAML("../config.yml");
    Jazz jazz = Jazz(0, 0, config, q, "jazz");
    jazz.vida = 1;
    Zanahoria zanahoria = Zanahoria(0, 0, config, q);

    jazz.colision(zanahoria);

    ASSERT_EQ(1 + zanahoria.life, jazz.vida);
}

TEST(personaje, si_personaje_come_una_zanahoria_envenenada_queda_en_estado_intoxicado)
{
    Queue<Container> q;
    std::map<std::string, float> config = load_config_YAML("../config.yml");
    Jazz jazz = Jazz(0, 0, config, q, "jazz");
    jazz.vida = 1;
    ZanahoriaEnvenenada zanahoriaEnvenenada = ZanahoriaEnvenenada(0, 0, config, q);

    jazz.colision(zanahoriaEnvenenada);

    ASSERT_EQ(PlayerState::INTOXICATED, jazz.get_state());
}
