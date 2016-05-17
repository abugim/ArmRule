#include <stdlib.h>
#include "armrulelib_novo.h"

struct Ponto {
	double x;
	double y;
	double z;
	double phi;
};

void mover_suave(Ponto source, Ponto dest);
void init_pontos(Ponto pontos[6]);

int main(int argc, char** argv) {
	init();
	if (argc < 7) {
		printf("Quantidade de argumentos insuficiente: %d", argc);
		exit(1);
	}

	Ponto p_preto;
	p_preto.x = 38;
	p_preto.y = 2;
	p_preto.z = 16;
	p_preto.phi = 0;

	Ponto pontos[6];
	init_pontos(pontos);

	// Mover para caneta
	mover(p_preto.x, p_preto.y, p_preto.z, p_preto.phi);
	// Pegar caneta
	pegar();

	Ponto p_ant = p_preto;

	// Mover entre cada ponto
	for (int i = 0; i < 6; i++) {
		Ponto p = pontos[atoi(argv[i+1])];
		mover_suave(p_ant, p);
		p_ant = p;
	}

	// Mover para preto
	mover_suave(p_ant, p_preto);
}

void mover_suave(Ponto source, Ponto dest) {
	Ponto p;
	p.x = (dest.x - source.x) / 10.0;
	p.y = (dest.y - source.y) / 10.0;
	p.z = (dest.z - source.z) / 10.0;
	p.phi = (dest.phi - source.phi) / 10.0;

	for (int i = 0; i < 10; i++) {
		mover(source.x + p.x * (i+1), source.y + p.y * (i+1), source.z + p.z * (i+1), source.phi + p.phi * (i+1));
	}
}

void init_pontos(Ponto pontos[6]) {
	pontos[0].x = 33;	pontos[0].y = -2;	pontos[0].z = 16;	pontos[0].phi = 0;
	pontos[1].x = 27.5;	pontos[1].y = -5;	pontos[1].z = 13;	pontos[1].phi = 0;
	pontos[2].x = 21;	pontos[2].y = -2;	pontos[2].z = 12;	pontos[2].phi = 0;
	pontos[3].x = 21;	pontos[3].y = 3.5;	pontos[3].z = 12;	pontos[3].phi = 0;
	pontos[4].x = 27;	pontos[4].y = 7;	pontos[4].z = 13.5;	pontos[4].phi = 0;
	pontos[5].x = 33;	pontos[5].y = 5;	pontos[5].z = 16;	pontos[5].phi = 0;
}
