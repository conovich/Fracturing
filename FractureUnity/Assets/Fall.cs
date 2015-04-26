using UnityEngine;
using System.Collections;

public class Fall : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		if (Input.GetKeyDown("f")) {
			Rigidbody rb = gameObject.GetComponent<Rigidbody> ();
			rb.AddForce (new Vector3 (100, 0, 0));
		}
	}
}
