import java.io.BufferedOutputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.File;


/**
 * Writes bits to a file. Accumulates bits until gets a byte, then writes it. On
 * closing writes an additional byte holding the number of valid bits in the
 * final byte written.
 * 
 * @author Emil H & Tanvir Saif Ahmed
 */
public class BitFileWriter {

    private int currentByte;             // The byte that is being filled
    private int numBitsWritten;          // Number of bits written to the current byte
    private BufferedOutputStream output;  // The output byte stream


    public BitFileWriter(String filename) throws FileNotFoundException {
        currentByte = 0;
        numBitsWritten = 0;
        output = new BufferedOutputStream(new FileOutputStream(filename));
    }

    // writes a bite to buffer then to a file if 8 bits in buffer
    public void writeBit(int bit) throws IOException {
        if (bit < 0 || bit > 1)
            throw new IllegalArgumentException("Argument to writeBit: bit = " + bit);

        numBitsWritten++;
        currentByte |= bit << (8 - numBitsWritten);  //Stores as bits

        if (numBitsWritten == 8) { // If we got a full byte... write to output
            writeByte(currentByte);
            numBitsWritten = 0;
            currentByte = 0;
        }
    }
    
    //Writes a byte to buffer
    public void writeByte (int b) throws IOException {
        output.write(b);
    }
    
    //Writes a vector of bytes to buffer
    public void writeBytes (byte[] b) throws IOException {
        output.write(b);
    }
    
    
    // Closes this bitstream. Writes any partial byte, followed by the number of
    // valid bits in the final byte (bynary form). The file will always have at least 1 byte.
    // An file representing no bits will have one zero byte.
    
    public void closeWriter() throws IOException {
        if (numBitsWritten != 0) {
        output.write(currentByte);             //Write in currentByte if not byte == 0
        }
        
        output.write(Integer.toString(numBitsWritten).getBytes());     //Write in end-byte telling how many bits is in the last byte written (binary form)

        output.close();
        System.out.println("...Done writing to code file");
    }
    
    public void closeWritingFile() throws IOException {
        
        output.close();
        System.out.println("...Done writing from code file");
    }
    
    // Small Test for BufferedBitWriter
public static void main(String[] args) throws IOException  {
    	BitFileWriter ss = new BitFileWriter("Test_BitFileWriter.txt");
    	
    	//Test_BitFileWriter.txt -> file content ABP4
    	
    	ss.writeBit(0);
    	ss.writeBit(1);
    	ss.writeBit(0);
    	ss.writeBit(0);
    	ss.writeBit(0);
    	ss.writeBit(0);
    	ss.writeBit(0);
    	ss.writeBit(1);
    	
    	ss.writeBit(0);
    	ss.writeBit(1);
    	ss.writeBit(0);
    	ss.writeBit(0);
    	ss.writeBit(0);
    	ss.writeBit(0);
    	ss.writeBit(1);
    	ss.writeBit(0);
        
        ss.writeBit(0);
        ss.writeBit(1);
        ss.writeBit(0);
        ss.writeBit(0);
        ss.writeBit(0);
        //ss.writeBit(0);
        //ss.writeBit(1);
        //ss.writeBit(1);
        
        ss.closeWriter();
    }
}
