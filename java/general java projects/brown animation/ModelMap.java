/*****************************************************************************************
 * 																						 *
 * Author: Tanvir Saif Ahmed															 *
 * Date: 6/2-2017																		 *
 * Program name: ModelMap.java													 		 *
 * Description: A class that represents the points of the particles to be created (map). *
 * 																						 *
 *****************************************************************************************/

public class ModelMap 
{
	final boolean[][] Map;
	private int mapRows;
	private int mapColumns;
	
    /**
     * Creates a map for all points and sets it to true (moveable area).
     */ 
	public ModelMap(int mapRows, int mapColumns)
	{
		this.mapRows = mapRows;
		this.mapColumns = mapColumns;
		Map = new boolean[mapRows][mapColumns];
		
		for (int x = 0; x < mapRows; ++x)
		{
			for (int y = 0; y < mapColumns; ++y)
			{
				this.Map[y][x] = true;
			}
		}
	}
	
    /**
     * Method for checking the surroundings of particle.
	 * If a particle has collided with a wall/stopped particle, it will change the state of the particle.
	 * This is done by changing the pixel status on the map.
     */ 
	
	public void ChangePixelStatus(int particleY, int particleX, 
			boolean pixelStatus, int particleRadius)
	{
		for (int particleAreaX = particleX - particleRadius; 
				particleAreaX < particleX + particleRadius;
				++particleAreaX)
		{
			for (int particleAreaY = particleY - particleRadius;
					particleAreaY <  particleY + particleRadius;
					++particleAreaY)
			{
				if(particleAreaX > 0 && particleAreaX < this.mapRows &&
						particleAreaY > 0 && particleAreaY < this.mapColumns)
				{
					//If the area collides with walls/stopped particle, change the pixel status of the map.
					this.Map[particleAreaY][particleAreaX] = pixelStatus;
				}
			}
		}
	}
	
    /**
	 * Get the rows of the map.
     */ 
	public int getMapRows()
	{
		return mapRows;
	}
	
    /**
	 * Get the columns of the map.
     */ 
	public int getMapColumns()
	{
		return mapColumns;
	}
}
