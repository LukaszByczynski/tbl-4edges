#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>

#include "vu.h"
#include "MicroCode.h"
#include "VuMem.h"

namespace ps2emu
{

extern MicroCode Instr;

int
Vu::VU_B(VuInstruction &A) {
    int a;
    a = PC;
    PC++;
    Tic(); //delay slot itself
    PC = (uint16)a;
    PC += (uint16)(A.Params[1][0].data);
    return -1;
}

int
Vu::VU_BAL(VuInstruction &A) {
    int a;

    RegInt[A.Params[1][0].index].lastWrite(PC);
    RegInt[A.Params[1][0].index].stall(2);
    RegInt[A.Params[1][0].index].value((int16)(PC+2));

    a = PC;
    PC++;
    Tic(); //delay slot itself
    PC = (uint16)a;
    PC += (uint16)(A.Params[1][1].data);
    return -1;
}

int
Vu::VU_DIV(VuInstruction &A) {
    int st1, st2;
    float d1,d2;

    st1=Stalling(A.Params[1][1]);
    st2=Stalling(A.Params[1][2]);

    //ths instruction can not return a warning
    if(st1>0) {
        return 2;
    }
    if(st2>0) {
        return 3;
    }

    if(toupper(A.Params[1][1].sufix[0])=='X')
        d1=RegFloat[A.Params[1][1].index].x();
    if(toupper(A.Params[1][1].sufix[0])=='Y')
        d1=RegFloat[A.Params[1][1].index].y();
    if(toupper(A.Params[1][1].sufix[0])=='Z')
        d1=RegFloat[A.Params[1][1].index].z();
    if(toupper(A.Params[1][1].sufix[0])=='W')
        d1=RegFloat[A.Params[1][1].index].w();

    if(toupper(A.Params[1][2].sufix[0])=='X')
        d2=RegFloat[A.Params[1][2].index].x();
    if(toupper(A.Params[1][2].sufix[0])=='Y')
        d2=RegFloat[A.Params[1][2].index].y();
    if(toupper(A.Params[1][2].sufix[0])=='Z')
        d2=RegFloat[A.Params[1][2].index].z();
    if(toupper(A.Params[1][2].sufix[0])=='W')
        d2=RegFloat[A.Params[1][2].index].w();

    if(d2==0.0 && d1==0.0) {
        StatusFlag|=16;   //Ivalid op 0/0;
    } else if(d2==0.0) {
        StatusFlag|=32;   //division by 0;
    } else {
        Q.x(d1/d2);
        Q.y(d1/d2);
        Q.z(d1/d2);
        Q.w(d1/d2);
    }

    RegInt[A.Params[1][1].index].lastRead(PC);
    RegInt[A.Params[1][2].index].lastRead(PC);
    Q.lastWrite(PC);
    Q.stall(7);
    return 0;
}

int Vu::VU_EATAN(VuInstruction &A)
{
    int st1;
    float d1;


    st1=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    if(toupper(A.Params[1][1].sufix[0])=='X')
        d1=RegFloat[A.Params[1][1].index].x();
    if(toupper(A.Params[1][1].sufix[0])=='Y')
        d1=RegFloat[A.Params[1][1].index].y();
    if(toupper(A.Params[1][1].sufix[0])=='Z')
        d1=RegFloat[A.Params[1][1].index].z();
    if(toupper(A.Params[1][1].sufix[0])=='W')
        d1=RegFloat[A.Params[1][1].index].w();

    if(d1>0.0 && d1<1.0)
        P.x(atan(d1));

    RegInt[A.Params[1][1].index].lastRead(PC);
    P.lastWrite(PC);
    P.stall(54);
    return 0;
}

int Vu::VU_EATANXY(VuInstruction &A)
{
    int st1;


    st1=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    if(RegFloat[A.Params[1][1].index].x()==0.0 ||
        RegFloat[A.Params[1][1].index].y()==0.0)
        P.x(atan(RegFloat[A.Params[1][1].index].y()/RegFloat[A.Params[1][1].index].x()));

    RegInt[A.Params[1][1].index].lastRead(PC);
    P.lastWrite(PC);
    P.stall(54);
    return 0;
}

int Vu::VU_EATANXZ(VuInstruction &A)
{
    int st1;


    st1=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    if(RegFloat[A.Params[1][1].index].x()==0.0 ||
        RegFloat[A.Params[1][1].index].z()==0.0)
        P.x(atan(RegFloat[A.Params[1][1].index].z()/RegFloat[A.Params[1][1].index].x()));

    RegInt[A.Params[1][1].index].lastRead(PC);
    P.lastWrite(PC);
    P.stall(54);
    return 0;
}

int Vu::VU_EEXP(VuInstruction &A)
{
    int st1;
    float d1;


    st1=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    if(toupper(A.Params[1][1].sufix[0])=='X')
        d1=RegFloat[A.Params[1][1].index].x();
    if(toupper(A.Params[1][1].sufix[0])=='Y')
        d1=RegFloat[A.Params[1][1].index].y();
    if(toupper(A.Params[1][1].sufix[0])=='Z')
        d1=RegFloat[A.Params[1][1].index].z();
    if(toupper(A.Params[1][1].sufix[0])=='W')
        d1=RegFloat[A.Params[1][1].index].w();

    if(d1>0.0)
        P.x(exp(-d1));

    RegInt[A.Params[1][1].index].lastRead(PC);
    P.lastWrite(PC);
    P.stall(44);
    return 0;
}

int Vu::VU_ELENG(VuInstruction &A)
{
    int st1;
    float d1,d2,d3;


    st1=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    d1=RegFloat[A.Params[1][1].index].x();
    d2=RegFloat[A.Params[1][1].index].y();
    d3=RegFloat[A.Params[1][1].index].z();

    P.x(sqrt((d1*d1)+(d2*d2)+(d3*d3)));

    RegInt[A.Params[1][1].index].lastRead(PC);
    P.lastWrite(PC);
    P.stall(18);
    return 0;
}

int Vu::VU_ERCPR(VuInstruction &A)
{
    int st1;
    float d1;


    st1=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    if(toupper(A.Params[1][1].sufix[0])=='X')
        d1=RegFloat[A.Params[1][1].index].x();
    if(toupper(A.Params[1][1].sufix[0])=='Y')
        d1=RegFloat[A.Params[1][1].index].y();
    if(toupper(A.Params[1][1].sufix[0])=='Z')
        d1=RegFloat[A.Params[1][1].index].z();
    if(toupper(A.Params[1][1].sufix[0])=='W')
        d1=RegFloat[A.Params[1][1].index].w();

    if(d1!=0.0)
        P.x(1/d1);

    RegInt[A.Params[1][1].index].lastRead(PC);
    P.lastWrite(PC);
    P.stall(12);
    return 0;
}

int Vu::VU_ERLENG(VuInstruction &A)
{
    int st1;
    float d1,d2,d3;


    st1=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    d1=RegFloat[A.Params[1][1].index].x();
    d2=RegFloat[A.Params[1][1].index].y();
    d3=RegFloat[A.Params[1][1].index].z();

    P.x(1/sqrt((d1*d1)+(d2*d2)+(d3*d3)));

    RegInt[A.Params[1][1].index].lastRead(PC);
    P.lastWrite(PC);
    P.stall(24);
    return 0;
}

int Vu::VU_ERSADD(VuInstruction &A)
{
    int st1;
    float d1,d2,d3;


    st1=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    d1=RegFloat[A.Params[1][1].index].x();
    d2=RegFloat[A.Params[1][1].index].y();
    d3=RegFloat[A.Params[1][1].index].z();

    P.x(1/((d1*d1)+(d2*d2)+(d3*d3)));

    RegInt[A.Params[1][1].index].lastRead(PC);
    P.lastWrite(PC);
    P.stall(18);
    return 0;
}

int Vu::VU_ERSQRT(VuInstruction &A)
{
    int st1;
    float d1;


    st1=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    if(toupper(A.Params[1][1].sufix[0])=='X')
        d1=RegFloat[A.Params[1][1].index].x();
    if(toupper(A.Params[1][1].sufix[0])=='Y')
        d1=RegFloat[A.Params[1][1].index].y();
    if(toupper(A.Params[1][1].sufix[0])=='Z')
        d1=RegFloat[A.Params[1][1].index].z();
    if(toupper(A.Params[1][1].sufix[0])=='W')
        d1=RegFloat[A.Params[1][1].index].w();

    if(d1!=0.0)
        P.x(1/sqrt(d1));

    RegInt[A.Params[1][1].index].lastRead(PC);
    P.lastWrite(PC);
    P.stall(18);
    return 0;
}

int Vu::VU_ESADD(VuInstruction &A)
{
    int st1;
    float d1,d2,d3;


    st1=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    d1=RegFloat[A.Params[1][1].index].x();
    d2=RegFloat[A.Params[1][1].index].y();
    d3=RegFloat[A.Params[1][1].index].z();

    P.x((d1*d1)+(d2*d2)+(d3*d3));

    RegInt[A.Params[1][1].index].lastRead(PC);
    P.lastWrite(PC);
    P.stall(11);
    return 0;
}


int Vu::VU_ESIN(VuInstruction &A)
{
    int st1;
    float d1;


    st1=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    if(toupper(A.Params[1][1].sufix[0])=='X')
        d1=RegFloat[A.Params[1][1].index].x();
    if(toupper(A.Params[1][1].sufix[0])=='Y')
        d1=RegFloat[A.Params[1][1].index].y();
    if(toupper(A.Params[1][1].sufix[0])=='Z')
        d1=RegFloat[A.Params[1][1].index].z();
    if(toupper(A.Params[1][1].sufix[0])=='W')
        d1=RegFloat[A.Params[1][1].index].w();

    P.x(sin(d1));

    RegInt[A.Params[1][1].index].lastRead(PC);
    P.lastWrite(PC);
    P.stall(29);
    return 0;
}

int Vu::VU_ESQRT(VuInstruction &A)
{
    int st1;
    float d1;


    st1=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    if(toupper(A.Params[1][1].sufix[0])=='X')
        d1=RegFloat[A.Params[1][1].index].x();
    if(toupper(A.Params[1][1].sufix[0])=='Y')
        d1=RegFloat[A.Params[1][1].index].y();
    if(toupper(A.Params[1][1].sufix[0])=='Z')
        d1=RegFloat[A.Params[1][1].index].z();
    if(toupper(A.Params[1][1].sufix[0])=='W')
        d1=RegFloat[A.Params[1][1].index].w();

    if(d1>=0.0)
        P.x(sqrt(d1));

    RegInt[A.Params[1][1].index].lastRead(PC);
    P.lastWrite(PC);
    P.stall(12);
    return 0;
}

int Vu::VU_ESUM(VuInstruction &A)
{
    int st1;
    float d1,d2,d3;


    st1=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    d1=RegFloat[A.Params[1][1].index].x();
    d2=RegFloat[A.Params[1][1].index].y();
    d3=RegFloat[A.Params[1][1].index].z();

    P.x(d1+d2+d3);

    RegInt[A.Params[1][1].index].lastRead(PC);
    P.lastWrite(PC);
    P.stall(12);
    return 0;
}

int
Vu::VU_FCAND(VuInstruction &A) {
    unsigned int test;
    int ct1, ct2, ct3, ct4;


    test=A.Params[1][1].udata;
    ct1=test & 63; //6 first bits
    test/=64;
    ct2=test & 63; //6 2nd bits
    test/=64;
    ct3=test & 63; //6 3rd bits
    test/=64;
    ct4=test & 63; //6 4th bits

    ct1&=ClipFlag[0];
    ct2&=ClipFlag[1];
    ct3&=ClipFlag[2];
    ct4&=ClipFlag[3];

    test=(ct4*64*64*64)+(ct3*64*64)+(ct2*64)+ct1;
    if(test)
        RegInt[A.Params[1][0].index].value(1);
    else
        RegInt[A.Params[1][0].index].value(0);

    RegInt[A.Params[1][0].index].lastWrite(PC);
    RegInt[A.Params[1][0].index].stall(1);
    return 0;
}


int
Vu::VU_FCEQ(VuInstruction &A) {
    unsigned int test;
    int ct1, ct2, ct3, ct4;


    test=A.Params[1][1].udata;
    ct1=test & 63; //6 first bits
    test/=64;
    ct2=test & 63; //6 2nd bits
    test/=64;
    ct3=test & 63; //6 3rd bits
    test/=64;
    ct4=test & 63; //6 4th bits

    ct1&=ClipFlag[0];
    ct2&=ClipFlag[1];
    ct3&=ClipFlag[2];
    ct4&=ClipFlag[3];

    test=(ct4*64*64*64)+(ct3*64*64)+(ct2*64)+ct1;
    if(test)
        RegInt[A.Params[1][0].index].value(0);
    else
        RegInt[A.Params[1][0].index].value(1);
    RegInt[A.Params[1][0].index].lastWrite(PC);
    RegInt[A.Params[1][0].index].stall(1);
    return 0;
}

int Vu::VU_FCGET(VuInstruction &A)
{
    uint16 test;


    test=(uint16)(ClipFlag[0]+(64*ClipFlag[0]));

    RegInt[A.Params[1][0].index].value(test);
    RegInt[A.Params[1][0].index].lastWrite(PC);
    RegInt[A.Params[1][0].index].stall(1);
    return 0;
}

int Vu::VU_FCOR(VuInstruction &A)
{
    unsigned int test;
    int ct1, ct2, ct3, ct4;


    test=A.Params[1][1].udata;
    ct1=test & 63; //6 first bits
    test/=64;
    ct2=test & 63; //6 2nd bits
    test/=64;
    ct3=test & 63; //6 3rd bits
    test/=64;
    ct4=test & 63; //6 4th bits

    ct1|=ClipFlag[0];
    ct2|=ClipFlag[1];
    ct3|=ClipFlag[2];
    ct4|=ClipFlag[3];

    test=(ct4*64*64*64)+(ct3*64*64)+(ct2*64)+ct1;
    if( (test & 16777215)== test )
        RegInt[A.Params[1][0].index].value(1);
    else
        RegInt[A.Params[1][0].index].value(0);

    RegInt[A.Params[1][0].index].lastWrite(PC);
    RegInt[A.Params[1][0].index].stall(1);
    return 0;
}

int
Vu::VU_FCSET(VuInstruction &A) {
    unsigned int test;
    uint16 ct1, ct2, ct3, ct4;


    test=A.Params[1][0].udata;
    ct1=(uint16)(test & 63); //6 first bits
    test/=(uint16)64;
    ct2=(uint16)(test & 63); //6 2nd bits
    test/=(uint16)64;
    ct3=(uint16)(test & 63); //6 3rd bits
    test/=(uint16)64;
    ct4=(uint16)(test & 63); //6 4th bits

    ClipFlag[0]=ct1;
    ClipFlag[1]=ct2;
    ClipFlag[2]=ct3;
    ClipFlag[3]=ct4;

    return 0;
}

int
Vu::VU_FMAND(VuInstruction &A) {
    uint16 test1, test2;
    int16 aux;
    int st1;

    st1=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    aux=RegInt[A.Params[1][1].index].value();
    memcpy(&test1,&aux,2);
    test2=(uint16)(MacZ+(MacS*16)+(MacU*16*16)+(MacO*16*16*16));
    test1&=test2;
    memcpy(&aux,&test1,2);
    if ( A.Params[1][0].index != 0 ) {
        RegInt[A.Params[1][0].index].value(aux);
    }
    RegInt[A.Params[1][1].index].lastRead(PC);
    RegInt[A.Params[1][0].index].lastWrite(PC);
    RegInt[A.Params[1][0].index].stall(1);
    return 0;
}

int Vu::VU_FMEQ(VuInstruction &A)
{
    uint16 test1, test2;
    int16 aux;
    int st1;


    st1=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    aux=RegInt[A.Params[1][1].index].value();
    memcpy(&test1,&aux,2);
    test2=(uint16)(MacZ+(MacS*16)+(MacU*16*16)+(MacO*16*16*16));

    if(test1==test2)
        RegInt[A.Params[1][0].index].value(1);
    else
        RegInt[A.Params[1][0].index].value(0);

    RegInt[A.Params[1][1].index].lastRead(PC);
    RegInt[A.Params[1][0].index].lastWrite(PC);
    RegInt[A.Params[1][0].index].stall(1);
    return 0;
}

int Vu::VU_FMOR(VuInstruction &A)
{
    uint16 test1, test2;
    int16 aux;
    int st1;


    st1=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    aux=RegInt[A.Params[1][1].index].value();
    memcpy(&test1,&aux,2);
    test2=(uint16)(MacZ+(MacS*16)+(MacU*16*16)+(MacO*16*16*16));
    test1|=test2;
    memcpy(&aux,&test1,2);
    RegInt[A.Params[1][0].index].value(aux);
    RegInt[A.Params[1][1].index].lastRead(PC);
    RegInt[A.Params[1][0].index].lastWrite(PC);
    RegInt[A.Params[1][0].index].stall(1);
    return 0;
}



int Vu::VU_FSAND(VuInstruction &A)
{
    uint16 test1,test2;
    int16 aux;



    test1=(uint16)A.Params[1][1].udata;
    test2=(uint16)StatusFlag;

    test1&=test2;
    memcpy(&aux,&test1,2);
    RegInt[A.Params[1][0].index].value(aux);
    RegInt[A.Params[1][0].index].lastWrite(PC);
    RegInt[A.Params[1][0].index].stall(1);
    return 0;
}


int Vu::VU_FSEQ(VuInstruction &A)
{
    uint16 test1,test2;



    test1=(uint16)A.Params[1][1].udata;
    test2=(uint16)StatusFlag;

    if(test1==test2)
        RegInt[A.Params[1][0].index].value(1);
    else
        RegInt[A.Params[1][0].index].value(0);
    RegInt[A.Params[1][0].index].lastWrite(PC);
    RegInt[A.Params[1][0].index].stall(1);
    return 0;
}


int Vu::VU_FSOR(VuInstruction &A)
{
    uint16 test1,test2;
    int16 aux;



    test1=(uint16)A.Params[1][1].udata;
    test2=(uint16)StatusFlag;

    test1|=test2;
    memcpy(&aux,&test1,2);
    RegInt[A.Params[1][0].index].value(aux);
    RegInt[A.Params[1][0].index].lastWrite(PC);
    RegInt[A.Params[1][0].index].stall(1);
    return 0;
}

int Vu::VU_FSSET(VuInstruction &A)
{
    uint16 test1;

    test1=(uint16)A.Params[1][0].udata;
    test1&=(uint16)4032;  //111111000000
    StatusFlag&=63; //000000111111

    StatusFlag+=test1;
    return 0;
}

int
Vu::VU_IADD(VuInstruction &A) {
    int st1, st2;
    int32 v1,v2;


    st1=Stalling(A.Params[1][1]);
    st2=Stalling(A.Params[1][2]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;
    if(st2>0)
        return 3;

    v1 = RegInt[A.Params[1][1].index].value();
    v2 = RegInt[A.Params[1][2].index].value();
    if ( A.Params[1][0].index != 0 ) {
        RegInt[A.Params[1][0].index].value((uint16)(v1+v2));
    }

    RegInt[A.Params[1][1].index].lastRead(PC);
    RegInt[A.Params[1][2].index].lastRead(PC);
    RegInt[A.Params[1][0].index].lastWrite(PC);
    RegInt[A.Params[1][0].index].stall(1);
    return 0;
}

int
Vu::VU_IADDI(VuInstruction &A) {
    int st1;
    int32 v1,v2;


    st1=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0) {
        return 2;
    }

    v1 = RegInt[A.Params[1][1].index].value();
    v2 = A.Params[1][2].data;
    RegInt[A.Params[1][1].index].lastRead(PC);
    RegInt[A.Params[1][0].index].lastWrite(PC);
    RegInt[A.Params[1][0].index].stall(1);

    if ( A.Params[1][0].index != 0 ) {
        RegInt[A.Params[1][0].index].value((uint16)(v1+v2));
    }
    return 0;
}

int
Vu::VU_IADDIU(VuInstruction &A) {
    int st1;
    int16 v1,v3;
    st1 = Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1 > 0) {
        return 2;
    }


