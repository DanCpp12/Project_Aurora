using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEditor;
using UnityEngine;

public class suction : MonoBehaviour
{
	[SerializeField]private float speed = 1f;
	private float step;

	private void OnTriggerStay(Collider other)
	{
		if (other.gameObject.tag == "Suck Boundry")
		{
            step = speed * Time.deltaTime;
            transform.position = Vector3.MoveTowards(transform.position, GameObject.FindGameObjectWithTag("Suck Position").transform.position, step);
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
