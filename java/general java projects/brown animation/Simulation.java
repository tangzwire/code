/*****************************************************************************************
 * 																						 *
 * Author: Tanvir Saif Ahmed															 *
 * Date: 6/2-2017																		 *
 * Program name: Simulation.java													 	 *
 * Description: A class that represents the runtime for the particles (movement).		 *
 * 																						 *
 *****************************************************************************************/

import java.awt.event.ActionEvent;
import java.util.LinkedList;

public class Simulation extends Thread 
{

	private Model2 model;
	private View view;
	private Thread t;
	static boolean running = false;
	static int sleepTime = 50;
	private TableFrame myController;
	
	/**
	 * Initiates the simulation (runtime) for the particles in order to move.
	 */
	public Simulation(Model2 mod, View v,TableFrame controller) 
	{
		myController = controller;
		model = mod;
		view = v;
	}

	/**
	 * Moves all the particles and repaints afterwards.
	 */
	public void moveAndPaint() 
	{
		model.moveAll();
		view.repaint();
	}

	/**
	 * Runs the thread (movement).
	 */
	public void run() 
	{
		System.out.println("Running...");
		while (true) 
		{	
			//Checks if simulation is running.
			if (Simulation.running) 
			{
				this.moveAndPaint();
				this.view.updateUI();
				try 
				{
					this.myController.updateTable();
				} 
				catch (NullPointerException e) 
				{
					e.printStackTrace();
				}
			}
			try 
			{	
					//Sleep time for the particles.
					Thread.sleep(sleepTime);
			} 
			catch (InterruptedException e2) 
			{
			}

		}
	}

	/**
	 * Starts the thread (movement).
	 */
	public void start() 
	{
		if (t == null) 
		{
			t = new Thread(this);
			t.start();
		}
	}
}