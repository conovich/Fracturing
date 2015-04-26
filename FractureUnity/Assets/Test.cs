using UnityEngine;
using System.Collections;

public class Test : MonoBehaviour {

	// Use this for initialization
	void Start () {

		Cell newCell = gameObject.GetComponent<Cell>();
		Vector3 p0 = new Vector3(0,0,0);
		Vector3 p1 = new Vector3(1,0,0);
		Vector3 p2 = new Vector3(0.5f,0,Mathf.Sqrt(0.75f));
		Vector3 p3 = new Vector3(0.5f,Mathf.Sqrt(0.75f),Mathf.Sqrt(0.75f)/3);
		newCell.VerticesArray = new Vector3[]{p0,p1,p2,p3};
		newCell.IndicesArray = new int[]{
			0,1,2,
			0,2,3,
			2,1,3,
			0,3,1
		};	
		newCell.Build ();

	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
