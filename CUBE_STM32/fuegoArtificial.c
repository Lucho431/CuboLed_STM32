
uint8_t exploded;


void fireWork(void)
{
	exploded = 0;
	rocket = new Particle(CUBE_SIZE/2, CUBE_SIZE/2, 0, 0, 0, 10, false, 0, CUBE_SIZE);
	debris = new Particle[0];
}

void Firework::update(unsigned long dt)
{
	for(byte x = 0 ; x < CUBE_SIZE ; x++)
	{
		for(byte y = 0 ; y < CUBE_SIZE ; y++)
		{
			for(byte z = 0 ; z < CUBE_SIZE ; z++)
			{
				cubeModel[x][y][z] = false;
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
