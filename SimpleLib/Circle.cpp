#include <stdlib.h>
#include "armrulelib.h"

struct Ponto {
	double x;
	double y;
	double z;
	double phi;
};

void mover_suave(Ponto source, Ponto dest);
void init_pontos(Ponto pontos[6]);

int main(int argc, char** argv) {
	if (argc < 7) {
		printf("Quantidade de argumentos insuficiente: %d", argc);
		exit(1);
	}

	Ponto p_preto;
	p_preto.x = 29.327;
	p_preto.y = 1.024;
	p_preto.z = -0.994;
	p_preto.phi = -90;

	Ponto pontos[6];
	init_pontos(pontos);

	// Mover para caneta
	mover(p_preto.x, p_preto.y, p_preto.z, p_preto.phi);
	// Pegar caneta
	pega();

	Ponto p_ant = p_preto;
	
	// Mover entre cada ponto
	for (int i = 0; i < 6; i++) {
		Ponto p = pontos[atoi(argv[i+1]);
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
	pontos[0].x = 22.711;	pontos[0].y = -2.387;	pontos[0].z = -2.648;	pontos[0].phi = -96;
	pontos[1].x = 14.503;	pontos[1].y = -4.434;	pontos[1].z = -3.467;	pontos[1].phi = -102;
	pontos[2].x = 7.327;	pontos[2].y = -1.691;	pontos[2].z = -3.920;	pontos[2].phi = -110;
	pontos[3].x = 7.327;	pontos[3].y = -1.691;	pontos[3].z = -3.920;	pontos[3].phi = -110;
	pontos[4].x = 14.503;	pontos[4].y = -4.434;	pontos[4].z = -3.467;	pontos[4].phi = -102;
	pontos[5].x = 22.711;	pontos[5].y = -2.387;	pontos[5].z = -2.648;	pontos[5].phi = -96;
}
