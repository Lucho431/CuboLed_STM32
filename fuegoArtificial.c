#define FIREWORK_TIME 0x8FFC

typedef enum{
	NEW_FW,
	RISING_ROCKET,
	EXPLODING,
}T_FW_STATUS;

typedef struct{
	int8_t partX;
	int8_t partY;
	int8_t partZ;
	int8_t velX;
	int8_t velY;
	int8_t velZ;
	int8_t acelZ;
} T_FW_PARTICLE;



uint8_t exploded;
T_FW_STATUS statusFireWork = NEW_FW;
uint8_t rocketX = 0;
uint8_t rocketY = 0;
uint8_t rocketZ = 0;
uint8_t numParticles;
T_FW_PARTICLE particle[40];
uint8_t deadParticles = 0;

void fireWork(int)
{
	exploded = 0;
//	rocket = new Particle(CUBE_SIZE/2, CUBE_SIZE/2, 0, 0, 0, 10, false, 0, CUBE_SIZE);
	setVoxel(4, 4, 0);
//	debris = new Particle[0];
}

void fireWork (void){

	if (loading != 0) {
	    clearCube();
	    loading = 0;
	}

	if (timer > FIREWORK_TIME){

		clearCube();

		switch (statusFireWork){
			case NEW_FW:
				rocketX = 2 + (rand() % 4); //between 2 and 5.
				rocketY = 2 + (rand() % 4); //between 2 and 5.
				rocketZ = 0;
				setVoxel(rocketX, rocketY, rocketZ);
				statusFireWork = RISING_ROCKET;
			break;
			case RISING_ROCKET:
				rocketZ++;
				if (rocketZ > 4){
					statusFireWork = EXPLODING;
					deadParticles = 0;
					numParticles = (30 + (rand() % 10) ); //num of particles between 30 and 40.
					for(uint8_t i = 0 ; i < numParticles; i++){
						particle[i].partX = rocketX;
						particle[i].partY = rocketY;
						particle[i].partZ = rocketZ;
						particle[i].velX = -1 + (rand() % 2);
						particle[i].velY = -1 + (rand() % 2);
						particle[i].velZ = rand() % 2;
					}
				}
				setVoxel(rocketX, rocketY, rocketZ);
			break;
			case EXPLODING:
				for(uint8_t i = 0 ; i < numParticles; i++){
					particle[i].velZ--;

					particle[i].velX--;
					particle[i].velY--;
					particle[i].velZ--;

					particle[i].partX += particle[i].velX;
					particle[i].partY += particle[i].velY;
					particle[i].partZ += particle[i].velZ;

					if(particle[i].partX < 0) particle[i].partX = 0;
					if(particle[i].partY < 0) particle[i].partY = 0;
//					if(particle[i].partZ < 0) particle[i].partZ = 0;
					if(particle[i].partX > 7) particle[i].partX = 7;
					if(particle[i].partY > 7) particle[i].partY = 7;
//					if(particle[i].partZ > 7) particle[i].partZ = 7;

					if(particle[i].partZ >= 0){
						setVoxel(particle[i].partX, particle[i].partY, particle[i].partZ);
					}else{
						deadParticles++;
					}

				} //end for i

				if (deadParticles == numParticles)
					statusFireWork = NEW_FW;
			break;
			default:
			break;
		} //end switch (statusFireWork)
	} //end if (timer > FIREWORK_TIME)
} //end fireWork ()

/*
		if (!exploded){

			clearCube(); //clean cube

			rocketZ++;

			if (rocketZ > 3){

				exploded = 1; //set explode status
				numParticles = (30 + (rand() % 10)); //num of particles between 30 and 40.

			}

		}


	}

	float timeChange = 1.0*dt/1000000;
	if(!exploded)
	{
		rocket->move(timeChange);
		if(rocket->getRoundedZ() >= 4)
		{
			delete[] debris;
			exploded = true;
			numDebris = random(30, 40);
			debris = new Particle[numDebris];
			for(byte i = 0 ; i < numDebris ; i++)
			{
				debris[i] = Particle(CUBE_SIZE/2, CUBE_SIZE/2, 4, random(-10,11), random(-10,11), random(0,21), false, 0, CUBE_SIZE);
			}
		}
		cubeModel[rocket->getRoundedX()][rocket->getRoundedY()][rocket->getRoundedZ()] = true;
	}
	else
	{
		byte visableCount = 0;
		for(byte i = 0 ; i < numDebris ; i++)
		{
			debris[i].accelerateZ(-15, timeChange);
			debris[i].drag(0.05, timeChange);
			debris[i].move(timeChange);
			if(debris[i].getRoundedZ() > 0)
			{
				visableCount++;
				cubeModel[debris[i].getRoundedX()][debris[i].getRoundedY()][debris[i].getRoundedZ()] = true;
			}
		}
		if (!visableCount)
		{
			exploded = false;
			delete rocket;
			rocket = new Particle(CUBE_SIZE/2, CUBE_SIZE/2, 0, 0, 0, 10, false, 0, CUBE_SIZE);
		}
	}
}
*/
