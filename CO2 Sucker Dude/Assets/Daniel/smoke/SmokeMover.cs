using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SmokeMover : MonoBehaviour
{
    public smokefx sfx;

    public void MoveSmoke(float distance, Transform target)
    {
        transform.position = Vector3.MoveTowards(transform.position, target.position, distance);
    }
}
