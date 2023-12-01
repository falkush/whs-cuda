#define _USE_MATH_DEFINES

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <math.h>


static uint8_t* buffer=0;
static double* vecl=0;

__global__ void addKernel(uint8_t* buffer, double* vecl, bool flipg, double dc, double uhpy, double pos0,double pos1, double pos2, double vec0, double vec1, double vec2, double addy0, double addy1, double addy2, double addz0, double addz1, double addz2, double bhsize, double whsize)
{
	double vecn0, vecn1, vecn2;
	double roomsize,schecker;


	bool flip;
	double sx, sy, sz;
	double dotp;

	double leangle,lecos,lesign,lecossq,lerayon,lex1,lex2,lexw;
	double vecperp0, vecperp1, vecperp2;
	double vecperpn;
	
	double exitlgt, exitangle, exitangle2;

	double pos20, pos21, pos22;
	double vecn20, vecn21, vecn22;
	double qa, qb, qc;
	double discr;
	double tcont;
	double tmpr;
	double tmpx2;

	double tmin,tsol;
	int tmincoord;
	double tmpsign;

	double coll0, coll1;
	int checker;
	int ctmp0, ctmp1, ctmp2;
	int dtmp0, dtmp1, dtmp2;

	int tmp = blockIdx.x * blockDim.x + threadIdx.x;
	int tmpx = tmp % 1280;
	int tmpy = (tmp-tmpx) /1280;
	flip = false;

	/////

	roomsize = 10;
	schecker = 1;
	/////

	vecn0 = vec0 + tmpx * addy0 + tmpy * addz0;
	vecn1 = vec1 + tmpx * addy1 + tmpy * addz1;
	vecn2 = vec2 + tmpx * addy2 + tmpy * addz2;

	vecn0 /= vecl[tmp];
	vecn1 /= vecl[tmp];
	vecn2 /= vecl[tmp];

	if (dc < 1)
	{
		sx = pos0/dc;
		sy = pos1/dc;
		sz = pos2/dc;

		dotp = sx * vecn0 + sy * vecn1 + sz * vecn2;
		leangle = acos(dotp);

		vecperp0 = vecn0 - dotp * sx;
		vecperp1 = vecn1 - dotp * sy;
		vecperp2 = vecn2 - dotp * sz;

		vecperpn = sqrt(vecperp0 * vecperp0 + vecperp1 * vecperp1 + vecperp2 * vecperp2);

		vecperp0 /= vecperpn;
		vecperp1 /= vecperpn;
		vecperp2 /= vecperpn;

		lecos = cos(leangle);
		if (lecos < 0) lesign = -1;
		else lesign = 1;

		lecossq = lecos * lecos;


		lerayon = uhpy * sqrt(1 / (1 - lecossq));


		lex1 = sqrt(lerayon * lerayon - uhpy * uhpy) * lesign;
		lex2 = sqrt(lerayon * lerayon - 1);



		if (lesign<0 && lerayon>whsize)
		{
			flip = true;

			lexw = sqrt(lerayon * lerayon - whsize * whsize);

			exitlgt = -lex1 + lex2 - 2 * lexw;
			exitangle = fmod(exitlgt,bhsize);
			exitangle = (2 * M_PI / bhsize) * exitangle;

			exitangle2 = acos((1 / uhpy) * sqrt(uhpy * uhpy - 1 + lecossq));


			pos20 = cos(exitangle) * sx + sin(exitangle) * vecperp0;
			pos21 = cos(exitangle) * sy + sin(exitangle) * vecperp1;
			pos22 = cos(exitangle) * sz + sin(exitangle) * vecperp2;

			vecn20 = cos(exitangle + exitangle2) * sx + sin(exitangle2 + exitangle) * vecperp0;
			vecn21 = cos(exitangle + exitangle2) * sy + sin(exitangle2 + exitangle) * vecperp1;
			vecn22 = cos(exitangle + exitangle2) * sz + sin(exitangle2 + exitangle) * vecperp2;
		}
		else
		{
			exitlgt = lex2 - lex1;
			exitangle = fmod(exitlgt,bhsize);
			exitangle = (2 * M_PI / bhsize) * exitangle;

			exitangle2 = acos((1 / uhpy) * sqrt(uhpy * uhpy - 1 + lecossq));

			pos20 = cos(exitangle) * sx + sin(exitangle) * vecperp0;
			pos21 = cos(exitangle) * sy + sin(exitangle) * vecperp1;
			pos22 = cos(exitangle) * sz + sin(exitangle) * vecperp2;


			vecn20 = cos(exitangle + exitangle2) * sx + sin(exitangle2 + exitangle) * vecperp0;
			vecn21 = cos(exitangle + exitangle2) * sy + sin(exitangle2 + exitangle) * vecperp1;
			vecn22 = cos(exitangle + exitangle2) * sz + sin(exitangle2 + exitangle) * vecperp2;
		}
		tcont = 0;


	}
	else
	{

		qa = vecn0 * vecn0 + vecn1 * vecn1 + vecn2 * vecn2;
		qb = 2 * (vecn0 * pos0 + vecn1 * pos1 + vecn2 * pos2);
		qc = pos0 * pos0 + pos1 * pos1 + pos2 * pos2 - 1;

		discr = qb * qb - 4 * qa * qc;

		if (discr <= 0) {
			pos20 = pos0;
			pos21 = pos1;
			pos22 = pos2;

			vecn20 = vecn0;
			vecn21 = vecn1;
			vecn22 = vecn2;

			tcont = 0;
		}
		else
		{

			tcont = ((-1) * qb - sqrt(discr)) / (2 * qa);

			if (tcont > 0) {
				sx = vecn0 * tcont + pos0;
				sy = vecn1 * tcont + pos1;
				sz = vecn2 * tcont + pos2;

				dotp = sx * vecn0 + sy * vecn1 + sz * vecn2;
				leangle = acos(dotp);

				vecperp0 = vecn0 - dotp * sx;
				vecperp1 = vecn1 - dotp * sy;
				vecperp2 = vecn2 - dotp * sz;

				vecperpn = sqrt(vecperp0 * vecperp0 + vecperp1 * vecperp1 + vecperp2 * vecperp2);

				vecperp0 /= vecperpn;
				vecperp1 /= vecperpn;
				vecperp2 /= vecperpn;

				lecos = cos(leangle);
				lecossq = lecos * lecos;

				lerayon = sqrt(1 / (1 - lecossq));




				if (lerayon > whsize)
				{

					flip = true;


					lexw = sqrt((1 / (1 - lecossq)) - whsize * whsize);

					exitlgt = -2 * (lexw + lerayon * lecos);
					exitangle = fmod(exitlgt,bhsize);

					exitangle = (2 * M_PI / bhsize) * exitangle;

					pos20 = cos(exitangle) * sx + sin(exitangle) * vecperp0;
					pos21 = cos(exitangle) * sy + sin(exitangle) * vecperp1;
					pos22 = cos(exitangle) * sz + sin(exitangle) * vecperp2;


					vecn20 = cos(M_PI + exitangle - leangle) * sx + sin(M_PI - leangle + exitangle) * vecperp0;
					vecn21 = cos(M_PI + exitangle - leangle) * sy + sin(M_PI - leangle + exitangle) * vecperp1;
					vecn22 = cos(M_PI + exitangle - leangle) * sz + sin(M_PI - leangle + exitangle) * vecperp2;
				}
				else
				{
					exitlgt = -2 * lerayon * lecos;
					exitangle = fmod(exitlgt,bhsize);

					exitangle = (2 * M_PI / bhsize) * exitangle;


					pos20 = cos(exitangle) * sx + sin(exitangle) * vecperp0;
					pos21 = cos(exitangle) * sy + sin(exitangle) * vecperp1;
					pos22 = cos(exitangle) * sz + sin(exitangle) * vecperp2;


					vecn20 = cos(M_PI + exitangle - leangle) * sx + sin(M_PI - leangle + exitangle) * vecperp0;
					vecn21 = cos(M_PI + exitangle - leangle) * sy + sin(M_PI - leangle + exitangle) * vecperp1;
					vecn22 = cos(M_PI + exitangle - leangle) * sz + sin(M_PI - leangle + exitangle) * vecperp2;
				}
			}
			else {
				pos20 = pos0;
				pos21 = pos1;
				pos22 = pos2;

				vecn20 = vecn0;
				vecn21 = vecn1;
				vecn22 = vecn2;

				tcont = 0;
			}

		}
	}


	if (vecn20 < 0) tmpsign = -1;
	else tmpsign = 1;

	tmin = (tmpsign * roomsize - pos20) / vecn20;
	tmincoord = 0;

	if (vecn21 < 0) tmpsign = -1;
	else tmpsign = 1;
	tsol = (tmpsign * roomsize - pos21) / vecn21;
	if (tsol < tmin)
	{
		tmin = tsol;
		tmincoord = 1;
	}

	if (vecn22 < 0) tmpsign = -1;
	else tmpsign = 1;
	tsol = (tmpsign * roomsize - pos22) / vecn22;
	if (tsol < tmin)
	{
		tmin = tsol;
		tmincoord = 2;
	}

	if (tmincoord == 0)
	{
		coll0 = pos21 + tmin * vecn21;
		coll1 = pos22 + tmin * vecn22;
	}
	else if (tmincoord == 1)
	{
		coll0 = pos20 + tmin * vecn20;
		coll1 = pos22 + tmin * vecn22;
	}
	else
	{
		coll0 = pos20 + tmin * vecn20;
		coll1 = pos21 + tmin * vecn21;
	}

	checker = ((int)floor(coll0 * schecker)) % 2;
	checker += ((int)floor(coll1 * schecker)) % 2;
	if (checker < 0) checker += 2;
	checker %= 2;


	if (flip ^ flipg)
	{
		if (tmincoord == 0)
		{
			if (vecn20 < 0)
			{
				ctmp0 = 27;
				ctmp1 = 205;
				ctmp2 = 1;

				dtmp0 = 9;
				dtmp1 = 66;
				dtmp2 = 0;
			}
			else
			{
				ctmp0 = 232;
				ctmp1 = 220;
				ctmp2 = 0;

				dtmp0 = 85;
				dtmp1 = 81;
				dtmp2 = 0;
			}
		}
		else if (tmincoord == 1)
		{
			if (vecn21 < 0)
			{
				ctmp0 = 18;
				ctmp1 = 0;
				ctmp2 = 242;

				dtmp0 = 6;
				dtmp1 = 0;
				dtmp2 = 85;
			}
			else
			{
				ctmp0 = 234;
				ctmp1 = 0;
				ctmp2 = 6;

				dtmp0 = 89;
				dtmp1 = 0;
				dtmp2 = 2;
			}
		}
		else
		{
			if (vecn22 < 0)
			{
				ctmp0 = 4;
				ctmp1 = 255;
				ctmp2 = 255;

				dtmp0 = 0;
				dtmp1 = 81;
				dtmp2 = 81;
			}
			else
			{
				ctmp0 = 100;
				ctmp1 = 100;
				ctmp2 = 100;

				dtmp0 = 50;
				dtmp1 = 50;
				dtmp2 = 50;
			}
		}



		if (checker == 0) {
			buffer[4 * tmp] = dtmp0;
			buffer[4 * tmp + 1] = dtmp1;
			buffer[4 * tmp + 2] = dtmp2;
			buffer[4 * tmp + 3] = 255;
		}
		else
		{
			
			buffer[4 * tmp] = ctmp0;
			buffer[4 * tmp + 1] = ctmp1;
			buffer[4 * tmp + 2] = ctmp2;
			buffer[4 * tmp + 3] = 255;
		}
	}
	else
	{
		if (tmincoord == 2) {
			ctmp0 = 255;
			ctmp1 = 255;
			ctmp2 = 255;
		}
		else if (tmincoord == 0)
		{
			if (vecn20 < 0)
			{
				tmpx2 = (1.0/8.0) - (coll0 / (8.0 * roomsize));
				tmpr = fmod(tmpx2, 1.0/6.0);

				if (tmpx2 < 1.0/6.0)
				{
					ctmp0 = 255.0;
					ctmp1 = (int)(1530.0 * tmpr);
					ctmp2 = 0;
				}
				else if (tmpx2 < 1.0/3.0)
				{
					ctmp1 = 255.0;
					ctmp0 = (int)(255.0 - 1530.0 * tmpr);
					ctmp2 = 0;
				}
				else if (tmpx2 < 0.5)
				{
					ctmp1 = 255.0;
					ctmp2 = (int)(1530.0 * tmpr);
					ctmp0 = 0;
				}
				else if (tmpx2 < 2.0/3.0)
				{
					ctmp2 = 255.0;
					ctmp1 = (int)(255.0 - 1530.0 * tmpr);
					ctmp0 = 0;
				}
				else if (tmpx2 < 5.0 / 6.0)
				{
					ctmp2 = 255.0;
					ctmp0 = (int)(1530.0 * tmpr);
					ctmp1 = 0;
				}
				else
				{
					ctmp0 = 255.0;
					ctmp2 = (int)(255.0 - 1530.0 * tmpr);
					ctmp1 = 0;
				}
			}
			else
			{
				tmpx2 = (1.0 / 2.0) + (1.0 / 8.0) + coll0 / (8.0 * roomsize);

				tmpr = fmod(tmpx2, 1.0 / 6.0);

				if (tmpx2 < 1.0 / 6.0)
				{
					ctmp0 = 255.0;
					ctmp1 = (int)(1530.0 * tmpr);
					ctmp2 = 0;
				}
				else if (tmpx2 < 1.0 / 3.0)
				{
					ctmp1 = 255.0;
					ctmp0 = (int)(255.0 - 1530.0 * tmpr);
					ctmp2 = 0;
				}
				else if (tmpx2 < 0.5)
				{
					ctmp1 = 255.0;
					ctmp2 = (int)(1530.0 * tmpr);
					ctmp0 = 0;
				}
				else if (tmpx2 < 2.0 / 3.0)
				{
					ctmp2 = 255.0;
					ctmp1 = (int)(255.0 - 1530.0 * tmpr);
					ctmp0 = 0;
				}
				else if (tmpx2 < 5.0 / 6.0)
				{
					ctmp2 = 255.0;
					ctmp0 = (int)(1530.0 * tmpr);
					ctmp1 = 0;
				}
				else
				{
					ctmp0 = 255.0;
					ctmp2 = (int)(255.0 - 1530.0 * tmpr);
					ctmp1 = 0;
				}
			}
		}
		else
		{
			if (vecn21 < 0)
			{
				tmpx2 = (1.0 / 4.0) + (1.0 / 8.0) + coll0 / (8.0 * roomsize);
				tmpr = fmod(tmpx2, 1.0 / 6.0);

				if (tmpx2 < 1.0 / 6.0)
				{
					ctmp0 = 255.0;
					ctmp1 = (int)(1530.0 * tmpr);
					ctmp2 = 0;
				}
				else if (tmpx2 < 1.0 / 3.0)
				{
					ctmp1 = 255.0;
					ctmp0 = (int)(255.0 - 1530.0 * tmpr);
					ctmp2 = 0;
				}
				else if (tmpx2 < 0.5)
				{
					ctmp1 = 255.0;
					ctmp2 = (int)(1530.0 * tmpr);
					ctmp0 = 0;
				}
				else if (tmpx2 < 2.0 / 3.0)
				{
					ctmp2 = 255.0;
					ctmp1 = (int)(255.0 - 1530.0 * tmpr);
					ctmp0 = 0;
				}
				else if (tmpx2 < 5.0 / 6.0)
				{
					ctmp2 = 255.0;
					ctmp0 = (int)(1530.0 * tmpr);
					ctmp1 = 0;
				}
				else
				{
					ctmp0 = 255.0;
					ctmp2 = (int)(255.0 - 1530.0 * tmpr);
					ctmp1 = 0;
				}
			}
			else
			{
				tmpx2= (3.0 / 4.0) + (1.0 / 8.0) - coll0 / (8.0 * roomsize);

				tmpr = fmod(tmpx2, 1.0 / 6.0);

				if (tmpx2 < 1.0 / 6.0)
				{
					ctmp0 = 255.0;
					ctmp1 = (int)(1530.0 * tmpr);
					ctmp2 = 0;
				}
				else if (tmpx2 < 1.0 / 3.0)
				{
					ctmp1 = 255.0;
					ctmp0 = (int)(255.0 - 1530.0 * tmpr);
					ctmp2 = 0;
				}
				else if (tmpx2 < 0.5)
				{
					ctmp1 = 255.0;
					ctmp2 = (int)(1530.0 * tmpr);
					ctmp0 = 0;
				}
				else if (tmpx2 < 2.0 / 3.0)
				{
					ctmp2 = 255.0;
					ctmp1 = (int)(255.0 - 1530.0 * tmpr);
					ctmp0 = 0;
				}
				else if (tmpx2 < 5.0 / 6.0)
				{
					ctmp2 = 255.0;
					ctmp0 = (int)(1530.0 * tmpr);
					ctmp1 = 0;
				}
				else
				{
					ctmp0 = 255.0;
					ctmp2 = (int)(255.0 - 1530.0 * tmpr);
					ctmp1 = 0;
				}
			}
		}

		if (checker == 0) {
			buffer[4 * tmp] = 0;
			buffer[4 * tmp + 1] = 0;
			buffer[4 * tmp + 2] = 0;
			buffer[4 * tmp + 3] = 255;

		}
		else
		{
			buffer[4 * tmp] = ctmp0;
			buffer[4 * tmp + 1] = ctmp1;
			buffer[4 * tmp + 2] = ctmp2;
			buffer[4 * tmp + 3] = 255;
		}
		
	}
}

