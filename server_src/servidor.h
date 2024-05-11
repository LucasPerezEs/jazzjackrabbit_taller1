
#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <list>
#include "partida.h"
#include "jugador.h"
#include "../common_src/socket.h"
#include "../common_src/thread.h"

class Servidor: public Thread {
private:
	std::list<Jugador> jugadores;
	bool& server_closed;
	unsigned int id_jugadores;
	Partida partida;

public:
	
	Servidor(bool& juego_finalizado);

	void add_player(Socket&& peer);

	void run() override;

	Servidor(const Servidor&) = delete;
    Servidor& operator=(const Servidor&) = delete;
};

#endif
