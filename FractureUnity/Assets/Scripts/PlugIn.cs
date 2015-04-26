using UnityEngine;
using System.Collections;
using System;
using System.Runtime.InteropServices;
public class PlugIn : MonoBehaviour {
	[DllImport ("FracturePlugin")]
	private static extern void outPutMesh(float[] vrts, int[] indices, Vector3[] vertices);
	// Use this for initialization
	void Start () {
		float[] vrts = new float[36];
		int[] indices = new int[4];
		Vector3[] vertices = new Vector3[4];
		outPutMesh (vrts, indices, vertices);
		for (int i = 0; i < vrts.Length; i++) {
			Debug.Log (vrts [i]);
		}
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
