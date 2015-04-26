using UnityEngine;
using System.Collections;

public class Shot : MonoBehaviour {
	public GameObject bullet;
	public float distance = 10.0f;
	public bool canon = false;
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		if (Input.GetKey ("c")) {
			canon = !canon;
		}
		if (Input.GetMouseButtonDown(0)) {

			Vector3 position = new Vector3(Input.mousePosition.x, Input.mousePosition.y, distance);
			position = Camera.main.ScreenToWorldPoint(position);
			GameObject go = Instantiate(bullet, transform.position, Quaternion.identity) as GameObject;
			go.transform.LookAt(position);    
			//Debug.Log(position);    
			Rigidbody rb = go.gameObject.GetComponent<Rigidbody>();
			if (!canon) {//AddForce(go.transform.forward * 1000);
				rb.AddForce (go.transform.forward * 3000);
			}
			else {
				rb.AddForce (go.transform.forward * 5000);
			}
		}
	}
	
}
