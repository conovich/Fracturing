using UnityEngine;
using UnityEditor;
using System.Collections;

[CustomEditor (typeof (Cell))] 
public class TetrahedronEditor : Editor {
	[MenuItem ("GameObject/Create Other/Tetrahedron")]
	static void Create(){
		GameObject gameObject = new GameObject("Cell");
		Cell s = gameObject.AddComponent<Cell>();
		MeshFilter meshFilter = gameObject.GetComponent<MeshFilter>();
		meshFilter.mesh = new Mesh();
		Vector3 p0 = new Vector3(0,0,0);
		Vector3 p1 = new Vector3(1,0,0);
		Vector3 p2 = new Vector3(0.5f,0,Mathf.Sqrt(0.75f));
		Vector3 p3 = new Vector3(0.5f,Mathf.Sqrt(0.75f),Mathf.Sqrt(0.75f)/3);
		s.VerticesArray = new Vector3[]{p0,p1,p2,
			p0,p2,p3,
			p2,p1,p3,
			p0,p3,p1
		};
		s.IndicesArray = new int[]{
			0,1,2,
			3,4,5,
			6,7,8,
			9,10,11
		};
		s.Build();
	}
	
	public override void OnInspectorGUI ()
	{
		Tetrahedron obj;
		
		obj = target as Tetrahedron;
		
		if (obj == null)
		{
			return;
		}
		
		base.DrawDefaultInspector();
		EditorGUILayout.BeginHorizontal ();
		
		// Rebuild mesh when user click the Rebuild button
		if (GUILayout.Button("Rebuild")){
			obj.Build();
		}
		EditorGUILayout.EndHorizontal ();
	}
}