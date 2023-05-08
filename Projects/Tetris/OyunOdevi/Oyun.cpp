#include "Oyun.h"

struct Point
{
	int x, y;
} parca[4], yedekParca[4];

int ekran[satir][sutun] = { 0 };

Oyun::Oyun()
{
	window.create(sf::VideoMode(ekrenGenisligi, ekranBoyu), oyunIsmi);
	srand(time(0));
	resimleriAl();
	ilkParcaOlustur();
}

void Oyun::guncel()
{
	while (window.isOpen())
	{
		float zaman = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += zaman;
		olaylarKontrolEt();
		hareketEttir();
		yeniParcaOlustur();
		satirlarKontrolEt();
		scoreGuncelle();
		ciz();
		bitisKontrolu();

		yon = 0; cevir = false; gecikme = 0.5;
	}
}

bool Oyun::check()
{
	for (int i = 0; i < 4; i++)
		if (parca[i].x < 0 || parca[i].x >= sutun || parca[i].y >= satir) return 0; // ekran etraflari
		else if (ekran[parca[i].y][parca[i].x]) return 0; // var olan parcalar

	return 1;
};

void Oyun::resimleriAl() {
	kaplama1.loadFromFile("resimler/tiles.png");
	kaplama2.loadFromFile("resimler/background.png");
	kaplama3.loadFromFile("resimler/frame.png");
	kare.setTexture(kaplama1);
	arkaplan.setTexture(kaplama2);
	cevre.setTexture(kaplama3);
	cevre.setScale(sf::Vector2f(2, 2));
	arkaplan.setScale(sf::Vector2f(2, 2));
}

void Oyun::ilkParcaOlustur() {
	renk = 1 + rand() % 7;
	
	for (int i = 0; i < 4; i++)
	{
		parca[i].x = Sekiller[renk-1][i] % 2 + sutun / 2 ;
		parca[i].y = Sekiller[renk-1][i] / 2 ;
	}
}

void Oyun::olaylarKontrolEt()
{
	while (window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			window.close();

		if (e.type == sf::Event::KeyPressed)
			if (e.key.code == sf::Keyboard::Up) cevir = true;
			else if (e.key.code == sf::Keyboard::Left) yon = -1;
			else if (e.key.code == sf::Keyboard::Right) yon = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) gecikme = 0.1;
	cevirle();
}

void Oyun::hareketEttir()
{
	for (int i = 0; i < 4; i++) { yedekParca[i] = parca[i]; parca[i].x += yon; }
	if (!check()) for (int i = 0; i < 4; i++) parca[i] = yedekParca[i];
}

void Oyun::cevirle()
{
	if (cevir)
	{
		Point merkez = parca[1]; //center of rotation
		for (int i = 0; i < 4; i++)
		{ 
			int x = parca[i].y - merkez.y;
			int y = parca[i].x - merkez.x;
			parca[i].x = merkez.x - x;
			parca[i].y = merkez.y + y;
		}
		if (!check()) for (int i = 0; i < 4; i++) parca[i] = yedekParca[i];
	}
}

void Oyun::yeniParcaOlustur()
{
	if (timer > gecikme)
	{
		for (int i = 0; i < 4; i++) { yedekParca[i] = parca[i]; parca[i].y += 1; }
		if (!check())
		{
			for (int i = 0; i < 4; i++) ekran[yedekParca[i].y][yedekParca[i].x] = renk;

			renk = 1 + rand() % 7;
			for (int i = 0; i < 4; i++)
			{
				parca[i].x = Sekiller[renk-1][i] % 2 + sutun / 2;
				parca[i].y = Sekiller[renk-1][i] / 2 ;
			}
		}
		timer = 0;
	}
}

void Oyun::satirlarKontrolEt()
{
	int k = satir - 1;
	for (int i = satir - 1; i > 0; i--)
	{
		int count = 0;
		for (int j = 0; j < sutun; j++)
		{
			if (ekran[i][j]) count++;
			ekran[k][j] = ekran[i][j];
		}
		if (count < sutun) {
			k--;
		}
		else {
			score = score + 8;
			scoreGuncelleme = true;
		}
	}
}

void Oyun::scoreGuncelle()
{
	if (scoreGuncelleme) {
		std::cout << " YOUR SCORE :" << score << std::endl;
		scoreGuncelleme = false;
	}
}

void Oyun::ciz()
{
	window.clear(sf::Color::White);
	window.draw(arkaplan);
	window.draw(cevre);

	for (int i = 0; i < satir; i++) {
		for (int j = 0; j < sutun; j++)
		{
			if (ekran[i][j] == 0) continue;
			kare.setTextureRect(sf::IntRect(ekran[i][j] * 18, 0, 18, 18));
			kare.setScale(sf::Vector2f(2, 2));
			kare.setPosition(j * 18 * 2, i * 18 * 2);
			kare.move(56, 62);
			window.draw(kare);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		kare.setTextureRect(sf::IntRect(renk * 18, 0, 18, 18));
		kare.setScale(sf::Vector2f(2, 2));
		kare.setPosition(parca[i].x * 18 * 2, parca[i].y * 18 * 2);
		kare.move(56, 62);
		window.draw(kare);
	}

	window.display();
}

void Oyun::bitisKontrolu()
{
	for (int i = 0; i < sutun; i++)
	{
		if (ekran[1][i] != 0 && !bittiMi)
		{
			std::cout << std::endl << std::endl << std::endl << "         OYUN  BITTI     ";
			std::cout << "         KAYBETTINIZ     " << std::endl << std::endl;
			bittiMi = true;
			window.close();
		}
	}
}


