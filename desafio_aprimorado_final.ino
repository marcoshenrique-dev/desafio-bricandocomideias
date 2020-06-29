/*
    
                  FORMULÁRIO INICIAL:
                   
 
  Autor: Marcos Henrique (Robótica e desafios)
  
  LINK:   https://www.youtube.com/channel/UC3ZaLCltfI-34EQaZmWFaeg?view_as=subscriber
    
 SKETCH:  desafio_aprimorado_final
 
  
     
 Data: 11/07/2019

                      

    

    COMENTÁRIOS:

                             --dia 08/07/2019--
  
                       começei a adicionar a função que 
                       regula o tempo de inatividade do
                       cliente ou usuário desse projeto
                       onde com um determinado tempo sem
                       tentar adicionar um numero ele zera
                       a variável posição responsável por
                       adicionar valor a senha tentativa
                       fazendo com que assim o utilizador
                       tenha mais segurança.     



                              --dia 11/07/2019--



                       Finalizei o desafio por completo

                              

*/

//------------------------BIBLIOTECAS-----------------------------


#include <EEPROM.h>//Biblioteca para usar a EEPROM para armazenar a senha

//-------------------------------------------------------

int atividade=10000;//TEMPO DE CONTROLE DA INATIVIDADE


//------------------------------DEFINIÇÕES ----------------------------


const byte qtPinosLEDS=8;//QUANTIDADE DE PINOS USADA NO ARRAY ABAIXO

byte Leds[qtPinosLEDS] = { 13 , 12  , 11 , 10 , 9 , 8 , 7 , 6  };//ARRAY DOS LEDS


#define espacoEEPROM 1000

//pino do potenciômetro:---------------------------------
#define pinP A0


// buzzer:----------------------------------------------
#define Buzzer 5





//pino do botao:-------------------------------------------
#define pinB 3

//pino da carga:------------------------------------------
#define pinRele 4


//-------------------------VARIÁVEIS GLOBAIS-----------------------------


//Quantidade de dígitos:
  
    const byte qtDigitos=5;
  




//array que vai armazenar a tentativa de senha:

   int senhaTentativa[qtDigitos]={0,0,0,0,0};





bool pausa;//VARIÁVEL USADA PARA ACIONAR O MODO SALVAR SENHA

int posicao=-1;//POSIÇÃO QUE SERÁ INCREMENTADA NO MODO TENTATIVA SENHA

int tempo= 500;//TEMPO DE PISCA

//----contagem - pisca----

bool piscada=false;
bool piscada2=false;
int valorAtual=0;
int valorAtual2=0;

//-----------------------

//VARIÁVEIS DE CONTROLE DE DEBOUNC E DE PISCA

bool valordasenha=false;

int mapeado;

int verifica;

unsigned long debouncB;

boolean estadoAnterior=HIGH;

unsigned long delayPisca;

int valorDebounc=200;

bool pronto=true;

bool estadoS=LOW;

int posicao2=0;

bool enquanto=false;

unsigned long tempo_atual=0;

unsigned long ultimo_tempo=0;









void setup() {

//------------------
Serial.begin(9600);
//------------------  
  
  int np=0;

  while( np< qtPinosLEDS){//WHILE QUE VAI DEFINIR O MODO DOS PINOS DOS LEDS

pinMode(Leds[np], OUTPUT);  
    np++;
  }
 


        
  
 

pinMode(pinB,INPUT);


pinMode(Buzzer,OUTPUT);
pinMode(pinRele,OUTPUT);
 
  
  digitalWrite(pinRele,!LOW);//O RELE POSSUI ESTADO INVERTIDO
  
}

