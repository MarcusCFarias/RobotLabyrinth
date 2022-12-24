#include <iostream>
#include "libs/EdubotLib.hpp"
using namespace std;

void dobrar(EdubotLib *edubotLib, double rotacao){

	edubotLib->rotate(rotacao);
	edubotLib->sleepMilliseconds(2000);
}

int saiuLabirinto(EdubotLib *edubotLib){
	
	int saiu = 0;	
	double valorSonar0 = 0;
	double valorSonar1 = 0;
	double valorSonar2 = 0;
	double valorSonar3 = 0;
	double valorSonar4 = 0;
	double valorSonar5 = 0;	
	double valorSonar6 = 0;

	valorSonar0 = edubotLib -> getSonar(0);
	//edubotLib->sleepMilliseconds(1);
	
	valorSonar1 = edubotLib -> getSonar(1);
	//edubotLib->sleepMilliseconds(1);
	
	valorSonar2 = edubotLib -> getSonar(2);
	//edubotLib->sleepMilliseconds(1);
	
	valorSonar3 = edubotLib -> getSonar(3);
	//edubotLib->sleepMilliseconds(1);
	
	valorSonar4 = edubotLib -> getSonar(4);
	//edubotLib->sleepMilliseconds(1);
	
	valorSonar5 = edubotLib -> getSonar(5);
	//edubotLib->sleepMilliseconds(1);
	
	valorSonar6 = edubotLib -> getSonar(6);
	//edubotLib->sleepMilliseconds(1);

	if(valorSonar0 == 2.0 
	   && valorSonar1 == 2.0
	   && valorSonar2 == 2.0
	   && valorSonar3 == 2.0
	   && valorSonar4 == 2.0
	   && valorSonar5 == 2.0
	   && valorSonar6 == 2.0) {

		saiu = 1;
	}
	
	return saiu;
}

