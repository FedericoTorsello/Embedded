#include "SonarTask.h"
#include "Time.h"

SonarTask::SonarTask(int trigPin, int echoPin, int maxDist, Context* pContext) {
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    this->MAX_DISTANCE = maxDist;
    this->pContext = pContext;
    // set the sonar, [timeout]
    this->sonar = new NewPing(this->trigPin, this->echoPin, this->MAX_DISTANCE);
}

void SonarTask::init(int period) {
    Task::init(period);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

int inc;
time_t t, t2 , t3;
time_t t_local;
bool tempoCorretto = false;
const int DELTA = 5, indovina = 20;
bool padlockOpen = false;

void SonarTask::tick() {
    // If game is started
    // if (pContext->getGame()) {
    //     // result from sonar
    //     int distance = sonar->ping() / US_ROUNDTRIP_CM;
    //     // distance to guess
    //     int distanceGuess = pContext->getDistanceGuess();
    //     distanceGuess = 10;
    //     if(distance <= distanceGuess + DELTA && distance >= distanceGuess - DELTA) {
    //         // Correct distance, check time
    //         endTime = millis();
    //         if (endTime - startTime >= MIN_TIME) {
    //             if (endTime - startTime <= MAX_TIME) {
    //                 pContext->setDetectedObj(30);
    //                 Serial.println("DENTRO");
    //             } else
    //                 Serial.println("TRPP DEN");
    //         }
    //     } else {
    //         pContext->setNoObjDetected();
    //         startTime = millis();
    //     }
    // }
    int distance = sonar->ping_cm();

	if(distance <= indovina + DELTA && distance >= indovina - DELTA && !padlockOpen){

		t = now();
		t = t - t2; // inizializzazione a zero

		if(tempoCorretto && t == 0){
			padlockOpen = true;
			printPadlockState();
		}

		switch (t) {
			case 1:
			Serial.println("hai trovato il lucchetto");
			break;

			case 2:
			Serial.println("ti stai avvicinando");
			break;

			case 3:
			Serial.println("ora bisogna stare attenti");
			break;

			case 4:
			Serial.println("ora bisogna stare attenti");
			break;
		}

		if (t >= 4) {
			t3 = now();
			t3 = t3 - t2 - 4; // -4 per far partire il tempo t3 da zero

			switch (t3) {
				case 1:
				Serial.println("stai scassinando il lucchetto");
				break;

				case 2:
				Serial.println("ancora un po' di pazienza");
				break;

				case 3:
				Serial.println("ce l'hai fatta!!! :D");
				tempoCorretto = true;
				break;
			}

			if(t3 >= 4 && t3 <= 5){
				Serial.println("...però non restare fermo...");
				tempoCorretto = true;
			}

			if(t3 == 6){
				Serial.println("Attento! rischi di romperlo!");
				tempoCorretto = true;
			}

			if(t3 >= 7){
				Serial.println("Noooooo, l'hai rotto! Devi riprovare");
				tempoCorretto = false;
			}
		}
	}else{
		if(!padlockOpen){
			t2 = now();
			// printPadlockState();
		}
	}


}

void SonarTask::printPadlockState(){
	if(padlockOpen){
		Serial.println("APERTO");
	}else{
		Serial.println("NON APERTO");
	}
}
