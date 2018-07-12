import java.io.*;
import java.util.*;
import java.lang.*;
public class evenpath
{
	public static void main ( String args []){
		BufferedReader infile = null;
		Writer outFile = null;
		evenpath obj = new evenpath();
		Vector<Node> nodeList = new Vector<Node>();
		try {
			infile = new BufferedReader(new FileReader(args[0]));
			outFile = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(args[1])));
			int n = Integer.parseInt(infile.readLine());
			for (int i=0; i<n; i++){
				String[] str = (infile.readLine()).split("->");
				Node node = obj.returnNode(nodeList,str[0]);
				if (node == null){
					node = new Node(str[0]);
					nodeList.add(node);
				}	
				for (int j=1; j<str.length; j++){
					Node node1 = obj.returnNode(nodeList,str[j]);
					if (node1 != null)
						node.addNode(node1);
					else{
						node1 = new Node(str[j]);
						node.addNode(node1);
						nodeList.add(node1);
					}
				}
			}
			Node node = obj.returnNode(nodeList,infile.readLine());
 			if (node != null){
	 			Vector<String> list = node.getEvenPath();
	 			int l = list.size();
				outFile.write(l + "\n");
				if (l!=0){
					outFile.write(list.get(0));
					for (int k=1; k<l; k++){
						outFile.write(","+list.get(k));
					}
				}
			}	
			outFile.write("\n");
			outFile.close();
		}
		catch (IOException e){
			e.printStackTrace();
		}
		finally{
			try{
				if (infile != null)
					infile.close();
			}
			catch (IOException ex){
				ex.printStackTrace();
			}
		}
	}
	public Node returnNode(Vector<Node> list, String node){
		for (int i=0; i<list.size(); i++){
			Node n = list.get(i);
			if (node.equals(n.name))
				return n;
		}
		return null;
	}
}
class Node{
	String name;
	int state;		/// -1 : Unvisited; 0 : Visited and at odd path;  1 : Visited and at even path; 2: AccesThe complete subtree has been already added
	Vector<Node> neighbours;
	public Node(String n){
		name = n;
		state = -1;
		neighbours = new Vector<Node>();
	}
	public void addNode(Node n){
		neighbours.add(n);
	}
	public Vector<String> getEvenPath(){
		Vector<String> evenPathNodes = new Vector<String>();
		Vector<Node> layer = new Vector<Node>();
		Vector<Node> layer1 = new Vector<Node>();
		layer.add(this);
		this.state = 1;
		evenPathNodes.add(this.name);
		boolean counter = false;
		while (!layer.isEmpty()){
			layer1 = new Vector<Node>();
			for (int i=0; i<layer.size(); i++){
				Vector<Node> neighbours = layer.get(i).neighbours;
				for (int j=0;j<neighbours.size();j++){
					Node str = neighbours.get(j);
					if (str.state == 2)
						continue;
					if (counter && str.state != 1){
						if (str.state == -1){
							layer1.add(str);
							str.insert(evenPathNodes);
							str.state = 1;
						}
						else{		////state == 0
							Vector<String> ep = str.getAll();
							evenPathNodes = str.merge(evenPathNodes,ep);
						}
					}
					else{
						if (str.state == -1){
							layer1.add(str);
							str.state = 0;
						}
					}
				}
			}
			counter = !counter;
			layer = layer1;
		}
		return evenPathNodes;	
	}
	public Vector<String> getAll(){
		Vector<String> v = new Vector<String>();
		if (this.state != 1)
			v.add(this.name);
		this.state = 2;
		Vector<Node> list = this.neighbours;
		for (int i=0; i<list.size(); i++){
			v = this.merge(v,list.get(i).getAll());
		}
		return v;
	}
	public void insert(Vector<String> v){
		int m = Integer.parseInt(this.name.substring(1,this.name.length()));
		int low = 0;
		int high = v.size();
		while (low <= high){
			int mid = low + (high - low)/2 ;
			if (mid == v.size())
				break;
			String n1 = v.get(mid);
			String n = n1.substring(1,n1.length());
			int m1 = Integer.parseInt(n);
			if (m<m1)
				high = mid -1;
			else
				low = mid + 1;
		}
		v.insertElementAt(this.name,low);
	}
	public Vector<String> merge(Vector<String> v1, Vector<String> v2){	///v1 & v2 are sorted.
		Vector<String> v = new Vector<String>();
		int i = 0;
		int j = 0;
		while (i<v1.size() && j<v2.size()){
			String n1 = v1.get(i);
			int n = Integer.parseInt(n1.substring(1,n1.length()));
			String m1 = v2.get(j);
			int m = Integer.parseInt(m1.substring(1,m1.length()));
			if (m<n){
				v.add(m1);
				j++;
			}
			else{
				v.add(n1);
				i++;
			}
		}
		while (i<v1.size()){
			String n1 = v1.get(i);
			int n = Integer.parseInt(n1.substring(1,n1.length()));
			v.add(n1);
			i++;
		}
		while (j<v2.size()){
			String m1 = v2.get(j);
			int m = Integer.parseInt(m1.substring(1,m1.length()));
			v.add(m1);
			j++;
		}
		return v;
	}
}
