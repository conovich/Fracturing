using UnityEngine;
using System.Collections;

public class CameraControls : MonoBehaviour {

	float RotationSpeed = 1;
	float MoveSpeed = 1;
	
	float turnIncrement = 1.0f; //in degrees

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		GetInput ();
	}

	void GetInput()
	{
		float verticalAxisInput = Input.GetAxis ("Vertical");
		
		if ( verticalAxisInput != 0 ) 
		{
			GetComponent<Rigidbody>().velocity = transform.forward*verticalAxisInput*MoveSpeed;
			//Move ( moveIncrement*verticalAxisInput*moveSpeed );
		}
		else{
			GetComponent<Rigidbody>().velocity = Vector3.zero;
		}
		
		
		float horizontalAxisInput = Input.GetAxis ("Horizontal");
		
		if ( horizontalAxisInput != 0)
		{
			Turn( turnIncrement*horizontalAxisInput*RotationSpeed );
		}
		
	}

	void Move( float amount ){
		transform.position += transform.forward * amount;
	}
	
	void Turn( float amount ){
		transform.RotateAround (transform.position, Vector3.up, amount );
	}
}
