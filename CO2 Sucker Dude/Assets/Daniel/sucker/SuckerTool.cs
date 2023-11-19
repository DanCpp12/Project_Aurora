using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SuckerTool : MonoBehaviour
{
    [Header("Sucker settings")]
    [SerializeField] private float speed = 1f;
    [SerializeField] private string suctionTag;
    [SerializeField] private GameObject suckpointObject;
    [SerializeField] private float distanceToDestroySmoke;

    void Start()
    {
        
    }


    void Update()
    {
        
    }
    private void OnTriggerEnter(Collider other)
    {
    }


    private void OnTriggerStay(Collider other)
    {
        // Check if we are inside a trigger. THen act god dammit
        if (other.gameObject.tag == suctionTag)
        {
            // We are inside a suction zone
            SmokeMover smokey = other.GetComponentInParent<SmokeMover>();
            if (smokey != null)
            {
                smokey.MoveSmoke(speed * Time.deltaTime, suckpointObject.transform);
                if (Vector3.Distance(smokey.transform.position, suckpointObject.transform.position) < distanceToDestroySmoke)
                {
                    // The smoke is at position, suck it up.
                    Debug.Log("SCORE, fångat röket och räddat dagen.");
                    Destroy(smokey.gameObject);
                }
            }
        }
    }
}
