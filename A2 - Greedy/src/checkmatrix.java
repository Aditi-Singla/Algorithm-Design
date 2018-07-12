import java.io.*;
import java.util.*;
import java.lang.*;
public class checkmatrix{
	public static void main ( String args []){
		BufferedReader infile = null;
		Writer outFile = null;
		checkmatrix obj = new checkmatrix();
		try {
			infile = new BufferedReader(new FileReader(args[0]));
			outFile = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(args[1])));
			int n = Integer.parseInt(infile.readLine());
			String[] strindegree = (infile.readLine()).split(",");
			String[] stroutdegree = (infile.readLine()).split(",");
			Vector<Node> indegree = new Vector<Node>();
			Vector<Node> outdegree = new Vector<Node>();
			int[][] array = new int[n][n];
			int sumin = 0;
			int sumout = 0;
			for (int i=0;i<n;i++){
				int p = Integer.parseInt(strindegree[i]);
				int q = Integer.parseInt(stroutdegree[i]);
				if (p>n || q>n){
					outFile.write(0);
					outFile.close();
					return;
				}
				else{
					(new Node(i,p)).insertIn(indegree);
					(new Node(i,q)).insertIn(outdegree);
					sumin += p;
					sumout += q;
				}
			}
			if (sumin == sumout){
				for (int i=0; i<n; i++){
					int a = indegree.get(i).index;
					int b = indegree.get(i).value;
					for (int j=0;j<b;j++){
						Node node = outdegree.get(j);
						(node.value)--;
						array[a][node.index] = 1;
					}
					outdegree = obj.sort(outdegree,b);
				}
				outFile.write(1 + "\n");
				for (int k = 0; k<n; k++){
					String str = "";
					if (array[k][0] == 1)
							str += "1";
						else
							str += "0";
					for (int l = 1; l<n; l++){
						if (array[k][l] == 1)
							str += ",1";
						else
							str += ",0";
					}
					outFile.write(str + "\n");
				}
				outFile.close();
			}
			else{
				outFile.write(0 + "\n");
				outFile.close();
				return;
			}
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
	public Vector<Node> sort(Vector<Node> v, int index){
		int n = v.size();
		for (int i=index; i<n; i++){
			Node node = v.get(i);
			for (int j=i-1; j>=0; j--){
				if (v.get(j).value>=node.value){
					v.remove(i);
					v.insertElementAt(node,j+1);
					break;
				}
				else if (j==0){
					v.remove(i);
					v.insertElementAt(node,j);
					break;
				}
			}
		}
		return v;
	}
}
class Node{
	int index;
	int value;
	public Node(int i, int v){
		index = i;
		value = v;
	}
	public void insertIn(Vector<Node> v){
		int m = this.value;
		int low = 0;
		int high = v.size();
		while (low <= high){
			int mid = low + (high - low)/2 ;
			if (mid == v.size())
				break;
			int m1 = v.get(mid).value;
			if (m>=m1)
				high = mid -1;
			else
				low = mid + 1;
		}
		v.insertElementAt(this,low);
	}
}