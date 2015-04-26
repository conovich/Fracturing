using UnityEngine;
using System.Collections;
using MIConvexHull;
using System.Collections.Generic;
using System;
using System.Runtime.InteropServices;

public class ShotCube : MonoBehaviour {
	[DllImport ("FracturePlugin")]
	private static extern int voroCubeExample(float x, float y, float z);

	[DllImport ("FracturePlugin")]
	private static extern float voroGeoDecomp(float x, float y, float z, IntPtr indices, IntPtr numVertices, int indSize, int vrtSize, int numParticles);

	[DllImport ("FracturePlugin")]
	private static extern void outPutMesh(float[] vrts, int[] indices, Vector3[] vertices, int numMesh);

	[DllImport ("FracturePlugin")]
	private static extern int voroGetNumNewMesh();

	[DllImport ("FracturePlugin")]
	private static extern int voroGetNumCellVerts(int i);

	[DllImport ("FracturePlugin")]
	private static extern void voroGetCellVertices(float[] outVertices, ref int k, ref bool inLoop);

	[DllImport ("FracturePlugin")]
	private static extern int numNewMesh ();

	[DllImport ("FracturePlugin")]
	private static extern int numVertices (int numMesh);

	public GameObject fragment;
	public enum MODE { CUBE_VOLUME, SPHERE_VOLUME, SPHERE_SURFACE };
	public MODE mode = MODE.SPHERE_SURFACE;
	public double size = 1;
	public int lifetime;
	int maxLife = 1;
	List<Vertex3> convexHullVertices;
	List<Face3> convexHullFaces;
	List<int> convexHullIndices;


