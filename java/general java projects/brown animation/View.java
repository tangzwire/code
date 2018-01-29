/*****************************************************************************************
 * 																						 *
 * Author: Tanvir Saif Ahmed															 *
 * Date: 6/2-2017																		 *
 * Program name: View.java													 		 	 *
 * Description: A class that represents view of the Brownian Motion application			 *
 * 																						 *
 *****************************************************************************************/

import javax.swing.JPanel;
import java.awt.*;
import java.util.ArrayList;

public class View extends JPanel
{
	private Model2 model;
	
    /**
     * Creates the view for the main window, where all the particles appear.
     */ 
	public View (Model2 mod)
	{
		model = mod;
		setBackground(Color.GRAY);
		setPreferredSize(new Dimension(model.xSizeMatrix,model.ySizeMatrix));
		setLayout(new FlowLayout());
		setVisible(true);
		
	}	
    /**
     * Paints the view for the main window.
     */ 
	public void paint(Graphics g)
	{
		super.paint(g);
	}
    /**
     * Paints the particles and the path of the particles (while tracking).
     */ 
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		for(Particle p: model.getParticles())
		{
			p.paint(g);
		}
		//Pathing of the particles on tracking.
		for (Particle tracingPart : model.traceData.keySet()) 
		{
			//If a particle is set to tracing, it will be assigned a tracking/path color.
			if (tracingPart.isTracing()) 
			{
				g.setColor(model.colorMap.get(tracingPart));
				ArrayList<int[]> path = model.traceData.get(tracingPart);
				for (int j = 0; j< path.size() - 1; ++j) 
				{
					int[] point1 = path.get(j);
					int[] point2 = path.get(j+1);
					g.drawLine(point1[0], point1[1], point2[0], point2[1]);
				}
				this.highlightPart(tracingPart,g);
			}
		}
		g.dispose();
	}

    /**
     * Update the graphics.
     */ 
	public void update(Graphics g)
	{
		super.update(g);
	}
	
    /**
     * This method will highlight the tracking particle and writes a number for it.
     */ 
	private void highlightPart(Particle tracingPart, Graphics g) 
	{
		//g.drawLine((int)tracingPart.x,0,(int)tracingPart.x, model.ySizeMatrix);
		//g.drawLine(0, (int)tracingPart.y, model.xSizeMatrix, (int)tracingPart.y);
		
		g.fillRect((int)tracingPart.x, (int)tracingPart.y, 20, 20);
		g.setColor(Color.BLACK);
		g.drawString(this.model.getParticles().indexOf(tracingPart)+1+"", 
				(int)tracingPart.x+6, (int)tracingPart.y+15);
	}
}
