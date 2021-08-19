﻿#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <iostream>
#include<gmpxx.h>
#include<gmp.h>
#include<time.h>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string>
#include "cryptopp/integer.h"
#include <cryptopp/aes.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/default.h>
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>
using namespace std;
using namespace CryptoPP;
mpz_t c1a_1, c1a_2;
mpz_t c2a_1, c2a_2;
mpz_t c1b_1, c1b_2;
mpz_t c2b_1, c2b_2;
mpz_t shared_KeyAC, shared_KeyBC;
mpz_t pa, pb;
mpz_t ga, gb;
mpz_t Getc1a, Getc2a;
mpz_t Getc1b, Getc2b;
mpz_t y, Shared_KeyBack;
mpz_t g_DH, p, k, g;
mpz_t c1, c2;
mpz_t ma;
mpz_t c1b, c2b;
mpz_t c1a, c2a;
int init1()
{
	mpz_init(c1a_1);
	mpz_init(c1a_2);
	mpz_init(c2a_1);
	mpz_init(c2a_2);
	mpz_init(c1b_1);
	mpz_init(c1b_2);
	mpz_init(c2b_1);
	mpz_init(c2b_2);
	mpz_init(shared_KeyAC);
	mpz_init(shared_KeyBC);
	mpz_init(pa);
	mpz_init(pb);
	mpz_init(ga);
	mpz_init(gb);
	mpz_init(Getc1a);
	mpz_init(Getc2a);
	mpz_init(Getc1b);
	mpz_init(Getc2b);
	mpz_init(y);
	mpz_init(Shared_KeyBack);
	mpz_init(g_DH);
	mpz_init(p);
	mpz_init(k);
	mpz_init(g);
	mpz_init(c1);
	mpz_init(c2);
	mpz_init(ma);
	mpz_init(c1b);
	mpz_init(c2b);
	char tmp1[1024];
	char tmp2[1024];
	char tmp3[1024];
	ifstream in1("DHSharedKeyAC.txt", ios::in);
	if (!in1) {
		cout << "error" << endl;
		return 0;
	}
	in1.getline(tmp1, 1024);
	in1.getline(tmp2, 1024);
	in1.getline(tmp3, 1024);
	in1.close();
	mpz_set_str(shared_KeyAC, tmp1, 37);
	mpz_set_str(y, tmp2, 37);
	mpz_set_str(k, tmp3, 37);
	char tmp[1024];
	ifstream in3("Elgamal_g.txt", ios::in);
	if (!in3) {
		cout << "error" << endl;
		return 0;
	}
	in3.getline(tmp, 1024);
	in3.close();
	mpz_set_str(g, tmp, 37);
	char temp[1024];
	ifstream in4("DH_g.txt", ios::in);
	if (!in4) {
		cout << "error" << endl;
		return 0;
	}
	in4.getline(temp, 1024);
	in4.close();
	mpz_set_str(g_DH, temp, 37);
	char pp[1024];
	ifstream in5("p.txt", ios::in);
	if (!in5) {
		cout << "error" << endl;
		return 0;
	}
	in5.getline(pp, 1024);
	in5.close();
	mpz_set_str(p, pp, 37);
	char tmp7[10];
	//以二进制模式打开 in.txt 文件
	ifstream in6("ma.txt", ios::in);
	//判断文件是否正常打开
	if (!in6) {
		cout << "error" << endl;
		return 0;
	}
	in6.getline(tmp7, 10);
	in6.close();
	mpz_set_str(ma, tmp7, 37);
	char tmp8[1024];
	char tmp9[1024];
	//以二进制模式打开 in.txt 文件
	ifstream in7("B2A.txt", ios::in);
	//判断文件是否正常打开
	if (!in7) {
		cout << "error" << endl;
		return 0;
	}
	in7.getline(tmp8, 1024);
	in7.getline(tmp9, 1024);
	in7.close();
	mpz_set_str(c1b, tmp8, 37);
	mpz_set_str(c2b, tmp9, 37);
}
int init2()
{
	mpz_init(c1a);
	mpz_init(c2a);
	char tmp8[1024];
	char tmp9[1024];
	//以二进制模式打开 in.txt 文件
	ifstream in7("C2A.txt", ios::in);
	//判断文件是否正常打开
	if (!in7) {
		cout << "error" << endl;
		return 0;
	}
	in7.getline(tmp8, 1024);
	in7.getline(tmp9, 1024);
	in7.close();
	mpz_set_str(c1a, tmp8, 37);
	mpz_set_str(c2a, tmp9, 37);
}
void DH_SharedKeyGen(mpz_t p_, mpz_t g_, mpz_t* shared_key)
{
	clock_t time = clock();
	gmp_randstate_t grt;
	gmp_randinit_default(grt); //设置随机数生成算法为默认
	gmp_randseed_ui(grt, time); //设置随机化种子为当前时间
	mpz_t xa, xb, ya, yb, k;
	mpz_t p1;
	mpz_init(ya);
	mpz_init(yb);
	mpz_init(p1);
	mpz_init(k);
	mpz_init(xa);
	mpz_init(xb);
	mpz_sub_ui(p1, p_, 1);
	mpz_urandomm(xa, grt, p1);
	mpz_urandomm(xb, grt, p1);
	mpz_powm(ya, g_, xa, p_);
	mpz_powm(yb, g_, xb, p_);
	mpz_powm(*shared_key, yb, xa, p_);
	mpz_clear(p1);
	mpz_clear(ya);
	mpz_clear(yb);
	mpz_clear(xa);
	mpz_clear(xb);
	mpz_clear(k);
}
void Elgamal_Decryption(mpz_t c1, mpz_t c2, mpz_t x, mpz_t p, mpz_t g, mpz_t* GetM)
{
	mpz_t tmp1, tmp2, tmp3, p1;
	mpz_init(*GetM);
	mpz_init(tmp1);
	mpz_init(tmp2);
	mpz_init(tmp3);
	mpz_init(p1);
	mpz_powm(tmp1, c1, x, p);
	mpz_invert(tmp2, tmp1, p);
	mpz_mul(tmp3, c2, tmp2);
	mpz_mod(*GetM, tmp3, p);
	mpz_clear(tmp1);
	mpz_clear(tmp2);
	mpz_clear(tmp3);
	mpz_clear(p1);
	/*mpz_sub_ui(p1, p, 2);
	mpz_powm(tmp1, c1, p1, p);
	mpz_powm(tmp2, tmp1, x, p);
	mpz_mul(tmp3, c2, tmp2);
	mpz_mod(GetM, tmp3, p);*/
	//int m;
	//int c1_ = pow_mod(c1, p - 2, p);
	//m = c2 * pow_mod(c1_, x, p) % p;
	//return m;
}
int compare()
{
	Elgamal_Decryption(c1a_1, c1a_2, shared_KeyAC, pa, ga, &Getc1a);
	Elgamal_Decryption(c2a_1, c2a_2, shared_KeyAC, pa, ga, &Getc2a);
	Elgamal_Decryption(c1b_1, c1b_2, shared_KeyBC, pb, gb, &Getc1b);
	Elgamal_Decryption(c2b_1, c2b_2, shared_KeyBC, pb, gb, &Getc2b);
	//gmp_printf("%Zd\n\n", Getc1a);
	//gmp_printf("%Zd\n\n", Getc2a);
	//gmp_printf("%Zd\n\n", Getc1b);
	//gmp_printf("%Zd\n\n", Getc2b);
	if ((mpz_cmp(Getc1a, Getc1b) == 0) && (mpz_cmp(Getc2a, Getc2b) == 0))
		return 1;
	else
		return 0;
}
int SendMsgBack2A()
{
	ofstream out("C2A.txt", ios::out);
	if (!out)
	{
		out.close(); //程序结束前不能忘记关闭以前打开过的文件
		cout << "error" << endl;
		return 0;
	}
	char c_1[1024];
	char c_2[1024];
	char xx[1024];
	char pp[1024];
	char gg[1024];
	mpz_get_str(c_1, 37, c1);
	mpz_get_str(c_2, 37, c2);
	mpz_get_str(xx, 37, Shared_KeyBack);
	mpz_get_str(pp, 37, p);
	mpz_get_str(gg, 37, g);
	int i = 0;
	while (i < strlen(c_1))
	{
		out << c_1[i];
		i++;
	}
	out << endl;
	i = 0;
	while (i < strlen(c_2))
	{
		out << c_2[i];
		i++;
	}
	out << endl;
	i = 0;
	while (i < strlen(xx))
	{
		out << xx[i];
		i++;
	}
	out << endl;
	i = 0;
	while (i < strlen(pp))
	{
		out << pp[i];
		i++;
	}
	out << endl;
	i = 0;
	while (i < strlen(gg))
	{
		out << gg[i];
		i++;
	}
	out.close();
}
int A2B()
{
	ofstream out("A2B.txt", ios::out);
	if (!out)
	{
		out.close(); //程序结束前不能忘记关闭以前打开过的文件
		cout << "error" << endl;
		return 0;
	}
	char c_1[1024];
	char c_2[1024];
	char c_3[1024];
	char c_4[1024];
	mpz_get_str(c_1, 37, c1b_1);
	mpz_get_str(c_2, 37, c1b_2);
	mpz_get_str(c_3, 37, c2b_1);
	mpz_get_str(c_4, 37, c2b_2);
	int i = 0;
	while (i < strlen(c_1))
	{
		out << c_1[i];
		i++;
	}
	out << endl;
	i = 0;
	while (i < strlen(c_2))
	{
		out << c_2[i];
		i++;
	}
	out << endl;
	i = 0;
	while (i < strlen(c_3))
	{
		out << c_3[i];
		i++;
	}
	out << endl;
	i = 0;
	while (i < strlen(c_4))
	{
		out << c_4[i];
		i++;
	}
	out.close();
}
int Nochaeting()
{
	ofstream out("IsCheating.txt", ios::out);
	if (!out)
	{
		out.close(); //程序结束前不能忘记关闭以前打开过的文件
		cout << "error" << endl;
		return 0;
	}
	out << "no";
	out.close();
}
void PublicKeyGen(mpz_t p, mpz_t g, mpz_t* x, mpz_t* y, mpz_t* k)
{
	clock_t time = clock();
	gmp_randstate_t grt;
	gmp_randinit_default(grt); //设置随机数生成算法为默认
	gmp_randseed_ui(grt, time); //设置随机化种子为当前时间
	mpz_t p1;
	mpz_init(p1);
	mpz_sub_ui(p1, p, 1);
	mpz_urandomm(*x, grt, p1);
	mpz_powm(*y, g, *x, p);
	mpz_urandomm(*k, grt, p1);
}
void Elgamal_Encryption(mpz_t m_, mpz_t y_, mpz_t k_, mpz_t p_, mpz_t g_, mpz_t* c1, mpz_t* c2)
{
	mpz_t tmp1, tmp2;
	mpz_init(tmp1);
	mpz_init(tmp2);
	mpz_powm(*c1, g_, k_, p_);
	mpz_powm(tmp1, y_, k_, p_);
	mpz_mul(tmp2, m_, tmp1);
	mpz_mod(*c2, tmp2, p_);
	mpz_clear(tmp1);
	mpz_clear(tmp2);
	//*c1 = pow_mod(g, k, p);
	//*c2 = m * pow_mod(pub, k, p) % p;
}
int main()
{

	int i;
	mpz_t result;
	init1();
	clock_t startTime, endTime;
	startTime = clock();
	Elgamal_Encryption(c1b, y, k, p, g, &c1b_1, &c1b_2);
	Elgamal_Encryption(c2b, y, k, p, g, &c2b_1, &c2b_2);
	A2B();
	Nochaeting();
	endTime = clock();//计时结束
	cout << "该程序运行时间: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	system("pause");
	init2();
	clock_t startTime1, endTime1;
	startTime1 = clock();
	if ((mpz_cmp(c1a, c1b) == 0) && (mpz_cmp(c2a, c2b) == 0))
		cout << "成绩一致" << endl;
	else
		cout << "成绩不一致" << endl;
	endTime1 = clock();//计时结束
	cout << "该程序运行时间: " << (double)(endTime1 - startTime1) / CLOCKS_PER_SEC << "s" << endl;
	system("pause");
}