	// Use this for initialization
	void Start () {
		gameObject.tag = "explode";
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	/*
	float triangleIntersection(Vector3 v0, Vector3 v1, Vector3 v2, Vector3 dir, Vector3 orig) {
		//Intersection inter;
		Vector3 xc = Vector3.Cross((v1 - v0), (v2 - v0));
		Vector3 p = Vector3.Cross(dir, v2 - v0);
		Vector3 norm = xc.normalized;

		if (Mathf.Abs(norm[0]) < .0001f && Mathf.Abs(norm[1]) < .0001f && Mathf.Abs(norm[2]) < .0001){

			return -1.0f;
		}
		
		float t;
		float a = Vector3.Dot(v1 - v0, p);
		
		if (a < .00001 && a > -.00001){

			return -1.0f;
		}
		else{
			float f = 1.0f/a;
			Vector3 s = orig - v0;
			float u = f*(Vector3.Dot(s, p));
			if ( u < 0.0f || u > 1.0f){

				return -1.0f;
			}
			
			Vector3 q = Vector3.Cross(s, v1 - v0);
			float v = f*Vector3.Dot(dir, q);
			
			if (v < 0.0f || u + v > 1.0f){

				return -1.0f;
			}
			
			t = f*Vector3.Dot(v2 - v0, q); //set t
			
			if (t < 0){

				return -1.0f;
			}
		}
		
		//inter.t = t;
		//inter.normal = xc;
		
		return t;
	}
	*/
	void OnCollisionEnter(Collision collider) {
		if (collider.gameObject.tag == "bullet" && lifetime < maxLife) {
			
			ContactPoint contact = collider.contacts [0];
			Vector3 hitPoint = contact.point;
			Vector3 local_vec = transform.InverseTransformPoint(contact.point);

			//Debug.Log (local_vec);
			//Rigidbody rg = gameObject.GetComponent<Rigidbody>();
			//Vector3 final = collider.rigidbody.mass * collider.relativeVelocity / (rg.mass + collider.rigidbody.mass);
			//Vector3 impulse = final * rg.mass;
			MeshFilter oldMesh = gameObject.GetComponent<MeshFilter>();
			Vector3[] oldMeshVrt = oldMesh.mesh.vertices;
			float[] oldVrts = new float[oldMeshVrt.Length * 3];
			for (int i = 0; i < oldMeshVrt.Length; i++) {
				oldVrts[i*3] = oldMeshVrt[i].x * gameObject.transform.localScale.x;
				oldVrts[(i*3)+1] = oldMeshVrt[i].y * gameObject.transform.localScale.y;
				oldVrts[(i*3)+2] = oldMeshVrt[i].z * gameObject.transform.localScale.z;
			}
			int[] oldMeshInd = oldMesh.mesh.triangles;
			Vector3 vel = (collider.rigidbody.velocity).normalized;
			//TRYING TO FIND POINT OF INTERSECTION
			/*
			float dist = -1.0f;
			Vector3 dir = vel;
			Vector3 orig = local_vec;
			//loop through the indices
			float xScale = gameObject.transform.localScale.x;
			float yScale = gameObject.transform.localScale.y;
			float zScale = gameObject.transform.localScale.z;
			for(int i = 0; i < oldMeshInd.Length; i+=3)
			{
				Vector3 p0 = new Vector3(oldMeshVrt[oldMeshInd[i]].x*xScale, oldMeshVrt[oldMeshInd[i]].y*yScale, oldMeshVrt[oldMeshInd[i]].z*zScale);
				Vector3 p1 = new Vector3(oldMeshVrt[oldMeshInd[i+1]].x*xScale, oldMeshVrt[oldMeshInd[i+1]].y*yScale, oldMeshVrt[oldMeshInd[i+1]].z*zScale);
				Vector3 p2 = new Vector3(oldMeshVrt[oldMeshInd[i+2]].x*xScale, oldMeshVrt[oldMeshInd[i+2]].y*yScale, oldMeshVrt[oldMeshInd[i+2]].z*zScale);

				float t = triangleIntersection(p0, p1, p2, dir, orig); //check every face	

				//if(smallest_inter.t == -1) smallest_inter = inter; //set smallest_inter to the first intersection
				if (dist < 0.0f){
					dist = t;
				}
				if(dist > t && t > 0) {
					dist = t;
					//smallest_inter = inter;
					//numOfIntersections++;  //only add to numOfIntersections if t != -1
				}

			}
			if (dist != -1){
				local_vec += dist*(dir);
			
			}
			*/

			RaycastHit hit;
			Ray ray = new Ray(collider.transform.position, -1*collider.transform.forward);
			if (Physics.Raycast (ray, out hit)) {
				if (hit.rigidbody != null && hit.collider.gameObject.tag == "explode"){
					local_vec = transform.InverseTransformPoint(hit.point);
				}
			}
			//local_vec = new Vector3(0, 0, 0);
			local_vec[0] = local_vec[0] * gameObject.transform.localScale.x;
			local_vec[1] = local_vec[1] * gameObject.transform.localScale.y;
			local_vec[2] = local_vec[2] * gameObject.transform.localScale.z;
			//DONE TRYING
			//local_vec += (vel * (-.1f));
			//GETTING INFO TO PASS TO OUR FUNCTION
			//Collider coll = collider.gameObject.GetComponent<Collider>();
			//Vector3 local_vec = coll.ClosestPointOnBounds(hitPoint);
			//local_vec = transform.InverseTransformPoint(local_vec);
			/*
			Rigidbody rb = gameObject.GetComponent<Rigidbody>();
			rb.constraints = RigidbodyConstraints.FreezeAll;
			Rigidbody rb1 = collider.gameObject.GetComponent<Rigidbody>();
			rb1.constraints = RigidbodyConstraints.FreezeAll;
			*/
			//CALL AND INPUT NEW FRAGMENTED CELLS
			//NEW STUFF BEGINS
			//int NumberOfVertices = 24;

			//int run = voroCubeExample();
			Mesh mesh = new Mesh();
			//int numberOfMeshes = numNewMesh();

			//int numberOfMeshes = voroCubeExample (local_vec.x, local_vec.y, local_vec.z);
			//int numberOfMeshes = voroCubeExample (local_vec.x*2, local_vec.y*2, local_vec.z*2);
			//float num = voroGeoDecomp(local_vec.x, local_vec.y, local_vec.z, oldMeshInd, oldVrts);
			//fixed (int* data = &oldMeshInd[0]);
			IntPtr initIndArray = Marshal.AllocHGlobal(oldMeshInd.Length*sizeof(int));
			IntPtr initVrtArray = Marshal.AllocHGlobal (oldVrts.Length*sizeof(float));
			//IntPtr allocIndArray = Marshal.AllocHGlobal (sizeof(int)*4);
			//Marshal.WriteInt32(initIndArray, allocIndArray.ToInt32 ());
			//Marshal.WriteInt32 (initIndArray + 4, allocIndArray.ToInt32 () + 2*sizeof(int));
			Marshal.Copy (oldMeshInd, 0, initIndArray, oldMeshInd.Length);
			Marshal.Copy (oldVrts, 0, initVrtArray, oldVrts.Length);
			float mag = collider.relativeVelocity.magnitude;
			int numParticles = (int)Mathf.Floor(mag*2);
			//Marshal.Copy (
			float numberOfMeshes = voroGeoDecomp(local_vec.x, local_vec.y, local_vec.z, initIndArray, initVrtArray, oldMeshInd.Length, oldVrts.Length, numParticles);
			Debug.Log (numberOfMeshes);
			Marshal.FreeHGlobal (initIndArray);
			Marshal.FreeHGlobal (initVrtArray);


			float[] verts; //= new float[72];
			bool inLoop = false;
			//bool run = false;

			ConvexHull<Vertex3, Face3> convexHull;
			for (int r = 0; r < numberOfMeshes; r++){
				//int numberOfVertices = numVertices(r);

				int otherNumber = voroGetNumCellVerts(r);
				if (otherNumber == 0) {
					continue;
				}
				int numberOfVertices = otherNumber*3;
				verts = new float[numberOfVertices];
					//mesh = new Mesh();
				mesh.Clear();

				//outPutMesh (verts, oldMeshInd, oldMeshVrt, r);
				voroGetCellVertices (verts, ref r, ref inLoop);
				/*
				Vector3 p0 = new Vector3(-.5f,.5f,-.5f);
				Vector3 p1 = new Vector3(.5f,.5f,-.5f);
				Vector3 p2 = new Vector3(0.5f, 0.5f, 0.5f);
				Vector3 p3 = new Vector3(-0.5f, 0.5f, 0.5f);
				Vector3 p4 = new Vector3(-0.5f, -0.5f, -0.5f);
				Vector3 p5 = new Vector3(0.5f, -0.5f, -0.5f);
				Vector3 p6 = new Vector3(0.5f, -0.5f, 0.5f);
				Vector3 p7 = new Vector3(-0.5f, -0.5f, 0.5f);
				Vector3 p8 = new Vector3 (.5f, 1, .5f);
				*/

				int NumberOfVertices = (verts.Length / 3) ;
				Vertex3[] vertices = new Vertex3[NumberOfVertices];
				Vector3[] meshVerts = new Vector3[NumberOfVertices];
				int[] meshIndices = new int[NumberOfVertices];

				int m = 0;
				//Vector3[] vert2;
				Vector3[] vert = new Vector3[NumberOfVertices];
				for (int j = 0; j < verts.Length; j+=3){
					vert[m] = new Vector3(verts[j], verts[j + 1], verts[j + 2]);
					m++;
				}
				//vert = new Vector3[]{p4,p5,p6,p7,p8};//,p1,p5,p4,p1,p5,p6,p2,p2,p3,p7,p6,p3,p0,p4,p7,p4,p5,p6,p7};
				int i = 0;
				while(i < NumberOfVertices)
				{
					Vector3 v = vert[i]; //new Vector3(Random.Range(-1.0f, 1.0f), Random.Range(-1.0f, 1.0f), Random.Range(-1.0f, 1.0f));
					
					if(mode == MODE.CUBE_VOLUME)
					{
						vertices[i] = new Vertex3(v.x,v.y,v.z);
						meshVerts[i] = vert[i]; //vertices[i].ToVector3();
						meshIndices[i] = i;
						
						i++;
					}
					else if(mode == MODE.SPHERE_VOLUME)
					{
						if(v.magnitude < 1.0f)
						{
							vertices[i] = new Vertex3(v.x,v.y,v.z);
							meshVerts[i] = vertices[i].ToVector3();
							meshIndices[i] = i;
							
							i++;
						}
						
					}
					else if(mode == MODE.SPHERE_SURFACE)
					{
						v.Normalize();
						
						vertices[i] = new Vertex3(v.x,v.y,v.z);
						meshVerts[i] = vertices[i].ToVector3();
						meshIndices[i] = i;
						
						i++;
					}
				}

				mesh.vertices = meshVerts;
				mesh.SetIndices(meshIndices, MeshTopology.Points, 0);
				//mesh.bounds = new Bounds(Vector3.zero, new Vector3((float)size,(float)size,(float)size));
				
				float now = Time.realtimeSinceStartup;
				convexHull = ConvexHull.Create<Vertex3, Face3>(vertices);
				float interval = Time.realtimeSinceStartup - now;
				
				convexHullVertices = new List<Vertex3>(convexHull.Points);
				convexHullFaces = new List<Face3>(convexHull.Faces);
				convexHullIndices = new List<int>();
				
				foreach(Face3 f in convexHullFaces)
				{
					convexHullIndices.Add(convexHullVertices.IndexOf(f.Vertices[0]));
					convexHullIndices.Add(convexHullVertices.IndexOf(f.Vertices[1]));
					convexHullIndices.Add(convexHullVertices.IndexOf(f.Vertices[2]));
				}
				//Debug.Log ("There are " + convexHullFaces.Count + " faces in this convex hull.");
				//Debug.Log("Out of the " + NumberOfVertices + " vertices, there are " + convexHullVertices.Count + " verts on the convex hull.");
				//Debug.Log("time = " + interval * 1000.0f + " ms");




				//NEW STUFF ENDS

				GameObject frag = Instantiate (fragment, gameObject.transform.position, gameObject.transform.rotation) as GameObject;
				Cell s = frag.gameObject.AddComponent<Cell>();
				//frag.gameObject.AddComponent<Rigidbody>();
				MeshFilter meshFilter = gameObject.GetComponent<MeshFilter>();
				meshFilter.mesh = new Mesh();
				Vector3[] vrts; 
				vrts = new Vector3[convexHullVertices.Count];
				for (i = 0; i < convexHullVertices.Count; i++) {
					vrts[i] = new Vector3((float)convexHullVertices[i].x, (float)convexHullVertices[i].y, (float)convexHullVertices[i].z);
				}
				s.VerticesArray = vrts;
				int[] inds;
				inds = new int[convexHullIndices.Count];
				for (i = 0; i < convexHullIndices.Count; i++) {
					inds[i] = convexHullIndices[i];
				}
				s.IndicesArray = inds;
				Renderer rend = gameObject.GetComponent<Renderer>();
				s.life = lifetime + 1;
				s.material = rend.material;
				s.Build();

			}

			Destroy (gameObject);
			Destroy (collider.gameObject);
			//Rigidbody rg = gameObject.GetComponent<Rigidbody>();
			//rg.constraints = RigidbodyConstraints.FreezeAll;
			//collider.gameObject.transform.position = Transform.localtoWorl(local_vec);
			//collider.rigidbody.constraints = RigidbodyConstraints.FreezeAll;

		}
		if (collider.gameObject.tag == "ground" && lifetime < maxLife) {
			
			ContactPoint contact = collider.contacts [0];
			Vector3 hitPoint = contact.point;
			Vector3 local_vec = transform.InverseTransformPoint(contact.point);
			
			//Debug.Log (local_vec);
			//Rigidbody rg = gameObject.GetComponent<Rigidbody>();
			//Vector3 final = collider.rigidbody.mass * collider.relativeVelocity / (rg.mass + collider.rigidbody.mass);
			//Vector3 impulse = final * rg.mass;
			MeshFilter oldMesh = gameObject.GetComponent<MeshFilter>();
			Vector3[] oldMeshVrt = oldMesh.mesh.vertices;
			float[] oldVrts = new float[oldMeshVrt.Length * 3];
			for (int i = 0; i < oldMeshVrt.Length; i++) {
				oldVrts[i*3] = oldMeshVrt[i].x * gameObject.transform.localScale.x;
				oldVrts[(i*3)+1] = oldMeshVrt[i].y * gameObject.transform.localScale.y;
				oldVrts[(i*3)+2] = oldMeshVrt[i].z * gameObject.transform.localScale.z;
			}
			int[] oldMeshInd = oldMesh.mesh.triangles;
			//Vector3 vel = (collider.rigidbody.velocity).normalized;
			//TRYING TO FIND POINT OF INTERSECTION
			/*
			float dist = -1.0f;
			Vector3 dir = vel;
			Vector3 orig = local_vec;
			//loop through the indices
			float xScale = gameObject.transform.localScale.x;
			float yScale = gameObject.transform.localScale.y;
			float zScale = gameObject.transform.localScale.z;
			for(int i = 0; i < oldMeshInd.Length; i+=3)
			{
				Vector3 p0 = new Vector3(oldMeshVrt[oldMeshInd[i]].x*xScale, oldMeshVrt[oldMeshInd[i]].y*yScale, oldMeshVrt[oldMeshInd[i]].z*zScale);
				Vector3 p1 = new Vector3(oldMeshVrt[oldMeshInd[i+1]].x*xScale, oldMeshVrt[oldMeshInd[i+1]].y*yScale, oldMeshVrt[oldMeshInd[i+1]].z*zScale);
				Vector3 p2 = new Vector3(oldMeshVrt[oldMeshInd[i+2]].x*xScale, oldMeshVrt[oldMeshInd[i+2]].y*yScale, oldMeshVrt[oldMeshInd[i+2]].z*zScale);

				float t = triangleIntersection(p0, p1, p2, dir, orig); //check every face	

				//if(smallest_inter.t == -1) smallest_inter = inter; //set smallest_inter to the first intersection
				if (dist < 0.0f){
					dist = t;
				}
				if(dist > t && t > 0) {
					dist = t;
					//smallest_inter = inter;
					//numOfIntersections++;  //only add to numOfIntersections if t != -1
				}

			}
			if (dist != -1){
				local_vec += dist*(dir);
			
			}
			*/
			
			RaycastHit hit;
			Ray ray = new Ray(collider.transform.position, -1*collider.transform.forward);
			if (Physics.Raycast (ray, out hit)) {
				if (hit.rigidbody != null && hit.collider.gameObject.tag == "explode"){
					local_vec = transform.InverseTransformPoint(hit.point);
				}
			}
			local_vec = new Vector3(0, 0, 0);
			local_vec[0] = local_vec[0] * gameObject.transform.localScale.x;
			local_vec[1] = local_vec[1] * gameObject.transform.localScale.y;
			local_vec[2] = local_vec[2] * gameObject.transform.localScale.z;
			//DONE TRYING
			//local_vec += (vel * (-.1f));
			//GETTING INFO TO PASS TO OUR FUNCTION
			//Collider coll = collider.gameObject.GetComponent<Collider>();
			//Vector3 local_vec = coll.ClosestPointOnBounds(hitPoint);
			//local_vec = transform.InverseTransformPoint(local_vec);
			/*
			Rigidbody rb = gameObject.GetComponent<Rigidbody>();
			rb.constraints = RigidbodyConstraints.FreezeAll;
			Rigidbody rb1 = collider.gameObject.GetComponent<Rigidbody>();
			rb1.constraints = RigidbodyConstraints.FreezeAll;
			*/
			//CALL AND INPUT NEW FRAGMENTED CELLS
			//NEW STUFF BEGINS
			//int NumberOfVertices = 24;
			
			//int run = voroCubeExample();
			Mesh mesh = new Mesh();
			//int numberOfMeshes = numNewMesh();
			
			//int numberOfMeshes = voroCubeExample (local_vec.x, local_vec.y, local_vec.z);
			//int numberOfMeshes = voroCubeExample (local_vec.x*2, local_vec.y*2, local_vec.z*2);
			//float num = voroGeoDecomp(local_vec.x, local_vec.y, local_vec.z, oldMeshInd, oldVrts);
			//fixed (int* data = &oldMeshInd[0]);
			IntPtr initIndArray = Marshal.AllocHGlobal(oldMeshInd.Length*sizeof(int));
			IntPtr initVrtArray = Marshal.AllocHGlobal (oldVrts.Length*sizeof(float));
			//IntPtr allocIndArray = Marshal.AllocHGlobal (sizeof(int)*4);
			//Marshal.WriteInt32(initIndArray, allocIndArray.ToInt32 ());
			//Marshal.WriteInt32 (initIndArray + 4, allocIndArray.ToInt32 () + 2*sizeof(int));
			Marshal.Copy (oldMeshInd, 0, initIndArray, oldMeshInd.Length);
			Marshal.Copy (oldVrts, 0, initVrtArray, oldVrts.Length);
			//float mag = collider.relativeVelocity.magnitude;
			int numParticles = 100;//(int)Mathf.Floor(mag*2);
			//Marshal.Copy (
			float numberOfMeshes = voroGeoDecomp(local_vec.x, local_vec.y, local_vec.z, initIndArray, initVrtArray, oldMeshInd.Length, oldVrts.Length, numParticles);
			Debug.Log (numberOfMeshes);
			Marshal.FreeHGlobal (initIndArray);
			Marshal.FreeHGlobal (initVrtArray);
			
			
			float[] verts; //= new float[72];
			bool inLoop = false;
			//bool run = false;
			
			ConvexHull<Vertex3, Face3> convexHull;
			for (int r = 0; r < numberOfMeshes; r++){
				//int numberOfVertices = numVertices(r);
				
				int otherNumber = voroGetNumCellVerts(r);
				if (otherNumber == 0) {
					continue;
				}
				int numberOfVertices = otherNumber*3;
				verts = new float[numberOfVertices];
				//mesh = new Mesh();
				mesh.Clear();
				
				//outPutMesh (verts, oldMeshInd, oldMeshVrt, r);
				voroGetCellVertices (verts, ref r, ref inLoop);
				/*
				Vector3 p0 = new Vector3(-.5f,.5f,-.5f);
				Vector3 p1 = new Vector3(.5f,.5f,-.5f);
				Vector3 p2 = new Vector3(0.5f, 0.5f, 0.5f);
				Vector3 p3 = new Vector3(-0.5f, 0.5f, 0.5f);
				Vector3 p4 = new Vector3(-0.5f, -0.5f, -0.5f);
				Vector3 p5 = new Vector3(0.5f, -0.5f, -0.5f);
				Vector3 p6 = new Vector3(0.5f, -0.5f, 0.5f);
				Vector3 p7 = new Vector3(-0.5f, -0.5f, 0.5f);
				Vector3 p8 = new Vector3 (.5f, 1, .5f);
				*/
				
				int NumberOfVertices = (verts.Length / 3) ;
				Vertex3[] vertices = new Vertex3[NumberOfVertices];
				Vector3[] meshVerts = new Vector3[NumberOfVertices];
				int[] meshIndices = new int[NumberOfVertices];
				
				int m = 0;
				//Vector3[] vert2;
				Vector3[] vert = new Vector3[NumberOfVertices];
				for (int j = 0; j < verts.Length; j+=3){
					vert[m] = new Vector3(verts[j], verts[j + 1], verts[j + 2]);
					m++;
				}
				//vert = new Vector3[]{p4,p5,p6,p7,p8};//,p1,p5,p4,p1,p5,p6,p2,p2,p3,p7,p6,p3,p0,p4,p7,p4,p5,p6,p7};
				int i = 0;
				while(i < NumberOfVertices)
				{
					Vector3 v = vert[i]; //new Vector3(Random.Range(-1.0f, 1.0f), Random.Range(-1.0f, 1.0f), Random.Range(-1.0f, 1.0f));
					
					if(mode == MODE.CUBE_VOLUME)
					{
						vertices[i] = new Vertex3(v.x,v.y,v.z);
						meshVerts[i] = vert[i]; //vertices[i].ToVector3();
						meshIndices[i] = i;
						
						i++;
					}
					else if(mode == MODE.SPHERE_VOLUME)
					{
						if(v.magnitude < 1.0f)
						{
							vertices[i] = new Vertex3(v.x,v.y,v.z);
							meshVerts[i] = vertices[i].ToVector3();
							meshIndices[i] = i;
							
							i++;
						}
						
					}
					else if(mode == MODE.SPHERE_SURFACE)
					{
						v.Normalize();
						
						vertices[i] = new Vertex3(v.x,v.y,v.z);
						meshVerts[i] = vertices[i].ToVector3();
						meshIndices[i] = i;
						
						i++;
					}
				}
				
				mesh.vertices = meshVerts;
				mesh.SetIndices(meshIndices, MeshTopology.Points, 0);
				//mesh.bounds = new Bounds(Vector3.zero, new Vector3((float)size,(float)size,(float)size));
				
				float now = Time.realtimeSinceStartup;
				convexHull = ConvexHull.Create<Vertex3, Face3>(vertices);
				float interval = Time.realtimeSinceStartup - now;
				
				convexHullVertices = new List<Vertex3>(convexHull.Points);
				convexHullFaces = new List<Face3>(convexHull.Faces);
				convexHullIndices = new List<int>();
				
				foreach(Face3 f in convexHullFaces)
				{
					convexHullIndices.Add(convexHullVertices.IndexOf(f.Vertices[0]));
					convexHullIndices.Add(convexHullVertices.IndexOf(f.Vertices[1]));
					convexHullIndices.Add(convexHullVertices.IndexOf(f.Vertices[2]));
				}
				//Debug.Log ("There are " + convexHullFaces.Count + " faces in this convex hull.");
				//Debug.Log("Out of the " + NumberOfVertices + " vertices, there are " + convexHullVertices.Count + " verts on the convex hull.");
				//Debug.Log("time = " + interval * 1000.0f + " ms");
				
				
				
				
				//NEW STUFF ENDS
				
				GameObject frag = Instantiate (fragment, gameObject.transform.position, gameObject.transform.rotation) as GameObject;
				Cell s = frag.gameObject.AddComponent<Cell>();
				//frag.gameObject.AddComponent<Rigidbody>();
				MeshFilter meshFilter = gameObject.GetComponent<MeshFilter>();
				meshFilter.mesh = new Mesh();
				Vector3[] vrts; 
				vrts = new Vector3[convexHullVertices.Count];
				for (i = 0; i < convexHullVertices.Count; i++) {
					vrts[i] = new Vector3((float)convexHullVertices[i].x, (float)convexHullVertices[i].y, (float)convexHullVertices[i].z);
				}
				s.VerticesArray = vrts;
				int[] inds;
				inds = new int[convexHullIndices.Count];
				for (i = 0; i < convexHullIndices.Count; i++) {
					inds[i] = convexHullIndices[i];
				}
				s.IndicesArray = inds;
				Renderer rend = gameObject.GetComponent<Renderer>();
				s.life = lifetime + 1;
				s.material = rend.material;
				s.Build();
				
			}
			
			Destroy (gameObject);
			//Destroy (collider.gameObject);
			//Rigidbody rg = gameObject.GetComponent<Rigidbody>();
			//rg.constraints = RigidbodyConstraints.FreezeAll;
			//collider.gameObject.transform.position = Transform.localtoWorl(local_vec);
			//collider.rigidbody.constraints = RigidbodyConstraints.FreezeAll;
			
		}
	}
}

