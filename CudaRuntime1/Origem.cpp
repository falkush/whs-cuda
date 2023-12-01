#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include "windows.h" 




void cudathingy(uint8_t* pixels, bool flipg, double dc, double uhpy, double pos0, double pos1, double pos2, double vec0, double vec1, double vec2, double addy0, double addy1, double addy2, double addz0, double addz1, double addz2, double bhsize, double whsize);
void cudaInit();
void cudaExit();

int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    //ShowWindow(GetConsoleWindow(), SW_SHOW);
	double whsize = M_PI;
	double bhsize = 2 * M_PI;
	double roomsize = 10;
	double schecker = 1;
	double dist = 1;
	double sqsz = 0.01 / 4;
	double speed = 0.01;

	double vecperp0, vecperp1, vecperp2;
	double vecperpn;


    int mousx, mousy, centralx, centraly;

    double dc, uhpy;

    double pos0=0, pos1=0, pos2=0;
    double vec0, vec1, vec2;
    double addy0, addy1, addy2;
    double addz0, addz1, addz2;
    double x00=1, x01=0, x02=0;
    double x10=0, x11=1, x12=0;
    double x20=0, x21=0, x22=1;
    double multy = (1 - 1280) * sqsz / 2;
    double multz = (720-1) * sqsz / 2;
    double angle;

	bool flipg = false;

    double newx00, newx01, newx02;
    double newx10, newx11, newx12;
    double newx20, newx21, newx22;

	double sxn, syn, szn;
	double dotp, leangle, theta;
	double dist1, ang;
	double lerayon, lex1, lex2, ley2;

	double exitlgt, exitangle, newang;
	double newv0, newv1, newv2;

	double dotp1, dotp2;
	double proj0, proj1, proj2;
	double projn;
	double tmpl, ang1;
	double vectmpx0, vectmpx1, vectmpx2;
	double angx1, dist2, distrem;

    bool focus = true;

    sf::RenderWindow window(sf::VideoMode(1280, 720, 32), "Wormhole Simulator - Press ESC to stop", sf::Style::Titlebar | sf::Style::Close);
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Uint8* pixels = new sf::Uint8[1280 * 720 * 4];
    sf::Vector2i winpos;

    cudaInit();
    texture.create(1280, 720);
    window.setMouseCursorVisible(false);

    pos0 = -5;

    winpos = window.getPosition();
    SetCursorPos(winpos.x + 1280 / 2, winpos.y + 720 / 2);
   
    while (window.isOpen())
    {
        Sleep(1);
        sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (focus && event.type == sf::Event::MouseMoved)
			{
				POINT p;
				GetCursorPos(&p);
				winpos = window.getPosition();
				centralx = winpos.x + 1280 / 2;
				centraly = winpos.y + 720 / 2;
				SetCursorPos(centralx, centraly);

				mousx = p.x - centralx;
				mousy = p.y - centraly;


				angle = 0.001 * sqrt(mousx * mousx + mousy * mousy);

				if (mousx > 0)
				{
					newx00 = x00 * cos(angle) + sin(angle) * x10;
					newx10 = x10 * cos(angle) - sin(angle) * x00;
					x00 = newx00;
					x10 = newx10;

					newx01 = x01 * cos(angle) + sin(angle) * x11;
					newx11 = x11 * cos(angle) - sin(angle) * x01;
					x01 = newx01;
					x11 = newx11;

					newx02 = x02 * cos(angle) + sin(angle) * x12;
					newx12 = x12 * cos(angle) - sin(angle) * x02;
					x02 = newx02;
					x12 = newx12;
				}
				else if (mousx < 0)
				{
					newx00 = x00 * cos(angle) - sin(angle) * x10;
					newx10 = x10 * cos(angle) + sin(angle) * x00;
					x00 = newx00;
					x10 = newx10;

					newx01 = x01 * cos(angle) - sin(angle) * x11;
					newx11 = x11 * cos(angle) + sin(angle) * x01;
					x01 = newx01;
					x11 = newx11;

					newx02 = x02 * cos(angle) - sin(angle) * x12;
					newx12 = x12 * cos(angle) + sin(angle) * x02;
					x02 = newx02;
					x12 = newx12;
				}

				if (mousy < 0)
				{
					newx00 = x00 * cos(angle) + sin(angle) * x20;
					newx20 = x20 * cos(angle) - sin(angle) * x00;
					x00 = newx00;
					x20 = newx20;

					newx01 = x01 * cos(angle) + sin(angle) * x21;
					newx21 = x21 * cos(angle) - sin(angle) * x01;
					x01 = newx01;
					x21 = newx21;

					newx02 = x02 * cos(angle) + sin(angle) * x22;
					newx22 = x22 * cos(angle) - sin(angle) * x02;
					x02 = newx02;
					x22 = newx22;
				}
				else if (mousy > 0)
				{
					newx00 = x00 * cos(angle) - sin(angle) * x20;
					newx20 = x20 * cos(angle) + sin(angle) * x00;
					x00 = newx00;
					x20 = newx20;

					newx01 = x01 * cos(angle) - sin(angle) * x21;
					newx21 = x21 * cos(angle) + sin(angle) * x01;
					x01 = newx01;
					x21 = newx21;

					newx02 = x02 * cos(angle) - sin(angle) * x22;
					newx22 = x22 * cos(angle) + sin(angle) * x02;
					x02 = newx02;
					x22 = newx22;
				}


			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			x00 = 1; x01 = 0; x02 = 0;
			x10 = 0; x11 = 1; x12 = 0;
			x20 = 0; x21 = 0; x22 = 1;
			pos0 = -5; pos1 = 0; pos2 = 0;
			bhsize = 2 * M_PI;
			whsize = M_PI;
		}

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                focus = false;
                window.setMouseCursorVisible(true);
            }

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                focus = true;
                window.setMouseCursorVisible(false);
            }

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) bhsize += 0.1;
			if (bhsize>0.1 && sf::Keyboard::isKeyPressed(sf::Keyboard::X)) bhsize -= 0.1;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) whsize += 0.1;
			if (whsize > 0.1 && sf::Keyboard::isKeyPressed(sf::Keyboard::V)) whsize -= 0.1;


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
				dc = sqrt(pos0 * pos0 + pos1 * pos1 + pos2 * pos2);
				uhpy = 1 / dc;

				if (dc > 1) {
					 pos0 += x00 * speed;
					 pos1 += x01 * speed;
					 pos2 += x02 * speed;
				}
				else
				{

					sxn = -pos0 / dc;
					syn = -pos1 / dc;
					szn = -pos2 / dc;

					dotp = sxn * x00 + syn * x01 + szn * x02;
					leangle = acos(dotp);

					theta = M_PI / 2 - leangle;

					dist1 = asinh(tan(theta));
					ang = atan(sinh(speed - dist1));

					lerayon = uhpy / sin(M_PI / 2 + theta);

					lex1 = lerayon * cos(M_PI / 2 + theta);

					lex2 = lerayon * cos(M_PI / 2 - ang);
					ley2 = lerayon * sin(M_PI / 2 - ang);

					sxn = -sxn;
					syn = -syn;
					szn = -szn;
					dotp = -dotp;
					leangle = acos(dotp);

					vecperp0 = x00 - dotp * sxn;
					vecperp1 = x01 - dotp * syn;
					vecperp2 = x02 - dotp * szn;

					vecperpn = sqrt(vecperp0 * vecperp0 + vecperp1 * vecperp1 + vecperp2 * vecperp2);
					
					if (vecperpn != 0) {
						vecperp0 /= vecperpn;
						vecperp1 /= vecperpn;
						vecperp2 /= vecperpn;


						if (ley2 < whsize)
						{

							exitlgt = lex2 - lex1;
							exitangle = fmod(exitlgt, bhsize);
							exitangle = (2 * M_PI / bhsize) * exitangle;
							newang = M_PI / 2 + ang;

							pos0 = cos(exitangle) * sxn + sin(exitangle) * vecperp0;
							pos1 = cos(exitangle) * syn + sin(exitangle) * vecperp1;
							pos2 = cos(exitangle) * szn + sin(exitangle) * vecperp2;

							pos0 *= 1 / ley2;
							pos1 *= 1 / ley2;
							pos2 *= 1 / ley2;

							newv0 = cos(M_PI + exitangle - newang) * sxn + sin(M_PI + exitangle - newang) * vecperp0;
							newv1 = cos(M_PI + exitangle - newang) * syn + sin(M_PI + exitangle - newang) * vecperp1;
							newv2 = cos(M_PI + exitangle - newang) * szn + sin(M_PI + exitangle - newang) * vecperp2;



							dotp1 = newv0 * x00 + newv1 * x01 + newv2 * x02;
							dotp2 = newv0 * x10 + newv1 * x11 + newv2 * x12;

							proj0 = x00 * dotp1 + x10 * dotp2;
							proj1 = x01 * dotp1 + x11 * dotp2;
							proj2 = x02 * dotp1 + x12 * dotp2;

							projn = sqrt(proj0 * proj0 + proj1 * proj1 + proj2 * proj2);

							proj0 /= projn;
							proj1 /= projn;
							proj2 /= projn;

							tmpl = proj0 * x00 + proj1 * x01 + proj2 * x02;
							if (abs(tmpl) > 1) ang1 = 0;
							else
							{
								ang1 = acos(tmpl);
								if (proj0 * x10 + proj1 * x11 + proj2 * x12 < 0) ang1 *= -1;
							}

							newx00 = x00 * cos(ang1) + sin(ang1) * x10;
							newx10 = x10 * cos(ang1) - sin(ang1) * x00;
							x00 = newx00;
							x10 = newx10;

							newx01 = x01 * cos(ang1) + sin(ang1) * x11;
							newx11 = x11 * cos(ang1) - sin(ang1) * x01;
							x01 = newx01;
							x11 = newx11;

							newx02 = x02 * cos(ang1) + sin(ang1) * x12;
							newx12 = x12 * cos(ang1) - sin(ang1) * x02;
							x02 = newx02;
							x12 = newx12;


							dotp1 = newv0 * x00 + newv1 * x01 + newv2 * x02;
							dotp2 = newv0 * x20 + newv1 * x21 + newv2 * x22;

							proj0 = x00 * dotp1 + x20 * dotp2;
							proj1 = x01 * dotp1 + x21 * dotp2;
							proj2 = x02 * dotp1 + x22 * dotp2;

							projn = sqrt(proj0 * proj0 + proj1 * proj1 + proj2 * proj2);

							proj0 /= projn;
							proj1 /= projn;
							proj2 /= projn;

							tmpl = proj0 * x00 + proj1 * x01 + proj2 * x02;
							if (abs(tmpl) > 1) ang1 = 0;
							else
							{
								ang1 = acos(tmpl);
								if (proj0 * x20 + proj1 * x21 + proj2 * x22 < 0) ang1 *= -1;
							}

							newx00 = x00 * cos(ang1) + sin(ang1) * x20;
							newx20 = x20 * cos(ang1) - sin(ang1) * x00;
							x00 = newx00;
							x20 = newx20;

							newx01 = x01 * cos(ang1) + sin(ang1) * x21;
							newx21 = x21 * cos(ang1) - sin(ang1) * x01;
							x01 = newx01;
							x21 = newx21;

							newx02 = x02 * cos(ang1) + sin(ang1) * x22;
							newx22 = x22 * cos(ang1) - sin(ang1) * x02;
							x02 = newx02;
							x22 = newx22;


						}
						else
						{

							flipg = !flipg;

							lex2 = -sqrt(lerayon * lerayon - whsize * whsize);

							angx1 = M_PI / 2 - asin(whsize / lerayon);
							dist2 = asinh(tan(angx1));
							distrem = speed - dist1 + dist2;
							ang = atan(sinh(speed - distrem - dist1));

							exitlgt = lex2 - lex1;
							exitangle = fmod(exitlgt, bhsize);
							exitangle = (2 * M_PI / bhsize) * exitangle;
							newang = M_PI / 2 + ang;

							pos0 = cos(exitangle) * sxn + sin(exitangle) * vecperp0;
							pos1 = cos(exitangle) * syn + sin(exitangle) * vecperp1;
							pos2 = cos(exitangle) * szn + sin(exitangle) * vecperp2;

							pos0 *= 1 / whsize;
							pos1 *= 1 / whsize;
							pos2 *= 1 / whsize;

							newv0 = cos(M_PI + exitangle - newang) * sxn + sin(M_PI + exitangle - newang) * vecperp0;
							newv1 = cos(M_PI + exitangle - newang) * syn + sin(M_PI + exitangle - newang) * vecperp1;
							newv2 = cos(M_PI + exitangle - newang) * szn + sin(M_PI + exitangle - newang) * vecperp2;


							dotp1 = newv0 * x00 + newv1 * x01 + newv2 * x02;
							dotp2 = newv0 * x10 + newv1 * x11 + newv2 * x12;

							proj0 = x00 * dotp1 + x10 * dotp2;
							proj1 = x01 * dotp1 + x11 * dotp2;
							proj2 = x02 * dotp1 + x12 * dotp2;

							projn = sqrt(proj0 * proj0 + proj1 * proj1 + proj2 * proj2);

							proj0 /= projn;
							proj1 /= projn;
							proj2 /= projn;

							tmpl = proj0 * x00 + proj1 * x01 + proj2 * x02;
							if (abs(tmpl) > 1) ang1 = 0;
							else
							{
								ang1 = acos(tmpl);
								if (proj0 * x10 + proj1 * x11 + proj2 * x12 < 0) ang1 *= -1;
							}

							newx00 = x00 * cos(ang1) + sin(ang1) * x10;
							newx10 = x10 * cos(ang1) - sin(ang1) * x00;
							x00 = newx00;
							x10 = newx10;

							newx01 = x01 * cos(ang1) + sin(ang1) * x11;
							newx11 = x11 * cos(ang1) - sin(ang1) * x01;
							x01 = newx01;
							x11 = newx11;

							newx02 = x02 * cos(ang1) + sin(ang1) * x12;
							newx12 = x12 * cos(ang1) - sin(ang1) * x02;
							x02 = newx02;
							x12 = newx12;

							dotp1 = newv0 * x00 + newv1 * x01 + newv2 * x02;
							dotp2 = newv0 * x20 + newv1 * x21 + newv2 * x22;

							proj0 = x00 * dotp1 + x20 * dotp2;
							proj1 = x01 * dotp1 + x21 * dotp2;
							proj2 = x02 * dotp1 + x22 * dotp2;

							projn = sqrt(proj0 * proj0 + proj1 * proj1 + proj2 * proj2);

							proj0 /= projn;
							proj1 /= projn;
							proj2 /= projn;

							tmpl = proj0 * x00 + proj1 * x01 + proj2 * x02;
							if (abs(tmpl) > 1) ang1 = 0;
							else
							{
								ang1 = acos(tmpl);
								if (proj0 * x20 + proj1 * x21 + proj2 * x22 < 0) ang1 *= -1;
							}

							newx00 = x00 * cos(ang1) + sin(ang1) * x20;
							newx20 = x20 * cos(ang1) - sin(ang1) * x00;
							x00 = newx00;
							x20 = newx20;

							newx01 = x01 * cos(ang1) + sin(ang1) * x21;
							newx21 = x21 * cos(ang1) - sin(ang1) * x01;
							x01 = newx01;
							x21 = newx21;

							newx02 = x02 * cos(ang1) + sin(ang1) * x22;
							newx22 = x22 * cos(ang1) - sin(ang1) * x02;
							x02 = newx02;
							x22 = newx22;




							dc = sqrt(pos0 * pos0 + pos1 * pos1 + pos2 * pos2);
							uhpy = 1 / dc;
							sxn = pos0 / dc;
							syn = pos1 / dc;
							szn = pos2 / dc;


							dotp = sxn * x00 + syn * x01 + szn * x02;

							vectmpx0 = sxn * dotp;
							vectmpx1 = syn * dotp;
							vectmpx2 = szn * dotp;

							x00 -= 2 * vectmpx0;
							x01 -= 2 * vectmpx1;
							x02 -= 2 * vectmpx2;


							dotp = sxn * x10 + syn * x11 + szn * x12;

							vectmpx0 = sxn * dotp;
							vectmpx1 = syn * dotp;
							vectmpx2 = szn * dotp;

							x10 -= 2 * vectmpx0;
							x11 -= 2 * vectmpx1;
							x12 -= 2 * vectmpx2;

							dotp = sxn * x20 + syn * x21 + szn * x22;

							vectmpx0 = sxn * dotp;
							vectmpx1 = syn * dotp;
							vectmpx2 = szn * dotp;

							x20 -= 2 * vectmpx0;
							x21 -= 2 * vectmpx1;
							x22 -= 2 * vectmpx2;


							sxn = -pos0 / dc;
							syn = -pos1 / dc;
							szn = -pos2 / dc;

							dotp = sxn * x00 + syn * x01 + szn * x02;
							leangle = acos(dotp);

							theta = M_PI / 2 - leangle;

							dist1 = asinh(tan(theta));
							ang = atan(sinh(distrem - dist1));

							lerayon = uhpy / sin(M_PI / 2 + theta);

							lex1 = lerayon * cos(M_PI / 2 + theta);

							lex2 = lerayon * cos(M_PI / 2 - ang);
							ley2 = lerayon * sin(M_PI / 2 - ang);

							sxn = -sxn;
							syn = -syn;
							szn = -szn;
							dotp = -dotp;
							leangle = acos(dotp);

							vecperp0 = x00 - dotp * sxn;
							vecperp1 = x01 - dotp * syn;
							vecperp2 = x02 - dotp * szn;

							vecperpn = sqrt(vecperp0 * vecperp0 + vecperp1 * vecperp1 + vecperp2 * vecperp2);

							vecperp0 /= vecperpn;
							vecperp1 /= vecperpn;
							vecperp2 /= vecperpn;


							exitlgt = lex2 - lex1;
							exitangle = fmod(exitlgt, bhsize);
							exitangle = (2 * M_PI / bhsize) * exitangle;
							newang = M_PI / 2 + ang;

							pos0 = cos(exitangle) * sxn + sin(exitangle) * vecperp0;
							pos1 = cos(exitangle) * syn + sin(exitangle) * vecperp1;
							pos2 = cos(exitangle) * szn + sin(exitangle) * vecperp2;

							pos0 *= 1 / ley2;
							pos1 *= 1 / ley2;
							pos2 *= 1 / ley2;

							newv0 = cos(M_PI + exitangle - newang) * sxn + sin(M_PI + exitangle - newang) * vecperp0;
							newv1 = cos(M_PI + exitangle - newang) * syn + sin(M_PI + exitangle - newang) * vecperp1;
							newv2 = cos(M_PI + exitangle - newang) * szn + sin(M_PI + exitangle - newang) * vecperp2;

							dotp1 = newv0 * x00 + newv1 * x01 + newv2 * x02;
							dotp2 = newv0 * x10 + newv1 * x11 + newv2 * x12;

							proj0 = x00 * dotp1 + x10 * dotp2;
							proj1 = x01 * dotp1 + x11 * dotp2;
							proj2 = x02 * dotp1 + x12 * dotp2;

							projn = sqrt(proj0 * proj0 + proj1 * proj1 + proj2 * proj2);

							proj0 /= projn;
							proj1 /= projn;
							proj2 /= projn;

							tmpl = proj0 * x00 + proj1 * x01 + proj2 * x02;
							if (abs(tmpl) > 1) ang1 = 0;
							else
							{
								ang1 = acos(tmpl);
								if (proj0 * x10 + proj1 * x11 + proj2 * x12 < 0) ang1 *= -1;
							}

							newx00 = x00 * cos(ang1) + sin(ang1) * x10;
							newx10 = x10 * cos(ang1) - sin(ang1) * x00;
							x00 = newx00;
							x10 = newx10;

							newx01 = x01 * cos(ang1) + sin(ang1) * x11;
							newx11 = x11 * cos(ang1) - sin(ang1) * x01;
							x01 = newx01;
							x11 = newx11;

							newx02 = x02 * cos(ang1) + sin(ang1) * x12;
							newx12 = x12 * cos(ang1) - sin(ang1) * x02;
							x02 = newx02;
							x12 = newx12;

							dotp1 = newv0 * x00 + newv1 * x01 + newv2 * x02;
							dotp2 = newv0 * x20 + newv1 * x21 + newv2 * x22;

							proj0 = x00 * dotp1 + x20 * dotp2;
							proj1 = x01 * dotp1 + x21 * dotp2;
							proj2 = x02 * dotp1 + x22 * dotp2;

							projn = sqrt(proj0 * proj0 + proj1 * proj1 + proj2 * proj2);

							proj0 /= projn;
							proj1 /= projn;
							proj2 /= projn;

							tmpl = proj0 * x00 + proj1 * x01 + proj2 * x02;
							if (abs(tmpl) > 1) ang1 = 0;
							else
							{
								ang1 = acos(tmpl);
								if (proj0 * x20 + proj1 * x21 + proj2 * x22 < 0) ang1 *= -1;
							}

							newx00 = x00 * cos(ang1) + sin(ang1) * x20;
							newx20 = x20 * cos(ang1) - sin(ang1) * x00;
							x00 = newx00;
							x20 = newx20;

							newx01 = x01 * cos(ang1) + sin(ang1) * x21;
							newx21 = x21 * cos(ang1) - sin(ang1) * x01;
							x01 = newx01;
							x21 = newx21;

							newx02 = x02 * cos(ang1) + sin(ang1) * x22;
							newx22 = x22 * cos(ang1) - sin(ang1) * x02;
							x02 = newx02;
							x22 = newx22;
						}

					}
				}
            }

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				dc = sqrt(pos0 * pos0 + pos1 * pos1 + pos2 * pos2);
				uhpy = 1 / dc;

				if (dc > 1) {
					pos0 += x10 * speed;
					pos1 += x11 * speed;
					pos2 += x12 * speed;
				}
				else
				{
					newx00 = x00;
					newx01 = x01;
					newx02 = x02;

					x00 = x10;
					x01 = x11;
					x02 = x12;

					x10 = newx00;
					x11 = newx01;
					x12 = newx02;

					sxn = -pos0 / dc;
					syn = -pos1 / dc;
					szn = -pos2 / dc;

					dotp = sxn * x00 + syn * x01 + szn * x02;
					leangle = acos(dotp);

					theta = M_PI / 2 - leangle;

					dist1 = asinh(tan(theta));
					ang = atan(sinh(speed - dist1));

					lerayon = uhpy / sin(M_PI / 2 + theta);

					lex1 = lerayon * cos(M_PI / 2 + theta);

					lex2 = lerayon * cos(M_PI / 2 - ang);
					ley2 = lerayon * sin(M_PI / 2 - ang);

					sxn = -sxn;
					syn = -syn;
					szn = -szn;
					dotp = -dotp;
					leangle = acos(dotp);

					vecperp0 = x00 - dotp * sxn;
					vecperp1 = x01 - dotp * syn;
					vecperp2 = x02 - dotp * szn;

					vecperpn = sqrt(vecperp0 * vecperp0 + vecperp1 * vecperp1 + vecperp2 * vecperp2);

					if (vecperpn != 0) {
						vecperp0 /= vecperpn;
						vecperp1 /= vecperpn;
						vecperp2 /= vecperpn;


						if (ley2 < whsize)
						{

							exitlgt = lex2 - lex1;
							exitangle = fmod(exitlgt, bhsize);
							exitangle = (2 * M_PI / bhsize) * exitangle;
							newang = M_PI / 2 + ang;

							pos0 = cos(exitangle) * sxn + sin(exitangle) * vecperp0;
							pos1 = cos(exitangle) * syn + sin(exitangle) * vecperp1;
							pos2 = cos(exitangle) * szn + sin(exitangle) * vecperp2;

							pos0 *= 1 / ley2;
							pos1 *= 1 / ley2;
							pos2 *= 1 / ley2;

							newv0 = cos(M_PI + exitangle - newang) * sxn + sin(M_PI + exitangle - newang) * vecperp0;
							newv1 = cos(M_PI + exitangle - newang) * syn + sin(M_PI + exitangle - newang) * vecperp1;
							newv2 = cos(M_PI + exitangle - newang) * szn + sin(M_PI + exitangle - newang) * vecperp2;



							dotp1 = newv0 * x00 + newv1 * x01 + newv2 * x02;
							dotp2 = newv0 * x10 + newv1 * x11 + newv2 * x12;

							proj0 = x00 * dotp1 + x10 * dotp2;
							proj1 = x01 * dotp1 + x11 * dotp2;
							proj2 = x02 * dotp1 + x12 * dotp2;

							projn = sqrt(proj0 * proj0 + proj1 * proj1 + proj2 * proj2);

							proj0 /= projn;
							proj1 /= projn;
							proj2 /= projn;

							tmpl = proj0 * x00 + proj1 * x01 + proj2 * x02;
							if (abs(tmpl) > 1) ang1 = 0;
							else
							{
								ang1 = acos(tmpl);
								if (proj0 * x10 + proj1 * x11 + proj2 * x12 < 0) ang1 *= -1;
							}

							newx00 = x00 * cos(ang1) + sin(ang1) * x10;
							newx10 = x10 * cos(ang1) - sin(ang1) * x00;
							x00 = newx00;
							x10 = newx10;

							newx01 = x01 * cos(ang1) + sin(ang1) * x11;
							newx11 = x11 * cos(ang1) - sin(ang1) * x01;
							x01 = newx01;
							x11 = newx11;

							newx02 = x02 * cos(ang1) + sin(ang1) * x12;
							newx12 = x12 * cos(ang1) - sin(ang1) * x02;
							x02 = newx02;
							x12 = newx12;


							dotp1 = newv0 * x00 + newv1 * x01 + newv2 * x02;
							dotp2 = newv0 * x20 + newv1 * x21 + newv2 * x22;

							proj0 = x00 * dotp1 + x20 * dotp2;
							proj1 = x01 * dotp1 + x21 * dotp2;
							proj2 = x02 * dotp1 + x22 * dotp2;

							projn = sqrt(proj0 * proj0 + proj1 * proj1 + proj2 * proj2);

							proj0 /= projn;
							proj1 /= projn;
							proj2 /= projn;

							tmpl = proj0 * x00 + proj1 * x01 + proj2 * x02;
							if (abs(tmpl) > 1) ang1 = 0;
							else
							{
								ang1 = acos(tmpl);
								if (proj0 * x20 + proj1 * x21 + proj2 * x22 < 0) ang1 *= -1;
							}

							newx00 = x00 * cos(ang1) + sin(ang1) * x20;
							newx20 = x20 * cos(ang1) - sin(ang1) * x00;
							x00 = newx00;
							x20 = newx20;

							newx01 = x01 * cos(ang1) + sin(ang1) * x21;
							newx21 = x21 * cos(ang1) - sin(ang1) * x01;
							x01 = newx01;
							x21 = newx21;

							newx02 = x02 * cos(ang1) + sin(ang1) * x22;
							newx22 = x22 * cos(ang1) - sin(ang1) * x02;
							x02 = newx02;
							x22 = newx22;


						}
						else
						{

							flipg = !flipg;

							lex2 = -sqrt(lerayon * lerayon - whsize * whsize);

							angx1 = M_PI / 2 - asin(whsize / lerayon);
							dist2 = asinh(tan(angx1));
							distrem = speed - dist1 + dist2;
							ang = atan(sinh(speed - distrem - dist1));

							exitlgt = lex2 - lex1;
							exitangle = fmod(exitlgt, bhsize);
							exitangle = (2 * M_PI / bhsize) * exitangle;
							newang = M_PI / 2 + ang;

							pos0 = cos(exitangle) * sxn + sin(exitangle) * vecperp0;
							pos1 = cos(exitangle) * syn + sin(exitangle) * vecperp1;
							pos2 = cos(exitangle) * szn + sin(exitangle) * vecperp2;

							pos0 *= 1 / whsize;
							pos1 *= 1 / whsize;
							pos2 *= 1 / whsize;

							newv0 = cos(M_PI + exitangle - newang) * sxn + sin(M_PI + exitangle - newang) * vecperp0;
							newv1 = cos(M_PI + exitangle - newang) * syn + sin(M_PI + exitangle - newang) * vecperp1;
							newv2 = cos(M_PI + exitangle - newang) * szn + sin(M_PI + exitangle - newang) * vecperp2;


							dotp1 = newv0 * x00 + newv1 * x01 + newv2 * x02;
							dotp2 = newv0 * x10 + newv1 * x11 + newv2 * x12;

							proj0 = x00 * dotp1 + x10 * dotp2;
							proj1 = x01 * dotp1 + x11 * dotp2;
							proj2 = x02 * dotp1 + x12 * dotp2;

							projn = sqrt(proj0 * proj0 + proj1 * proj1 + proj2 * proj2);

							proj0 /= projn;
							proj1 /= projn;
							proj2 /= projn;

							tmpl = proj0 * x00 + proj1 * x01 + proj2 * x02;
							if (abs(tmpl) > 1) ang1 = 0;
							else
							{
								ang1 = acos(tmpl);
								if (proj0 * x10 + proj1 * x11 + proj2 * x12 < 0) ang1 *= -1;
							}

							newx00 = x00 * cos(ang1) + sin(ang1) * x10;
							newx10 = x10 * cos(ang1) - sin(ang1) * x00;
							x00 = newx00;
							x10 = newx10;

							newx01 = x01 * cos(ang1) + sin(ang1) * x11;
							newx11 = x11 * cos(ang1) - sin(ang1) * x01;
							x01 = newx01;
							x11 = newx11;

							newx02 = x02 * cos(ang1) + sin(ang1) * x12;
							newx12 = x12 * cos(ang1) - sin(ang1) * x02;
							x02 = newx02;
							x12 = newx12;

							dotp1 = newv0 * x00 + newv1 * x01 + newv2 * x02;
							dotp2 = newv0 * x20 + newv1 * x21 + newv2 * x22;

							proj0 = x00 * dotp1 + x20 * dotp2;
							proj1 = x01 * dotp1 + x21 * dotp2;
							proj2 = x02 * dotp1 + x22 * dotp2;

							projn = sqrt(proj0 * proj0 + proj1 * proj1 + proj2 * proj2);

							proj0 /= projn;
							proj1 /= projn;
							proj2 /= projn;

							tmpl = proj0 * x00 + proj1 * x01 + proj2 * x02;
							if (abs(tmpl) > 1) ang1 = 0;
							else
							{
								ang1 = acos(tmpl);
								if (proj0 * x20 + proj1 * x21 + proj2 * x22 < 0) ang1 *= -1;
							}

							newx00 = x00 * cos(ang1) + sin(ang1) * x20;
							newx20 = x20 * cos(ang1) - sin(ang1) * x00;
							x00 = newx00;
							x20 = newx20;

							newx01 = x01 * cos(ang1) + sin(ang1) * x21;
							newx21 = x21 * cos(ang1) - sin(ang1) * x01;
							x01 = newx01;
							x21 = newx21;

							newx02 = x02 * cos(ang1) + sin(ang1) * x22;
							newx22 = x22 * cos(ang1) - sin(ang1) * x02;
							x02 = newx02;
							x22 = newx22;




							dc = sqrt(pos0 * pos0 + pos1 * pos1 + pos2 * pos2);
							uhpy = 1 / dc;
							sxn = pos0 / dc;
							syn = pos1 / dc;
							szn = pos2 / dc;


							dotp = sxn * x00 + syn * x01 + szn * x02;

							vectmpx0 = sxn * dotp;
							vectmpx1 = syn * dotp;
							vectmpx2 = szn * dotp;

							x00 -= 2 * vectmpx0;
							x01 -= 2 * vectmpx1;
							x02 -= 2 * vectmpx2;


							dotp = sxn * x10 + syn * x11 + szn * x12;

							vectmpx0 = sxn * dotp;
							vectmpx1 = syn * dotp;
							vectmpx2 = szn * dotp;

							x10 -= 2 * vectmpx0;
							x11 -= 2 * vectmpx1;
							x12 -= 2 * vectmpx2;

							dotp = sxn * x20 + syn * x21 + szn * x22;

							vectmpx0 = sxn * dotp;
							vectmpx1 = syn * dotp;
							vectmpx2 = szn * dotp;

							x20 -= 2 * vectmpx0;
							x21 -= 2 * vectmpx1;
							x22 -= 2 * vectmpx2;


							sxn = -pos0 / dc;
							syn = -pos1 / dc;
							szn = -pos2 / dc;

							dotp = sxn * x00 + syn * x01 + szn * x02;
							leangle = acos(dotp);

							theta = M_PI / 2 - leangle;

							dist1 = asinh(tan(theta));
							ang = atan(sinh(distrem - dist1));

							lerayon = uhpy / sin(M_PI / 2 + theta);

							lex1 = lerayon * cos(M_PI / 2 + theta);

							lex2 = lerayon * cos(M_PI / 2 - ang);
							ley2 = lerayon * sin(M_PI / 2 - ang);

							sxn = -sxn;
							syn = -syn;
							szn = -szn;
							dotp = -dotp;
							leangle = acos(dotp);

							vecperp0 = x00 - dotp * sxn;
							vecperp1 = x01 - dotp * syn;
							vecperp2 = x02 - dotp * szn;

							vecperpn = sqrt(vecperp0 * vecperp0 + vecperp1 * vecperp1 + vecperp2 * vecperp2);

							vecperp0 /= vecperpn;
							vecperp1 /= vecperpn;
							vecperp2 /= vecperpn;


							exitlgt = lex2 - lex1;
							exitangle = fmod(exitlgt, bhsize);
							exitangle = (2 * M_PI / bhsize) * exitangle;
							newang = M_PI / 2 + ang;

							pos0 = cos(exitangle) * sxn + sin(exitangle) * vecperp0;
							pos1 = cos(exitangle) * syn + sin(exitangle) * vecperp1;
							pos2 = cos(exitangle) * szn + sin(exitangle) * vecperp2;

							pos0 *= 1 / ley2;
							pos1 *= 1 / ley2;
							pos2 *= 1 / ley2;

							newv0 = cos(M_PI + exitangle - newang) * sxn + sin(M_PI + exitangle - newang) * vecperp0;
							newv1 = cos(M_PI + exitangle - newang) * syn + sin(M_PI + exitangle - newang) * vecperp1;
							newv2 = cos(M_PI + exitangle - newang) * szn + sin(M_PI + exitangle - newang) * vecperp2;

							dotp1 = newv0 * x00 + newv1 * x01 + newv2 * x02;
							dotp2 = newv0 * x10 + newv1 * x11 + newv2 * x12;

							proj0 = x00 * dotp1 + x10 * dotp2;
							proj1 = x01 * dotp1 + x11 * dotp2;
							proj2 = x02 * dotp1 + x12 * dotp2;

							projn = sqrt(proj0 * proj0 + proj1 * proj1 + proj2 * proj2);

							proj0 /= projn;
							proj1 /= projn;
							proj2 /= projn;

							tmpl = proj0 * x00 + proj1 * x01 + proj2 * x02;
							if (abs(tmpl) > 1) ang1 = 0;
							else
							{
								ang1 = acos(tmpl);
								if (proj0 * x10 + proj1 * x11 + proj2 * x12 < 0) ang1 *= -1;
							}

							newx00 = x00 * cos(ang1) + sin(ang1) * x10;
							newx10 = x10 * cos(ang1) - sin(ang1) * x00;
							x00 = newx00;
							x10 = newx10;

							newx01 = x01 * cos(ang1) + sin(ang1) * x11;
							newx11 = x11 * cos(ang1) - sin(ang1) * x01;
							x01 = newx01;
							x11 = newx11;

							newx02 = x02 * cos(ang1) + sin(ang1) * x12;
							newx12 = x12 * cos(ang1) - sin(ang1) * x02;
							x02 = newx02;
							x12 = newx12;

							dotp1 = newv0 * x00 + newv1 * x01 + newv2 * x02;
							dotp2 = newv0 * x20 + newv1 * x21 + newv2 * x22;

							proj0 = x00 * dotp1 + x20 * dotp2;
							proj1 = x01 * dotp1 + x21 * dotp2;
							proj2 = x02 * dotp1 + x22 * dotp2;

							projn = sqrt(proj0 * proj0 + proj1 * proj1 + proj2 * proj2);

							proj0 /= projn;
							proj1 /= projn;
							proj2 /= projn;

							tmpl = proj0 * x00 + proj1 * x01 + proj2 * x02;
							if (abs(tmpl) > 1) ang1 = 0;
							else
							{
								ang1 = acos(tmpl);
								if (proj0 * x20 + proj1 * x21 + proj2 * x22 < 0) ang1 *= -1;
							}

							newx00 = x00 * cos(ang1) + sin(ang1) * x20;
							newx20 = x20 * cos(ang1) - sin(ang1) * x00;
							x00 = newx00;
							x20 = newx20;

							newx01 = x01 * cos(ang1) + sin(ang1) * x21;
							newx21 = x21 * cos(ang1) - sin(ang1) * x01;
							x01 = newx01;
							x21 = newx21;

							newx02 = x02 * cos(ang1) + sin(ang1) * x22;
							newx22 = x22 * cos(ang1) - sin(ang1) * x02;
							x02 = newx02;
							x22 = newx22;
						}

					}

					newx00 = x00;
					newx01 = x01;
					newx02 = x02;

					x00 = x10;
					x01 = x11;
					x02 = x12;

					x10 = newx00;
					x11 = newx01;
					x12 = newx02;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				dc = sqrt(pos0 * pos0 + pos1 * pos1 + pos2 * pos2);
				uhpy = 1 / dc;

				if (dc > 1) {
					pos0 -= x10 * speed;
					pos1 -= x11 * speed;
					pos2 -= x12 * speed;
				}
				else
				{


					newx00 = x00;
					newx01 = x01;
					newx02 = x02;

					x00 = x10;
					x01 = x11;
					x02 = x12;

					x10 = newx00;
					x11 = newx01;
					x12 = newx02;

					x00 = -x00;
					x01 = -x01;
					x02 = -x02;

					sxn = -pos0 / dc;
					syn = -pos1 / dc;
					szn = -pos2 / dc;

					dotp = sxn * x00 + syn * x01 + szn * x02;
					leangle = acos(dotp);

					theta = M_PI / 2 - leangle;

					dist1 = asinh(tan(theta));
					ang = atan(sinh(speed - dist1));

					lerayon = uhpy / sin(M_PI / 2 + theta);

					lex1 = lerayon * cos(M_PI / 2 + theta);

					lex2 = lerayon * cos(M_PI / 2 - ang);
					ley2 = lerayon * sin(M_PI / 2 - ang);

					sxn = -sxn;
					syn = -syn;
					szn = -szn;
					dotp = -dotp;
					leangle = acos(dotp);

					vecperp0 = x00 - dotp * sxn;
					vecperp1 = x01 - dotp * syn;
					vecperp2 = x02 - dotp * szn;

					vecperpn = sqrt(vecperp0 * vecperp0 + vecperp1 * vecperp1 + vecperp2 * vecperp2);

					if (vecperpn != 0) {
						vecperp0 /= vecperpn;
						vecperp1 /= vecperpn;
						vecperp2 /= vecperpn;


						if (ley2 < whsize)
						{

							exitlgt = lex2 - lex1;
							exitangle = fmod(exitlgt, bhsize);
							exitangle = (2 * M_PI / bhsize) * exitangle;
							newang = M_PI / 2 + ang;

							pos0 = cos(exitangle) * sxn + sin(exitangle) * vecperp0;
							pos1 = cos(exitangle) * syn + sin(exitangle) * vecperp1;
							pos2 = cos(exitangle) * szn + sin(exitangle) * vecperp2;

							pos0 *= 1 / ley2;
							pos1 *= 1 / ley2;
							pos2 *= 1 / ley2;

							newv0 = cos(M_PI + exitangle - newang) * sxn + sin(M_PI + exitangle - newang) * vecperp0;
							newv1 = cos(M_PI + exitangle - newang) * syn + sin(M_PI + exitangle - newang) * vecperp1;
							newv2 = cos(M_PI + exitangle - newang) * szn + sin(M_PI + exitangle - newang) * vecperp2;



							dotp1 = newv0 * x00 + newv1 * x01 + newv2 * x02;
							dotp2 = newv0 * x10 + newv1 * x11 + newv2 * x12;

							proj0 = x00 * dotp1 + x10 * dotp2;
							proj1 = x01 * dotp1 + x11 * dotp2;
							proj2 = x02 * dotp1 + x12 * dotp2;

							projn = sqrt(proj0 * proj0 + proj1 * proj1 + proj2 * proj2);

							proj0 /= projn;
							proj1 /= projn;
							proj2 /= projn;

							tmpl = proj0 * x00 + proj1 * x01 + proj2 * x02;
							if (abs(tmpl) > 1) ang1 = 0;
							else
							{
								ang1 = acos(tmpl);
								if (proj0 * x10 + proj1 * x11 + proj2 * x12 < 0) ang1 *= -1;
							}

							newx00 = x00 * cos(ang1) + sin(ang1) * x10;
							newx10 = x10 * cos(ang1) - sin(ang1) * x00;
							x00 = newx00;
							x10 = newx10;

							newx01 = x01 * cos(ang1) + sin(ang1) * x11;
							newx11 = x11 * cos(ang1) - sin(ang1) * x01;
							x01 = newx01;
							x11 = newx11;

							newx02 = x02 * cos(ang1) + sin(ang1) * x12;
							newx12 = x12 * cos(ang1) - sin(ang1) * x02;
							x02 = newx02;
							x12 = newx12;


							dotp1 = newv0 * x00 + newv1 * x01 + newv2 * x02;
							dotp2 = newv0 * x20 + newv1 * x21 + newv2 * x22;

							proj0 = x00 * dotp1 + x20 * dotp2;
							proj1 = x01 * dotp1 + x21 * dotp2;
							proj2 = x02 * dotp1 + x22 * dotp2;

							projn = sqrt(proj0 * proj0 + proj1 * proj1 + proj2 * proj2);

							proj0 /= projn;
							proj1 /= projn;
							proj2 /= projn;

							tmpl = proj0 * x00 + proj1 * x01 + proj2 * x02;
							if (abs(tmpl) > 1) ang1 = 0;
							else
							{
								ang1 = acos(tmpl);
								if (proj0 * x20 + proj1 * x21 + proj2 * x22 < 0) ang1 *= -1;
							}

							newx00 = x00 * cos(ang1) + sin(ang1) * x20;
							newx20 = x20 * cos(ang1) - sin(ang1) * x00;
							x00 = newx00;
							x20 = newx20;

							newx01 = x01 * cos(ang1) + sin(ang1) * x21;
							newx21 = x21 * cos(ang1) - sin(ang1) * x01;
							x01 = newx01;
							x21 = newx21;

							newx02 = x02 * cos(ang1) + sin(ang1) * x22;
							newx22 = x22 * cos(ang1) - sin(ang1) * x02;
							x02 = newx02;
							x22 = newx22;


						}
						else
						{

							flipg = !flipg;

							lex2 = -sqrt(lerayon * lerayon - whsize * whsize);

							angx1 = M_PI / 2 - asin(whsize / lerayon);
							dist2 = asinh(tan(angx1));
							distrem = speed - dist1 + dist2;
							ang = atan(sinh(speed - distrem - dist1));

							exitlgt = lex2 - lex1;
							exitangle = fmod(exitlgt, bhsize);
							exitangle = (2 * M_PI / bhsize) * exitangle;
							newang = M_PI / 2 + ang;

							pos0 = cos(exitangle) * sxn + sin(exitangle) * vecperp0;
							pos1 = cos(exitangle) * syn + sin(exitangle) * vecperp1;
							pos2 = cos(exitangle) * szn + sin(exitangle) * vecperp2;

							pos0 *= 1 / whsize;
							pos1 *= 1 / whsize;
							pos2 *= 1 / whsize;

							newv0 = cos(M_PI + exitangle - newang) * sxn + sin(M_PI + exitangle - newang) * vecperp0;
							newv1 = cos(M_PI + exitangle - newang) * syn + sin(M_PI + exitangle - newang) * vecperp1;
							newv2 = cos(M_PI + exitangle - newang) * szn + sin(M_PI + exitangle - newang) * vecperp2;


							dotp1 = newv0 * x00 + newv1 * x01 + newv2 * x02;
							dotp2 = newv0 * x10 + newv1 * x11 + newv2 * x12;

							proj0 = x00 * dotp1 + x10 * dotp2;
							proj1 = x01 * dotp1 + x11 * dotp2;
							proj2 = x02 * dotp1 + x12 * dotp2;

							projn = sqrt(proj0 * proj0 + proj1 * proj1 + proj2 * proj2);

							proj0 /= projn;
							proj1 /= projn;
							proj2 /= projn;

							tmpl = proj0 * x00 + proj1 * x01 + proj2 * x02;
							if (abs(tmpl) > 1) ang1 = 0;
							else
							{
								ang1 = acos(tmpl);
								if (proj0 * x10 + proj1 * x11 + proj2 * x12 < 0) ang1 *= -1;
							}

							newx00 = x00 * cos(ang1) + sin(ang1) * x10;
							newx10 = x10 * cos(ang1) - sin(ang1) * x00;
							x00 = newx00;
							x10 = newx10;

							newx01 = x01 * cos(ang1) + sin(ang1) * x11;
							newx11 = x11 * cos(ang1) - sin(ang1) * x01;
							x01 = newx01;
							x11 = newx11;

							newx02 = x02 * cos(ang1) + sin(ang1) * x12;
							newx12 = x12 * cos(ang1) - sin(ang1) * x02;
							x02 = newx02;
							x12 = newx12;

							dotp1 = newv0 * x00 + newv1 * x01 + newv2 * x02;
							dotp2 = newv0 * x20 + newv1 * x21 + newv2 * x22;

							proj0 = x00 * dotp1 + x20 * dotp2;
							proj1 = x01 * dotp1 + x21 * dotp2;
							proj2 = x02 * dotp1 + x22 * dotp2;

							projn = sqrt(proj0 * proj0 + proj1 * proj1 + proj2 * proj2);

							proj0 /= projn;
							proj1 /= projn;
							proj2 /= projn;

							tmpl = proj0 * x00 + proj1 * x01 + proj2 * x02;
							if (abs(tmpl) > 1) ang1 = 0;
							else
							{
								ang1 = acos(tmpl);
								if (proj0 * x20 + proj1 * x21 + proj2 * x22 < 0) ang1 *= -1;
							}

							newx00 = x00 * cos(ang1) + sin(ang1) * x20;
							newx20 = x20 * cos(ang1) - sin(ang1) * x00;
							x00 = newx00;
							x20 = newx20;

							newx01 = x01 * cos(ang1) + sin(ang1) * x21;
							newx21 = x21 * cos(ang1) - sin(ang1) * x01;
							x01 = newx01;
							x21 = newx21;

							newx02 = x02 * cos(ang1) + sin(ang1) * x22;
							newx22 = x22 * cos(ang1) - sin(ang1) * x02;
							x02 = newx02;
							x22 = newx22;




							dc = sqrt(pos0 * pos0 + pos1 * pos1 + pos2 * pos2);
							uhpy = 1 / dc;
							sxn = pos0 / dc;
							syn = pos1 / dc;
							szn = pos2 / dc;


							dotp = sxn * x00 + syn * x01 + szn * x02;

							vectmpx0 = sxn * dotp;
							vectmpx1 = syn * dotp;
							vectmpx2 = szn * dotp;

							x00 -= 2 * vectmpx0;
							x01 -= 2 * vectmpx1;
							x02 -= 2 * vectmpx2;


							dotp = sxn * x10 + syn * x11 + szn * x12;

							vectmpx0 = sxn * dotp;
							vectmpx1 = syn * dotp;
							vectmpx2 = szn * dotp;

							x10 -= 2 * vectmpx0;
							x11 -= 2 * vectmpx1;
							x12 -= 2 * vectmpx2;

							dotp = sxn * x20 + syn * x21 + szn * x22;

							vectmpx0 = sxn * dotp;
							vectmpx1 = syn * dotp;
							vectmpx2 = szn * dotp;

							x20 -= 2 * vectmpx0;
							x21 -= 2 * vectmpx1;
							x22 -= 2 * vectmpx2;


							sxn = -pos0 / dc;
							syn = -pos1 / dc;
							szn = -pos2 / dc;

							dotp = sxn * x00 + syn * x01 + szn * x02;
							leangle = acos(dotp);

							theta = M_PI / 2 - leangle;

							dist1 = asinh(tan(theta));
							ang = atan(sinh(distrem - dist1));

							lerayon = uhpy / sin(M_PI / 2 + theta);

							lex1 = lerayon * cos(M_PI / 2 + theta);

							lex2 = lerayon * cos(M_PI / 2 - ang);
							ley2 = lerayon * sin(M_PI / 2 - ang);

							sxn = -sxn;
							syn = -syn;
							szn = -szn;
							dotp = -dotp;
							leangle = acos(dotp);

							vecperp0 = x00 - dotp * sxn;
							vecperp1 = x01 - dotp * syn;
							vecperp2 = x02 - dotp * szn;

							vecperpn = sqrt(vecperp0 * vecperp0 + vecperp1 * vecperp1 + vecperp2 * vecperp2);

							vecperp0 /= vecperpn;
							vecperp1 /= vecperpn;
							vecperp2 /= vecperpn;


							exitlgt = lex2 - lex1;
							exitangle = fmod(exitlgt, bhsize);
							exitangle = (2 * M_PI / bhsize) * exitangle;
							newang = M_PI / 2 + ang;

							pos0 = cos(exitangle) * sxn + sin(exitangle) * vecperp0;
							pos1 = cos(exitangle) * syn + sin(exitangle) * vecperp1;
							pos2 = cos(exitangle) * szn + sin(exitangle) * vecperp2;

							pos0 *= 1 / ley2;
							pos1 *= 1 / ley2;
							pos2 *= 1 / ley2;

							newv0 = cos(M_PI + exitangle - newang) * sxn + sin(M_PI + exitangle - newang) * vecperp0;
							newv1 = cos(M_PI + exitangle - newang) * syn + sin(M_PI + exitangle - newang) * vecperp1;
							newv2 = cos(M_PI + exitangle - newang) * szn + sin(M_PI + exitangle - newang) * vecperp2;

							dotp1 = newv0 * x00 + newv1 * x01 + newv2 * x02;
							dotp2 = newv0 * x10 + newv1 * x11 + newv2 * x12;

							proj0 = x00 * dotp1 + x10 * dotp2;
							proj1 = x01 * dotp1 + x11 * dotp2;
							proj2 = x02 * dotp1 + x12 * dotp2;

							projn = sqrt(proj0 * proj0 + proj1 * proj1 + proj2 * proj2);

							proj0 /= projn;
							proj1 /= projn;
							proj2 /= projn;

							tmpl = proj0 * x00 + proj1 * x01 + proj2 * x02;
							if (abs(tmpl) > 1) ang1 = 0;
							else
							{
								ang1 = acos(tmpl);
								if (proj0 * x10 + proj1 * x11 + proj2 * x12 < 0) ang1 *= -1;
							}

							newx00 = x00 * cos(ang1) + sin(ang1) * x10;
							newx10 = x10 * cos(ang1) - sin(ang1) * x00;
							x00 = newx00;
							x10 = newx10;

							newx01 = x01 * cos(ang1) + sin(ang1) * x11;
							newx11 = x11 * cos(ang1) - sin(ang1) * x01;
							x01 = newx01;
							x11 = newx11;

							newx02 = x02 * cos(ang1) + sin(ang1) * x12;
							newx12 = x12 * cos(ang1) - sin(ang1) * x02;
							x02 = newx02;
							x12 = newx12;

							dotp1 = newv0 * x00 + newv1 * x01 + newv2 * x02;
							dotp2 = newv0 * x20 + newv1 * x21 + newv2 * x22;

							proj0 = x00 * dotp1 + x20 * dotp2;
							proj1 = x01 * dotp1 + x21 * dotp2;
							proj2 = x02 * dotp1 + x22 * dotp2;

							projn = sqrt(proj0 * proj0 + proj1 * proj1 + proj2 * proj2);

							proj0 /= projn;
							proj1 /= projn;
							proj2 /= projn;

							tmpl = proj0 * x00 + proj1 * x01 + proj2 * x02;
							if (abs(tmpl) > 1) ang1 = 0;
							else
							{
								ang1 = acos(tmpl);
								if (proj0 * x20 + proj1 * x21 + proj2 * x22 < 0) ang1 *= -1;
							}

							newx00 = x00 * cos(ang1) + sin(ang1) * x20;
							newx20 = x20 * cos(ang1) - sin(ang1) * x00;
							x00 = newx00;
							x20 = newx20;

							newx01 = x01 * cos(ang1) + sin(ang1) * x21;
							newx21 = x21 * cos(ang1) - sin(ang1) * x01;
							x01 = newx01;
							x21 = newx21;

							newx02 = x02 * cos(ang1) + sin(ang1) * x22;
							newx22 = x22 * cos(ang1) - sin(ang1) * x02;
							x02 = newx02;
							x22 = newx22;
						}

					}

					x00 = -x00;
					x01 = -x01;
					x02 = -x02;

					newx00 = x00;
					newx01 = x01;
					newx02 = x02;

					x00 = x10;
					x01 = x11;
					x02 = x12;

					x10 = newx00;
					x11 = newx01;
					x12 = newx02;
				}
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				dc = sqrt(pos0 * pos0 + pos1 * pos1 + pos2 * pos2);
				uhpy = 1 / dc;

				if (dc > 1) {
					pos0 -= x00 * speed;
					pos1 -= x01 * speed;
					pos2 -= x02 * speed;
				}
				else
				{
					x00 = -x00;
					x01 = -x01;
					x02 = -x02;

					sxn = -pos0 / dc;
					syn = -pos1 / dc;
					szn = -pos2 / dc;

					dotp = sxn * x00 + syn * x01 + szn * x02;
					leangle = acos(dotp);

					theta = M_PI / 2 - leangle;

					dist1 = asinh(tan(theta));
					ang = atan(sinh(speed - dist1));

					lerayon = uhpy / sin(M_PI / 2 + theta);

					lex1 = lerayon * cos(M_PI / 2 + theta);

					lex2 = lerayon * cos(M_PI / 2 - ang);
					ley2 = lerayon * sin(M_PI / 2 - ang);

					sxn = -sxn;
					syn = -syn;
					szn = -szn;
					dotp = -dotp;
					leangle = acos(dotp);

					vecperp0 = x00 - dotp * sxn;
					vecperp1 = x01 - dotp * syn;
					vecperp2 = x02 - dotp * szn;

					vecperpn = sqrt(vecperp0 * vecperp0 + vecperp1 * vecperp1 + vecperp2 * vecperp2);

					if (vecperpn != 0) {
						vecperp0 /= vecperpn;
						vecperp1 /= vecperpn;
						vecperp2 /= vecperpn;


						if (ley2 < whsize)
						{

							exitlgt = lex2 - lex1;
							exitangle = fmod(exitlgt, bhsize);
							exitangle = (2 * M_PI / bhsize) * exitangle;
							newang = M_PI / 2 + ang;

							pos0 = cos(exitangle) * sxn + sin(exitangle) * vecperp0;
							pos1 = cos(exitangle) * syn + sin(exitangle) * vecperp1;
							pos2 = cos(exitangle) * szn + sin(exitangle) * vecperp2;

							pos0 *= 1 / ley2;
							pos1 *= 1 / ley2;
							pos2 *= 1 / ley2;

							newv0 = cos(M_PI + exitangle - newang) * sxn + sin(M_PI + exitangle - newang) * vecperp0;
							newv1 = cos(M_PI + exitangle - newang) * syn + sin(M_PI + exitangle - newang) * vecperp1;
							newv2 = cos(M_PI + exitangle - newang) * szn + sin(M_PI + exitangle - newang) * vecperp2;



							dotp1 = newv0 * x00 + newv1 * x01 + newv2 * x02;
							dotp2 = newv0 * x10 + newv1 * x11 + newv2 * x12;

							proj0 = x00 * dotp1 + x10 * dotp2;
							proj1 = x01 * dotp1 + x11 * dotp2;
							proj2 = x02 * dotp1 + x12 * dotp2;

							projn = sqrt(proj0 * proj0 + proj1 * proj1 + proj2 * proj2);

							proj0 /= projn;
							proj1 /= projn;
							proj2 /= projn;

							tmpl = proj0 * x00 + proj1 * x01 + proj2 * x02;
							if (abs(tmpl) > 1) ang1 = 0;
							else
							{
								ang1 = acos(tmpl);
								if (proj0 * x10 + proj1 * x11 + proj2 * x12 < 0) ang1 *= -1;
							}

							newx00 = x00 * cos(ang1) + sin(ang1) * x10;
							newx10 = x10 * cos(ang1) - sin(ang1) * x00;
							x00 = newx00;
							x10 = newx10;

							newx01 = x01 * cos(ang1) + sin(ang1) * x11;
							newx11 = x11 * cos(ang1) - sin(ang1) * x01;
							x01 = newx01;
							x11 = newx11;

							newx02 = x02 * cos(ang1) + sin(ang1) * x12;
							newx12 = x12 * cos(ang1) - sin(ang1) * x02;
							x02 = newx02;
							x12 = newx12;


							dotp1 = newv0 * x00 + newv1 * x01 + newv2 * x02;
							dotp2 = newv0 * x20 + newv1 * x21 + newv2 * x22;

							proj0 = x00 * dotp1 + x20 * dotp2;
							proj1 = x01 * dotp1 + x21 * dotp2;
							proj2 = x02 * dotp1 + x22 * dotp2;

							projn = sqrt(proj0 * proj0 + proj1 * proj1 + proj2 * proj2);

							proj0 /= projn;
							proj1 /= projn;
							proj2 /= projn;

							tmpl = proj0 * x00 + proj1 * x01 + proj2 * x02;
							if (abs(tmpl) > 1) ang1 = 0;
							else
							{
								ang1 = acos(tmpl);
								if (proj0 * x20 + proj1 * x21 + proj2 * x22 < 0) ang1 *= -1;
							}

							newx00 = x00 * cos(ang1) + sin(ang1) * x20;
							newx20 = x20 * cos(ang1) - sin(ang1) * x00;
							x00 = newx00;
							x20 = newx20;

							newx01 = x01 * cos(ang1) + sin(ang1) * x21;
							newx21 = x21 * cos(ang1) - sin(ang1) * x01;
							x01 = newx01;
							x21 = newx21;

							newx02 = x02 * cos(ang1) + sin(ang1) * x22;
							newx22 = x22 * cos(ang1) - sin(ang1) * x02;
							x02 = newx02;
							x22 = newx22;


						}
						else
						{

							flipg = !flipg;

							lex2 = -sqrt(lerayon * lerayon - whsize * whsize);

							angx1 = M_PI / 2 - asin(whsize / lerayon);
							dist2 = asinh(tan(angx1));
							distrem = speed - dist1 + dist2;
							ang = atan(sinh(speed - distrem - dist1));

							exitlgt = lex2 - lex1;
							exitangle = fmod(exitlgt, bhsize);
							exitangle = (2 * M_PI / bhsize) * exitangle;
							newang = M_PI / 2 + ang;

							pos0 = cos(exitangle) * sxn + sin(exitangle) * vecperp0;
							pos1 = cos(exitangle) * syn + sin(exitangle) * vecperp1;
							pos2 = cos(exitangle) * szn + sin(exitangle) * vecperp2;

							pos0 *= 1 / whsize;
							pos1 *= 1 / whsize;
							pos2 *= 1 / whsize;

							newv0 = cos(M_PI + exitangle - newang) * sxn + sin(M_PI + exitangle - newang) * vecperp0;
							newv1 = cos(M_PI + exitangle - newang) * syn + sin(M_PI + exitangle - newang) * vecperp1;
							newv2 = cos(M_PI + exitangle - newang) * szn + sin(M_PI + exitangle - newang) * vecperp2;


							dotp1 = newv0 * x00 + newv1 * x01 + newv2 * x02;
							dotp2 = newv0 * x10 + newv1 * x11 + newv2 * x12;

							proj0 = x00 * dotp1 + x10 * dotp2;
							proj1 = x01 * dotp1 + x11 * dotp2;
							proj2 = x02 * dotp1 + x12 * dotp2;

							projn = sqrt(proj0 * proj0 + proj1 * proj1 + proj2 * proj2);

							proj0 /= projn;
							proj1 /= projn;
							proj2 /= projn;

							tmpl = proj0 * x00 + proj1 * x01 + proj2 * x02;
							if (abs(tmpl) > 1) ang1 = 0;
							else
							{
								ang1 = acos(tmpl);
								if (proj0 * x10 + proj1 * x11 + proj2 * x12 < 0) ang1 *= -1;
							}

							newx00 = x00 * cos(ang1) + sin(ang1) * x10;
							newx10 = x10 * cos(ang1) - sin(ang1) * x00;
							x00 = newx00;
							x10 = newx10;

							newx01 = x01 * cos(ang1) + sin(ang1) * x11;
							newx11 = x11 * cos(ang1) - sin(ang1) * x01;
							x01 = newx01;
							x11 = newx11;

							newx02 = x02 * cos(ang1) + sin(ang1) * x12;
							newx12 = x12 * cos(ang1) - sin(ang1) * x02;
							x02 = newx02;
							x12 = newx12;

							dotp1 = newv0 * x00 + newv1 * x01 + newv2 * x02;
							dotp2 = newv0 * x20 + newv1 * x21 + newv2 * x22;

							proj0 = x00 * dotp1 + x20 * dotp2;
							proj1 = x01 * dotp1 + x21 * dotp2;
							proj2 = x02 * dotp1 + x22 * dotp2;

							projn = sqrt(proj0 * proj0 + proj1 * proj1 + proj2 * proj2);

							proj0 /= projn;
							proj1 /= projn;
							proj2 /= projn;

							tmpl = proj0 * x00 + proj1 * x01 + proj2 * x02;
							if (abs(tmpl) > 1) ang1 = 0;
							else
							{
								ang1 = acos(tmpl);
								if (proj0 * x20 + proj1 * x21 + proj2 * x22 < 0) ang1 *= -1;
							}

							newx00 = x00 * cos(ang1) + sin(ang1) * x20;
							newx20 = x20 * cos(ang1) - sin(ang1) * x00;
							x00 = newx00;
							x20 = newx20;

							newx01 = x01 * cos(ang1) + sin(ang1) * x21;
							newx21 = x21 * cos(ang1) - sin(ang1) * x01;
							x01 = newx01;
							x21 = newx21;

							newx02 = x02 * cos(ang1) + sin(ang1) * x22;
							newx22 = x22 * cos(ang1) - sin(ang1) * x02;
							x02 = newx02;
							x22 = newx22;




							dc = sqrt(pos0 * pos0 + pos1 * pos1 + pos2 * pos2);
							uhpy = 1 / dc;
							sxn = pos0 / dc;
							syn = pos1 / dc;
							szn = pos2 / dc;


							dotp = sxn * x00 + syn * x01 + szn * x02;

							vectmpx0 = sxn * dotp;
							vectmpx1 = syn * dotp;
							vectmpx2 = szn * dotp;

							x00 -= 2 * vectmpx0;
							x01 -= 2 * vectmpx1;
							x02 -= 2 * vectmpx2;


							dotp = sxn * x10 + syn * x11 + szn * x12;

							vectmpx0 = sxn * dotp;
							vectmpx1 = syn * dotp;
							vectmpx2 = szn * dotp;

							x10 -= 2 * vectmpx0;
							x11 -= 2 * vectmpx1;
							x12 -= 2 * vectmpx2;

							dotp = sxn * x20 + syn * x21 + szn * x22;

							vectmpx0 = sxn * dotp;
							vectmpx1 = syn * dotp;
							vectmpx2 = szn * dotp;

							x20 -= 2 * vectmpx0;
							x21 -= 2 * vectmpx1;
							x22 -= 2 * vectmpx2;


							sxn = -pos0 / dc;
							syn = -pos1 / dc;
							szn = -pos2 / dc;

							dotp = sxn * x00 + syn * x01 + szn * x02;
							leangle = acos(dotp);

							theta = M_PI / 2 - leangle;

							dist1 = asinh(tan(theta));
							ang = atan(sinh(distrem - dist1));

							lerayon = uhpy / sin(M_PI / 2 + theta);

							lex1 = lerayon * cos(M_PI / 2 + theta);

							lex2 = lerayon * cos(M_PI / 2 - ang);
							ley2 = lerayon * sin(M_PI / 2 - ang);

							sxn = -sxn;
							syn = -syn;
							szn = -szn;
							dotp = -dotp;
							leangle = acos(dotp);

							vecperp0 = x00 - dotp * sxn;
							vecperp1 = x01 - dotp * syn;
							vecperp2 = x02 - dotp * szn;

							vecperpn = sqrt(vecperp0 * vecperp0 + vecperp1 * vecperp1 + vecperp2 * vecperp2);

							vecperp0 /= vecperpn;
							vecperp1 /= vecperpn;
							vecperp2 /= vecperpn;


							exitlgt = lex2 - lex1;
							exitangle = fmod(exitlgt, bhsize);
							exitangle = (2 * M_PI / bhsize) * exitangle;
							newang = M_PI / 2 + ang;

							pos0 = cos(exitangle) * sxn + sin(exitangle) * vecperp0;
							pos1 = cos(exitangle) * syn + sin(exitangle) * vecperp1;
							pos2 = cos(exitangle) * szn + sin(exitangle) * vecperp2;

							pos0 *= 1 / ley2;
							pos1 *= 1 / ley2;
							pos2 *= 1 / ley2;

							newv0 = cos(M_PI + exitangle - newang) * sxn + sin(M_PI + exitangle - newang) * vecperp0;
							newv1 = cos(M_PI + exitangle - newang) * syn + sin(M_PI + exitangle - newang) * vecperp1;
							newv2 = cos(M_PI + exitangle - newang) * szn + sin(M_PI + exitangle - newang) * vecperp2;

							dotp1 = newv0 * x00 + newv1 * x01 + newv2 * x02;
							dotp2 = newv0 * x10 + newv1 * x11 + newv2 * x12;

							proj0 = x00 * dotp1 + x10 * dotp2;
							proj1 = x01 * dotp1 + x11 * dotp2;
							proj2 = x02 * dotp1 + x12 * dotp2;

							projn = sqrt(proj0 * proj0 + proj1 * proj1 + proj2 * proj2);

							proj0 /= projn;
							proj1 /= projn;
							proj2 /= projn;

							tmpl = proj0 * x00 + proj1 * x01 + proj2 * x02;
							if (abs(tmpl) > 1) ang1 = 0;
							else
							{
								ang1 = acos(tmpl);
								if (proj0 * x10 + proj1 * x11 + proj2 * x12 < 0) ang1 *= -1;
							}

							newx00 = x00 * cos(ang1) + sin(ang1) * x10;
							newx10 = x10 * cos(ang1) - sin(ang1) * x00;
							x00 = newx00;
							x10 = newx10;

							newx01 = x01 * cos(ang1) + sin(ang1) * x11;
							newx11 = x11 * cos(ang1) - sin(ang1) * x01;
							x01 = newx01;
							x11 = newx11;

							newx02 = x02 * cos(ang1) + sin(ang1) * x12;
							newx12 = x12 * cos(ang1) - sin(ang1) * x02;
							x02 = newx02;
							x12 = newx12;

							dotp1 = newv0 * x00 + newv1 * x01 + newv2 * x02;
							dotp2 = newv0 * x20 + newv1 * x21 + newv2 * x22;

							proj0 = x00 * dotp1 + x20 * dotp2;
							proj1 = x01 * dotp1 + x21 * dotp2;
							proj2 = x02 * dotp1 + x22 * dotp2;

							projn = sqrt(proj0 * proj0 + proj1 * proj1 + proj2 * proj2);

							proj0 /= projn;
							proj1 /= projn;
							proj2 /= projn;

							tmpl = proj0 * x00 + proj1 * x01 + proj2 * x02;
							if (abs(tmpl) > 1) ang1 = 0;
							else
							{
								ang1 = acos(tmpl);
								if (proj0 * x20 + proj1 * x21 + proj2 * x22 < 0) ang1 *= -1;
							}

							newx00 = x00 * cos(ang1) + sin(ang1) * x20;
							newx20 = x20 * cos(ang1) - sin(ang1) * x00;
							x00 = newx00;
							x20 = newx20;

							newx01 = x01 * cos(ang1) + sin(ang1) * x21;
							newx21 = x21 * cos(ang1) - sin(ang1) * x01;
							x01 = newx01;
							x21 = newx21;

							newx02 = x02 * cos(ang1) + sin(ang1) * x22;
							newx22 = x22 * cos(ang1) - sin(ang1) * x02;
							x02 = newx02;
							x22 = newx22;
						}

					}

					x00 = -x00;
					x01 = -x01;
					x02 = -x02;
				}
			}

        

        if (focus)
        {
            vec0 = dist * x00 + multy * x10 + multz * x20;
            vec1 = dist * x01 + multy * x11 + multz * x21;
            vec2 = dist * x02 + multy * x12 + multz * x22;

            addy0 = sqsz * x10;
            addy1 = sqsz * x11;
            addy2 = sqsz * x12;

            addz0 = -sqsz * x20;
            addz1 = -sqsz * x21;
            addz2 = -sqsz * x22;

            dc = sqrt(pos0 * pos0 + pos1 * pos1 + pos2 * pos2);
            uhpy = 1 / dc;

            cudathingy(pixels, flipg, dc, uhpy, pos0, pos1, pos2, vec0, vec1, vec2, addy0, addy1, addy2, addz0, addz1, addz2,bhsize, whsize);

            texture.update(pixels);
            sprite.setTexture(texture);
            window.draw(sprite);
            window.display();
        }
    }

    cudaExit();
    return 0;
}