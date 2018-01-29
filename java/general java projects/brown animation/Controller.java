/*****************************************************************************************
 * 																						 *
 * Author: Tanvir Saif Ahmed															 *
 * Date: 6/2-2017																		 *
 * Program name: Controller.java													 	 *
 * Description: A class that represents the controlling of the Brownian Motion.			 *
 * 																						 *
 *****************************************************************************************/

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;
import javax.swing.JPanel;
import javax.swing.JButton;
import javax.swing.JSlider;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

public class Controller extends JPanel implements ActionListener, ChangeListener {

	private Model2 model;
	private JButton pauseButton = new JButton();
	private JPanel thePanel = new JPanel();
	static long sleepTime = 10;
	private JSlider particleVelocity = new JSlider(JSlider.VERTICAL, 0, 50, 1);
	private JSlider particleDistance = new JSlider(JSlider.VERTICAL, 1, 20, 1);

	/**
	 * Initiates the controller for the application by creating buttons, etc.
	 */
	Controller(Model2 mod)
	{
		add(thePanel);
		this.model = mod;
		pauseButton.setToolTipText("This Button Toggles Pause/Play");
		pauseButton.addActionListener(this);
		pauseButton.setText("Play");
		pauseButton.setPreferredSize(new Dimension(70,30));
		
		particleVelocity.setMajorTickSpacing(10);
		particleVelocity.setMinorTickSpacing(5);
		particleVelocity.setPaintTicks(true);
		particleVelocity.setPaintLabels(true);
		particleVelocity.addChangeListener(this);

		particleDistance.setPaintTicks(true);
		particleDistance.setPaintLabels(true);
		particleDistance.addChangeListener(this);
		particleDistance.setMajorTickSpacing(5);
		particleDistance.setMinorTickSpacing(1);

		JLabel velocityLabel = new JLabel("Velocity");
		JLabel distanceLabel = new JLabel("Distance");

		thePanel.add(pauseButton);
		thePanel.add(particleVelocity);
		thePanel.add(velocityLabel);
		thePanel.add(particleDistance);
		thePanel.add(distanceLabel);
	}
	
	/**
	 * When using the scroll bar, two things can be controlled in the application:
	 * 1. Velocity = sleep time will change.
	 * 2. Distance = step distance will change.
	 */
	public void stateChanged(ChangeEvent l) 
	{
		if (particleVelocity.getValueIsAdjusting()) 
		{
			model.setSleepTime(1 + particleVelocity.getMaximum() - particleVelocity.getValue());
		} 
		else if (particleDistance.getValueIsAdjusting()) 
		{
			model.setStepDistance(particleDistance.getValue());

		}
	}

	/**
	 * When using the buttons, two things can be done to control the Brownian Motion.
	 * 1. Start = start the Brownian Motion. 
	 * 2. Stop = stop (pause the Brownian Motion).
	 */
	public void actionPerformed(ActionEvent e) 
	{
		if (e.getSource() == pauseButton)
		{
			if (pauseButton.getText() == "Play") 
			{
				pauseButton.setText("Stop");
			} 
			else 
			{
				pauseButton.setText("Play");
			}
			model.togglePauseButton();
		}
	}

}

