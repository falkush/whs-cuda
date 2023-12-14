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
	double anglex, angley;
	double xl;

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

	double vectmpx0, vectmpx1, vectmpx2;
	double angx1, dist2, distrem;

	double leangle2;
	double dotpx1s, dotpx1vp, vecproj0, vecproj1, vecproj2, angf1, vecprojn, leangletmp;
	double levectmp0, levectmp1, levectmp2;

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
	pos1 = 0.001;

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

				anglex = 0.002 * mousx;
				angley = 0.002 * mousy;

				if (anglex < 0) anglex *= -1;
				if (angley < 0) angley *= -1;


				if (mousx > 0)
				{
					newx00 = x00 * cos(anglex) + sin(anglex) * x10;
					newx10 = x10 * cos(anglex) - sin(anglex) * x00;
					x00 = newx00;
					x10 = newx10;

					newx01 = x01 * cos(anglex) + sin(anglex) * x11;
					newx11 = x11 * cos(anglex) - sin(anglex) * x01;
					x01 = newx01;
					x11 = newx11;

					newx02 = x02 * cos(anglex) + sin(anglex) * x12;
					newx12 = x12 * cos(anglex) - sin(anglex) * x02;
					x02 = newx02;
					x12 = newx12;
				}
				else if (mousx < 0)
				{
					newx00 = x00 * cos(anglex) - sin(anglex) * x10;
					newx10 = x10 * cos(anglex) + sin(anglex) * x00;
					x00 = newx00;
					x10 = newx10;

					newx01 = x01 * cos(anglex) - sin(anglex) * x11;
					newx11 = x11 * cos(anglex) + sin(anglex) * x01;
					x01 = newx01;
					x11 = newx11;

					newx02 = x02 * cos(anglex) - sin(anglex) * x12;
					newx12 = x12 * cos(anglex) + sin(anglex) * x02;
					x02 = newx02;
					x12 = newx12;
				}

				if (mousy < 0)
				{
					newx00 = x00 * cos(angley) + sin(angley) * x20;
					newx20 = x20 * cos(angley) - sin(angley) * x00;
					x00 = newx00;
					x20 = newx20;

					newx01 = x01 * cos(angley) + sin(angley) * x21;
					newx21 = x21 * cos(angley) - sin(angley) * x01;
					x01 = newx01;
					x21 = newx21;

					newx02 = x02 * cos(angley) + sin(angley) * x22;
					newx22 = x22 * cos(angley) - sin(angley) * x02;
					x02 = newx02;
					x22 = newx22;
				}
				else if (mousy > 0)
				{
					newx00 = x00 * cos(angley) - sin(angley) * x20;
					newx20 = x20 * cos(angley) + sin(angley) * x00;
					x00 = newx00;
					x20 = newx20;

					newx01 = x01 * cos(angley) - sin(angley) * x21;
					newx21 = x21 * cos(angley) + sin(angley) * x01;
					x01 = newx01;
					x21 = newx21;

					newx02 = x02 * cos(angley) - sin(angley) * x22;
					newx22 = x22 * cos(angley) + sin(angley) * x02;
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
			pos0 = -5; pos1 = 0.001; pos2 = 0;
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

							leangle2 = M_PI + exitangle - newang;
							x00 = cos(leangle2) * sxn + sin(leangle2) * vecperp0;
							x01 = cos(leangle2) * syn + sin(leangle2) * vecperp1;
							x02 = cos(leangle2) * szn + sin(leangle2) * vecperp2;
							
							
							dotpx1s = x10 * sxn + x11 * syn + x12 * szn;
							dotpx1vp = x10 * vecperp0 + x11 * vecperp1 + x12 * vecperp2;

							vecproj0 = dotpx1s * sxn + dotpx1vp * vecperp0;
							vecproj1 = dotpx1s * syn + dotpx1vp * vecperp1;
							vecproj2 = dotpx1s * szn + dotpx1vp * vecperp2;

							vecprojn = sqrt(vecproj0 * vecproj0 + vecproj1 * vecproj1 + vecproj2 * vecproj2);
							 
							vecproj0 /= vecprojn;
							vecproj1 /= vecprojn;
							vecproj2 /= vecprojn;

							 
								
							angf1 = acos(vecproj0*sxn+vecproj1*syn+vecproj2*szn);
							if (vecproj0 * vecperp0 + vecproj1 * vecperp1 + vecproj2 * vecperp2 < 0) angf1 *= -1;

							
							leangletmp = angf1 + leangle2 - leangle;

							levectmp0 = cos(leangletmp) * sxn + sin(leangletmp) * vecperp0;
							levectmp1 = cos(leangletmp) * syn + sin(leangletmp) * vecperp1;
							levectmp2 = cos(leangletmp) * szn + sin(leangletmp) * vecperp2;

							levectmp0 *= vecprojn;
							levectmp1 *= vecprojn;
							levectmp2 *= vecprojn;

							vecproj0 *= vecprojn;
							vecproj1 *= vecprojn;
							vecproj2 *= vecprojn;

							x10 = x10 - vecproj0 + levectmp0;
							x11 = x11 - vecproj1 + levectmp1;
							x12 = x12 - vecproj2 + levectmp2;



							dotpx1s = x20 * sxn + x21 * syn + x22 * szn;
							dotpx1vp = x20 * vecperp0 + x21 * vecperp1 + x22 * vecperp2;

							vecproj0 = dotpx1s * sxn + dotpx1vp * vecperp0;
							vecproj1 = dotpx1s * syn + dotpx1vp * vecperp1;
							vecproj2 = dotpx1s * szn + dotpx1vp * vecperp2;

							vecprojn = sqrt(vecproj0 * vecproj0 + vecproj1 * vecproj1 + vecproj2 * vecproj2);
							 
							vecproj0 /= vecprojn;
							vecproj1 /= vecprojn;
							vecproj2 /= vecprojn;
							 

							angf1 = acos(vecproj0 * sxn + vecproj1 * syn + vecproj2 * szn);
							if (vecproj0 * vecperp0 + vecproj1 * vecperp1 + vecproj2 * vecperp2 < 0) angf1 *= -1;

							

							leangletmp = angf1 + leangle2 - leangle;

							levectmp0 = cos(leangletmp) * sxn + sin(leangletmp) * vecperp0;
							levectmp1 = cos(leangletmp) * syn + sin(leangletmp) * vecperp1;
							levectmp2 = cos(leangletmp) * szn + sin(leangletmp) * vecperp2;

							levectmp0 *= vecprojn;
							levectmp1 *= vecprojn;
							levectmp2 *= vecprojn;

							vecproj0 *= vecprojn;
							vecproj1 *= vecprojn;
							vecproj2 *= vecprojn;

							x20 = x20 - vecproj0 + levectmp0;
							x21 = x21 - vecproj1 + levectmp1;
							x22 = x22 - vecproj2 + levectmp2;

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

							leangle2 = M_PI + exitangle - newang;
							x00 = cos(leangle2) * sxn + sin(leangle2) * vecperp0;
							x01 = cos(leangle2) * syn + sin(leangle2) * vecperp1;
							x02 = cos(leangle2) * szn + sin(leangle2) * vecperp2;


							dotpx1s = x10 * sxn + x11 * syn + x12 * szn;
							dotpx1vp = x10 * vecperp0 + x11 * vecperp1 + x12 * vecperp2;

							vecproj0 = dotpx1s * sxn + dotpx1vp * vecperp0;
							vecproj1 = dotpx1s * syn + dotpx1vp * vecperp1;
							vecproj2 = dotpx1s * szn + dotpx1vp * vecperp2;

							vecprojn = sqrt(vecproj0 * vecproj0 + vecproj1 * vecproj1 + vecproj2 * vecproj2);
							 
							vecproj0 /= vecprojn;
							vecproj1 /= vecprojn;
							vecproj2 /= vecprojn;
							 
							angf1 = acos(vecproj0 * sxn + vecproj1 * syn + vecproj2 * szn);
							if (vecproj0 * vecperp0 + vecproj1 * vecperp1 + vecproj2 * vecperp2 < 0) angf1 *= -1;


							leangletmp = angf1 + leangle2 - leangle;

							levectmp0 = cos(leangletmp) * sxn + sin(leangletmp) * vecperp0;
							levectmp1 = cos(leangletmp) * syn + sin(leangletmp) * vecperp1;
							levectmp2 = cos(leangletmp) * szn + sin(leangletmp) * vecperp2;

							levectmp0 *= vecprojn;
							levectmp1 *= vecprojn;
							levectmp2 *= vecprojn;

							vecproj0 *= vecprojn;
							vecproj1 *= vecprojn;
							vecproj2 *= vecprojn;

							x10 = x10 - vecproj0 + levectmp0;
							x11 = x11 - vecproj1 + levectmp1;
							x12 = x12 - vecproj2 + levectmp2;



							dotpx1s = x20 * sxn + x21 * syn + x22 * szn;
							dotpx1vp = x20 * vecperp0 + x21 * vecperp1 + x22 * vecperp2;

							vecproj0 = dotpx1s * sxn + dotpx1vp * vecperp0;
							vecproj1 = dotpx1s * syn + dotpx1vp * vecperp1;
							vecproj2 = dotpx1s * szn + dotpx1vp * vecperp2;

							vecprojn = sqrt(vecproj0 * vecproj0 + vecproj1 * vecproj1 + vecproj2 * vecproj2);
							 
							vecproj0 /= vecprojn;
							vecproj1 /= vecprojn;
							vecproj2 /= vecprojn;
							 
							angf1 = acos(vecproj0 * sxn + vecproj1 * syn + vecproj2 * szn);
							if (vecproj0 * vecperp0 + vecproj1 * vecperp1 + vecproj2 * vecperp2 < 0) angf1 *= -1;



							leangletmp = angf1 + leangle2 - leangle;

							levectmp0 = cos(leangletmp) * sxn + sin(leangletmp) * vecperp0;
							levectmp1 = cos(leangletmp) * syn + sin(leangletmp) * vecperp1;
							levectmp2 = cos(leangletmp) * szn + sin(leangletmp) * vecperp2;

							levectmp0 *= vecprojn;
							levectmp1 *= vecprojn;
							levectmp2 *= vecprojn;

							vecproj0 *= vecprojn;
							vecproj1 *= vecprojn;
							vecproj2 *= vecprojn;

							x20 = x20 - vecproj0 + levectmp0;
							x21 = x21 - vecproj1 + levectmp1;
							x22 = x22 - vecproj2 + levectmp2;




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

							leangle2 = M_PI + exitangle - newang;
							x00 = cos(leangle2) * sxn + sin(leangle2) * vecperp0;
							x01 = cos(leangle2) * syn + sin(leangle2) * vecperp1;
							x02 = cos(leangle2) * szn + sin(leangle2) * vecperp2;


							dotpx1s = x10 * sxn + x11 * syn + x12 * szn;
							dotpx1vp = x10 * vecperp0 + x11 * vecperp1 + x12 * vecperp2;

							vecproj0 = dotpx1s * sxn + dotpx1vp * vecperp0;
							vecproj1 = dotpx1s * syn + dotpx1vp * vecperp1;
							vecproj2 = dotpx1s * szn + dotpx1vp * vecperp2;

							vecprojn = sqrt(vecproj0 * vecproj0 + vecproj1 * vecproj1 + vecproj2 * vecproj2);
							 
							vecproj0 /= vecprojn;
							vecproj1 /= vecprojn;
							vecproj2 /= vecprojn;
							 
							angf1 = acos(vecproj0 * sxn + vecproj1 * syn + vecproj2 * szn);
							if (vecproj0 * vecperp0 + vecproj1 * vecperp1 + vecproj2 * vecperp2 < 0) angf1 *= -1;


							leangletmp = angf1 + leangle2 - leangle;

							levectmp0 = cos(leangletmp) * sxn + sin(leangletmp) * vecperp0;
							levectmp1 = cos(leangletmp) * syn + sin(leangletmp) * vecperp1;
							levectmp2 = cos(leangletmp) * szn + sin(leangletmp) * vecperp2;

							levectmp0 *= vecprojn;
							levectmp1 *= vecprojn;
							levectmp2 *= vecprojn;

							vecproj0 *= vecprojn;
							vecproj1 *= vecprojn;
							vecproj2 *= vecprojn;

							x10 = x10 - vecproj0 + levectmp0;
							x11 = x11 - vecproj1 + levectmp1;
							x12 = x12 - vecproj2 + levectmp2;



							dotpx1s = x20 * sxn + x21 * syn + x22 * szn;
							dotpx1vp = x20 * vecperp0 + x21 * vecperp1 + x22 * vecperp2;

							vecproj0 = dotpx1s * sxn + dotpx1vp * vecperp0;
							vecproj1 = dotpx1s * syn + dotpx1vp * vecperp1;
							vecproj2 = dotpx1s * szn + dotpx1vp * vecperp2;

							vecprojn = sqrt(vecproj0 * vecproj0 + vecproj1 * vecproj1 + vecproj2 * vecproj2);
							 
							vecproj0 /= vecprojn;
							vecproj1 /= vecprojn;
							vecproj2 /= vecprojn;
							 
							angf1 = acos(vecproj0 * sxn + vecproj1 * syn + vecproj2 * szn);
							if (vecproj0 * vecperp0 + vecproj1 * vecperp1 + vecproj2 * vecperp2 < 0) angf1 *= -1;



							leangletmp = angf1 + leangle2 - leangle;

							levectmp0 = cos(leangletmp) * sxn + sin(leangletmp) * vecperp0;
							levectmp1 = cos(leangletmp) * syn + sin(leangletmp) * vecperp1;
							levectmp2 = cos(leangletmp) * szn + sin(leangletmp) * vecperp2;

							levectmp0 *= vecprojn;
							levectmp1 *= vecprojn;
							levectmp2 *= vecprojn;

							vecproj0 *= vecprojn;
							vecproj1 *= vecprojn;
							vecproj2 *= vecprojn;

							x20 = x20 - vecproj0 + levectmp0;
							x21 = x21 - vecproj1 + levectmp1;
							x22 = x22 - vecproj2 + levectmp2;
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

							leangle2 = M_PI + exitangle - newang;
							x00 = cos(leangle2) * sxn + sin(leangle2) * vecperp0;
							x01 = cos(leangle2) * syn + sin(leangle2) * vecperp1;
							x02 = cos(leangle2) * szn + sin(leangle2) * vecperp2;


							dotpx1s = x10 * sxn + x11 * syn + x12 * szn;
							dotpx1vp = x10 * vecperp0 + x11 * vecperp1 + x12 * vecperp2;

							vecproj0 = dotpx1s * sxn + dotpx1vp * vecperp0;
							vecproj1 = dotpx1s * syn + dotpx1vp * vecperp1;
							vecproj2 = dotpx1s * szn + dotpx1vp * vecperp2;

							vecprojn = sqrt(vecproj0 * vecproj0 + vecproj1 * vecproj1 + vecproj2 * vecproj2);
							 

							vecproj0 /= vecprojn;
							vecproj1 /= vecprojn;
							vecproj2 /= vecprojn;
							 
							angf1 = acos(vecproj0 * sxn + vecproj1 * syn + vecproj2 * szn);
							if (vecproj0 * vecperp0 + vecproj1 * vecperp1 + vecproj2 * vecperp2 < 0) angf1 *= -1;


							leangletmp = angf1 + leangle2 - leangle;

							levectmp0 = cos(leangletmp) * sxn + sin(leangletmp) * vecperp0;
							levectmp1 = cos(leangletmp) * syn + sin(leangletmp) * vecperp1;
							levectmp2 = cos(leangletmp) * szn + sin(leangletmp) * vecperp2;

							levectmp0 *= vecprojn;
							levectmp1 *= vecprojn;
							levectmp2 *= vecprojn;

							vecproj0 *= vecprojn;
							vecproj1 *= vecprojn;
							vecproj2 *= vecprojn;

							x10 = x10 - vecproj0 + levectmp0;
							x11 = x11 - vecproj1 + levectmp1;
							x12 = x12 - vecproj2 + levectmp2;



							dotpx1s = x20 * sxn + x21 * syn + x22 * szn;
							dotpx1vp = x20 * vecperp0 + x21 * vecperp1 + x22 * vecperp2;

							vecproj0 = dotpx1s * sxn + dotpx1vp * vecperp0;
							vecproj1 = dotpx1s * syn + dotpx1vp * vecperp1;
							vecproj2 = dotpx1s * szn + dotpx1vp * vecperp2;

							vecprojn = sqrt(vecproj0 * vecproj0 + vecproj1 * vecproj1 + vecproj2 * vecproj2);
							 
							vecproj0 /= vecprojn;
							vecproj1 /= vecprojn;
							vecproj2 /= vecprojn;
							 
							angf1 = acos(vecproj0 * sxn + vecproj1 * syn + vecproj2 * szn);
							if (vecproj0 * vecperp0 + vecproj1 * vecperp1 + vecproj2 * vecperp2 < 0) angf1 *= -1;



							leangletmp = angf1 + leangle2 - leangle;

							levectmp0 = cos(leangletmp) * sxn + sin(leangletmp) * vecperp0;
							levectmp1 = cos(leangletmp) * syn + sin(leangletmp) * vecperp1;
							levectmp2 = cos(leangletmp) * szn + sin(leangletmp) * vecperp2;

							levectmp0 *= vecprojn;
							levectmp1 *= vecprojn;
							levectmp2 *= vecprojn;

							vecproj0 *= vecprojn;
							vecproj1 *= vecprojn;
							vecproj2 *= vecprojn;

							x20 = x20 - vecproj0 + levectmp0;
							x21 = x21 - vecproj1 + levectmp1;
							x22 = x22 - vecproj2 + levectmp2;
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

							leangle2 = M_PI + exitangle - newang;
							x00 = cos(leangle2) * sxn + sin(leangle2) * vecperp0;
							x01 = cos(leangle2) * syn + sin(leangle2) * vecperp1;
							x02 = cos(leangle2) * szn + sin(leangle2) * vecperp2;


							dotpx1s = x10 * sxn + x11 * syn + x12 * szn;
							dotpx1vp = x10 * vecperp0 + x11 * vecperp1 + x12 * vecperp2;

							vecproj0 = dotpx1s * sxn + dotpx1vp * vecperp0;
							vecproj1 = dotpx1s * syn + dotpx1vp * vecperp1;
							vecproj2 = dotpx1s * szn + dotpx1vp * vecperp2;

							vecprojn = sqrt(vecproj0 * vecproj0 + vecproj1 * vecproj1 + vecproj2 * vecproj2);
							 
							vecproj0 /= vecprojn;
							vecproj1 /= vecprojn;
							vecproj2 /= vecprojn;
							 
							angf1 = acos(vecproj0 * sxn + vecproj1 * syn + vecproj2 * szn);
							if (vecproj0 * vecperp0 + vecproj1 * vecperp1 + vecproj2 * vecperp2 < 0) angf1 *= -1;


							leangletmp = angf1 + leangle2 - leangle;

							levectmp0 = cos(leangletmp) * sxn + sin(leangletmp) * vecperp0;
							levectmp1 = cos(leangletmp) * syn + sin(leangletmp) * vecperp1;
							levectmp2 = cos(leangletmp) * szn + sin(leangletmp) * vecperp2;

							levectmp0 *= vecprojn;
							levectmp1 *= vecprojn;
							levectmp2 *= vecprojn;

							vecproj0 *= vecprojn;
							vecproj1 *= vecprojn;
							vecproj2 *= vecprojn;

							x10 = x10 - vecproj0 + levectmp0;
							x11 = x11 - vecproj1 + levectmp1;
							x12 = x12 - vecproj2 + levectmp2;



							dotpx1s = x20 * sxn + x21 * syn + x22 * szn;
							dotpx1vp = x20 * vecperp0 + x21 * vecperp1 + x22 * vecperp2;

							vecproj0 = dotpx1s * sxn + dotpx1vp * vecperp0;
							vecproj1 = dotpx1s * syn + dotpx1vp * vecperp1;
							vecproj2 = dotpx1s * szn + dotpx1vp * vecperp2;

							vecprojn = sqrt(vecproj0 * vecproj0 + vecproj1 * vecproj1 + vecproj2 * vecproj2);
							 
							vecproj0 /= vecprojn;
							vecproj1 /= vecprojn;
							vecproj2 /= vecprojn;
							 
							angf1 = acos(vecproj0 * sxn + vecproj1 * syn + vecproj2 * szn);
							if (vecproj0 * vecperp0 + vecproj1 * vecperp1 + vecproj2 * vecperp2 < 0) angf1 *= -1;



							leangletmp = angf1 + leangle2 - leangle;

							levectmp0 = cos(leangletmp) * sxn + sin(leangletmp) * vecperp0;
							levectmp1 = cos(leangletmp) * syn + sin(leangletmp) * vecperp1;
							levectmp2 = cos(leangletmp) * szn + sin(leangletmp) * vecperp2;

							levectmp0 *= vecprojn;
							levectmp1 *= vecprojn;
							levectmp2 *= vecprojn;

							vecproj0 *= vecprojn;
							vecproj1 *= vecprojn;
							vecproj2 *= vecprojn;

							x20 = x20 - vecproj0 + levectmp0;
							x21 = x21 - vecproj1 + levectmp1;
							x22 = x22 - vecproj2 + levectmp2;




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

							leangle2 = M_PI + exitangle - newang;
							x00 = cos(leangle2) * sxn + sin(leangle2) * vecperp0;
							x01 = cos(leangle2) * syn + sin(leangle2) * vecperp1;
							x02 = cos(leangle2) * szn + sin(leangle2) * vecperp2;


							dotpx1s = x10 * sxn + x11 * syn + x12 * szn;
							dotpx1vp = x10 * vecperp0 + x11 * vecperp1 + x12 * vecperp2;

							vecproj0 = dotpx1s * sxn + dotpx1vp * vecperp0;
							vecproj1 = dotpx1s * syn + dotpx1vp * vecperp1;
							vecproj2 = dotpx1s * szn + dotpx1vp * vecperp2;

							vecprojn = sqrt(vecproj0 * vecproj0 + vecproj1 * vecproj1 + vecproj2 * vecproj2);
							 
							vecproj0 /= vecprojn;
							vecproj1 /= vecprojn;
							vecproj2 /= vecprojn;
							 
							angf1 = acos(vecproj0 * sxn + vecproj1 * syn + vecproj2 * szn);
							if (vecproj0 * vecperp0 + vecproj1 * vecperp1 + vecproj2 * vecperp2 < 0) angf1 *= -1;


							leangletmp = angf1 + leangle2 - leangle;

							levectmp0 = cos(leangletmp) * sxn + sin(leangletmp) * vecperp0;
							levectmp1 = cos(leangletmp) * syn + sin(leangletmp) * vecperp1;
							levectmp2 = cos(leangletmp) * szn + sin(leangletmp) * vecperp2;

							levectmp0 *= vecprojn;
							levectmp1 *= vecprojn;
							levectmp2 *= vecprojn;

							vecproj0 *= vecprojn;
							vecproj1 *= vecprojn;
							vecproj2 *= vecprojn;

							x10 = x10 - vecproj0 + levectmp0;
							x11 = x11 - vecproj1 + levectmp1;
							x12 = x12 - vecproj2 + levectmp2;



							dotpx1s = x20 * sxn + x21 * syn + x22 * szn;
							dotpx1vp = x20 * vecperp0 + x21 * vecperp1 + x22 * vecperp2;

							vecproj0 = dotpx1s * sxn + dotpx1vp * vecperp0;
							vecproj1 = dotpx1s * syn + dotpx1vp * vecperp1;
							vecproj2 = dotpx1s * szn + dotpx1vp * vecperp2;

							vecprojn = sqrt(vecproj0 * vecproj0 + vecproj1 * vecproj1 + vecproj2 * vecproj2);
							 
							vecproj0 /= vecprojn;
							vecproj1 /= vecprojn;
							vecproj2 /= vecprojn;
							 
							angf1 = acos(vecproj0 * sxn + vecproj1 * syn + vecproj2 * szn);
							if (vecproj0 * vecperp0 + vecproj1 * vecperp1 + vecproj2 * vecperp2 < 0) angf1 *= -1;



							leangletmp = angf1 + leangle2 - leangle;

							levectmp0 = cos(leangletmp) * sxn + sin(leangletmp) * vecperp0;
							levectmp1 = cos(leangletmp) * syn + sin(leangletmp) * vecperp1;
							levectmp2 = cos(leangletmp) * szn + sin(leangletmp) * vecperp2;

							levectmp0 *= vecprojn;
							levectmp1 *= vecprojn;
							levectmp2 *= vecprojn;

							vecproj0 *= vecprojn;
							vecproj1 *= vecprojn;
							vecproj2 *= vecprojn;

							x20 = x20 - vecproj0 + levectmp0;
							x21 = x21 - vecproj1 + levectmp1;
							x22 = x22 - vecproj2 + levectmp2;
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

							leangle2 = M_PI + exitangle - newang;
							x00 = cos(leangle2) * sxn + sin(leangle2) * vecperp0;
							x01 = cos(leangle2) * syn + sin(leangle2) * vecperp1;
							x02 = cos(leangle2) * szn + sin(leangle2) * vecperp2;


							dotpx1s = x10 * sxn + x11 * syn + x12 * szn;
							dotpx1vp = x10 * vecperp0 + x11 * vecperp1 + x12 * vecperp2;

							vecproj0 = dotpx1s * sxn + dotpx1vp * vecperp0;
							vecproj1 = dotpx1s * syn + dotpx1vp * vecperp1;
							vecproj2 = dotpx1s * szn + dotpx1vp * vecperp2;

							vecprojn = sqrt(vecproj0 * vecproj0 + vecproj1 * vecproj1 + vecproj2 * vecproj2);
							 
							vecproj0 /= vecprojn;
							vecproj1 /= vecprojn;
							vecproj2 /= vecprojn;
							 
							angf1 = acos(vecproj0 * sxn + vecproj1 * syn + vecproj2 * szn);
							if (vecproj0 * vecperp0 + vecproj1 * vecperp1 + vecproj2 * vecperp2 < 0) angf1 *= -1;


							leangletmp = angf1 + leangle2 - leangle;

							levectmp0 = cos(leangletmp) * sxn + sin(leangletmp) * vecperp0;
							levectmp1 = cos(leangletmp) * syn + sin(leangletmp) * vecperp1;
							levectmp2 = cos(leangletmp) * szn + sin(leangletmp) * vecperp2;

							levectmp0 *= vecprojn;
							levectmp1 *= vecprojn;
							levectmp2 *= vecprojn;

							vecproj0 *= vecprojn;
							vecproj1 *= vecprojn;
							vecproj2 *= vecprojn;

							x10 = x10 - vecproj0 + levectmp0;
							x11 = x11 - vecproj1 + levectmp1;
							x12 = x12 - vecproj2 + levectmp2;



							dotpx1s = x20 * sxn + x21 * syn + x22 * szn;
							dotpx1vp = x20 * vecperp0 + x21 * vecperp1 + x22 * vecperp2;

							vecproj0 = dotpx1s * sxn + dotpx1vp * vecperp0;
							vecproj1 = dotpx1s * syn + dotpx1vp * vecperp1;
							vecproj2 = dotpx1s * szn + dotpx1vp * vecperp2;

							vecprojn = sqrt(vecproj0 * vecproj0 + vecproj1 * vecproj1 + vecproj2 * vecproj2);
							 
							vecproj0 /= vecprojn;
							vecproj1 /= vecprojn;
							vecproj2 /= vecprojn;
							 
							angf1 = acos(vecproj0 * sxn + vecproj1 * syn + vecproj2 * szn);
							if (vecproj0 * vecperp0 + vecproj1 * vecperp1 + vecproj2 * vecperp2 < 0) angf1 *= -1;



							leangletmp = angf1 + leangle2 - leangle;

							levectmp0 = cos(leangletmp) * sxn + sin(leangletmp) * vecperp0;
							levectmp1 = cos(leangletmp) * syn + sin(leangletmp) * vecperp1;
							levectmp2 = cos(leangletmp) * szn + sin(leangletmp) * vecperp2;

							levectmp0 *= vecprojn;
							levectmp1 *= vecprojn;
							levectmp2 *= vecprojn;

							vecproj0 *= vecprojn;
							vecproj1 *= vecprojn;
							vecproj2 *= vecprojn;

							x20 = x20 - vecproj0 + levectmp0;
							x21 = x21 - vecproj1 + levectmp1;
							x22 = x22 - vecproj2 + levectmp2;
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

							leangle2 = M_PI + exitangle - newang;
							x00 = cos(leangle2) * sxn + sin(leangle2) * vecperp0;
							x01 = cos(leangle2) * syn + sin(leangle2) * vecperp1;
							x02 = cos(leangle2) * szn + sin(leangle2) * vecperp2;


							dotpx1s = x10 * sxn + x11 * syn + x12 * szn;
							dotpx1vp = x10 * vecperp0 + x11 * vecperp1 + x12 * vecperp2;

							vecproj0 = dotpx1s * sxn + dotpx1vp * vecperp0;
							vecproj1 = dotpx1s * syn + dotpx1vp * vecperp1;
							vecproj2 = dotpx1s * szn + dotpx1vp * vecperp2;

							vecprojn = sqrt(vecproj0 * vecproj0 + vecproj1 * vecproj1 + vecproj2 * vecproj2);
							 
							vecproj0 /= vecprojn;
							vecproj1 /= vecprojn;
							vecproj2 /= vecprojn;
							 
							angf1 = acos(vecproj0 * sxn + vecproj1 * syn + vecproj2 * szn);
							if (vecproj0 * vecperp0 + vecproj1 * vecperp1 + vecproj2 * vecperp2 < 0) angf1 *= -1;


							leangletmp = angf1 + leangle2 - leangle;

							levectmp0 = cos(leangletmp) * sxn + sin(leangletmp) * vecperp0;
							levectmp1 = cos(leangletmp) * syn + sin(leangletmp) * vecperp1;
							levectmp2 = cos(leangletmp) * szn + sin(leangletmp) * vecperp2;

							levectmp0 *= vecprojn;
							levectmp1 *= vecprojn;
							levectmp2 *= vecprojn;

							vecproj0 *= vecprojn;
							vecproj1 *= vecprojn;
							vecproj2 *= vecprojn;

							x10 = x10 - vecproj0 + levectmp0;
							x11 = x11 - vecproj1 + levectmp1;
							x12 = x12 - vecproj2 + levectmp2;



							dotpx1s = x20 * sxn + x21 * syn + x22 * szn;
							dotpx1vp = x20 * vecperp0 + x21 * vecperp1 + x22 * vecperp2;

							vecproj0 = dotpx1s * sxn + dotpx1vp * vecperp0;
							vecproj1 = dotpx1s * syn + dotpx1vp * vecperp1;
							vecproj2 = dotpx1s * szn + dotpx1vp * vecperp2;

							vecprojn = sqrt(vecproj0 * vecproj0 + vecproj1 * vecproj1 + vecproj2 * vecproj2);
							 
							vecproj0 /= vecprojn;
							vecproj1 /= vecprojn;
							vecproj2 /= vecprojn;
							 
							angf1 = acos(vecproj0 * sxn + vecproj1 * syn + vecproj2 * szn);
							if (vecproj0 * vecperp0 + vecproj1 * vecperp1 + vecproj2 * vecperp2 < 0) angf1 *= -1;



							leangletmp = angf1 + leangle2 - leangle;

							levectmp0 = cos(leangletmp) * sxn + sin(leangletmp) * vecperp0;
							levectmp1 = cos(leangletmp) * syn + sin(leangletmp) * vecperp1;
							levectmp2 = cos(leangletmp) * szn + sin(leangletmp) * vecperp2;

							levectmp0 *= vecprojn;
							levectmp1 *= vecprojn;
							levectmp2 *= vecprojn;

							vecproj0 *= vecprojn;
							vecproj1 *= vecprojn;
							vecproj2 *= vecprojn;

							x20 = x20 - vecproj0 + levectmp0;
							x21 = x21 - vecproj1 + levectmp1;
							x22 = x22 - vecproj2 + levectmp2;




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

							leangle2 = M_PI + exitangle - newang;
							x00 = cos(leangle2) * sxn + sin(leangle2) * vecperp0;
							x01 = cos(leangle2) * syn + sin(leangle2) * vecperp1;
							x02 = cos(leangle2) * szn + sin(leangle2) * vecperp2;


							dotpx1s = x10 * sxn + x11 * syn + x12 * szn;
							dotpx1vp = x10 * vecperp0 + x11 * vecperp1 + x12 * vecperp2;

							vecproj0 = dotpx1s * sxn + dotpx1vp * vecperp0;
							vecproj1 = dotpx1s * syn + dotpx1vp * vecperp1;
							vecproj2 = dotpx1s * szn + dotpx1vp * vecperp2;

							vecprojn = sqrt(vecproj0 * vecproj0 + vecproj1 * vecproj1 + vecproj2 * vecproj2);
							 
							vecproj0 /= vecprojn;
							vecproj1 /= vecprojn;
							vecproj2 /= vecprojn;
							 
							angf1 = acos(vecproj0 * sxn + vecproj1 * syn + vecproj2 * szn);
							if (vecproj0 * vecperp0 + vecproj1 * vecperp1 + vecproj2 * vecperp2 < 0) angf1 *= -1;


							leangletmp = angf1 + leangle2 - leangle;

							levectmp0 = cos(leangletmp) * sxn + sin(leangletmp) * vecperp0;
							levectmp1 = cos(leangletmp) * syn + sin(leangletmp) * vecperp1;
							levectmp2 = cos(leangletmp) * szn + sin(leangletmp) * vecperp2;

							levectmp0 *= vecprojn;
							levectmp1 *= vecprojn;
							levectmp2 *= vecprojn;

							vecproj0 *= vecprojn;
							vecproj1 *= vecprojn;
							vecproj2 *= vecprojn;

							x10 = x10 - vecproj0 + levectmp0;
							x11 = x11 - vecproj1 + levectmp1;
							x12 = x12 - vecproj2 + levectmp2;



							dotpx1s = x20 * sxn + x21 * syn + x22 * szn;
							dotpx1vp = x20 * vecperp0 + x21 * vecperp1 + x22 * vecperp2;

							vecproj0 = dotpx1s * sxn + dotpx1vp * vecperp0;
							vecproj1 = dotpx1s * syn + dotpx1vp * vecperp1;
							vecproj2 = dotpx1s * szn + dotpx1vp * vecperp2;

							vecprojn = sqrt(vecproj0 * vecproj0 + vecproj1 * vecproj1 + vecproj2 * vecproj2);
							 
							vecproj0 /= vecprojn;
							vecproj1 /= vecprojn;
							vecproj2 /= vecprojn;
							 
							angf1 = acos(vecproj0 * sxn + vecproj1 * syn + vecproj2 * szn);
							if (vecproj0 * vecperp0 + vecproj1 * vecperp1 + vecproj2 * vecperp2 < 0) angf1 *= -1;



							leangletmp = angf1 + leangle2 - leangle;

							levectmp0 = cos(leangletmp) * sxn + sin(leangletmp) * vecperp0;
							levectmp1 = cos(leangletmp) * syn + sin(leangletmp) * vecperp1;
							levectmp2 = cos(leangletmp) * szn + sin(leangletmp) * vecperp2;

							levectmp0 *= vecprojn;
							levectmp1 *= vecprojn;
							levectmp2 *= vecprojn;

							vecproj0 *= vecprojn;
							vecproj1 *= vecprojn;
							vecproj2 *= vecprojn;

							x20 = x20 - vecproj0 + levectmp0;
							x21 = x21 - vecproj1 + levectmp1;
							x22 = x22 - vecproj2 + levectmp2;
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

							leangle2 = M_PI + exitangle - newang;
							x00 = cos(leangle2) * sxn + sin(leangle2) * vecperp0;
							x01 = cos(leangle2) * syn + sin(leangle2) * vecperp1;
							x02 = cos(leangle2) * szn + sin(leangle2) * vecperp2;


							dotpx1s = x10 * sxn + x11 * syn + x12 * szn;
							dotpx1vp = x10 * vecperp0 + x11 * vecperp1 + x12 * vecperp2;

							vecproj0 = dotpx1s * sxn + dotpx1vp * vecperp0;
							vecproj1 = dotpx1s * syn + dotpx1vp * vecperp1;
							vecproj2 = dotpx1s * szn + dotpx1vp * vecperp2;

							vecprojn = sqrt(vecproj0 * vecproj0 + vecproj1 * vecproj1 + vecproj2 * vecproj2);
							 
							vecproj0 /= vecprojn;
							vecproj1 /= vecprojn;
							vecproj2 /= vecprojn;
							 
							angf1 = acos(vecproj0 * sxn + vecproj1 * syn + vecproj2 * szn);
							if (vecproj0 * vecperp0 + vecproj1 * vecperp1 + vecproj2 * vecperp2 < 0) angf1 *= -1;


							leangletmp = angf1 + leangle2 - leangle;

							levectmp0 = cos(leangletmp) * sxn + sin(leangletmp) * vecperp0;
							levectmp1 = cos(leangletmp) * syn + sin(leangletmp) * vecperp1;
							levectmp2 = cos(leangletmp) * szn + sin(leangletmp) * vecperp2;

							levectmp0 *= vecprojn;
							levectmp1 *= vecprojn;
							levectmp2 *= vecprojn;

							vecproj0 *= vecprojn;
							vecproj1 *= vecprojn;
							vecproj2 *= vecprojn;

							x10 = x10 - vecproj0 + levectmp0;
							x11 = x11 - vecproj1 + levectmp1;
							x12 = x12 - vecproj2 + levectmp2;



							dotpx1s = x20 * sxn + x21 * syn + x22 * szn;
							dotpx1vp = x20 * vecperp0 + x21 * vecperp1 + x22 * vecperp2;

							vecproj0 = dotpx1s * sxn + dotpx1vp * vecperp0;
							vecproj1 = dotpx1s * syn + dotpx1vp * vecperp1;
							vecproj2 = dotpx1s * szn + dotpx1vp * vecperp2;

							vecprojn = sqrt(vecproj0 * vecproj0 + vecproj1 * vecproj1 + vecproj2 * vecproj2);
							 
							vecproj0 /= vecprojn;
							vecproj1 /= vecprojn;
							vecproj2 /= vecprojn;
							 
							angf1 = acos(vecproj0 * sxn + vecproj1 * syn + vecproj2 * szn);
							if (vecproj0 * vecperp0 + vecproj1 * vecperp1 + vecproj2 * vecperp2 < 0) angf1 *= -1;



							leangletmp = angf1 + leangle2 - leangle;

							levectmp0 = cos(leangletmp) * sxn + sin(leangletmp) * vecperp0;
							levectmp1 = cos(leangletmp) * syn + sin(leangletmp) * vecperp1;
							levectmp2 = cos(leangletmp) * szn + sin(leangletmp) * vecperp2;

							levectmp0 *= vecprojn;
							levectmp1 *= vecprojn;
							levectmp2 *= vecprojn;

							vecproj0 *= vecprojn;
							vecproj1 *= vecprojn;
							vecproj2 *= vecprojn;

							x20 = x20 - vecproj0 + levectmp0;
							x21 = x21 - vecproj1 + levectmp1;
							x22 = x22 - vecproj2 + levectmp2;

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

							leangle2 = M_PI + exitangle - newang;
							x00 = cos(leangle2) * sxn + sin(leangle2) * vecperp0;
							x01 = cos(leangle2) * syn + sin(leangle2) * vecperp1;
							x02 = cos(leangle2) * szn + sin(leangle2) * vecperp2;


							dotpx1s = x10 * sxn + x11 * syn + x12 * szn;
							dotpx1vp = x10 * vecperp0 + x11 * vecperp1 + x12 * vecperp2;

							vecproj0 = dotpx1s * sxn + dotpx1vp * vecperp0;
							vecproj1 = dotpx1s * syn + dotpx1vp * vecperp1;
							vecproj2 = dotpx1s * szn + dotpx1vp * vecperp2;

							vecprojn = sqrt(vecproj0 * vecproj0 + vecproj1 * vecproj1 + vecproj2 * vecproj2);
							 
							vecproj0 /= vecprojn;
							vecproj1 /= vecprojn;
							vecproj2 /= vecprojn;
							 
							angf1 = acos(vecproj0 * sxn + vecproj1 * syn + vecproj2 * szn);
							if (vecproj0 * vecperp0 + vecproj1 * vecperp1 + vecproj2 * vecperp2 < 0) angf1 *= -1;


							leangletmp = angf1 + leangle2 - leangle;

							levectmp0 = cos(leangletmp) * sxn + sin(leangletmp) * vecperp0;
							levectmp1 = cos(leangletmp) * syn + sin(leangletmp) * vecperp1;
							levectmp2 = cos(leangletmp) * szn + sin(leangletmp) * vecperp2;

							levectmp0 *= vecprojn;
							levectmp1 *= vecprojn;
							levectmp2 *= vecprojn;

							vecproj0 *= vecprojn;
							vecproj1 *= vecprojn;
							vecproj2 *= vecprojn;

							x10 = x10 - vecproj0 + levectmp0;
							x11 = x11 - vecproj1 + levectmp1;
							x12 = x12 - vecproj2 + levectmp2;



							dotpx1s = x20 * sxn + x21 * syn + x22 * szn;
							dotpx1vp = x20 * vecperp0 + x21 * vecperp1 + x22 * vecperp2;

							vecproj0 = dotpx1s * sxn + dotpx1vp * vecperp0;
							vecproj1 = dotpx1s * syn + dotpx1vp * vecperp1;
							vecproj2 = dotpx1s * szn + dotpx1vp * vecperp2;

							vecprojn = sqrt(vecproj0 * vecproj0 + vecproj1 * vecproj1 + vecproj2 * vecproj2);
							 
							vecproj0 /= vecprojn;
							vecproj1 /= vecprojn;
							vecproj2 /= vecprojn;
							 
							angf1 = acos(vecproj0 * sxn + vecproj1 * syn + vecproj2 * szn);
							if (vecproj0 * vecperp0 + vecproj1 * vecperp1 + vecproj2 * vecperp2 < 0) angf1 *= -1;



							leangletmp = angf1 + leangle2 - leangle;

							levectmp0 = cos(leangletmp) * sxn + sin(leangletmp) * vecperp0;
							levectmp1 = cos(leangletmp) * syn + sin(leangletmp) * vecperp1;
							levectmp2 = cos(leangletmp) * szn + sin(leangletmp) * vecperp2;

							levectmp0 *= vecprojn;
							levectmp1 *= vecprojn;
							levectmp2 *= vecprojn;

							vecproj0 *= vecprojn;
							vecproj1 *= vecprojn;
							vecproj2 *= vecprojn;

							x20 = x20 - vecproj0 + levectmp0;
							x21 = x21 - vecproj1 + levectmp1;
							x22 = x22 - vecproj2 + levectmp2;




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

							leangle2 = M_PI + exitangle - newang;
							x00 = cos(leangle2) * sxn + sin(leangle2) * vecperp0;
							x01 = cos(leangle2) * syn + sin(leangle2) * vecperp1;
							x02 = cos(leangle2) * szn + sin(leangle2) * vecperp2;


							dotpx1s = x10 * sxn + x11 * syn + x12 * szn;
							dotpx1vp = x10 * vecperp0 + x11 * vecperp1 + x12 * vecperp2;

							vecproj0 = dotpx1s * sxn + dotpx1vp * vecperp0;
							vecproj1 = dotpx1s * syn + dotpx1vp * vecperp1;
							vecproj2 = dotpx1s * szn + dotpx1vp * vecperp2;

							vecprojn = sqrt(vecproj0 * vecproj0 + vecproj1 * vecproj1 + vecproj2 * vecproj2);
							 
							vecproj0 /= vecprojn;
							vecproj1 /= vecprojn;
							vecproj2 /= vecprojn;
							 
							angf1 = acos(vecproj0 * sxn + vecproj1 * syn + vecproj2 * szn);
							if (vecproj0 * vecperp0 + vecproj1 * vecperp1 + vecproj2 * vecperp2 < 0) angf1 *= -1;


							leangletmp = angf1 + leangle2 - leangle;

							levectmp0 = cos(leangletmp) * sxn + sin(leangletmp) * vecperp0;
							levectmp1 = cos(leangletmp) * syn + sin(leangletmp) * vecperp1;
							levectmp2 = cos(leangletmp) * szn + sin(leangletmp) * vecperp2;

							levectmp0 *= vecprojn;
							levectmp1 *= vecprojn;
							levectmp2 *= vecprojn;

							vecproj0 *= vecprojn;
							vecproj1 *= vecprojn;
							vecproj2 *= vecprojn;

							x10 = x10 - vecproj0 + levectmp0;
							x11 = x11 - vecproj1 + levectmp1;
							x12 = x12 - vecproj2 + levectmp2;



							dotpx1s = x20 * sxn + x21 * syn + x22 * szn;
							dotpx1vp = x20 * vecperp0 + x21 * vecperp1 + x22 * vecperp2;

							vecproj0 = dotpx1s * sxn + dotpx1vp * vecperp0;
							vecproj1 = dotpx1s * syn + dotpx1vp * vecperp1;
							vecproj2 = dotpx1s * szn + dotpx1vp * vecperp2;

							vecprojn = sqrt(vecproj0 * vecproj0 + vecproj1 * vecproj1 + vecproj2 * vecproj2);
							 
							vecproj0 /= vecprojn;
							vecproj1 /= vecprojn;
							vecproj2 /= vecprojn;
							 
							angf1 = acos(vecproj0 * sxn + vecproj1 * syn + vecproj2 * szn);
							if (vecproj0 * vecperp0 + vecproj1 * vecperp1 + vecproj2 * vecperp2 < 0) angf1 *= -1;



							leangletmp = angf1 + leangle2 - leangle;

							levectmp0 = cos(leangletmp) * sxn + sin(leangletmp) * vecperp0;
							levectmp1 = cos(leangletmp) * syn + sin(leangletmp) * vecperp1;
							levectmp2 = cos(leangletmp) * szn + sin(leangletmp) * vecperp2;

							levectmp0 *= vecprojn;
							levectmp1 *= vecprojn;
							levectmp2 *= vecprojn;

							vecproj0 *= vecprojn;
							vecproj1 *= vecprojn;
							vecproj2 *= vecprojn;

							x20 = x20 - vecproj0 + levectmp0;
							x21 = x21 - vecproj1 + levectmp1;
							x22 = x22 - vecproj2 + levectmp2;
						}

					}

					x00 = -x00;
					x01 = -x01;
					x02 = -x02;
				}
			}

        

        if (focus)
        {
			xl = sqrt(x00 * x00 + x01 * x01 + x02 * x02);
			x00 /= xl;
			x01 /= xl;
			x02 /= xl;

			dotp = x00 * x10 + x01 * x11 + x02 * x12;

			x10 = x10 - x00 * dotp;
			x11 = x11 - x01 * dotp;
			x12 = x12 - x02 * dotp;

			xl = sqrt(x10 * x10 + x11 * x11 + x12 * x12);
			x10 /= xl;
			x11 /= xl;
			x12 /= xl;

			dotp = x00 * x20 + x01 * x21 + x02 * x22;

			x20 = x20 - x00 * dotp;
			x21 = x21 - x01 * dotp;
			x22 = x22 - x02 * dotp;

			dotp = x10 * x20 + x11 * x21 + x12 * x22;

			x20 = x20 - x10 * dotp;
			x21 = x21 - x11 * dotp;
			x22 = x22 - x12 * dotp;

			xl = sqrt(x20 * x20 + x21 * x21 + x22 * x22);
			x20 /= xl;
			x21 /= xl;
			x22 /= xl;

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