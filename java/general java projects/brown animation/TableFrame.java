/*****************************************************************************************
 * 																						 *
 * Author: Tanvir Saif Ahmed															 *
 * Date: 6/2-2017																		 *
 * Program name: TableFrame.java													     *
 * Description: A class that represents the frame for tracking particles.				 *
 * 																						 *
 *****************************************************************************************/

import java.awt.Component;
import java.awt.FlowLayout;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTable;


public class TableFrame extends JFrame 
{
	private JTable trackingTable;
	private Model2 myModel;
	
    /**
     * Initiates a window for tracking particles.
     */
	TableFrame(Model2 mod) 
	{
		myModel = mod;
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		this.setSize(300, 100);
		TableParticles table = new TableParticles(this.myModel);
		trackingTable = new JTable(table);
		
		this.add(trackingTable);
		this.repaint();
		this.setVisible(true);
		pack();
	}
	
	/**
	 * Updates the table with new values for the particles.
	 */
	public void updateTable() 
	{
		//Chooses up to 10 particles to track.
		for (int i = 0; i < 10; ++i) 
		{
			//Shows the particles number, position, moving state and tracing state.
			Particle currentPart = myModel.getParticles().get(i);
			String state = "";
 			String coord = "" + ((int) currentPart.x) + "," + ((int) currentPart.y);
			trackingTable.setValueAt(coord,i, 1);
			
			if (currentPart.isMoving) 
			{
				state = "Moving";
			} 
			else 
			{
				state = "Not Moving";
			}
			trackingTable.setValueAt(state,i, 2);
			
			//Choose to track (trace) a particle.
			if ((Boolean)this.trackingTable.getValueAt(i, 3) == true) 
			{
				currentPart.setTracing(true);
			} 
			else 
			{
				currentPart.setTracing(false);
			}
		}
	}
}
