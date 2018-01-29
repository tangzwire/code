/*****************************************************************************************
 * 																						 *
 * Author: Tanvir Saif Ahmed															 *
 * Date: 6/2-2017																		 *
 * Program name: Particle.java													 		 *
 * Description: A class that represents a particle for the Brownian Motion.			     *
 * 																						 *
 *****************************************************************************************/

import java.util.Random;
import java.awt.*;

class Particle 
{
    public double x, y;
    public static double stepDistance = 1;
    public boolean isMoving;
    public int radius = 4;
    private boolean tracing = false;

    /**
     * Sets the particles position for x and y-coordinates and the condition of movement to true.
     */    
    Particle (double xStart, double yStart, boolean moving)
    {
    	x = xStart;
    	y = yStart;
    	isMoving = moving;
    }
    
    /**
     * Moves the particle randomly by calculating a random angle for the particle to move.
     */ 
    void randomMove() 
    {
    	if (isMoving)
    	{
    	  	Random rand = new Random();
        	double angle = rand.nextFloat()*2*Math.PI;
        	x = x + stepDistance*Math.cos(angle);
        	y = y + stepDistance*Math.sin(angle);
    	}
    }
    
    /**
     * Makes the particle stop moving and also setting the condition of movement to false.
     */ 
    void stopMoving()
    {
    	isMoving = false;
    }
    
    /**
     * Checks if the particles are being traced.
     */ 
    public boolean isTracing() 
    {
    	return tracing;
    }
    
    /**
     * Sets the tracing of the particles to true or false.
     */ 
    public void setTracing(boolean trace) 
    {
    	this.tracing = trace;
    }
    
    /**
     * Stops the tracing of the particles.
     */ 
    public void stopTracing() 
    {
    	this.tracing = false;
    }
    
    /**
     * Sets the step distance of the particles to a certain value.
     */
    public void setStepDistance(double value)
    {
    	stepDistance = value;
    }
    
    public String toString()
    {
    	return "P";
    }
 
    /**
     * Paints the particles into different colors, according to their state.
     */
    public void paint(Graphics g)
    {
    	if (isMoving == true)
    	{
    		g.setColor(Color.BLUE);
    	} 
    	else 
    	{
    		g.setColor(Color.BLACK);
    	}
    	g.fillRect((int) x, (int) y, radius, radius);
    }
}
