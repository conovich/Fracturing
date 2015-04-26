using UnityEngine;
using System.Collections;

public class GameState : MonoBehaviour {

	public bool shouldFreezeFracture = false;

	public GameObject cube;
	public GameObject sphere;
	public GameObject[] randomObjects;

	public Transform maxBoundX;
	public Transform maxBoundY;
	public Transform maxBoundZ;

	public Transform minBoundX;
	public Transform minBoundY;
	public Transform minBoundZ;



	//SINGLETON
	private static GameState _instance;
	
	public static GameState Instance{
		get {
			return _instance;
		}
	}
	
	void Awake(){
		if(Instance == null){
			_instance = this;
		}
		else{
			Debug.Log("Instance already exists!");
		}
	}


	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	public void ToggleFreezing(){
		shouldFreezeFracture = !shouldFreezeFracture;
	}

	Vector3 GenerateRandomSpawnPos(){
		float maxX = maxBoundX.transform.position.x;
		float maxY = maxBoundY.transform.position.y;
		float maxZ = maxBoundZ.transform.position.z;

		float minX = minBoundX.transform.position.x;
		float minY = minBoundY.transform.position.y;
		float minZ = minBoundZ.transform.position.z;

		float randomX = Random.Range(minX, maxX);
		float randomY = Random.Range(minY, maxY);
		float randomZ = Random.Range(minZ, maxZ);

		return new Vector3(randomX, randomY, randomZ);
	}

	public void SpawnCube(){
		Vector3 spawnPos = GenerateRandomSpawnPos();
		Instantiate(cube, spawnPos, Quaternion.identity);
	}

	public void SpawnSphere(){
		Vector3 spawnPos = GenerateRandomSpawnPos();
		Instantiate(sphere, spawnPos, Quaternion.identity);
	}

	public void SpawnRandom(){
		int randomIndex = Random.Range(0, randomObjects.Length);

		GameObject randomObject = randomObjects[randomIndex];

		Vector3 spawnPos = GenerateRandomSpawnPos();
		Instantiate(randomObject, spawnPos, Quaternion.identity);
	}

	public void LoadFirstLevel(){
		Application.LoadLevel(0); //hack.
	}

	public void LoadSecondLevel(){
		Application.LoadLevel(1); //hack.
	}

	public void Quit(){
		Application.Quit();
	}
}
