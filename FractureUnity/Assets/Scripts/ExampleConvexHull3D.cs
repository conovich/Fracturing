using UnityEngine;
using System.Collections.Generic;
using MIConvexHull;

public class ExampleConvexHull3D : MonoBehaviour 
{

	public enum MODE { CUBE_VOLUME, SPHERE_VOLUME, SPHERE_SURFACE };

	public MODE mode = MODE.CUBE_VOLUME;
	public int NumberOfVertices = 16;
	public double size = 5;

	Material lineMaterial;
	Mesh mesh;
	
	List<Vertex3> convexHullVertices;
	List<Face3> convexHullFaces;
	List<int> convexHullIndices;
	Matrix4x4 rotation = Matrix4x4.identity;

	float theta;
	float beta;
	bool drawHull = true;
	
	void CreateLineMaterial() 
	{
		if( !lineMaterial ) 
		{
			lineMaterial = new Material("Shader \"Lines/Colored Blended\" {" +
			                            "SubShader { Pass { " +
			                            "    Blend SrcAlpha OneMinusSrcAlpha " +
			                            "    ZWrite Off Cull Off Fog { Mode Off } " +
			                            "    BindChannels {" +
			                            "      Bind \"vertex\", vertex Bind \"color\", color }" +
			                            "} } }" );
			
			lineMaterial.hideFlags = HideFlags.HideAndDontSave;
			lineMaterial.shader.hideFlags = HideFlags.HideAndDontSave;
		}
	}

	// Use this for initialization
	void Start () 
	{
		CreateLineMaterial();
		
		mesh = new Mesh();
		Vertex3[] vertices = new Vertex3[NumberOfVertices];
		Vector3[] meshVerts = new Vector3[NumberOfVertices];
		int[] meshIndices = new int[NumberOfVertices];

		Random.seed = 0;
		int i = 0;
		Vector3 p0 = new Vector3(0,0,0);
		Vector3 p1 = new Vector3(1,0,0);
		Vector3 p2 = new Vector3(1, 1, 0);
		Vector3 p3 = new Vector3(1, 1, 1);
		Vector3 p4 = new Vector3(0,1,1);
		Vector3 p5 = new Vector3(0,0,1);
		Vector3 p6 = new Vector3(1, 0, 1);
		Vector3 p7 = new Vector3(0, 1, 0);
		Vector3 p8 = new Vector3 (.5f, 1, .5f);
		Vector3[] vert = new Vector3[]{p1, p6, p5, p0, p1, p6, p8, p0, p5, p8, p0, p1, p8, p5, p6, p8};
		//Vector3[] vert = new Vector3[]{p1,p2,p3,p6,p3,p6,p5,p4,p5,p4,p7,p0,p0,p1,p2,p7,p2,p3,p4,p7,p5,p6,p1,p0};
		while(i < NumberOfVertices)
		{
			Vector3 v = vert[i]; //new Vector3(Random.Range(-1.0f, 1.0f), Random.Range(-1.0f, 1.0f), Random.Range(-1.0f, 1.0f));

			if(mode == MODE.CUBE_VOLUME)
			{
				vertices[i] = new Vertex3(size * v.x, size * v.y, size * v.z);
				meshVerts[i] = vertices[i].ToVector3();
				meshIndices[i] = i;
				
				i++;
			}
			else if(mode == MODE.SPHERE_VOLUME)
			{
				if(v.magnitude < 1.0f)
				{
					vertices[i] = new Vertex3(size * v.x, size * v.y, size * v.z);
					meshVerts[i] = vertices[i].ToVector3();
					meshIndices[i] = i;

					i++;
				}

			}
			else if(mode == MODE.SPHERE_SURFACE)
			{
				v.Normalize();

				vertices[i] = new Vertex3(size * v.x, size * v.y, size * v.z);
				meshVerts[i] = vertices[i].ToVector3();
				meshIndices[i] = i;
				
				i++;
			}
		}
		
		mesh.vertices = meshVerts;
		mesh.SetIndices(meshIndices, MeshTopology.Points, 0);
		//mesh.bounds = new Bounds(Vector3.zero, new Vector3((float)size,(float)size,(float)size));
		
		float now = Time.realtimeSinceStartup;
		ConvexHull<Vertex3, Face3> convexHull = ConvexHull.Create<Vertex3, Face3>(vertices);
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
		Debug.Log ("There are " + convexHullFaces.Count + " faces in this convex hull.");
		Debug.Log("Out of the " + NumberOfVertices + " vertices, there are " + convexHullVertices.Count + " verts on the convex hull.");
		Debug.Log("time = " + interval * 1000.0f + " ms");
		
	}
	
	void Update()
	{
		if(Input.GetKeyDown(KeyCode.F1)) drawHull = !drawHull;

		if(Input.GetKey("a") || Input.GetKey(KeyCode.KeypadMinus))
		{
			theta += (Input.GetKey("a")) ?  0.005f : -0.005f;
			
			rotation[0,0] = Mathf.Cos(theta);
			rotation[0,2] = Mathf.Sin(theta);
			rotation[2,0] = -Mathf.Sin(theta);
			rotation[2,2] = Mathf.Cos(theta);
		}
		if (Input.GetKey ("s")){
			beta += (Input.GetKey("s")) ?  0.005f : -0.005f;
			rotation[1,1] = Mathf.Sin (beta);
		}
		Graphics.DrawMesh(mesh, rotation, lineMaterial, 0, Camera.main);
	}
	
	void OnPostRender() 
	{
		GL.PushMatrix();
		
		GL.LoadIdentity();
		GL.MultMatrix(GetComponent<Camera>().worldToCameraMatrix * rotation);
		GL.LoadProjectionMatrix(GetComponent<Camera>().projectionMatrix);
		
		lineMaterial.SetPass( 0 );
		GL.Begin( GL.LINES );
		GL.Color( Color.red );

		if(drawHull)
		{
			for(int i = 0; i < convexHullIndices.Count; i+=3)
			{
				int v0 = convexHullIndices[i+0];
				int v1 = convexHullIndices[i+1];
				int v2 = convexHullIndices[i+2];

				GL.Vertex3( (float)convexHullVertices[v0].x, (float)convexHullVertices[v0].y, (float)convexHullVertices[v0].z);
				GL.Vertex3( (float)convexHullVertices[v1].x, (float)convexHullVertices[v1].y, (float)convexHullVertices[v1].z);

				GL.Vertex3( (float)convexHullVertices[v0].x, (float)convexHullVertices[v0].y, (float)convexHullVertices[v0].z);
				GL.Vertex3( (float)convexHullVertices[v2].x, (float)convexHullVertices[v2].y, (float)convexHullVertices[v2].z);

				GL.Vertex3( (float)convexHullVertices[v1].x, (float)convexHullVertices[v1].y, (float)convexHullVertices[v1].z);
				GL.Vertex3( (float)convexHullVertices[v2].x, (float)convexHullVertices[v2].y, (float)convexHullVertices[v2].z);

			}
		}
		
		GL.End();
		
		GL.PopMatrix();
	}
}



















