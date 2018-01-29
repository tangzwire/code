import java.io.*;

/**
 * Reads bytes from a file. Assumes that the last byte of the file
 * contains the number of valid bits in the previous byte.
 * Returns int 0 or 1 to indicate bit.
 *  
 * @author Emil H & Tanvir Saif Ahmed
 */
public class BitFileReader {
    private BufferedInputStream input; // buffer
    private int currentByte;           // Current byte being returned, bit by bit
    private int bitPos;                // position in currentByte
    private int returnByte;            // Byte to be read from buffer

    
    //Constructor
    protected BitFileReader(String fileName) throws IOException {
        input = new BufferedInputStream(new FileInputStream(fileName));
        currentByte = input.read();  // loads the first byte
        bitPos = 7;
    }
    
    // Loads byte from the buffer
    public int loadByte() throws IOException 
    {
        bitPos = 7;      // sets the position of a byte-vector to 7
        currentByte = input.read();
        return currentByte;
    }
    
    public void nextByte() throws IOException 
    {
        currentByte = input.read();
    }
    
    public int currentByte() 
    {
        return currentByte;
    }
    
    // Returns one bit in int 1 or 0
    public int nextBit() throws IOException {
        int res = (currentByte>>bitPos) & 1;
        --bitPos;
        if (bitPos < 0) {
            currentByte = input.read(); // -1 if end of file has been reached
            bitPos = 7;
        }
        return res ;
    }

    // Close the input
    public void closeReader() throws IOException {
        input.close();
    }
    
    // Small test...
    public static void main(String[] args) throws IOException{
    	
    	/*//Test 1
    	File temp;
    	temp = File.createTempFile("test1", "txt");
        temp.deleteOnExit();
        BufferedWriter out = new BufferedWriter(new FileWriter(temp));  
        out.write("A0"); // A,B,0 = 0100 0001, 0100 0010, 0011 0000
        out.close();*/
    	
        //Test 2
    	BitFileReader reader = new BitFileReader("Test_BitFileReader.txt"); //ABC
        
        System.out.println("byte = "+reader.currentByte);
        for (int i = 1; i <= 40; i++) {
            System.out.println(reader.nextBit());
            if (i % 8 == 0) {
                System.out.println("new byte");
                System.out.println("byte = "+reader.currentByte());
            }
        }
    	reader.closeReader();
    }
}
