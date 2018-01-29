import java.util.*;
import java.io.*;
import java.lang.*;

/**
 * Methods to read/write huffman code file
 * @author Emil H & Tanvir Saif Ahmed
 */
public class Huffman {
    private int[] byteVector;         //To store byte
    private int[] byteFreqVector;     //To store frequency of each byte
    private String [] codeVector;     //To store code of each byte
    private int totNum;               //Total number of bits in codefile
    PriorityQueue<HuffmanTree> pTree; //The tree holdning values and frequencies
    
    // Constructor
    private Huffman() {
        this.byteVector = new int[127];     //Mac uses the 127 first letters in UTF-8
        this.byteFreqVector = new int[127];
        
        for (int i = 0; i < 127; i++)
            byteFreqVector[i] = 0;
        
        this.codeVector = new String [127];
        this.totNum = 0;
        this.pTree = new PriorityQueue<HuffmanTree>();
    }
    
//-------------------------------------------------------------------------------------------
    // Encoding method: to read a text file and make a code file
    private void HuffmanEncode(String fileName) throws FileNotFoundException, IOException {
        
        //Reading the input file to buffer
        BufferedInputStream inBytes = new BufferedInputStream(new FileInputStream(fileName));
        
        //Reads in bytes and makes a frequency vector store in byteFreqVector
        int byteIn;
        while ((byteIn = inBytes.read()) != -1) {
            byteFreqVector[(byteIn)]++;
        }
        
        // Puts in bytes to byteVector to mach coresponding frequencies
        // and counts unique bytes to int n
        int n = 0;
        for (int i=0; i<127; i++) {
            if (byteFreqVector[i] > 0) {
                byteVector[i] = i;
                n++;
            }
        }
        
        //Creat a file to write in information
        BitFileWriter outputBuffer = new BitFileWriter("EncodedFile.txt");
        
        //Number of diffenent bytes
        String s = ""+n;   // from int to String
        
        //Put to the file the number of different bytes - n -
        outputBuffer.writeBytes(s.getBytes());
        outputBuffer.writeBytes(" ".getBytes());
        
        // Put in all bytes from byteVector and frequencies with space between
        for (int i=0; i<127; i++) {
            if (byteFreqVector[i] > 0) {
                outputBuffer.writeByte(byteVector[i]);
                outputBuffer.writeBytes(" ".getBytes());
                outputBuffer.writeBytes(Integer.toString(byteFreqVector[i]).getBytes());
                outputBuffer.writeBytes(" ".getBytes());
            }
        }
        
        // Do not forget to close inputBuffer reader!
        inBytes.close();
        
        // Create a Huffman tree leaf for each value and store those in a priority queue
        // which is kept SORTED by the weight we get from the frequency vector.
        // As long as the queue has more than two members, combine the two with
        // the lowest weights into a new tree, and add it to the PriorityQueue.
        CreatePriorityTree();
        //Test: System.out.println(p.Tree.peek().getValue());
        
        // The final Huffman tree
        HuffmanTree htree = pTree.poll();
        
        // Build a codeVector corresponding to byteVector and
        // count number of bites tu put in totNum.
        traverse(htree, "", 0, byteFreqVector);
        
        // Open the output file again and write the codes to the file
        BufferedInputStream readBytes = new BufferedInputStream(new FileInputStream(fileName));
        
        int oneByte;
        while ((oneByte = readBytes.read()) != -1) {
            String x = codeVector[oneByte];
            String [] y = x.split("");
            // Test System.out.println("Byten: "+oneByte);
            // Test System.out.println("Code: "+x);
            for (int i=0; i < y.length; i++) {
                outputBuffer.writeBit(Integer.parseInt(y[i]));
                // Test System.out.println("Bit: "+Integer.parseInt(y[i]));
            }
        }
        
        // Do not forget to close inputBuffer reader!
        readBytes.close();
        
        
        // Do not forget to close outputBuffer writer and complement with bites if needed.
        outputBuffer.closeWriter();
        
    } // Done With Writing To Output File! End HuffmanEncode()
    
//-------------------------------------------------------------------------------------------
    // Decoding method: reads a huffman code file and write it to a new txt file
    private void HuffmanDecode(String fileName) throws FileNotFoundException, IOException {
        
        //Reading the input file to buffer by using BifFileReader()
        BitFileReader file = new BitFileReader(fileName);
        
        // Reading in number of unique values in code file (first char in file)
        int n = stringInt(file);

        // Reads file and puts in bytes and corresponding frequencies
        // in byteVector & byteFreqVector
        int feed = file.loadByte();      //First char
        for (int i = 0; i < n; i++) {
            byteVector[feed] = feed;     // Insert first byte (value of character)
            file.nextByte();             // Step forward to an empty space
            file.nextByte();             // Step forward to frequency
            byteFreqVector[feed] = stringInt(file); // Insert frequency and steps forward
            // test System.out.println(byteFreqVector[feed]);
            feed = file.loadByte();      // Load next char/byte
        }
        
        // Create a Huffman tree leaf for each value and store those in a priority queue
        // which is kept SORTED by the weight we get from the frequency vector.
        // As long as the queue has more than two members, combine the two with
        // the lowest weights into a new tree, and add it to the PriorityQueue.
        CreatePriorityTree();
        
        // The final Huffman tree is dragd from the priorityQueue
        HuffmanTree htree = pTree.poll();
        
        //Creat a file to write in information from coded file
        BitFileWriter outputBuffer = new BitFileWriter("DecodedFile.txt");
        
        // Build a codeVector corresponding to byteVector and
        // count number of bites tu put in totNum.
        traverse(htree, "", 0, byteFreqVector);
        
        // Reading bit by bit and constructning a text file
        // The start pointer points to the first byte of the code text
        int bitIn = file.nextBit();
        HuffmanTree newTree = htree;
        for (int i = 0; i<totNum; i++) {
            if (bitIn == 0) {
                if (newTree.left.hasValue()) {
                    int resByteL = newTree.left.getValue();
                    outputBuffer.writeByte(resByteL);
                    newTree = htree;
                }
                else {
                    newTree = newTree.left;
                }
            }
            else {   // bitIn must be 1 if it is not 0
                if (newTree.right.hasValue()) {
                    int resByteR = newTree.right.getValue();
                    outputBuffer.writeByte(resByteR);
                    newTree = htree;
                }
                else {
                    newTree = newTree.right;
                }
            }
            bitIn = file.nextBit();
        }
        
        // Do not forget to close outputBuffer writer and complement with bites if needed.
        outputBuffer.closeWritingFile();
        
        // And to not forget to close reading file
        file.closeReader();
    } // Done With writing code to File! End HuffmanDecode()
    
//-----------------------------------------------------------------------------------
    // Reads bytes in code file and returns number
    // assembles bytes to String untill space is encountered in file
    
