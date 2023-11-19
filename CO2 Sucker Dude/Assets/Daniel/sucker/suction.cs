using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEditor;
using UnityEngine;

public class suction : MonoBehaviour
{
	[SerializeField]private float speed = 1f;
	private float step;
	private GameObject suckpointObject;

    private void Start()
    {
		suckpointObject = GameObject.FindGameObjectWithTag("Suck Position");
		if (suckpointObject != null )
		{
			Debug.Log("Rökpuff " + name + " har hittat sugaren.");
		} else
		{
			Debug.LogError("Could not find the smoke sucker. That sucks BWHAHAHAHAHAHA");
		}
    }

    private void OnTriggerStay(Collider other)
	{
		if (other.gameObject.tag == "Suck Boundry")
		{
            step = speed * Time.deltaTime;
            transform.position = Vector3.MoveTowards(transform.position, suckpointObject.transform.position, step);
        }
	}
	private void OnTriggerExit(Collider other)
	{
		if (other.gameObject.tag == "Suck Boundry")
		{
            step = 0;
        }
	}
}
