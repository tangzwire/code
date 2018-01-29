/*****************************************************************************************
 * 																						 *
 * Author: Tanvir Saif Ahmed															 *
 * Date: 6/2-2017																		 *
 * Program name: BrownianAnimation.java													 *
 * Description: A class that represents the animation, Brownian Motion.					 *
 * 																						 *
 *****************************************************************************************/

import javax.swing.JFrame;
import java.awt.FlowLayout;

class BrownAnimation extends JFrame 
{
	int windowXSize = 500;
	int windowYSize = 500;
	int numberOfParticles = 10000;

    /**
     * Initiates a BrownianAnimation by using all the different classes.
     */
	BrownAnimation ()
	{
		//Set window.
		super("Brownian Motion");
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setVisible(true);
		setSize(windowXSize, windowYSize);
		this.setLocationRelativeTo(null);
		this.setLayout(new FlowLayout());
		
		//Uses all the classes to create the necessary parts for BrownianAnimation.
		Model2 model = new Model2(numberOfParticles, windowXSize, windowYSize);
		View view = new View(model);
		TableFrame myTable = new TableFrame(model);
		Controller controller = new Controller(model);
		Simulation simulation = new Simulation(model,view,myTable);
		
		//Creates the necessary windows on different sides.
		add(view,"Center");
		add(controller,"East");

		//Packs all the classes together.
		pack();
		
		simulation.start();
		
	}

	public static void main (String[] arg)
	{
		//Creates a BrownianMotion.
		new BrownAnimation();	
	}
}