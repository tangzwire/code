/**
 * Class to store Huffman tree.
 * @author Emil H & Tanvir Saif Ahmed
 */
class HuffmanTree implements Comparable <HuffmanTree> {
    HuffmanTree left, right;    // The subbranches of this node.
    int value;                  // The value this node represents.
    int weight;                 // The weight of this tree.
    
    //Creates a three with one node: just a value and a weight.
    public HuffmanTree( Integer v, Integer w ) {
        left = null;
        right = null;
        value = v;
        weight = w;
    }
    
    // Creates a tree from two subtrees and sums the frequencies
    public HuffmanTree( HuffmanTree l, HuffmanTree r ) {
        left = l;
        right = r;
        value = -1;       // the value of the new tree is -1
        weight = l.getWeight() + r.getWeight(); //New weight = sum of the subtrees.
    }
    
    // Compares this tree to another by weight AND needed to impelemnts Comparable
    public int compareTo(HuffmanTree tr) {
        return getWeight().compareTo(tr.getWeight());
    }
    
    // Returns the value of this node.
    public int getValue() {
        return value;
    }
    
    // Returns the weight of this tree.
    public Integer getWeight() {
        return weight;
    }
    
    // Does node has a value (is a leaf)?.
    public Boolean hasValue() {
        return value >= 0;
    }
}
