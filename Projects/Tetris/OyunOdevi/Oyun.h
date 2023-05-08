#pragma once
#include "temeller.h"

class Oyun
{
public:
	Oyun();
	void guncel();
private:
    sf::RenderWindow window;
    sf::Texture kaplama1, kaplama2, kaplama3;
    sf::Sprite kare, arkaplan, cevre;
    sf::Clock clock;
    sf::Event e;
    int yon = 0, renk, score = 0;
    float timer = 0, gecikme = 0.5;
    bool cevir = false, bittiMi = false, scoreGuncelleme = false;

    int Sekiller[7][4] =
    {
        1,3,5,7, // I
        2,4,5,7, // Z
        3,5,4,6, // S
        3,5,4,7, // T
        2,3,5,7, // L
        3,5,7,6, // J
        2,3,4,5, // O
    };

    bool check();
    void resimleriAl();
    void ilkParcaOlustur();
    void olaylarKontrolEt();
    void hareketEttir();
    void cevirle();
    void yeniParcaOlustur();
    void satirlarKontrolEt();
    void scoreGuncelle();
    void ciz();
    void bitisKontrolu();

};

