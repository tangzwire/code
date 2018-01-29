/*****************************************************************************************
 * 																						 *
 * Author: Tanvir Saif Ahmed															 *
 * Date: 6/2-2017																		 *
 * Program name: TableParticles.java													 *
 * Description: A class that represents the table for particles that will be tracked.	 *
 * 																						 *
 *****************************************************************************************/

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.AbstractTableModel;

import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.LinkedList;


public class TableParticles extends AbstractTableModel
{
    private static Model2 myModel;
    public static Object[][] data;
    public static int numberOfParticles = 10;
    public static LinkedList<Particle> myTenParticles;
    public JTable table;
    
    private String[] columnNames = 
    	{"Particle", 
		 "Coordinates", 
		 "State", 
		 "Tracking"};

    /**
     * Creates a table with particles to be tracked.
     */
    TableParticles(Model2 model) 
    {
        myModel = model;
        this.createTable();
    }
    
    /**
     * Initiates a table with 10 particles that will be tracked during running of application.
     */
    public void createTable()
    {
        data = new Object[10][4];
        for(int y=0; y < 10;++y)
        {
        	Particle currentPart = myModel.getParticles().get(y);
        	
    		data[y][0] = new Integer(y+1);
    		data[y][1] = ""+ (int)currentPart.x + "," + 
    					(int)currentPart.y;
    		data[y][2] = "Moving";
    		data[y][3] = Boolean.FALSE;
        }
        this.table = new JTable(data, columnNames);
    }
    
    /**
	 * Sets the value at row and column for the particles table.
     */
    public void setValueAt(Object value,int row, int column)
    {
    	data[row][column] = value;
    	fireTableCellUpdated(row, column);
    }
    /**
	 * Gets number of columns.
     */
    public int getColumnCount() 
    {
    	return this.columnNames.length;
    }
    
    /**
	 * Gets number of rows.
     */
    public int getRowCount() 
    {
    	return this.data.length;
    }
    
    /**
	 * Gets the values at row and column.
     */
    public Object getValueAt(int row, int column) 
    {
    	return data[row][column];
    }
    
    /**
     * Changes the check boxes (rendering).
     */
    public Class getColumnClass(int column) 
    {
    	//Columns of the table.
    	switch (column) 
    	{
	    	case 0: return String.class;
	    	case 1: return String.class;
	    	case 2: return Integer.class;
	    	case 3: return Boolean.class;
	    	default: return String.class;
    	}
    }
    
    /**
     * Make sures that only the third column is editable (for tracking).
     */
    public boolean isCellEditable(int row, int column) 
    {
    	return (column == 3);
    }

}