    v1 = RegInt[A.Params[1][1].index].value();
    v3 = (uint16)A.Params[1][2].udata;

    if ( A.Params[1][0].index != 0 ) {
        RegInt[A.Params[1][0].index].value((uint16)(v1+v3));
    }
    RegInt[A.Params[1][1].index].lastRead(PC);
    RegInt[A.Params[1][0].index].lastWrite(PC);
    RegInt[A.Params[1][0].index].stall(1);
    return 0;
}

int
Vu::VU_IAND(VuInstruction &A) {
    int st1, st2;
    int32 v1,v2;


    st1=Stalling(A.Params[1][1]);
    st2=Stalling(A.Params[1][2]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;
    if(st2>0)
        return 3;

    v1=RegInt[A.Params[1][1].index].value();
    v2=RegInt[A.Params[1][2].index].value();
    if ( A.Params[1][0].index != 0 ) {
        RegInt[A.Params[1][0].index].value((uint16)(v1&v2));
    }
    RegInt[A.Params[1][1].index].lastRead(PC);
    RegInt[A.Params[1][2].index].lastRead(PC);
    RegInt[A.Params[1][0].index].lastWrite(PC);
    RegInt[A.Params[1][0].index].stall(1);
    return 0;
}

int Vu::VU_IBEQ(VuInstruction &A)
{
    int st1, st2,a;


    st1=Stalling(A.Params[1][0]);
    st2=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;
    if(st2>0)
        return 3;

    RegInt[A.Params[1][0].index].lastRead(PC);
    RegInt[A.Params[1][1].index].lastRead(PC);
    if(RegInt[A.Params[1][0].index].value()==RegInt[A.Params[1][1].index].value()) {
        a=PC;
        CallBackFn(CallBackObj, LOWER, 6);
        PC++;
        Tic(); //delay slot itself
        PC=(uint16)a;
        CallBackFn(CallBackObj, LOWER, 7);
        if(A.Params[1][2].label[0])
            PC=(uint16)(A.Params[1][2].data-1);
        else //need to sub 1 because of the PC++ of the TIC instruction
            PC+=(uint16)(A.Params[1][2].data-1);
        return -1;
    }
    return 0;
}

int Vu::VU_IBGEZ(VuInstruction &A)
{
    int st1, a;


    st1=Stalling(A.Params[1][0]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    RegInt[A.Params[1][0].index].lastRead(PC);
    if(RegInt[A.Params[1][0].index].value()>=0) {
        a=PC;
        CallBackFn(CallBackObj, LOWER, 6);
        PC++;
        Tic(); //delay slot itself
        PC=(uint16)a;
        CallBackFn(CallBackObj, LOWER, 7);
        if(A.Params[1][1].label[0])
            PC=(uint16)(A.Params[1][1].data-1);
        else //need to sub 1 because of the PC++ of the TIC instruction
            PC+=(uint16)(A.Params[1][1].data-1);
        return -1;
    }
    return 0;
}

int Vu::VU_IBGTZ(VuInstruction &A)
{
    int st1, a;


    st1=Stalling(A.Params[1][0]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    RegInt[A.Params[1][0].index].lastRead(PC);
    if(RegInt[A.Params[1][0].index].value()>0) {
        a=PC;
        CallBackFn(CallBackObj, LOWER, 6);
        PC++;
        Tic(); //delay slot itself
        PC=(uint16)a;
        CallBackFn(CallBackObj, LOWER, 7);
        if(A.Params[1][1].label[0])
            PC=(uint16)(A.Params[1][1].data-1);
        else //need to sub 1 because of the PC++ of the TIC instruction
            PC+=(uint16)(A.Params[1][1].data-1);
        return -1;
    }
    return 0;
}

int Vu::VU_IBLEZ(VuInstruction &A)
{
    int st1, a;


    st1=Stalling(A.Params[1][0]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    RegInt[A.Params[1][0].index].lastRead(PC);
    if(RegInt[A.Params[1][0].index].value()<=0) {
        a=PC;
        CallBackFn(CallBackObj, LOWER, 6);
        PC++;
        Tic(); //delay slot itself
        PC=(uint16)a;
        CallBackFn(CallBackObj, LOWER, 7);
        if(A.Params[1][1].label[0])
            PC=(uint16)(A.Params[1][1].data-1);
        else //need to sub 1 because of the PC++ of the TIC instruction
            PC+=(uint16)(A.Params[1][1].data-1);
        return -1;
    }
    return 0;
}

int Vu::VU_IBLTZ(VuInstruction &A)
{
    int st1, a;
    st1=Stalling(A.Params[1][0]);
    if(st1>0) {
        return 2;
    }

    RegInt[A.Params[1][0].index].lastRead(PC);
    if(RegInt[A.Params[1][0].index].value()<0) {
        a=PC;
        CallBackFn(CallBackObj, LOWER, 6);
        PC++;
        Tic(); //delay slot itself
        PC=(uint16)a;
        CallBackFn(CallBackObj, LOWER, 7);
        if(A.Params[1][1].label[0])
            PC=(uint16)(A.Params[1][1].data-1);
        else //need to sub 1 because of the PC++ of the TIC instruction
            PC+=(uint16)(A.Params[1][1].data-1);
        return -1;
    }
    return 0;
}

int Vu::VU_IBNE(VuInstruction &A)
{
    int st1, st2,a;


    st1=Stalling(A.Params[1][0]);
    st2=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;
    if(st2>0)
        return 3;

    RegInt[A.Params[1][0].index].lastRead(PC);
    RegInt[A.Params[1][1].index].lastRead(PC);
    if(RegInt[A.Params[1][0].index].value()!=RegInt[A.Params[1][1].index].value()) {
        a = PC;
        //CallBackFn(CallBackObj, LOWER, 6);
        PC++;
        Tic();
        PC = (uint16)a;
        //CallBackFn(CallBackObj, LOWER, 7);
        if(A.Params[1][2].label[0]) {
            PC = (uint16)(A.Params[1][2].data-1);
        } else {
            PC += (uint16)(A.Params[1][2].data);
        }
        return -1;
    }
    return 0;
}

int Vu::VU_ILW(VuInstruction &A)
{
    int st1;
    char dst[50];
    int16 v1, v2;

    st1=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    RegInt[A.Params[1][0].index].lastWrite(PC);
    RegInt[A.Params[1][0].index].stall(4);
    RegInt[A.Params[1][1].index].lastRead(PC);
    v1 = RegInt[A.Params[1][1].index].value();
    v2 = (uint16)A.Params[1][1].data;

    if (A.dest[1][0])
        strcpy(dst,A.dest[1]);
    else
        strcpy(dst,"X");
    if(strstr(dst,"X"))
        MemVal16((uint16)(v2+v1),'X', &v2);
    if(strstr(dst,"Y"))
        MemVal16((uint16)(v2+v1),'Y', &v2);
    if(strstr(dst,"Z"))
        MemVal16((uint16)(v2+v1),'Z', &v2);
    if(strstr(dst,"W"))
        MemVal16((uint16)(v2+v1),'W', &v2);

    if ( A.Params[1][0].index != 0 ) {
        RegInt[A.Params[1][0].index].value(v2);
    }
    return 0;
}

int
Vu::VU_ILWR(VuInstruction &A) {
    int st1;
    char dst[50];
    int16 v1, v2;

    st1=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    RegInt[A.Params[1][0].index].lastWrite(PC);
    RegInt[A.Params[1][0].index].stall(4);
    RegInt[A.Params[1][1].index].lastRead(PC);
    v1=RegInt[A.Params[1][1].index].value();

    if (A.dest[1][0])
        strcpy(dst,A.dest[1]);
    else
        strcpy(dst,"X");
    if(strstr(dst,"X"))
        MemVal16(v1,'X', &v2);
    if(strstr(dst,"Y"))
        MemVal16(v1,'Y', &v2);
    if(strstr(dst,"Z"))
        MemVal16(v1,'Z', &v2);
    if(strstr(dst,"W"))
        MemVal16(v1,'W', &v2);

    if ( A.Params[1][0].index != 0 ) {
        RegInt[A.Params[1][0].index].value(v2);
    }
    return 0;
}

int
Vu::VU_IOR(VuInstruction &A) {
    int st1, st2;
    int32 v1,v2;


    st1=Stalling(A.Params[1][1]);
    st2=Stalling(A.Params[1][2]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;
    if(st2>0)
        return 3;

    v1=RegInt[A.Params[1][1].index].value();
    v2=RegInt[A.Params[1][2].index].value();
    if ( A.Params[1][0].index != 0 ) {
        RegInt[A.Params[1][0].index].value((uint16)(v1|v2));
    }

    RegInt[A.Params[1][1].index].lastRead(PC);
    RegInt[A.Params[1][2].index].lastRead(PC);
    RegInt[A.Params[1][0].index].lastWrite(PC);
    RegInt[A.Params[1][0].index].stall(1);
    return 0;
}

int Vu::VU_ISUB(VuInstruction &A)
{
    int st1, st2;
    int32 v1,v2;


    st1=Stalling(A.Params[1][1]);
    st2=Stalling(A.Params[1][2]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;
    if(st2>0)
        return 3;

    v1=RegInt[A.Params[1][1].index].value();
    v2=RegInt[A.Params[1][2].index].value();
    if ( A.Params[1][0].index != 0 ) {
        RegInt[A.Params[1][0].index].value((uint16)(v1-v2));
    }
    RegInt[A.Params[1][1].index].lastRead(PC);
    RegInt[A.Params[1][2].index].lastRead(PC);
    RegInt[A.Params[1][0].index].lastWrite(PC);
    RegInt[A.Params[1][0].index].stall(1);
    return 0;
}


int
Vu::VU_ISUBIU(VuInstruction &A) {
    int st1;
    int16 v2;
    int16 v1;

    st1 = Stalling(A.Params[1][1]);
    if(st1>0) {
        return 2;
    }
    v1 = RegInt[A.Params[1][1].index].value();
    v2 = (uint16)A.Params[1][2].udata;

    if ( A.Params[1][0].index != 0 ) {
        RegInt[A.Params[1][0].index].value((uint16)(v1-v2));
    }
    RegInt[A.Params[1][1].index].lastRead(PC);
    RegInt[A.Params[1][0].index].lastWrite(PC);
    RegInt[A.Params[1][0].index].stall(1);
    return 0;
}

int
Vu::VU_ISW(VuInstruction &A) {
    int st1;
    char dst[50];
    uint16 v1, v2;
    int16 v3;

    st1 = Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    RegInt[A.Params[1][0].index].lastRead(PC);
    RegInt[A.Params[1][1].index].lastRead(PC);
    v1 = RegInt[A.Params[1][1].index].value();
    v2 = (uint16)A.Params[1][1].data;
    v3 = RegInt[A.Params[1][0].index].value();

    if (A.dest[1][0]) {
        strcpy(dst,A.dest[1]);
    } else {
        strcpy(dst,"X");
    }
    if(strstr(dst,"X")) {
        MemSetVal16((uint16)(v2+v1),'X', v3);
    }
    if(strstr(dst,"Y")) {
        MemSetVal16((uint16)(v2+v1),'Y', v3);
    }
    if(strstr(dst,"Z")) {
        MemSetVal16((uint16)(v2+v1),'Z', v3);
    }
    if(strstr(dst,"W")) {
        MemSetVal16((uint16)(v2+v1),'W', v3);
    }
    return 0;
}


int
Vu::VU_ISWR(VuInstruction &A) {
    int st1;
    char dst[50];
    int16 v1, v2;

    st1 = Stalling(A.Params[1][1]);
    if(st1>0) {
        return 2;
    }
    RegInt[A.Params[1][0].index].lastRead(PC);
    RegInt[A.Params[1][1].index].lastRead(PC);
    v1 = RegInt[A.Params[1][1].index].value();
    v2 = RegInt[A.Params[1][0].index].value();

    if (strcmp(A.Params[1][1].sufix, ""))
        strcpy(dst, A.Params[1][1].sufix);
    else
        strcpy(dst,"x");
    if(strstr(dst,"x"))
        MemSetVal16(v1,'X', v2);
    if(strstr(dst,"y"))
        MemSetVal16(v1,'Y', v2);
    if(strstr(dst,"z"))
        MemSetVal16(v1,'Z', v2);
    if(strstr(dst,"w"))
        MemSetVal16(v1,'W', v2);
    return 0;
}

int Vu::VU_JARL(VuInstruction &A)
{
    int a;

    RegInt[A.Params[1][1].index].lastRead(PC);
    RegInt[A.Params[1][0].index].lastWrite(PC);
    RegInt[A.Params[1][0].index].stall(2);
    RegInt[A.Params[1][0].index].value((uint16)(PC+2));

    a=PC;
    PC++;
    Tic(); //delay slot itself
    PC=(uint16)a;

    PC= (uint16)(RegInt[A.Params[1][1].index].value()-1);
    return -1;
}

int
Vu::VU_JR(VuInstruction &A) {
    int a;

    RegInt[A.Params[1][0].index].lastRead(PC);
    a=PC;
    PC++;
    Tic(); //delay slot itself
    PC=(uint16)a;
    PC=(uint16)(RegInt[A.Params[1][0].index].value()-1);
    return -1;
}

int Vu::VU_LQ(VuInstruction &A)
{
    char dst[50];
    int st1;
    int16 v1, v2;
    float vx,vy,vz,vw;


    st1=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    RegInt[A.Params[1][1].index].lastRead(PC);
    v1 = RegInt[A.Params[1][1].index].value();
    v2 = (uint16)A.Params[1][1].data;
    // memcpy(&vx, &(dataMem[v1+v2].x),4);
    // memcpy(&vy, &(dataMem[v1+v2].y),4);
    // memcpy(&vz, &(dataMem[v1+v2].z),4);
    // memcpy(&vw, &(dataMem[v1+v2].w),4);
    vx = m_pVuMem->ReadFloatX(v1+v2);
    vy = m_pVuMem->ReadFloatY(v1+v2);
    vz = m_pVuMem->ReadFloatZ(v1+v2);
    vw = m_pVuMem->ReadFloatW(v1+v2);
    RegFloat[A.Params[1][0].index].stall(4);
    RegFloat[A.Params[1][0].index].lastWrite(PC);

    if ( A.Params[1][0].index == 0 ) {
        return 0;
    }

    if (A.dest[1][0])
        strcpy(dst,A.dest[1]);
    else
        strcpy(dst,"XYZW");
    if(strstr(dst,"X"))
        RegFloat[A.Params[1][0].index].x(vx);
    if(strstr(dst,"Y"))
        RegFloat[A.Params[1][0].index].y(vy);
    if(strstr(dst,"Z"))
        RegFloat[A.Params[1][0].index].z(vz);
    if(strstr(dst,"W"))
        RegFloat[A.Params[1][0].index].w(vw);

    return 0;
}

int Vu::VU_LQD(VuInstruction &A)
{
    char dst[50];
    int st1;
    int16 v1;
    int32 vx,vy,vz,vw;


    st1=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    RegInt[A.Params[1][1].index].lastRead(PC);
    RegInt[A.Params[1][1].index].lastWrite(PC);
    v1=RegInt[A.Params[1][1].index].value();
    v1--;
    RegInt[A.Params[1][1].index].value(v1);

    vx = m_pVuMem->ReadFloatX(v1);
    vy = m_pVuMem->ReadFloatY(v1);
    vz = m_pVuMem->ReadFloatZ(v1);
    vw = m_pVuMem->ReadFloatW(v1);
    // vx=dataMem[v1].x;
    // vy=dataMem[v1].y;
    // vz=dataMem[v1].z;
    // vw=dataMem[v1].w;

    RegFloat[A.Params[1][0].index].stall(4);
    RegInt[A.Params[1][1].index].stall(4);
    RegFloat[A.Params[1][0].index].lastWrite(PC);

    if ( A.Params[1][0].index == 0 ) {
        return 0;
    }

    if (A.dest[1][0])
        strcpy(dst,A.dest[1]);
    else
        strcpy(dst,"XYZW");
    if(strstr(dst,"X"))
        RegFloat[A.Params[1][0].index].mwrite(&vx,0);
    if(strstr(dst,"Y"))
        RegFloat[A.Params[1][0].index].mwrite(&vy,1);
    if(strstr(dst,"Z"))
        RegFloat[A.Params[1][0].index].mwrite(&vz,2);
    if(strstr(dst,"W"))
        RegFloat[A.Params[1][0].index].mwrite(&vw,3);
    return 0;
}

int Vu::VU_LQI(VuInstruction &A)
{
    char dst[50];
    int st1;
    int16 v1;
    int32 vx,vy,vz,vw;


    st1=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    RegInt[A.Params[1][1].index].lastRead(PC);
    RegInt[A.Params[1][1].index].lastWrite(PC);
    v1=RegInt[A.Params[1][1].index].value();

    vx = m_pVuMem->ReadFloatX(v1);
    vy = m_pVuMem->ReadFloatY(v1);
    vz = m_pVuMem->ReadFloatZ(v1);
    vw = m_pVuMem->ReadFloatW(v1);
    // vx=dataMem[v1].x;
    // vy=dataMem[v1].y;
    // vz=dataMem[v1].z;
    // vw=dataMem[v1].w;
    v1++;
    RegFloat[A.Params[1][0].index].stall(4);
    RegInt[A.Params[1][1].index].stall(4);
    RegFloat[A.Params[1][0].index].lastWrite(PC);
    if ( A.Params[1][1].index != 0 ) {
        RegInt[A.Params[1][1].index].value(v1);
    }
    if ( A.Params[1][0].index == 0 ) {
        return 0;
    }
    if (A.dest[1][0])
        strcpy(dst,A.dest[1]);
    else
        strcpy(dst,"XYZW");
    if(strstr(dst,"X"))
        RegFloat[A.Params[1][0].index].mwrite(&vx,0);
    if(strstr(dst,"Y"))
        RegFloat[A.Params[1][0].index].mwrite(&vy,1);
    if(strstr(dst,"Z"))
        RegFloat[A.Params[1][0].index].mwrite(&vz,2);
    if(strstr(dst,"W"))
        RegFloat[A.Params[1][0].index].mwrite(&vw,3);
    return 0;
}

int Vu::VU_MFIR(VuInstruction &A)
{
    char dst[50];
    int st1;
    int16 v1;
    int32 v2;

    st1 = Stalling(A.Params[1][1]);
    if(st1>0)
        return 2;

    RegInt[A.Params[1][1].index].lastRead(PC);
    RegFloat[A.Params[1][0].index].lastWrite(PC);

    v1 = RegInt[A.Params[1][1].index].value();
    v2 = v1;

    if (A.dest[1][0])
        strcpy(dst,A.dest[1]);
    else
        strcpy(dst,"XYZW");

    WriteFloatRegister(
        A.Params[1][0].index,
        dst,
        v2, v2, v2, v2
        );

    // if(strstr(dst,"X"))
    //     RegFloat[A.Params[1][0].index].mwrite(&v2,0);
    // if(strstr(dst,"Y"))
    //     RegFloat[A.Params[1][0].index].mwrite(&v2,1);
    // if(strstr(dst,"Z"))
    //     RegFloat[A.Params[1][0].index].mwrite(&v2,2);
    // if(strstr(dst,"W"))
    //     RegFloat[A.Params[1][0].index].mwrite(&v2,3);

    RegFloat[A.Params[1][0].index].stall(4);
    return 0;
}


int Vu::VU_MFP(VuInstruction &A)
{
    char dst[50];
    float d1;
    int st1;


    st1=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    P.lastRead(PC);
    RegFloat[A.Params[1][0].index].lastWrite(PC);

    d1=P.x();

    if (A.dest[1][0])
        strcpy(dst,A.dest[1]);
    else
        strcpy(dst,"XYZW");
    if(strstr(dst,"X"))
        RegFloat[A.Params[1][0].index].x(d1);
    if(strstr(dst,"Y"))
        RegFloat[A.Params[1][0].index].y(d1);
    if(strstr(dst,"Z"))
        RegFloat[A.Params[1][0].index].z(d1);
    if(strstr(dst,"W"))
        RegFloat[A.Params[1][0].index].w(d1);

    RegFloat[A.Params[1][0].index].stall(4);
    return 0;
}

int Vu::VU_MOVE(VuInstruction &A)
{
    char dst[50];
    int st1;

    st1=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    RegFloat[A.Params[1][1].index].lastRead(PC);
    RegFloat[A.Params[1][0].index].lastWrite(PC);
    RegFloat[A.Params[1][0].index].stall(4);
    if ( A.Params[1][0].index == 0 ) {
        return 0;
    }

    if (A.dest[1][0])
        strcpy(dst,A.dest[1]);
    else
        strcpy(dst,"XYZW");
    if(strstr(dst,"X"))
        RegFloat[A.Params[1][0].index].x(RegFloat[A.Params[1][1].index].x());
    if(strstr(dst,"Y"))
        RegFloat[A.Params[1][0].index].y(RegFloat[A.Params[1][1].index].y());
    if(strstr(dst,"Z"))
        RegFloat[A.Params[1][0].index].z(RegFloat[A.Params[1][1].index].z());
    if(strstr(dst,"W"))
        RegFloat[A.Params[1][0].index].w(RegFloat[A.Params[1][1].index].w());

    return 0;
}

int Vu::VU_MR32(VuInstruction &A)
{
    char dst[50];
    int st1;

    st1=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    RegFloat[A.Params[1][1].index].lastRead(PC);
    RegFloat[A.Params[1][0].index].lastWrite(PC);
    RegFloat[A.Params[1][0].index].stall(4);

    if ( A.Params[1][0].index == 0 ) {
        return 0;
    }

    if (A.dest[1][0])
        strcpy(dst,A.dest[1]);
    else
        strcpy(dst,"XYZW");
    if(strstr(dst,"X"))
        RegFloat[A.Params[1][0].index].x(RegFloat[A.Params[1][1].index].y());
    if(strstr(dst,"Y"))
        RegFloat[A.Params[1][0].index].y(RegFloat[A.Params[1][1].index].z());
    if(strstr(dst,"Z"))
        RegFloat[A.Params[1][0].index].z(RegFloat[A.Params[1][1].index].w());
    if(strstr(dst,"W"))
        RegFloat[A.Params[1][0].index].w(RegFloat[A.Params[1][1].index].x());

    return 0;
}

int Vu::VU_MTIR(VuInstruction &A)
{
    int st1;
    float d1;
    int16 v1;


    st1=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    RegInt[A.Params[1][0].index].lastWrite(PC);
    RegFloat[A.Params[1][1].index].lastRead(PC);

    if(toupper(A.Params[1][1].sufix[0])=='X')
        d1=RegFloat[A.Params[1][1].index].x();
    if(toupper(A.Params[1][1].sufix[0])=='Y')
        d1=RegFloat[A.Params[1][1].index].y();
    if(toupper(A.Params[1][1].sufix[0])=='Z')
        d1=RegFloat[A.Params[1][1].index].z();
    if(toupper(A.Params[1][1].sufix[0])=='W')
        d1=RegFloat[A.Params[1][1].index].w();
    memcpy(&v1,&d1,2);
    RegInt[A.Params[1][0].index].value(v1);
    RegInt[A.Params[1][0].index].stall(4);
    return 0;
}


int Vu::VU_RGET(VuInstruction &A)
{
    int st1;
    st1 = Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    R.lastRead(PC);
    RegFloat[A.Params[1][0].index].lastWrite(PC);
    RegFloat[A.Params[1][0].index].stall(4);
    if ( A.Params[1][0].index == 0 ) {
        return 0;
    }
    if(toupper(A.Params[1][1].sufix[0])=='X')
        RegFloat[A.Params[1][0].index].x(R.x());
    if(toupper(A.Params[1][1].sufix[0])=='Y')
        RegFloat[A.Params[1][0].index].y(R.x());
    if(toupper(A.Params[1][1].sufix[0])=='Z')
        RegFloat[A.Params[1][0].index].z(R.x());
    if(toupper(A.Params[1][1].sufix[0])=='W')
        RegFloat[A.Params[1][0].index].w(R.x());
    return 0;
}

int Vu::VU_RINIT(VuInstruction &A)
{
    int st1;
    st1 = Stalling(A.Params[1][1]);
    if(st1>0)
        return 2;
    R.lastRead(PC);
    RegFloat[A.Params[1][1].index].lastWrite(PC);
    R.stall(4);
    if(toupper(A.Params[1][1].sufix[0])=='X')
        R.x(RegFloat[A.Params[1][1].index].x());
    if(toupper(A.Params[1][1].sufix[0])=='Y')
        R.x(RegFloat[A.Params[1][1].index].y());
    if(toupper(A.Params[1][1].sufix[0])=='Z')
        R.x(RegFloat[A.Params[1][1].index].z());
    if(toupper(A.Params[1][1].sufix[0])=='W')
        R.x(RegFloat[A.Params[1][1].index].w());
    return 0;
}

int Vu::VU_RNEXT(VuInstruction &A)
{
    int st1;
    float v1;
    v1 = (float)((float)rand()/(float)RAND_MAX)+1.0;
    st1 = Stalling(A.Params[1][1]);
    //ths instruction can not return a warning
    if(st1>0)
        return 2;
    // rand;
    R.x(v1);
    R.lastRead(PC);
    R.lastWrite(PC);
    RegFloat[A.Params[1][0].index].lastWrite(PC);

    if(toupper(A.Params[1][1].sufix[0])=='X')
        RegFloat[A.Params[1][0].index].x(R.x());
    if(toupper(A.Params[1][1].sufix[0])=='Y')
        RegFloat[A.Params[1][0].index].y(R.x());
    if(toupper(A.Params[1][1].sufix[0])=='Z')
        RegFloat[A.Params[1][0].index].z(R.x());
    if(toupper(A.Params[1][1].sufix[0])=='W')
        RegFloat[A.Params[1][0].index].w(R.x());

    RegFloat[A.Params[1][0].index].stall(4);
    return 0;
}


int Vu::VU_RSQRT(VuInstruction &A)
{
    int st1, st2;
    float d1,d2;

    st1=Stalling(A.Params[1][1]);
    st2=Stalling(A.Params[1][2]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;
    if(st2>0)
        return 3;

    if(toupper(A.Params[1][1].sufix[0])=='X')
        d1=RegFloat[A.Params[1][1].index].x();
    if(toupper(A.Params[1][1].sufix[0])=='Y')
        d1=RegFloat[A.Params[1][1].index].y();
    if(toupper(A.Params[1][1].sufix[0])=='Z')
        d1=RegFloat[A.Params[1][1].index].z();
    if(toupper(A.Params[1][1].sufix[0])=='W')
        d1=RegFloat[A.Params[1][1].index].w();

    if(toupper(A.Params[1][2].sufix[0])=='X')
        d2=RegFloat[A.Params[1][2].index].x();
    if(toupper(A.Params[1][2].sufix[0])=='Y')
        d2=RegFloat[A.Params[1][2].index].y();
    if(toupper(A.Params[1][2].sufix[0])=='Z')
        d2=RegFloat[A.Params[1][2].index].z();
    if(toupper(A.Params[1][2].sufix[0])=='W')
        d2=RegFloat[A.Params[1][2].index].w();

    if(d2==0.0 && d1==0.0) {
        StatusFlag|=16;   //Ivalid op 0/0;
    } else if(d2==0.0) {
        StatusFlag|=32;   //division by 0;
    } else {
        Q.x(d1/sqrt(d2));
        Q.y(d1/sqrt(d2));
        Q.z(d1/sqrt(d2));
        Q.w(d1/sqrt(d2));
    }

    RegInt[A.Params[1][1].index].lastRead(PC);
    RegInt[A.Params[1][2].index].lastRead(PC);
    Q.lastWrite(PC);
    Q.stall(13);
    return 0;
}

int Vu::VU_RXOR(VuInstruction &A)
{
    int st1;
    int32 v1,v2;

    st1=Stalling(A.Params[1][1]);
    // randomize(); //init rnd seed
    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    R.lastWrite(PC);
    RegFloat[A.Params[1][1].index].lastRead(PC);
    R.mcopy(&v1, 0);

    if(toupper(A.Params[1][1].sufix[0])=='X')
        RegFloat[A.Params[1][1].index].mcopy(&v2, 0);
    if(toupper(A.Params[1][1].sufix[0])=='Y')
        RegFloat[A.Params[1][1].index].mcopy(&v2, 1);
    if(toupper(A.Params[1][1].sufix[0])=='Z')
        RegFloat[A.Params[1][1].index].mcopy(&v2, 2);
    if(toupper(A.Params[1][1].sufix[0])=='W')
        RegFloat[A.Params[1][1].index].mcopy(&v2, 3);

    v1^=v2;
    R.mwrite(&v1,0);
    R.stall(1);
    return 0;
}

int
Vu::VU_SQ(VuInstruction &A) {
    char dst[50];
    int st1, st2;
    int16 v1, v2;
    int32 vx,vy,vz,vw;

    st1=Stalling(A.Params[1][0]);
    st2=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0) {
        return 2;
    }
    if(st2>0) {
        return 3;
    }

    RegInt[A.Params[1][1].index].lastRead(PC);
    RegFloat[A.Params[1][0].index].lastRead(PC);
    v1=RegInt[A.Params[1][1].index].value();
    v2=(uint16)A.Params[1][1].data;

    RegFloat[A.Params[1][0].index].mcopy(&vx,0);
    RegFloat[A.Params[1][0].index].mcopy(&vy,1);
    RegFloat[A.Params[1][0].index].mcopy(&vz,2);
    RegFloat[A.Params[1][0].index].mcopy(&vw,3);

    if (A.dest[1][0]) {
        strcpy(dst,A.dest[1]);
    } else {
        strcpy(dst,"XYZW");
    }
    if(strstr(dst,"X")) {
        m_pVuMem->WriteX(v1+v2, vx);
        // memcpy(&(dataMem[v1+v2].x),&vx,4);
    }
    if(strstr(dst,"Y")) {
        m_pVuMem->WriteY(v1+v2, vy);
        // memcpy(&(dataMem[v1+v2].y),&vy,4);
    }
    if(strstr(dst,"Z")) {
        m_pVuMem->WriteZ(v1+v2, vz);
        // memcpy(&(dataMem[v1+v2].z),&vz,4);
    }
    if(strstr(dst,"W")) {
        m_pVuMem->WriteW(v1+v2, vw);
        // memcpy(&(dataMem[v1+v2].w),&vw,4);
    }
    return 0;
}

int
Vu::VU_SQD(VuInstruction &A) {
    char dst[50];
    int st1,st2;
    int16 v1;
    int32 vx,vy,vz,vw;

    st1=Stalling(A.Params[1][0]);
    st2=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;
    if(st2>0)
        return 3;

    RegFloat[A.Params[1][0].index].lastRead(PC);
    RegInt[A.Params[1][1].index].lastRead(PC);
    RegInt[A.Params[1][1].index].lastWrite(PC);
    v1 = RegInt[A.Params[1][1].index].value();
    v1--;
    if ( A.Params[1][1].index != 0 ) {
        RegInt[A.Params[1][1].index].value(v1);
    }

    RegFloat[A.Params[1][0].index].mcopy(&vx,0);
    RegFloat[A.Params[1][0].index].mcopy(&vy,1);
    RegFloat[A.Params[1][0].index].mcopy(&vz,2);
    RegFloat[A.Params[1][0].index].mcopy(&vw,3);

    if (A.dest[1][0]) {
        strcpy(dst,A.dest[1]);
    } else {
        strcpy(dst,"XYZW");
    }
    if(strstr(dst,"X")) {
        // memcpy(&(dataMem[v1].x),&vx,4);
        m_pVuMem->WriteX(v1, vx);
    }
    if(strstr(dst,"Y")) {
        // memcpy(&(dataMem[v1].y),&vy,4);
        m_pVuMem->WriteY(v1, vy);
    }
    if(strstr(dst,"Z")) {
        // memcpy(&(dataMem[v1].z),&vz,4);
        m_pVuMem->WriteZ(v1, vz);
    }
    if(strstr(dst,"W")) {
        // memcpy(&(dataMem[v1].w),&vw,4);
        m_pVuMem->WriteW(v1, vw);
    }

    RegInt[A.Params[1][1].index].stall(4);
    return 0;
}

int Vu::VU_SQI(VuInstruction &A)
{
    char dst[50];
    int st1, st2;
    int16 v1;
    int32 vx,vy,vz,vw;

    st1=Stalling(A.Params[1][0]);
    st2=Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;
    if(st2>0)
        return 3;

    RegFloat[A.Params[1][0].index].lastRead(PC);
    RegInt[A.Params[1][1].index].lastRead(PC);
    v1 = RegInt[A.Params[1][1].index].value();

    RegFloat[A.Params[1][0].index].mcopy(&vx,0);
    RegFloat[A.Params[1][0].index].mcopy(&vy,1);
    RegFloat[A.Params[1][0].index].mcopy(&vz,2);
    RegFloat[A.Params[1][0].index].mcopy(&vw,3);

    if (A.dest[1][0])
        strcpy(dst,A.dest[1]);
    else
        strcpy(dst,"XYZW");
    if(strstr(dst,"X")) {
        // memcpy(&(dataMem[v1].x),&vx,4);
        m_pVuMem->WriteX(v1, vx);
    }
    if(strstr(dst,"Y")) {
        // memcpy(&(dataMem[v1].y),&vy,4);
        m_pVuMem->WriteY(v1, vy);
    }
    if(strstr(dst,"Z")) {
        // memcpy(&(dataMem[v1].z),&vz,4);
        m_pVuMem->WriteZ(v1, vz);
    }
    if(strstr(dst,"W")) {
        // memcpy(&(dataMem[v1].w),&vw,4);
        m_pVuMem->WriteW(v1, vw);
    }

    v1++;
    if ( A.Params[1][1].index != 0 ) {
        RegInt[A.Params[1][1].index].value(v1);
    }
    RegInt[A.Params[1][1].index].stall(4);
    RegInt[A.Params[1][1].index].lastWrite(PC);
    return 0;
}

int
Vu::VU_SQRT(VuInstruction &A) {
    int st1;
    float d1;

    st1 = Stalling(A.Params[1][1]);

    //ths instruction can not return a warning
    if(st1>0)
        return 2;

    if(toupper(A.Params[1][1].sufix[0])=='X')
        d1=RegFloat[A.Params[1][1].index].x();
    if(toupper(A.Params[1][1].sufix[0])=='Y')
        d1=RegFloat[A.Params[1][1].index].y();
    if(toupper(A.Params[1][1].sufix[0])=='Z')
        d1=RegFloat[A.Params[1][1].index].z();
    if(toupper(A.Params[1][1].sufix[0])=='W')
        d1=RegFloat[A.Params[1][1].index].w();

    if(d1!=0.0) {
        Q.x(sqrt(d1));
        Q.y(sqrt(d1));
        Q.z(sqrt(d1));
        Q.w(sqrt(d1));
    }

    RegInt[A.Params[1][1].index].lastRead(PC);
    Q.lastWrite(PC);
    Q.stall(18);
    return 0;
}

int
Vu::VU_WAITP(void) {
    while(P.stall()) {
        program[PC].tics++;
        m_clock++;
        DecStall(); //dec stall registers
        Instr.DecThroughput(); //dec throughput counter
    }
    return 0;
}

int
Vu::VU_WAITQ(void) {
    while(Q.stall()) {
        program[PC].tics++;
        m_clock++;
        DecStall(); //dec stall registers
        Instr.DecThroughput(); //dec throughput counter
    }
    return 0; 
}

int
Vu::VU_XGKICK(VuInstruction &A) {
    uint32 start = RegInt[A.Params[1][0].index].value();
    if ( start > 1023 ) {
        return -1;
    }
    return start;
}

int
Vu::VU_XITOP(VuInstruction &A) {
    RegInt[A.Params[1][0].index].value(0);
    return 0;
}

int
Vu::VU_XTOP(VuInstruction &A) {
    RegInt[A.Params[1][0].index].value(0);
    return 0;
}

int
Vu::VU_LOI_LOWER(VuInstruction &A) {
    m_lowerFloatTemp.x(A.Params[1][0].fdata);
    m_lowerFloatTemp.y(A.Params[1][0].fdata);
    m_lowerFloatTemp.z(A.Params[1][0].fdata);
    m_lowerFloatTemp.w(A.Params[1][0].fdata);
    I.lastWrite(PC);
    I.stall(1);
    m_specialRegisterWrite = true;
    m_specialFloatIndex = 1;
    return 0;
}

}
