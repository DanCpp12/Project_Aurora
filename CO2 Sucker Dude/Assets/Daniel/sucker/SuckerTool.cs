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
    [SerializeField] private score score;

    [Header("Audio")]
    [SerializeField] private AudioSource hooverSound;
    [SerializeField] private float idlePitch;
    [SerializeField] private float suckPitch;

    void Start()
    {
        score.Score = 0;
    }


    void Update()
    {
        
    }
    private void OnTriggerEnter(Collider other)
    {
    }


    private void OnTriggerStay(Collider other)
    {
        float newPitch = idlePitch;
        // Check if we are inside a trigger. THen act god dammit
        if (other.gameObject.tag == suctionTag)
        {
            // We are inside a suction zone
            newPitch = suckPitch;
            SmokeMover smokey = other.GetComponentInParent<SmokeMover>();
            if (smokey != null)
            {
                smokey.MoveSmoke(speed * Time.deltaTime, suckpointObject.transform);
                if (Vector3.Distance(smokey.transform.position, suckpointObject.transform.position) < distanceToDestroySmoke)
                {
                    // The smoke is at position, suck it up.
                    score.Score++;
                    Debug.Log("Aktuell poäng: "+score.Score.ToString());
                    Destroy(smokey.gameObject);
                }
            }
        }
        if (newPitch != hooverSound.pitch)
        {
            hooverSound.pitch = newPitch;
        }
    }
}