    private int stringInt (BitFileReader file) throws IOException {
        
        byte b = (byte) file.currentByte();
        byte [] c = " ".getBytes();
        String s = "";
        while (b != c[0]) {
            String str = new String(new byte[] {b});
            s = s+str;
            b = (byte) file.loadByte();
        }
        // Test System.out.println("Antalet char: "+Integer.parseInt(s));
        return Integer.parseInt(s);
    }
    
//----------------------------------------------------------------------------------
    //Create a Huffman tree leaf for each value and store those in a priority queue
    // which is kept SORTED by the weight we get from the frequency vector.
    
    private void CreatePriorityTree() {
        for( int i = 0; i < 127; i++ ) {
            if (byteFreqVector[i] > 0) {
                pTree.add( new HuffmanTree(byteVector[i], byteFreqVector[i]));
            }
        }
        
        // As long as the queue has more than two members, combine the two with
        // the lowest weights into a new tree, and add it to the PriorityQueue.
        while( pTree.size() > 1 ) {
            HuffmanTree nRight = pTree.poll(), nLeft = pTree.poll();
            pTree.add( new HuffmanTree(nLeft, nRight));
        }
    }
    
//----------------------------------------------------------------------------------
    // traverse: implements a String vector of code values
    // Each child of a tree is a root of its subtree.

    private void traverse (HuffmanTree tr, String sCode, int num, int[] byteFreqVector) {
        
        if (tr.left.getValue() == -1) {
            String lsCode = sCode+"0";
            int lsnum = num + 1;
            traverse(tr.left, lsCode, lsnum, byteFreqVector);
        }
        
        if (tr.left.getValue() != -1) {
            String sfCode = sCode +"0";
            int slnum = num + 1;
            codeVector[tr.left.getValue()] = sfCode;
            totNum += (slnum * byteFreqVector[tr.left.getValue()]);
            // Test System.out.println("Kod "+sfCode+" num "+slnum+" Value: "+tr.left.getValue());
        }
        
        if (tr.right.getValue() == -1) {
            String rsCode = sCode +"1";
            int rsnum = num + 1;
            traverse(tr.right, rsCode, rsnum, byteFreqVector);
        }
        
        if (tr.right.getValue() != -1) {
            String sffCode = sCode +"1";
            int sffnum = num + 1;
            codeVector[tr.right.getValue()] = sffCode;
            totNum += (sffnum * byteFreqVector[tr.right.getValue()]);
            // Test System.out.println("Kod "+sffCode+" num "+sffnum+" Value: "+tr.right.getValue());
        }
    }
    
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
    //
	public static void main(String[] args) throws FileNotFoundException, IOException {
        
        Huffman huffEncoding = new Huffman();
        huffEncoding.HuffmanEncode("wap.txt");
        
        Huffman huffDecoding = new Huffman();
        huffDecoding.HuffmanDecode("EncodedFile.txt");
	}
    
} // End Huffman()