int main(){
	
	int angulo;
	double rotacao = 0;
	int sonarFrontal = 3, sonarDireito = 6, sonarEsquerda = 0;
	int valorBumper0 = 0, valorBumper1 = 0;
	
	double velocidade = 0.3, distanciaFrontalMinima = 0.07, distanciaDireitaMinima = 0.1;

	EdubotLib *edubotLib = new EdubotLib();
	
	if(edubotLib->connect()){
		
		edubotLib->sleepMilliseconds(2000);

		edubotLib->move(velocidade);
		edubotLib->sleepMilliseconds(800);	
		
		//anda ate achar uma parede
		while(edubotLib -> getSonar(sonarFrontal) > 0.065){
			
		}

		rotacao = -90; //-60
		dobrar(edubotLib, rotacao);
		edubotLib->move(velocidade);
		edubotLib->sleepMilliseconds(750);	
		
		while(edubotLib -> isConnected()){			

			/*cout<< "BUMPER 0: " << edubotLib->getBumper(0) <<endl;
			edubotLib->sleepMilliseconds(1);
			cout<< "BUMPER 1: " << edubotLib->getBumper(1) <<endl;
			edubotLib->sleepMilliseconds(1);
			cout<< "BUMPER 2: " << edubotLib->getBumper(2) <<endl;
		     edubotLib->sleepMilliseconds(1);
			cout<< "BUMPER 3: " << edubotLib->getBumper(3) <<endl;
			edubotLib->sleepMilliseconds(1);*/

			if(edubotLib->getBumper(0) == 1 || edubotLib->getBumper(1) == 1){

				edubotLib->stop();
		     	cout<< "BATEU FRENTE" <<endl;
		     	edubotLib->sleepMilliseconds(3000);

		     	angulo = edubotLib->getTheta();
				cout<< "ANGULO DE BATIDA: "<< angulo <<endl;
		     	edubotLib->sleepMilliseconds(3000);
		     	
		     	angulo = angulo%90;
		     	cout<< "ANGULO NOVO: "<< -angulo <<endl;
		     	edubotLib->sleepMilliseconds(3000);

				cout<< "INDO PARA TRAS: "<<endl;
		     	edubotLib->sleepMilliseconds(3000);
		     	
		     	edubotLib->move(-velocidade);
		     	edubotLib->sleepMilliseconds(500);

		     	dobrar(edubotLib, -angulo);
				edubotLib->sleepMilliseconds(3000);
		     }
		     
		     if(edubotLib->getBumper(2) == 1 || edubotLib->getBumper(3) == 1){
		     	
		     	edubotLib->stop();
		     	cout<< "BATEU TRASEIRA" <<endl;
		     	edubotLib->sleepMilliseconds(3000);

		     	angulo = edubotLib->getTheta();
				cout<< "ANGULO DE BATIDA: "<< angulo <<endl;
		     	edubotLib->sleepMilliseconds(3000);
		     	
		     	angulo = angulo%90;
		     	cout<< "ANGULO NOVO: "<< angulo <<endl;
		     	edubotLib->sleepMilliseconds(3000);

				cout<< "INDO PARA FRENTE: "<<endl;
		     	edubotLib->sleepMilliseconds(3000);
		     	
		     	edubotLib->move(velocidade);
		     	edubotLib->sleepMilliseconds(1000);
		     	//edubotLib->stop();
		     	edubotLib->sleepMilliseconds(1000);

		     	dobrar(edubotLib, -angulo);
				edubotLib->sleepMilliseconds(3000);
		     }
			
			do{	
				if(saiuLabirinto(edubotLib) == 1){
					edubotLib->sleepMilliseconds(100);
					std::cout << "SAIU" << std::endl;
					edubotLib->sleepMilliseconds(2000);
					edubotLib->stop();
					edubotLib->disconnect();
				}
				/*else{
					std::cout << "| EM LOOP |" << std::endl;
					edubotLib->sleepMilliseconds(1);
				}*/

			}while(edubotLib->getSonar(sonarDireito) <= distanciaDireitaMinima 
					&& edubotLib -> getSonar(sonarFrontal) >= distanciaFrontalMinima);

			edubotLib->stop();
			cout<< "PAROU: " <<endl;
			edubotLib->sleepMilliseconds(1000);
			cout<< "SONAR FRONTAL: "<<  edubotLib -> getSonar(sonarFrontal) <<endl;
			edubotLib->sleepMilliseconds(2000);
			cout<< "SONAR DIREITA: "<<  edubotLib -> getSonar(sonarDireito) <<endl;
			edubotLib->sleepMilliseconds(2000);
			
			if(edubotLib->getSonar(sonarFrontal) <= distanciaFrontalMinima){

				//cout<< "DOBRANDO PQ TEM PAREDE NA FRENTE" <<endl;
				//edubotLib->sleepMilliseconds(3000);
				
				if(edubotLib -> getSonar(sonarDireito) < distanciaDireitaMinima){
					dobrar(edubotLib, -90);
				}
				else{
					dobrar(edubotLib, 90);
				}

				edubotLib -> move(velocidade);
			}
			
			else{
				
				edubotLib->sleepMilliseconds(100);
				cout<< "DOBRANDO PQ SE PERDEU DA PAREDE DIREITA" <<endl;
				edubotLib->sleepMilliseconds(2000);
				
				if(edubotLib -> getSonar(sonarFrontal) < 1.0){

					edubotLib->sleepMilliseconds(100);
					cout<< "HA ALGO NA FRENTE" <<endl;
					edubotLib->sleepMilliseconds(2000);
					
					edubotLib->move(velocidade);
					do{
						
					}while(edubotLib->getSonar(sonarFrontal) < distanciaFrontalMinima);
			
					edubotLib->sleepMilliseconds(500);
				}else{	

					edubotLib->sleepMilliseconds(100);
					cout<< "NAO HA NADA NA FRENTE"<<endl;
					edubotLib->sleepMilliseconds(3000);

					edubotLib->move(velocidade);								
					edubotLib->sleepMilliseconds(700);	
				}
						
				dobrar(edubotLib, 90);
				edubotLib->move(velocidade);	
				edubotLib->sleepMilliseconds(1000);	
			}
		}
	}	
	else{
		cout<< "Could not connect on robot" <<endl;
	}
 
	return 0;
}