void loop() {

  int lendo=analogRead(pinP);//LEITURA DO POTENCIOMETRO

mapeado=map(lendo,0,1023,1,9); //MAPEANDO A SUA POSICAO PARA QUANTIDADE DE LEDS
//========================================
bool estadoB=digitalRead(pinB);//LENDO O BOTAO
//======================================

int pino=digitalRead(3);

//===================================

tempo_atual=millis();//FAZENDO A CONTAGEM DE TEMPO APERTADO

//=======================================================
if(pino==0){//SETANDO O TEMPO QUE O BOTAO FOI APERTADO ATE QUE SE IGUALE A 1

ultimo_tempo=tempo_atual;

  
}


  




//---------------setando Variáveis de acordo com botão-------------------------------------------------------

if((pino==1)  && (tempo_atual-ultimo_tempo>1000)){//CASO SEJA PRESSIONADO POR 2 SEGUNDOS
    posicao=-1;
    piscada2=true;
    piscada=true;
    valorAtual=0;
    valorAtual2=0;
    pronto=false;
    pausa=false;
  
  enquanto=true;
  digitalWrite(Buzzer,LOW);
 digitalWrite(pinRele,!LOW);
  ultimo_tempo=tempo_atual;
 
   
}//SETA VARIÁVEIS DE CONTROLE PARA SALVAR A SENHA
////////////////--se pino for apertado e ficar 1 segundo pressionado--------------------
if(enquanto){

pisca(2);//FUNÇÃO QUE RECEBE PARAMETRO DE QUANTAS VEZES É PARA PISCAR

 
 
if(pausa==true){//adicona valor na senha




if((millis()-debouncB)>valorDebounc){//CONTROLE DO DEBOUNC
   
    if(estadoB && estadoAnterior){
      posicao2++;//POSICAO SOMA E ARMAZENA O VALOR DE MAPEADO NO BOTÃO
      EEPROM.write(posicao2,mapeado);
   
     
      debouncB=millis();//SETA O MILLIS();
    }


 if(posicao2==5){//se terminar aciona função que usa a senha

 
      pisca2(3);//FUNÇÃO QUE RECEBE PARAMETRO PARA MOSTRAR COM PISCAS QUE A SENHA FOI SALVA
   
       pronto=true;
     
      
      
      
     
    
       
      
    }
    
  }
  
     }
  
    
  }
     
   
     
  
    
     
      
  
   


//--------------------------------------------------------------------------------

    
if(pronto){// nessa função testa se a tentativa de senha é igual a senha

if((pino==0)&&(millis()-debouncB)>atividade){//SE FICAR INATIVO POR 10 SEGUNDOS :

verificaAtividade();//EXECUTA ESSA FUNÇÃO QUE ESTÁ MAIS ABAIXO

}


if((millis()-debouncB)>valorDebounc){
   
    if(pino && estadoAnterior){

     
      posicao++;//ARMAZENA VALOR NA TENTATIVA DE SENHA A PARTIR DO BOTÃO E DA POSIÇÃO DO POTENCIOMETRO
      
      senhaTentativa[posicao]=mapeado;
      
      debouncB=millis();
    }

////////////////controle da quantidade de caracteres armazenados e se a senha esta correta///////    
 if(posicao==4){//QUANDO ATINGIR 4 
  if(senhaTentativa[0]==EEPROM.read(1)){//VERIFICA SE O VALOR DA PRIMEIRA POSIÇÃO É IGUAL AO CADASTRADO NO 0
   if(senhaTentativa[1]==EEPROM.read(2)){//1
   if(senhaTentativa[2]==EEPROM.read(3)){//2
   if(senhaTentativa[3]==EEPROM.read(4)){//3
    if(senhaTentativa[4]==EEPROM.read(5)){//4 DO ARRAY

 
   digitalWrite(pinRele,!HIGH);// SE FOREM IGUAIS LIGA O RELE E DESLIGA O BUZZER
   digitalWrite(Buzzer,LOW);
      posicao=-1;//ALEM DE SETAR AS VARIÁVEIS DE POSIÇÃO
      enquanto=false;
    }
    
  }
  
     }
  
    
  }
     }
   }
     if(posicao==4){//se estiver errada liga o buzzer e desativa o rele
  if(senhaTentativa[0]!=EEPROM.read(1) || senhaTentativa[1]!=EEPROM.read(2) ||senhaTentativa[2]!=EEPROM.read(3) || senhaTentativa[3]!=EEPROM.read(4) || senhaTentativa[4]!=EEPROM.read(5)){
digitalWrite(Buzzer,HIGH);
digitalWrite(pinRele,!LOW);
posicao=-1;

  }
    }
     }
      
}
   



  
  
  









/////////////////////////////////////controle dos leds para que pisquem/////////////////

if(mapeado==1){//SE O POTENCIOMETRO ESTIVER NA POSICAO 0:
 if ((millis()-delayPisca)<tempo){

   
   digitalWrite(Leds[0],LOW);
   digitalWrite(Leds[7],LOW);

   
 }else if((millis()-delayPisca)<tempo*2){
  
  digitalWrite(Leds[0],HIGH);
 
 }else{
  delayPisca=millis();
  
  digitalWrite(Leds[0],LOW);
   digitalWrite(Leds[1],LOW);

 
  
  
 
 

 
}

}

//////////////////////////////////////////////////////////
if(mapeado==2){
 if ((millis()-delayPisca)<tempo){
  digitalWrite(Leds[0],LOW);
   digitalWrite(Leds[1],LOW);
   
 }else if((millis()-delayPisca)<tempo*2){
 
  digitalWrite(Leds[1],HIGH);
 
 }else{
  delayPisca=millis();
  digitalWrite(Leds[1],LOW);
   digitalWrite(Leds[2],LOW);
   

  
  
  
 
 

 
}
}

//////////////////////////////////////////////////////////
if(mapeado==3){
 if ((millis()-delayPisca)<tempo){
  digitalWrite(Leds[1],LOW);
   digitalWrite(Leds[2],LOW);
   
   
 }else if((millis()-delayPisca)<tempo*2){
  digitalWrite(Leds[2],HIGH);
 
 }else{
  delayPisca=millis();
  digitalWrite(Leds[2],LOW);
   digitalWrite(Leds[3],LOW);
   

  
  
  
 
 

 
}

}

//////////////////////////////////////////////////////////
if(mapeado==4){
 if ((millis()-delayPisca)<tempo){
  digitalWrite(Leds[2],LOW);
   
  digitalWrite(Leds[3],LOW);
   
 }else if((millis()-delayPisca)<tempo*2){
  digitalWrite(Leds[3],HIGH);
 
 }else{
  delayPisca=millis();
  digitalWrite(Leds[3],LOW);
  digitalWrite(Leds[4],LOW);

  
  
  
 
 

 
}

}

//////////////////////////////////////////////////////////
if(mapeado==5){
 if ((millis()-delayPisca)<tempo){
  digitalWrite(Leds[3],LOW);
  digitalWrite(Leds[4],LOW);
   
 }else if((millis()-delayPisca)<tempo*2){
  digitalWrite(Leds[4],HIGH);
 
 }else{
  delayPisca=millis();
  digitalWrite(Leds[4],LOW);
  digitalWrite(Leds[5],LOW);

  
  
  
 
 

 
}

}

//////////////////////////////////////////////////////////
if(mapeado==6){
 if ((millis()-delayPisca)<tempo){
   digitalWrite(Leds[4],LOW);
  digitalWrite(Leds[5],LOW);
   
 }else if((millis()-delayPisca)<tempo*2){
  digitalWrite(Leds[5],HIGH);
 
 }else{
  delayPisca=millis();
   digitalWrite(Leds[5],LOW);
  digitalWrite(Leds[6],LOW);

  
  
  
 
 

 
}

}

//////////////////////////////////////////////////////////
if(mapeado==7){
 if ((millis()-delayPisca)<tempo){
 digitalWrite(Leds[5],LOW);
  digitalWrite(Leds[6],LOW);
   
 }else if((millis()-delayPisca)<tempo*2){
  digitalWrite(Leds[6],HIGH);
 
 }else{
  delayPisca=millis();
  digitalWrite(Leds[6],LOW);
  digitalWrite(Leds[7],LOW);

  
  
  
 
 

 
}

}

//////////////////////////////////////////////////////////
if(mapeado==8){
 if ((millis()-delayPisca)<tempo){
   
   digitalWrite(Leds[6],LOW);
  
  digitalWrite(Leds[7],LOW);
   
 }else if((millis()-delayPisca)<tempo*2){
  digitalWrite(Leds[7],HIGH);
 
 }else{
  delayPisca=millis();
  digitalWrite(Leds[7],LOW);
  
  
 

  
  
  
 
 

 
}




}


 estadoAnterior=pinB; 


}