void cudaInit()
{
	double dist = 1;
	double sqsz = 0.01 / 4;
	int tmpx, tmpy;
	double* vecltmp = new double[1280 * 720];

	double vec0, vec1, vec2;
	double addy0, addy1, addy2;
	double addz0, addz1, addz2;
	double vecn0, vecn1, vecn2;
	double x00 = 1, x01 = 0, x02 = 0;
	double x10 = 0, x11 = 1, x12 = 0;
	double x20 = 0, x21 = 0, x22 = 1;
	double multy = (1 - 1280) * sqsz / 2;
	double multz = (720 - 1) * sqsz / 2;

	cudaSetDevice(0);
	cudaMalloc((void**)&buffer, 4 * 1280 * 720 * sizeof(uint8_t));
	cudaMalloc((void**)&vecl, 1280 * 720 * sizeof(double));

	
	vec0 = dist * x00 + multy * x10 + multz * x20;
	vec1 = dist * x01 + multy * x11 + multz * x21;
	vec2 = dist * x02 + multy * x12 + multz * x22;
	
	addy0 = sqsz * x10;
	addy1 = sqsz * x11;
	addy2 = sqsz * x12;

	addz0 = -sqsz * x20;
	addz1 = -sqsz * x21;
	addz2 = -sqsz * x22;
	
	for (int i = 0; i < 1280 * 720; i++)
	{
		tmpx = i % 1280;
		tmpy = (i - tmpx) / 1280;

		vecn0 = vec0 + tmpx * addy0 + tmpy * addz0;
		vecn1 = vec1 + tmpx * addy1 + tmpy * addz1;
		vecn2 = vec2 + tmpx * addy2 + tmpy * addz2;

		vecltmp[i] = sqrt(vecn0*vecn0+vecn1*vecn1+vecn2*vecn2);
	}

	cudaMemcpy(vecl, vecltmp, 1280 * 720 * sizeof(double), cudaMemcpyHostToDevice);
}

void cudaExit()
{
	cudaFree(buffer);
	cudaFree(vecl);
	cudaDeviceReset();
}

void cudathingy(uint8_t* pixels, bool flipg, double dc, double uhpy, double pos0, double pos1, double pos2, double vec0, double vec1, double vec2, double addy0, double addy1, double addy2, double addz0, double addz1, double addz2, double bhsize, double whsize)
{




	addKernel <<<(int)(1280 * 720 / 600), 600>>>(buffer, vecl, flipg, dc,uhpy, pos0,pos1,pos2,vec0,vec1,vec2,addy0,addy1,addy2,addz0,addz1,addz2,bhsize,whsize);


	cudaDeviceSynchronize();

	cudaMemcpy(pixels, buffer, 4 * 1280 * 720 * sizeof(uint8_t), cudaMemcpyDeviceToHost);


}
