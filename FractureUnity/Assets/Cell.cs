using UnityEngine;
using System.Collections;

[RequireComponent (typeof (MeshCollider))]
[RequireComponent (typeof (MeshFilter))]
[RequireComponent (typeof (MeshRenderer))]
public class Cell : MonoBehaviour {
	public Vector3[] VerticesArray;
	public int[] IndicesArray;
	public Material material;
	public int life;
	// Use this for initialization
	public bool sharedVertices = false;
	// Use this for initialization
	public void Build () {
		MeshFilter meshFilter = GetComponent<MeshFilter>();
		if (meshFilter==null){
			Debug.LogError("MeshFilter not found!");
			return;
		}
		/*
		Vector3 p0 = new Vector3(0,0,0);
		Vector3 p1 = new Vector3(1,0,0);
		Vector3 p2 = new Vector3(0.5f,0,Mathf.Sqrt(0.75f));
		Vector3 p3 = new Vector3(0.5f,Mathf.Sqrt(0.75f),Mathf.Sqrt(0.75f)/3);
		*/
		Mesh mesh = meshFilter.sharedMesh;
		if (mesh == null){
			meshFilter.mesh = new Mesh();
			mesh = meshFilter.sharedMesh;
		}
		mesh.Clear();

		int[] indexTemp = new int[IndicesArray.Length];
		if (sharedVertices){
			Vector3[] vrtTemp = new Vector3[VerticesArray.Length];
			for (int i = 0; i < VerticesArray.Length; i++) {
				vrtTemp[i] = VerticesArray[i];
			}
			mesh.vertices = vrtTemp;
			//mesh.vertices = new Vector3[]{p0,p1,p2,p3};
			for (int i = 0; i < IndicesArray.Length; i++) {
				indexTemp[i] = IndicesArray[i];
			}
			mesh.triangles = indexTemp;
			/*mesh.triangles = new int[]{
				0,1,2,
				0,2,3,
				2,1,3,
				0,3,1
			};	*/
			// basically just assigns a corner of the texture to each vertex
			/*
			mesh.uv = new Vector2[]{
				new Vector2(0,0),
				new Vector2(1,0),
				new Vector2(0,1),
				new Vector2(1,1),
			};
			*/
		} else {
			Vector3[] vrtTemp = new Vector3[IndicesArray.Length];
			for (int i = 0; i < IndicesArray.Length; i++) {
				vrtTemp[i] = VerticesArray[IndicesArray[i]];
			}
			mesh.vertices = vrtTemp;
			/*
			mesh.vertices = new Vector3[]{
				p0,p1,p2,
				p0,p2,p3,
				p2,p1,p3,
				p0,p3,p1
			};
			*/
			for (int i = 0; i < IndicesArray.Length; i++) {
				indexTemp[i] = i;
			}
			mesh.triangles = indexTemp;
			/*
			mesh.triangles = new int[]{
				0,1,2,
				3,4,5,
				6,7,8,
				9,10,11
			};
			*/
			/*
			Vector2 uv0 = new Vector2(0,0);
			Vector2 uv1 = new Vector2(1,0);
			Vector2 uv2 = new Vector2(0.5f,1);
			
			mesh.uv = new Vector2[]{
				uv0,uv1,uv2,
				uv0,uv1,uv2,
				uv0,uv1,uv2,
				uv0,uv1,uv2
			};
			*/
		}
		
		mesh.RecalculateNormals();
		mesh.RecalculateBounds();
		mesh.Optimize();
		MeshCollider meshCollider = GetComponent<MeshCollider> ();

		meshCollider.sharedMesh = mesh;
		meshCollider.convex = true;
		MeshRenderer mr = GetComponent<MeshRenderer>();
		mr.material = material;
		gameObject.AddComponent<Rigidbody> ();
		gameObject.AddComponent<ShotCube> ();
		ShotCube SC = gameObject.GetComponent<ShotCube> ();
		SC.fragment = GameObject.Find ("GameObject 1");
		SC.lifetime = life;

		if(GameState.Instance.shouldFreezeFracture){
			Rigidbody freeze = gameObject.GetComponent<Rigidbody> ();
			freeze.constraints = RigidbodyConstraints.FreezeAll;
		}

	}
	void Start() {

	}
	// Update is called once per frame
	void Update () {
		
	}

	void OnCollisionEnter(Collision collider) {
		if (collider.gameObject.tag == "bullet") {
			ContactPoint contact = collider.contacts [0];
			Vector3 local_vec = transform.InverseTransformPoint(contact.point);
			Debug.Log (local_vec);
			//Destroy (collider.gameObject);
		}
	}
}