void pisca (byte quantPisca){//______________FUNCÃO QUE PISCA O LED_______________

if(piscada==true){
if(quantPisca!=valorAtual){

if ((millis()-delayPisca)<tempo){//-----------pisca 
   

for(int nl=0; nl < qtPinosLEDS;nl++){

  digitalWrite(Leds[nl],LOW);
  
}
   
 }else if((millis()-delayPisca)<tempo*2){
  
  
  for(int nD=0; nD < qtPinosLEDS;nD++){
  
  digitalWrite(Leds[nD],HIGH);
  
  } 
 
  
 }else{
  valorAtual++;
  //pausa=true;
  delayPisca=millis();
  
  
  
  
  for(int nC; nC<qtPinosLEDS;nC++){

  digitalWrite(Leds[nC],LOW);
  
}

 
  
  
 
 

 
}




  
}

if (valorAtual==quantPisca){
  valorAtual=0;
  pausa=true;
 piscada=false;
 
  
}


}
  
}


void pisca2 (byte quantPisca2){//RECEBE UM PARAMETRO

Serial.println(valorAtual2);
if(piscada2==true){
if(quantPisca2!=valorAtual2){


if ((millis()-delayPisca)<tempo){//-----------pisca 
   

for(int nl=0; nl < qtPinosLEDS;nl++){

  digitalWrite(Leds[nl],LOW);
  
}
   
 }else if((millis()-delayPisca)<tempo*2){
  
  
  for(int nD=0; nD < qtPinosLEDS;nD++){
  
  digitalWrite(Leds[nD],HIGH);
  
  } 
 
  
 }else{
  valorAtual2++;
  //pausa=true;
  delayPisca=millis();
  
  
  
  
  for(int nC; nC<qtPinosLEDS;nC++){

  digitalWrite(Leds[nC],LOW);
  
}

 
  
  
 
 

 
}




  
}

if (valorAtual2==quantPisca2){
  
  valorAtual2=0;
  posicao2=0;
  enquanto=false;
  pronto=true;
  
  
  
  
      //valorAtual=0;
 piscada2=false;
 
  
}


}
  
}



void verificaAtividade  ( )  { //FUNÇÃO QUE VAI SETAR AS VARIÁVEIS PARA QUE ZERE AS SENHAS


     
    posicao=-1;
    for(byte zera=0; zera < 5;zera++){//FOR QUE ADICIONA 0 A TODAS AS POSIÇÕES DA SENHA TENTATIVA 
   
    
 
      senhaTentativa[zera]=0;
 
    }
    debouncB=millis();


  
}


   ///////________________________-FIM DO DESAFIO :>-_________________________________________////////  
