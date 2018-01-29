/*****************************************************************************************
 * 																						 *
 * Author: Tanvir Saif Ahmed															 *
 * Date: 6/2-2017																		 *
 * Program name: Model2.java													 		 *
 * Description: A class that represents the particles to be created.					 *
 * 																						 *
 *****************************************************************************************/

import java.awt.Color;
import java.awt.Dimension;
import java.util.ArrayList;
import java.util.HashMap;

public class Model2 
{
	private ArrayList<Particle> particles = new ArrayList<Particle>();
	public int xSizeMatrix = 500;
	public int ySizeMatrix = 500;
	private ModelMap screenMap = new ModelMap(ySizeMatrix+1, xSizeMatrix+1);
	public HashMap<Particle, ArrayList<int[]>> traceData 
		= new HashMap<Particle, ArrayList<int[]>>(); 
	public static long limitTrack = 1000;
	
	public HashMap<Particle,Color> colorMap = new HashMap<Particle,Color>();
	
	/**
	 * Initiates and creates a specified number of particles in random locations.
	 */
	public Model2 (int numberOfParticles, int xSizeMatrix, int ySizeMatrix) 
	{
		this.xSizeMatrix = xSizeMatrix;
		this.ySizeMatrix = ySizeMatrix;
		
		//Adds the particles.
		for (int i = 0; i < numberOfParticles; ++i) 
		{
			Particle p = new Particle(xSizeMatrix/2,ySizeMatrix/2,true);
			particles.add(p);
		}
		
		//Adds 10 particles to be tracked.
		for (int i=0; i<10;++i) 
		{
			//Adds X and Y values of 10 particles into an array.
			ArrayList<int[]> coord = new ArrayList<int[]>();
			int[] newCoord = new int[2];
			newCoord[0] = (int) particles.get(i).x;
			newCoord[1] = (int) particles.get(i).y;
			coord.add(newCoord);
			
			//Path of the particle being mapped.
			traceData.put(particles.get(i),coord);
		}
		this.createMapColor();
	}
	
	/**
	 * Creates colors for the 10 particles that will be tracked during running of the application.
	 */
	private void createMapColor() 
	{

		Color[] myColors = new Color[] {Color.CYAN,Color.PINK,Color.YELLOW,
				Color.GREEN, Color.MAGENTA, Color.ORANGE, Color.DARK_GRAY,
				Color.RED,Color.WHITE,Color.LIGHT_GRAY};
		
		for (int i=0; i<10;i++) 
		{
			colorMap.put(particles.get(i),myColors[i]);
		}
	}

	/**
	 * Moves all the particles at random directions and in a specific distance.
	 */
	void moveAll() 
	{
		for (Particle eachParticle : particles) 
		{
			if (eachParticle.isMoving) 
			{
				eachParticle.randomMove();
				
				//If a particle have not hit a wall, check if it has hit a non-moving particle.
				if (this.checkWallCollision(eachParticle) == false) 
				{
					this.checkParticleCollision(eachParticle);
				}
				
				--Model2.limitTrack;
				
				if(Model2.limitTrack <0) 
				{
					this.track();
					Model2.limitTrack = 10000;
				}
				this.updateDeadZoneMap(eachParticle);
			} 
		}
	}
	
	/**
	 * Gets the coordinates of the tracking particles.
	 */
	private void track() 
	{
		for (int i=0;i<10;++i) 
		{
			ArrayList<int[]> coord = traceData.get(particles.get(i));
			int[] newCoord = new int[2];
			newCoord[0] = (int) particles.get(i).x;
			newCoord[1] = (int) particles.get(i).y;
			coord.add(newCoord);
		}
	}
	
	/**
	 * Checks if a particle has hit the wall.
	 * If it has, fix the position of the particle and do not move it.
	 */
	private boolean checkWallCollision(Particle eachParticle) 
	{
		boolean hasHit = false;
		
		//These will check if it has hit any of the four walls.
		if (eachParticle.x > this.xSizeMatrix + eachParticle.radius)
		{
			eachParticle.x = this.xSizeMatrix - eachParticle.radius/2;
			hasHit = true;
		}
		if (eachParticle.x < eachParticle.radius) 
		{
			eachParticle.x =  eachParticle.radius;
			hasHit = true;
		}
		if (eachParticle.y > this.ySizeMatrix + eachParticle.radius)
		{
			eachParticle.y = this.ySizeMatrix - eachParticle.radius/2;
			hasHit = true;
		}
		if (eachParticle.y < eachParticle.radius)
		{
			eachParticle.y = eachParticle.radius;
			hasHit = true;
		}
		
		//If true, stop moving the particle.
		if (hasHit)
		{ 
			eachParticle.stopMoving();
			return hasHit;
		}
		return hasHit;
	}
	
	/**
	 * Checks if a particle has collided with a false spot in the map.
	 * False spot = a spot where another particle has stopped moving.
	 */
	private void checkParticleCollision(Particle eachParticle)
	{
		int particleX = (int) eachParticle.x;
		int particleY = (int) eachParticle.y;
		
		//Checks if a particle is within a legal moving area.
		if (particleX > 0 && particleX <= xSizeMatrix &&
				particleY > 0 && particleY <= ySizeMatrix) {
			
			//Stop move the particle that has hit this false spot.
			if(screenMap.Map[particleY][particleX] == false) 
			{
				eachParticle.stopMoving();
			}
		}
		
	}
	
	/**
	 * When a particle has hit, update the map so close by moving particles can be stopped.
	 */
	private void updateDeadZoneMap(Particle eachParticle) 
	{
		if (!eachParticle.isMoving) 
		{
			int deadX = (int) eachParticle.x;
			int deadY = (int) eachParticle.y;
			int deadRad = (int) eachParticle.radius;
			screenMap.ChangePixelStatus(deadY, deadX, false, deadRad);
		}
	}

	/**
	 * Sets the step distance of the particles.
	 */
	double setStepDistance(double value) 
	{
		return Particle.stepDistance = value;

	}

	/**
	 * Sets the sleep time of the particles.
	 */
	int setSleepTime(int ms) 
	{
		return Simulation.sleepTime = ms;

	}
	
	/**
	 * Toggles the pause button. When pressed, this will be called.
	 */
	void togglePauseButton()
	{

		if (Simulation.running == false)
		{
			Simulation.running = true;
		} 
		else 
		{
			Simulation.running = false;
		}
		
	}
	
	/**
	 * Gets the dimensions of the model.
	 */
	public Dimension getDimension() 
	{
		return new Dimension(this.xSizeMatrix,this.ySizeMatrix);
	}
	
	/**
	 * Gets the list of all particles.
	 */
	public ArrayList<Particle> getParticles() 
	{
		return particles;
	}
	
	/**
	 * Adds a particle to the list of particles.
	 */
	public void addParticle(Particle myParticle) 
	{
		particles.add(myParticle);
	}
	

}